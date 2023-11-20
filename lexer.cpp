//
// Created by mpkow on 24.04.2023.
//

#include "lexer.h"

std::unordered_map<std::wstring, unsigned short int> const Lexer::keywordMap = {
        {L"while", WHILE_TYPE},
        {L"if", IF_TYPE},
        {L"elsif", ELSIF_TYPE},
        {L"else", ELSE_TYPE},
        {L"func", FUNC_TYPE},
        {L"figure", FIGURE_TYPE},
        {L"return", RETURN_TYPE},
        {L"for", FOR_TYPE},
        {L"range", RANGE_TYPE},
        {L"vv", VV_TYPE},
        {L"true", TRUE_TYPE},
        {L"false", FALSE_TYPE},
        {L"is", IS_TYPE},
        {L"in", IN_TYPE},
        {L"to", TO_TYPE},
        {L"double", DOUBLE_KEYWORD_TYPE},
        {L"int", INT_KEYWORD_TYPE},
        {L"str", STRING_KEYWORD_TYPE},
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
    if (is >> std::noskipws >> this->character) {
        if(this->character < 0 && this->character!=EOF){
            bufferLen++;
        } else {
            bufferLen++;
        }
        return true;
    } else {
        bufferLen++;
        this->character = EOF;
    }
    return false;
}

std::optional<Token> Lexer::nextToken()
{
    std::optional<Token> token;
    while((this->character == ' ') || tryMoveEndline()){
        moveToNextCharacter();
    }
    pos.characterNum += bufferLen;
    bufferLen = 0;
    if (token = tryBuildEOF())
        return token;
    if (token = tryBuildIdentifierOrKeyword())
        return token;
    if (token = tryBuildNumber())
        return token;
    if (token = tryBuildCompOrAssign())
        return token;
    if (token = tryBuildAndOrOr())
        return token;
    if (token = tryBuildOther())
        return token;
    if (token = tryBuildString())
        return token;
    if (token = tryBuildNegationOrNeq())
        return token;
    if (token = tryBuildComment())
        return token;
    errorHandler.onLexerError(ERR_UNRECOGNIZED_CHARACTER, this->pos, {this->character});
    moveToNextCharacter();
    return buildToken(ERR_TYPE);
}

