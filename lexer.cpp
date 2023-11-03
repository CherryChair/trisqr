//
// Created by mpkow on 24.04.2023.
//

#include "lexer.h"

Token::Token() {

}

Token::Token(Position pos, unsigned short int token_type) {
    this->pos = pos;
    this->token_type = token_type;
}

Token::Token(Position pos, int value, unsigned short int token_type) {
    this->pos = pos;
    this->value = value;
    this->token_type = token_type;
}

Token::Token(Position pos, double value, unsigned short int token_type) {
    this->pos = pos;
    this->value = value;
    this->token_type = token_type;
}

Token::Token(Position pos, std::string value, unsigned short int token_type) {
    this->pos = pos;
    this->value = value;
    this->token_type = token_type;
}

std::unordered_map<std::string, unsigned short int> const Lexer::keywordMap = {
        {"while", WHILE_TYPE},
        {"if", IF_TYPE},
        {"elsif", ELSIF_TYPE},
        {"else", ELSE_TYPE},
        {"func", FUNC_TYPE},
        {"return", RETURN_TYPE},
        {"fora", FORA_TYPE},
        {"fori", FORI_TYPE},
        {"vv", VV_TYPE},
        {"true", TRUE_TYPE},
        {"false", FALSE_TYPE},
        {"is", IS_TYPE},
        {"in", IN_TYPE},
        {"to", TO_TYPE},
};

Lexer::~Lexer()
{
}

bool Lexer::moveToNextCharacter()
{

    if (is >> std::noskipws >> this->character) {
        if (bufferLen < USHRT_MAX) {
            bufferLen++;
        } else {
            error(ERR_MAX_LEN_EXCEEDED);
            return buildToken(ERR_TYPE);
        }
        return true;
    }
    return false;
}

Token* Lexer::nextToken()
{
    Token * token;
    while(this->character == ' '){
        moveToNextCharacter();
    }
    pos.characterNum += bufferLen;
    bufferLen = 0;
    if (token = tryBuildIdentifierOrKeyword())
        return token;
    else if (token = tryBuildNumber())
        return token;
    else if (token = tryBuildEndOfExpression())
        return token;
    else if (token = tryBuildCompOrAssign())
        return token;
    else if (token = tryBuildMultiplicationOrAddition())
        return token;
    else if (token = tryBuildAndOrOr())
        return token;
    else if (token = tryBuildOther())
        return token;
    else if (token = tryBuildEndlineChar())
        return token;
    else if (token = tryBuildString())
        return token;
    else if (token = tryBuildNegationOrNeq())
        return token;
    else if (token = tryBuildComment())
        return token;
    else if (token = tryBuildEOF())
        return token;
    return nullptr;
}

