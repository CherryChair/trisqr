//
// Created by mpkow on 24.04.2023.
//

#include "lexer.h"

std::unordered_map<std::wstring, unsigned short int> const Lexer::keywordMap = {
        {L"while",  WHILE_TYPE},
        {L"if",     IF_TYPE},
        {L"elsif",  ELSIF_TYPE},
        {L"else",   ELSE_TYPE},
        {L"func",   FUNC_TYPE},
        {L"figure", FIGURE_KEYWORD_TYPE},
        {L"return", RETURN_TYPE},
        {L"for",    FOR_TYPE},
        {L"range",  RANGE_TYPE},
        {L"vv",     VV_TYPE},
        {L"true",   TRUE_TYPE},
        {L"false",  FALSE_TYPE},
        {L"is",     IS_TYPE},
        {L"in",     IN_TYPE},
        {L"to",     TO_TYPE},
        {L"double", DOUBLE_KEYWORD_TYPE},
        {L"int",    INT_KEYWORD_TYPE},
        {L"str",    STRING_KEYWORD_TYPE},
        {L"none",   NONE_KEYWORD_TYPE},
        {L"bool",   BOOL_KEYWORD_TYPE},
        {L"point",  POINT_KEYWORD_TYPE},
        {L"list",  LIST_KEYWORD_TYPE},
};

std::unordered_map<wchar_t, unsigned short int> const Lexer::oneCharMap = {
        {'.', DOT_TYPE},
        {'/', DIVIDE_TYPE},
        {'+', PLUS_TYPE},
        {'-', MINUS_TYPE},
        {'*', MULTIPLY_TYPE},
        {'(', L_BRACKET_TYPE},
        {')', R_BRACKET_TYPE},
        {'{', L_CURL_BRACKET_TYPE},
        {'}', R_CURL_BRACKET_TYPE},
        {'[', L_SQR_BRACKET_TYPE},
        {']', R_SQR_BRACKET_TYPE},
        {',', COMMA_TYPE},
        {';', SEMICOLON_TYPE},
        {':', COLON_TYPE},
};

Lexer::~Lexer()
{
}

bool Lexer::moveToNextCharacter()
{
    if (this->character == '\n') {
        this->pos.line++;
        this->pos.characterNum = 0;
    } else if(this->character == WEOF) {
        return false;
    }
    if (this->is >> std::noskipws >> this->character) {
        this->pos.characterNum++;
        tryMoveEndline();
        return true;
    } else {
        this->character = WEOF;
    }
    return false;
}

bool Lexer::tryMoveEndline()
{
    if(this->character == '\n' || this->character == '\r') {
        std::wstring endline = L"";
        endline += this->character;
        if(this->endline_char.empty()){
            endline += this->is.peek();
            if(endline == L"\n\r" || endline == L"\r\n"){
                this->endline_char = endline;
                this->is >> std::noskipws >> this->character;
            } else {
                this->endline_char += this->character;
            }
            return moveNewline();
        } else {
            Position current_pos = this->pos;
            if(this->endline_char.length() == 1 && this->endline_char[0] != this->character){
                if((this->is.peek() == '\n' || this->is.peek() == '\r') && this->is.peek()!=endline[0]){
                    this->is >> std::noskipws >> this->character;
                    endline += this->character;
                }//\n \r\n
                errorHandler->onLexerError(ERR_WRONG_ENDLINE_CHAR, current_pos, endline);
                return moveNewline();
            } else if(this->endline_char.length() == 2){
                char next_char = this->is.peek();
                if((next_char == '\n' || next_char == '\r') && next_char!=endline[0]){
                    this->is >> std::noskipws >> this->character;
                    endline += this->character;
                    if(endline != this->endline_char){
                        errorHandler->onLexerError(ERR_WRONG_ENDLINE_CHAR, current_pos, endline);
                        return moveNewline();
                    }
                } else {
                    errorHandler->onLexerError(ERR_WRONG_ENDLINE_CHAR, current_pos, endline);
                    return moveNewline();
                }
            }
            return moveNewline();
        }
    }
    return false;
}

bool Lexer::moveNewline()
{
    this->character = '\n';
    return true;
}


std::optional<Token> Lexer::nextToken()
{
    std::optional<Token> token;
    while(iswspace(this->character)){
        moveToNextCharacter();
    }
    this->token_position = this->pos;
    if (token = tryBuildEOF())
        return token;
    if (token = tryBuildIdentifierOrKeyword())
        return token;
    if (token = tryBuildNumber())
        return token;
    if (token = tryBuildCompOrAssignOrNegate())
        return token;
    if (token = tryBuildAndOrOr())
        return token;
    if (token = tryBuildOther())
        return token;
    if (token = tryBuildString())
        return token;
    if (token = tryBuildComment())
        return token;
    errorHandler->onLexerError(ERR_UNRECOGNIZED_CHARACTER, this->token_position, {this->character});
    moveToNextCharacter();
    return buildToken(ERR_TYPE);
}

