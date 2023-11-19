//
// Created by mpkow on 16.05.2023.
//

#include "Token.h"



Token::Token(){};
Token::Token(Position pos, unsigned short int token_type) : pos(pos), token_type(token_type){};
Token::Token(Position pos, int value, unsigned short int token_type) : pos(pos), value(value), token_type(token_type){};
Token::Token(Position pos, double value, unsigned short int token_type)  : pos(pos), value(value), token_type(token_type){};
Token::Token(Position pos, std::string value, unsigned short int token_type)  : pos(pos), value(value), token_type(token_type){}

unsigned short Token::getTokenType() const {
    return token_type;
}

void Token::setTokenType(unsigned short tokenType) {
    token_type = tokenType;
}

const std::variant<int, double, std::string> &Token::getValue() const {
    return value;
}

void Token::setValue(const std::variant<int, double, std::string> &value) {
    Token::value = value;
}

const Position &Token::getPos() const {
    return pos;
}

void Token::setPos(const Position &pos) {
    Token::pos = pos;
}
