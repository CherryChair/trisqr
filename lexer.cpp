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
            error(ERR_NON_ASCII_CHAR);
        } else {
            bufferLen++;
        }
        return true;
    } else {
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
    error(ERR_UNRECOGNIZED_CHARACTER);
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
            if(this->endline_char[0] != this->character){
                error(ERR_WRONG_ENDLINE_CHAR);
                return true;
            } else if(this->endline_char.length() == 2){
                endline += this->is.peek();
                if(endline != this->endline_char){
                    error(ERR_WRONG_ENDLINE_CHAR);
                    return true;
                }
            }
            moveToNextCharacter();
            return moveNewline();
        }
    }
    return false;
}

bool Lexer::moveNewline()
{
    this->pos.line++;
    this->pos.characterNum=1;
    this->bufferLen = 0;
    return true;
}


std::optional<Token> Lexer::tryBuildIdentifierOrKeyword()
{
    if (isalpha(this->character) || this->character == '_') {
        std::string identifier = "";
        identifier += this->character;
        moveToNextCharacter();
        while((isalnum(this->character) || this->character == '_') && identifier.length()<UCHAR_MAX){
            identifier += this->character;
            moveToNextCharacter();
        }
        if(identifier.length() == UCHAR_MAX) {
            error(ERR_MAX_LEN_EXCEEDED);
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
    if(! isdigit(this->character)) {
        return std::nullopt;
    }
    int before_dot = int(this->character - '0');
    int after_dot = 0;
    moveToNextCharacter();
    while (isdigit(this->character)) {
        if ((INT_MAX - (this->character - '0')) / 10 < before_dot) {
            error(ERR_INT_TOO_BIG);
            return buildToken(ERR_TYPE);
        }
        before_dot = before_dot*10 + int(this->character - '0');
        moveToNextCharacter();
    }
    int dec = 0;
    if (this->character == '.') {
        moveToNextCharacter();
        while (isdigit(this->character)) {
            if ((INT_MAX - (this->character - '0')) / 10 < after_dot) {
                error(ERR_INT_TOO_BIG);
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
            return buildToken(nextInCompEq(GEQ_TYPE, GRATER_TYPE));
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
        while(!is.eof() || str.length()<max_string_chars){
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
        if(is.eof() || str.length()==max_string_chars) {
            error(ERR_NOT_CLOSED_STRING);
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
        ;
        while (moveToNextCharacter() && this->character!='\n' && this->character!='\r' && comment.length()<1000){
            comment += this->character;
            moveToNextCharacter();
        }
        if(comment.length() == 1000) {
            error(ERR_MAX_LEN_EXCEEDED);
            return buildToken(ERR_TYPE);
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

void Lexer::error(int error_type)
{
//    unsigned short tokenPos = bufferLen;
//    std::string code = "";
//    bool too_long = false;
//    if(tokenPos > 100){
//        tokenPos = 100;
//        too_long = true;
//    }
//    char buffer[102] = {};
//    if(error_type == ERR_NOT_CLOSED_STRING) {
//        this->is.clear();
//        this->is.seekg(-1, std::ios_base::cur);
//        tokenPos--;
//    }
//    this->is.seekg(-tokenPos-1, std::ios_base::cur);
//    this->is.readsome(buffer, tokenPos+1);
//    code += buffer;
//    std::cerr << "ERR: " << error_mesages.at(error_type) << '\n';
//    int char_pos = too_long ? pos.characterNum+bufferLen : pos.characterNum;
//    if(error_type == ERR_WRONG_ENDLINE_CHAR) {
//        std::cerr << "Before newline char was: " << this->endline_char_representation << '\n';
//    };
//    std::string escaped_string = "";
//    for(char& c : code) {
//        if(escape_sequences.find(c) != escape_sequences.end()) {
//            escaped_string += escape_sequences.at(c);
//        } else {
//            escaped_string += c;
//        }
//    }
//    std::string line_text_display = (too_long ? "Token too long to display, error at line " : "Line ");
//    std::cerr << line_text_display << pos.line << ", character " << char_pos << ": ";
//    std::cerr << escaped_string << " << error\n";
    moveToNextCharacter();
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