std::optional<Token> Lexer::buildToken(unsigned int type)
{
    Token token = Token(this->token_position, type);
    return token;
}

//std::optional<Token> Lexer::buildToken(unsigned int type, Position position, int value)
//{
//    Token token = Token(position, value, type);
//    return token;
//}
//
//std::optional<Token> Lexer::buildToken(unsigned int type, Position position, double value)
//{
//    Token token = Token(position, value, type);
//    return token;
//}
//
//std::optional<Token> Lexer::buildToken(unsigned int type, Position position, std::wstring value)
//{
//    Token token = Token(position, value, type);
//    return token;
//}//const &&
template <typename T>
std::optional<Token> Lexer::buildToken(unsigned int type, T value)
{
    Token token = Token(this->token_position, value, type);
    return token;
}

std::optional<Token> Lexer::handleIdentiferError(std::wstring & identifier){
    if(identifier.length() >= this->max_identifier_chars) {
        int i = 0;
        while (iswalnum(this->character) || this->character == '_' && i<max_analyzed_chars) {
            moveToNextCharacter();
            i++;
        }
        if (i<this->max_analyzed_chars) {
            errorHandler->onLexerError(ERR_MAX_IDENTIFIER_LEN_EXCEEDED, this->token_position, identifier);
        } else {
            errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, identifier);
            return buildToken(CRITICAL_ERR_TYPE);
        }
    }
}

std::optional<Token> Lexer::tryBuildIdentifierOrKeyword()
{
    if (!iswalpha( this->character) && this->character != '_') {
        return std::nullopt;
    }
    std::wstring identifier = L"";
    identifier += this->character;
    moveToNextCharacter();
    while((iswalnum(this->character) || this->character == '_') && identifier.length() < this->max_identifier_chars){
        if (identifier.length() < this->max_identifier_chars) {
            identifier += this->character;
            moveToNextCharacter();
        } else {
            //obsluga bledu w innej metodzie handleToolongIdentifier()
        }
    }
    if(identifier.length() >= this->max_identifier_chars) {
        int i = 0;
        while (iswalnum(this->character) || this->character == '_' && i<max_analyzed_chars) {
            moveToNextCharacter();
            i++;
        }
        if (i<this->max_analyzed_chars) {
            errorHandler->onLexerError(ERR_MAX_IDENTIFIER_LEN_EXCEEDED, this->token_position, identifier);
        } else {
            errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, identifier);
            return buildToken(CRITICAL_ERR_TYPE);
        }
    }
    std::unordered_map<std::wstring, unsigned short int>::const_iterator iter = this->keywordMap.find(identifier);
    if (iter != this->keywordMap.end()){
        return buildToken(iter->second);
    }
    return buildToken(IDENTIFIER_TYPE, identifier);
}

std::optional<Token> Lexer::handleIntegerError(int value_before_dot) {
    std::wstring analyzed_string = std::to_wstring(value_before_dot) + std::wstring{this->character};
    bool dot_found = false;
    int i = analyzed_string.length();
    while (moveToNextCharacter() && i<this->max_analyzed_chars) {
        if (this->character == '.') {
            if (dot_found) {
                break;
            } else {
                dot_found = true;
            }
        } else if (!isdigit( this->character)) {
            break;
        }
        i++;
    }
    if (i < this->max_analyzed_chars) {
        errorHandler->onLexerError(ERR_INT_TOO_BIG, this->token_position, analyzed_string);
        return buildToken(ERR_TYPE);
    } else {
        errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, analyzed_string);
        return buildToken(CRITICAL_ERR_TYPE);
    }
}

std::optional<Token> Lexer::handleDoubleError(int value_before_dot, int value_after_dot) {
    std::wstring analyzed_string = std::to_wstring(value_before_dot);
    analyzed_string += '.';
    analyzed_string += std::to_wstring(value_after_dot);
    analyzed_string += this->character;
    moveToNextCharacter();
    int i = analyzed_string.length();
    while (iswdigit(this->character) && i<this->max_analyzed_chars) {
        moveToNextCharacter();
        i++;
    }
    if (i < this->max_analyzed_chars) {
        errorHandler->onLexerError(ERR_INT_TOO_BIG, this->token_position, analyzed_string);
        return buildToken(ERR_TYPE);
    } else {
        errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, analyzed_string);
        return buildToken(CRITICAL_ERR_TYPE);
    }
}

std::optional<Token> Lexer::tryBuildNumber()
{
    if(!iswdigit( this->character)) {
        return std::nullopt;
    }
    int value_before_dot = int(this->character - '0');
    moveToNextCharacter();
    if(value_before_dot > 0) {
        while (iswdigit( this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < value_before_dot) {
                return handleIntegerError(value_before_dot);
            }
            value_before_dot = value_before_dot * 10 + int(this->character - '0');
            moveToNextCharacter();
        }
    }
    if (this->character == '.') {
        int dec = 0;
        int value_after_dot = 0;
        moveToNextCharacter();
        while (iswdigit( this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < value_after_dot) {
                return handleDoubleError(value_before_dot, value_after_dot);
            }
            value_after_dot = value_after_dot * 10 + int(this->character - '0');
            dec++;
            moveToNextCharacter();
        }
        int magnitude = 1;
        for (int i=0; i<dec; i++){
            magnitude *= 10;
        }
        double remainder = (double) value_after_dot / (double) magnitude;
        return buildToken(DOUBLE_TYPE, (double) value_before_dot + remainder);
    }
    return buildToken(INTEGER_TYPE, value_before_dot);
}