std::optional<Token> Lexer::buildToken(unsigned int type)
{
    Token token = Token(this->pos, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

std::optional<Token> Lexer::buildToken(unsigned int type, int value)
{
    Token token = Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

std::optional<Token> Lexer::buildToken(unsigned int type, double value)
{
    Token token = Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

std::optional<Token> Lexer::buildToken(unsigned int type, std::wstring value)
{
    Token token = Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
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
                moveToNextCharacter();
            } else {
                this->endline_char += this->character;
            }
            return moveNewline();
        } else {
            pos.characterNum += bufferLen;
            bufferLen = 0;
            if(this->endline_char.length() == 1 && this->endline_char[0] != this->character){
                if((this->is.peek() == '\n' || this->is.peek() == '\r') && this->is.peek()!=endline[0]){
                    moveToNextCharacter();
                    endline += this->character;
                }
                errorHandler.onLexerError(ERR_WRONG_ENDLINE_CHAR, this->pos, endline);
                return true;
            } else if(this->endline_char.length() == 2){
                char next_char = this->is.peek();
                if((next_char == '\n' || next_char == '\r') && next_char!=endline[0]){
                    moveToNextCharacter();
                    endline += this->character;
                    if(endline != this->endline_char){
                        errorHandler.onLexerError(ERR_WRONG_ENDLINE_CHAR, this->pos, endline);
                        return true;
                    }
                } else {
                    errorHandler.onLexerError(ERR_WRONG_ENDLINE_CHAR, this->pos, endline);
                    return true;
                }
            }
            return moveNewline();
        }
    }
    return false;
}

bool Lexer::moveNewline()
{
    this->pos.line++;
    this->pos.characterNum=0;
    this->bufferLen = 0;
    return true;
}


std::optional<Token> Lexer::tryBuildIdentifierOrKeyword()
{
    if (isalpha( this->character) || this->character == '_') {
        std::wstring identifier = L"";
        identifier += this->character;
        moveToNextCharacter();
        while((isalnum(this->character) || this->character == '_')){
            identifier += this->character; //po max druga petla bez zapisu, tez nie nieskonczona, przerwana analiza,
            moveToNextCharacter();
        }
        if(identifier.length() > this->max_identifier_chars) {
            errorHandler.onLexerError(ERR_MAX_IDENTIFIER_LEN_EXCEEDED, this->pos, identifier);
            moveToNextCharacter();
            return buildToken(ERR_TYPE);//error krytyczny
        }
        if (this->keywordMap.find(identifier) != this->keywordMap.end()){
            return buildToken(this->keywordMap.at(identifier));//uzyc iteratora z find
        }
        return buildToken(IDENTIFIER_TYPE, identifier);//szablon
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildNumber()
{
    if(! isdigit( this->character)) {
        return std::nullopt;
    }//isdigit dla wide_char wchar spojrzec, wstring
    int value_before_dot = int(this->character - '0');
    moveToNextCharacter();
    if(value_before_dot > 0) {
        while (isdigit( this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < value_before_dot) {
                //do osobnej funkcji obsaluga bledow, tez przerwanie i niezapisywanie
                std::wstring analyzed_string = std::to_wstring(value_before_dot) + std::wstring{this->character};
                bool dot_found = false;
                while (moveToNextCharacter()) {
                    if (this->character == '.') {
                        if (dot_found) {
                            break;
                        } else {
                            dot_found = true;
                        }
                    } else if (!isdigit( this->character)) {
                        break;
                    }
                    analyzed_string += this->character;
                }
                errorHandler.onLexerError(ERR_INT_TOO_BIG, this->pos, analyzed_string);
                return buildToken(ERR_TYPE);
            }
            value_before_dot = value_before_dot * 10 + int(this->character - '0');
            moveToNextCharacter();
        }
    }
    if (this->character == '.') {
        int dec = 0;
        int value_after_dot = 0;
        moveToNextCharacter();
        while (isdigit( this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < value_after_dot) {
                // tez do innej funkcji obsluge bledow
                std::wstring analyzed_string = std::to_wstring(value_before_dot);
                analyzed_string += '.';
                analyzed_string += std::to_wstring(value_after_dot);
                analyzed_string += this->character;
                moveToNextCharacter();
                while (isdigit( this->character)) {
                    analyzed_string += this->character;
                    moveToNextCharacter();
                }
                errorHandler.onLexerError(ERR_INT_TOO_BIG, this->pos, analyzed_string);
                return buildToken(ERR_TYPE);
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

std::optional<Token> Lexer::tryBuildCompOrAssign()
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
    if(this->character == EOF){
        return buildToken(EOF_TYPE);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildString()
{
    if(this->character == '\''){
        std::wstring str= L"";
        moveToNextCharacter();
        while(!is.eof() && this->character != '\n' && this->character != '\r'){
            if(str.length()>1 && *(str.end()-1) == '\\'){
                *(str.end()-1) = escape_characters.at(this->character);
            }//len 1, if \\ obsluga backslash, do poprawki
            else if(this->character=='\'' ){
                break;
            } else {
                str += this->character;
            }
            moveToNextCharacter();
        }
        if(is.eof() || this->character == '\n' || this->character == '\r') {// if this->char== '
            errorHandler.onLexerError(ERR_NOT_CLOSED_STRING, this->pos, L"'" + str);
            return buildToken(ERR_TYPE);
        } else if (str.length()>max_string_chars) { //podobnie jak w identifier
            moveToNextCharacter();
            errorHandler.onLexerError(ERR_MAX_STRING_LEN_EXCEEDED, this->pos, L"'" + str + L"'");
            return buildToken(ERR_TYPE);
        }
        moveToNextCharacter();
        return buildToken(STRING_TYPE, str);
    }

    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildComment()
{
    if(this->character == '#'){
        std::wstring comment = L"";
        while (moveToNextCharacter() && this->character!='\n' && this->character!='\r'){//jak w identifer
            comment += this->character;
        }
        return buildToken(COMMENT_TYPE, comment);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildNegationOrNeq() {
    if(this->character == '!'){
        moveToNextCharacter();
        if(this->character == '=') {
            return buildToken(NEQ_TYPE);
        } else {
            return buildToken(NEGATION_TYPE);
        }//funkcja z comp użyc i wrzucic do nich
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildOther() {
    if(this->oneCharMap.find(this->character) != this->oneCharMap.end()){//find iterator wykorzystac
        unsigned int token_type = this->oneCharMap.at(this->character);
        moveToNextCharacter();
        return buildToken(token_type);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildAndOrOr() {
    if(this->character == '&') {
        moveToNextCharacter();
        if(this->character == '&'){
            moveToNextCharacter();
            return buildToken(AND_TYPE);
        }
        errorHandler.onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->pos, L"&" + std::wstring{this->character});
        return buildToken(ERR_TYPE);//zwrocic and
    } else if (this->character == '|'){
        moveToNextCharacter();
        if(this->character == '|'){ //  to samo co wyzej
            moveToNextCharacter();
            return buildToken(OR_TYPE);
        }
        errorHandler.onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->pos, L"|" + std::wstring{this->character});
        return buildToken(ERR_TYPE);
    }
    return std::nullopt;
}