Token* Lexer::buildToken(unsigned int type)
{
    Token * token = new Token(this->pos, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

Token* Lexer::buildToken(unsigned int type, int value)
{
    Token * token = new Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

Token* Lexer::buildToken(unsigned int type, double value)
{
    Token * token = new Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

Token* Lexer::buildToken(unsigned int type, std::string value)
{
    Token * token = new Token(this->pos, value, type);
    pos.characterNum += bufferLen;
    bufferLen = 0;
    return token;
}

Token* Lexer::tryBuildIdentifierOrKeyword()
{
    if (isalpha(this->character) || this->character == '_') {
        std::string identifier = "";
        identifier += this->character;
        moveToNextCharacter();
        while(isalpha(this->character) || this->character == '_'){
            identifier += this->character;
            moveToNextCharacter();
        }
        if (this->keywordMap.find(identifier) != this->keywordMap.end()){
            return buildToken(this->keywordMap.at(identifier));
        }
        return buildToken(IDENTIFIER_TYPE, identifier);
    }
    return nullptr;
}

Token* Lexer::tryBuildNumber()
{
    if(isdigit(this->character)) {
        int before_dot = this->character-48;
        int after_dot = 0;
        int dec = 0;
        int double_point = 0;
        dec++;
        int *current_part = &before_dot;
        bool is_double = false;
        bool is_number = true;

        moveToNextCharacter();
        while (is_number){
            if(isdigit(this->character)){
                if((INT_MAX-(this->character-48))/10 < *current_part) {
                    error(ERR_INT_TOO_BIG);
                    return buildToken(ERR_TYPE);
                }
                *current_part = *current_part*10 + this->character-48;
                dec++;
                moveToNextCharacter();
            } else if (this->character == '.') {
                if(!is_double) {
                    is_double = true;
                    double_point = dec;
                    current_part = &after_dot;
                    moveToNextCharacter();
                } else {
                    error(ERR_TWO_DOTS_IN_NUM);
                    return buildToken(ERR_TYPE);
                }
            } else{
                is_number = false;
            }
        }
        if (is_double) {

            int len_after_dot = dec - double_point;
            if (len_after_dot > 0) {
                double remainder = (double) after_dot;
                for (int i=0; i<len_after_dot; i++){
                    remainder /= 10.0;
                }
                return buildToken(DOUBLE_TYPE, (double) before_dot + remainder);
            } else {
                return buildToken(DOUBLE_TYPE, (double) before_dot);
            }
        } else {
            return buildToken(INTEGER_TYPE, before_dot);
        }
    } else {
        return nullptr;
    }
}

Token* Lexer::tryBuildCompOrAssign()
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
            return buildToken(nextInCompEq(GEQ_TYPE, GRATER_TYPE));
        default:
            return nullptr;
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


Token* Lexer::tryBuildEndlineChar()
{
    if(this->character == '\n' || this->character == '\r') {
        std::string endline = "";
        endline += this->character;
        if(this->endline_char.empty()){
            if(this->character == '\r'){
                moveToNextCharacter();
                if(this->character == '\n'){
                    this->endline_char = "\r\n";
                    moveToNextCharacter();
                } else {
                    this->endline_char = "\r";
                }
                this->pos.line++;
                this->pos.characterNum=1;
                this->bufferLen = 0;
                return buildToken(NEWLINE_TYPE);
            } else {
                moveToNextCharacter();
                if(this->character == '\r'){
                    this->endline_char = "\n\r";
                    moveToNextCharacter();
                } else {
                    this->endline_char = "\n";
                }
                this->pos.line++;
                this->pos.characterNum=1;
                this->bufferLen = 0;
                return buildToken(NEWLINE_TYPE);
            }
        } else {
            if(endline[0] == this->character && endline != this->endline_char){
                endline += this->is.peek();
                if(endline != this->endline_char){
                    error(ERR_WRONG_ENDLINE_CHAR);
                    return buildToken(ERR_TYPE);
                }
                moveToNextCharacter();
            } else if(endline[0] != this->character){
                error(ERR_WRONG_ENDLINE_CHAR);
            }
            moveToNextCharacter();
            this->pos.line++;
            this->pos.characterNum=1;
            this->bufferLen = 0;
            return buildToken(NEWLINE_TYPE);
            return buildToken(ERR_TYPE);
        }
    }
    return nullptr;
}

Token* Lexer::tryBuildEOF()
{
    if(this->is.eof() || this->character == EOF){
        return buildToken(EOF_TYPE);
    }
    return nullptr;
}

Token* Lexer::tryBuildString()
{
    if(this->character == '\''){
        std::string str= "";
        moveToNextCharacter();
        while(this->character!='\'' && !is.eof()){
            str += this->character;
            moveToNextCharacter();
        }
        if(is.eof()) {
            error(ERR_NOT_CLOSED_STRING);
            return buildToken(ERR_TYPE);
        }
        moveToNextCharacter();
        return buildToken(STRING_TYPE, str);
    }

    return nullptr;
}

Token* Lexer::tryBuildEndOfExpression()
{
    if(this->character == ';'){
        moveToNextCharacter();
        return buildToken(SEMICOLON_TYPE);
    }
    return nullptr;
}

Token* Lexer::tryBuildComment()
{
    if(this->character == '#'){
        std::string comment = "";
        moveToNextCharacter();
        while (this->character!='\n' && this->character!='\r' && this->character!= EOF){
            comment += this->character;
            moveToNextCharacter();
        }
        return buildToken(COMMENT_TYPE, comment);
    }
    return nullptr;
}

Token* Lexer::tryBuildNegationOrNeq() {
    if(this->character == '!'){
        moveToNextCharacter();
        if(this->character == '=') {
            return buildToken(NEQ_TYPE);
        } else {
            return buildToken(NEGATION_TYPE);
        }
    }
    return nullptr;
}

void Lexer::error(int error_type)
{
    unsigned short tokenPos = bufferLen;
    std::string code = "";
    bool too_long = false;
    if(tokenPos > 100){
        tokenPos = 100;
        too_long = true;
    }
    char buffer[101] = {};
    this->is.seekg(bufferLen, std::ios_base::beg);
    this->is.readsome(buffer, bufferLen);
    code += buffer;
    std::cout << "ERR: " << error_mesages.at(error_type) << '\n';
    int line_pos = too_long ? pos.line+bufferLen : pos.line;
    int char_pos = too_long ? pos.characterNum+bufferLen : pos.characterNum;
    std::string line_text_display = (too_long ? "Word too long to display, error at line" : "Line ");
    std::cout << line_text_display << line_pos << ", character " << char_pos << ": " << code << " << error\n";
}

Token *Lexer::tryBuildMultiplicationOrAddition() {
    if(this->character == '+') {
        moveToNextCharacter();
        return buildToken(PLUS_TYPE);
    } else if (this->character == '-'){
        moveToNextCharacter();
        return buildToken(MINUS_TYPE);
    } else if (this->character == '*'){
        moveToNextCharacter();
        return buildToken(MULTIPLY_TYPE);
    } else if (this->character == '/'){
        moveToNextCharacter();
        return buildToken(DIVIDE_TYPE);
    }
    return nullptr;
}

Token *Lexer::tryBuildOther() {
    switch (this->character) {
        case '(':
            moveToNextCharacter();
            return buildToken(L_BRACKET_TYPE);
        case ')':
            moveToNextCharacter();
            return buildToken(R_BRACKET_TYPE);
        case '{':
            moveToNextCharacter();
            return buildToken(L_CURL_BRACKET_TYPE);
        case '}':
            moveToNextCharacter();
            return buildToken(R_CURL_BRACKET_TYPE);
        case '[':
            moveToNextCharacter();
            return buildToken(L_SQR_BRACKET_TYPE);
        case ']':
            moveToNextCharacter();
            return buildToken(R_SQR_BRACKET_TYPE);
        case '.':
            moveToNextCharacter();
            return buildToken(DOT_TYPE);
        case ',':
            moveToNextCharacter();
            return buildToken(COMMA_TYPE);

    }
    return nullptr;
}

Token *Lexer::tryBuildAndOrOr() {
    if(this->character == '&') {
        moveToNextCharacter();
        if(this->character == '&'){
            return buildToken(AND_TYPE);
        }
        error(ERR_WRONG_LOGICAL_OPERATOR);
        return buildToken(ERR_TYPE);
    } else if (this->character == '|'){
        moveToNextCharacter();
        if(this->character == '|'){
            return buildToken(OR_TYPE);
        }
        error(ERR_WRONG_LOGICAL_OPERATOR);
        return buildToken(ERR_TYPE);
    }
    return nullptr;
}

void printToken(Token * tkn) {
    std::cout << "Type: " << tkn->token_type << "- "<< type_map.at(tkn->token_type) << ", ";
    std::cout << "Type: " << tkn->token_type << ", ";
    std::cout << "Value: ";
    if (std::holds_alternative<int>(tkn->value)) {
        std::cout << std::get<int>(tkn->value);
    } else if (std::holds_alternative<double>(tkn->value)) {
        std::cout << std::get<double>(tkn->value);
    } else if (std::holds_alternative<std::string>(tkn->value)) {
        std::cout << std::get<std::string>(tkn->value);
    }
    std::cout << ", ";
    std::cout << "L: " << tkn->pos.line << ", C: " << tkn->pos.characterNum << '\n';

}