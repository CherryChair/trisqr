//
// Created by mpkow on 24.04.2023.
//

#include "lexer.h"

std::unordered_map<std::string, unsigned short int> const Lexer::keywordMap = {
        {"while", WHILE_TYPE},
        {"if", IF_TYPE},
        {"elsif", ELSIF_TYPE},
        {"else", ELSE_TYPE},
        {"func", FUNC_TYPE},
        {"figure", FIGURE_TYPE},
        {"return", RETURN_TYPE},
        {"for", FOR_TYPE},
        {"vv", VV_TYPE},
        {"true", TRUE_TYPE},
        {"false", FALSE_TYPE},
        {"is", IS_TYPE},
        {"in", IN_TYPE},
        {"to", TO_TYPE},
        {"double", DOUBLE_KEYWORD_TYPE},
        {"int", INT_KEYWORD_TYPE},
        {"str", STRING_KEYWORD_TYPE},
};

std::unordered_map<char, unsigned short int> const Lexer::oneCharMap = {
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
    while(this->character == ' ' || tryMoveEndline()){
        moveToNextCharacter();
    }
    pos.characterNum += bufferLen;
    bufferLen = 0;
    if (token = tryBuildEOF())
        return token;
    else if (token = tryBuildIdentifierOrKeyword())
        return token;
    else if (token = tryBuildNumber())
        return token;
    else if (token = tryBuildCompOrAssign())
        return token;
    else if (token = tryBuildAndOrOr())
        return token;
    else if (token = tryBuildOther())
        return token;
    else if (token = tryBuildString())
        return token;
    else if (token = tryBuildNegationOrNeq())
        return token;
    else if (token = tryBuildComment())
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

std::optional<Token> Lexer::buildToken(unsigned int type, std::string value)
{
    Token token = Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

bool Lexer::tryMoveEndline()
{
    if(this->character == '\n' || this->character == '\r') {
        std::string endline = "";
        endline += this->character;
        if(this->endline_char.empty()){
            endline += this->is.peek();
            if(endline == "\n\r" || endline == "\r\n"){
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
    if (isalpha((unsigned char) this->character) || this->character == '_') {
        std::string identifier = "";
        identifier += this->character;
        moveToNextCharacter();
        while((isalnum((unsigned char)this->character) || this->character == '_')){
            identifier += this->character;
            moveToNextCharacter();
        }
        if(identifier.length() > this->max_identifier_chars) {
            errorHandler.onLexerError(ERR_MAX_IDENTIFIER_LEN_EXCEEDED, this->pos, identifier);
            moveToNextCharacter();
            return buildToken(ERR_TYPE);
        }
        if (this->keywordMap.find(identifier) != this->keywordMap.end()){
            return buildToken(this->keywordMap.at(identifier));
        }
        return buildToken(IDENTIFIER_TYPE, identifier);
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildNumber()
{
    if(! isdigit((unsigned char) this->character)) {
        return std::nullopt;
    }
    int before_dot = int(this->character - '0');
    int after_dot = 0;
    moveToNextCharacter();
    while (isdigit((unsigned char) this->character)) {
        if ((INT_MAX - (this->character - '0')) / 10 < before_dot) {
            std::string analyzed_string = std::to_string(before_dot) + std::string{this->character};
            bool dot_found = false;
            while (moveToNextCharacter()) {
                if(this->character == '.') {
                    if (dot_found) {
                        break;
                    } else {
                        dot_found = true;
                    }
                } else if (!isdigit((unsigned char) this->character)) {
                    break;
                }
                analyzed_string += this->character;
            }
            errorHandler.onLexerError(ERR_INT_TOO_BIG, this->pos, analyzed_string);
            return buildToken(ERR_TYPE);
        }
        before_dot = before_dot*10 + int(this->character - '0');
        moveToNextCharacter();
    }
    int dec = 0;
    if (this->character == '.') {
        moveToNextCharacter();
        while (isdigit((unsigned char) this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < after_dot) {
                std::string analyzed_string = std::to_string(before_dot);
                analyzed_string += '.';
                analyzed_string += std::to_string(after_dot);
                analyzed_string += this->character;
                moveToNextCharacter();
                while (isdigit((unsigned char) this->character)) {
                    analyzed_string += this->character;
                    moveToNextCharacter();
                }
                errorHandler.onLexerError(ERR_INT_TOO_BIG, this->pos, analyzed_string);
                return buildToken(ERR_TYPE);
            }
            after_dot = after_dot * 10 + int(this->character - '0');
            dec++;
            moveToNextCharacter();
        }
        int magnitude = 1;
        for (int i=0; i<dec; i++){
            magnitude *= 10;
        }
        double remainder = (double) after_dot / (double) magnitude;
        return buildToken(DOUBLE_TYPE, (double) before_dot + remainder);
    }
    return buildToken(INTEGER_TYPE, before_dot);
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
        std::string str= "";
        moveToNextCharacter();
        while(!is.eof() && this->character != '\n' && this->character != '\r'){
            if(str.length()>1 && *(str.end()-1) == '\\'){
                *(str.end()-1) = escape_characters.at(this->character);
            }
            else if(this->character=='\'' ){
                break;
            } else {
                str += this->character;
            }
            moveToNextCharacter();
        }
        if(is.eof() || this->character == '\n' || this->character == '\r') {
            errorHandler.onLexerError(ERR_NOT_CLOSED_STRING, this->pos, "'" + str);
            return buildToken(ERR_TYPE);
        } else if (str.length()>max_string_chars) {
            moveToNextCharacter();
            errorHandler.onLexerError(ERR_MAX_STRING_LEN_EXCEEDED, this->pos, "'" + str + "'");
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
        std::string comment = "";
        char next_char = this->is.peek();
        while (moveToNextCharacter() && this->character!='\n' && this->character!='\r'){
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
        }
    }
    return std::nullopt;
}

std::optional<Token> Lexer::tryBuildOther() {
    if(this->oneCharMap.find(this->character) != this->oneCharMap.end()){
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
            return buildToken(AND_TYPE);
        }
        errorHandler.onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->pos, "&" + std::string{this->character});
        return buildToken(ERR_TYPE);
    } else if (this->character == '|'){
        moveToNextCharacter();
        if(this->character == '|'){
            return buildToken(OR_TYPE);
        }
        errorHandler.onLexerError(ERR_WRONG_LOGICAL_OPERATOR, this->pos, "|" + std::string{this->character});
        return buildToken(ERR_TYPE);
    }
    return std::nullopt;
}

void printToken(Token tkn) {
    std::cout << "Type: " << tkn.getTokenType() << "- "<< type_map.at(tkn.getTokenType()) << ", ";
    std::cout << "Type: " << tkn.getTokenType() << ", ";
    std::cout << "Value: ";
    if (std::holds_alternative<int>(tkn.getValue())) {
        std::cout << std::get<int>(tkn.getValue());
    } else if (std::holds_alternative<double>(tkn.getValue())) {
        std::cout << std::get<double>(tkn.getValue());
    } else if (std::holds_alternative<std::string>(tkn.getValue())) {
        std::cout << std::get<std::string>(tkn.getValue());
    }
    std::cout << ", ";
    std::cout << "L: " << tkn.getPos().line << ", C: " << tkn.getPos().characterNum << '\n';
}