std::optional<Token> Lexer::tryBuildCompOrAssignOrNegate()
{
    switch (this->character) {
        case '=':
            moveToNextCharacter();
            return buildToken(nextInCompEq(EQ_TYPE, ASSIGN_TYPE));
        case '<':
            moveToNextCharacter();
            return buildToken(nextInCompEq(LEQ_TYPE, LESS_TYPE));
        case '>':
            moveToNextCharacter();
            return buildToken(nextInCompEq(GEQ_TYPE, GREATER_TYPE));
        case '!':
            moveToNextCharacter();
            return buildToken(nextInCompEq(NEQ_TYPE, NEGATION_TYPE));
        default:
            return std::nullopt;
    }
}

unsigned int Lexer::nextInCompEq(unsigned int type1, unsigned int type2){
    if(this->character == '=') {
        moveToNextCharacter();
        return type1;
    } else {
        return type2;
    }
}

std::optional<Token> Lexer::tryBuildEOF()
{
    if(this->character == WEOF){
        return buildToken(EOF_TYPE);
    }
    return std::nullopt;
}



std::optional<Token> Lexer::tryBuildString()
{
    if(this->character == '\''){
        std::wstring str= L"";
        moveToNextCharacter();
        while(!is.eof() && this->character != '\n' && this->character!='\''){//if str.length() < this->max_string_chars
            wchar_t char_to_add = this->character;
            if(this->character == '\\'){
                moveToNextCharacter();
                std::unordered_map<wchar_t, wchar_t>::const_iterator iter = escape_characters.find(this->character);
                if(iter != escape_characters.end()) {
                    char_to_add = iter->second;
                }
            }
            if (str.length() < this->max_string_chars) {
                str += char_to_add;
                moveToNextCharacter();
            } else {
                break;
            }
        }
        if(this->character == '\'') {
            moveToNextCharacter();
            return buildToken(STRING_TYPE, str);
        } else if (str.length()>=this->max_string_chars) {
            int i=str.length();
            while(!is.eof() && this->character != '\n' && this->character!='\'' && i < this->max_analyzed_chars) {
                moveToNextCharacter();
                i++;
            }
            if (i >= this->max_analyzed_chars) {
                errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, L"'" + str);
                return buildToken(CRITICAL_ERR_TYPE);
            }
            moveToNextCharacter();
            errorHandler->onLexerError(ERR_MAX_STRING_LEN_EXCEEDED, this->token_position, L"'" + str);
        } else {
            errorHandler->onLexerError(ERR_NOT_CLOSED_STRING, this->token_position, L"'" + str);
        }
        return buildToken(STRING_TYPE, str);
    }

    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildComment()
{
    if(this->character == '#'){
        std::wstring comment = L"";
        while (!is.eof() && this->character!='\n' && comment.length() < this->max_comment_length){
            moveToNextCharacter();
            comment += this->character;
        } //handlery ze wstrzyknietym warunkiem i komunikatem
        if (comment.length() >= this->max_comment_length) {
            int i = comment.length();
            while (!is.eof() && this->character!='\n' && i < this->max_analyzed_chars) {
                moveToNextCharacter();
                i++;
            }
            if (i >= this->max_analyzed_chars) {
                errorHandler->onLexerError(ERR_MAX_ANALYZED_CHARS_EXCEEDED, this->token_position, L"#" + comment);
                return buildToken(CRITICAL_ERR_TYPE);
            }
            errorHandler->onLexerError(ERR_MAX_COMMENT_LENGTH_EXCEEDED, this->token_position, L"#" + comment);
        }
        return buildToken(COMMENT_TYPE, comment);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildOther() {
    std::unordered_map<wchar_t, unsigned short int>::const_iterator iter = this->oneCharMap.find(this->character);
    if(iter != this->oneCharMap.end()){
        moveToNextCharacter();
        return buildToken(iter->second);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildAndOrOr() {
    if(this->character == '&') {
        moveToNextCharacter();
        if(this->character == '&'){
            moveToNextCharacter();
        } else {
            errorHandler->onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->token_position, L"&" + std::wstring{this->character});
        }
        return buildToken(AND_TYPE);
    } else if (this->character == '|'){
        moveToNextCharacter();
        if (this->character == '|'){
            moveToNextCharacter();
        } else {
            errorHandler->onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->token_position, L"|" + std::wstring{this->character});
        }
        return buildToken(OR_TYPE);
    }
    return std::nullopt;
}
