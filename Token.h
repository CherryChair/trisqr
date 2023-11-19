//
// Created by mpkow on 16.05.2023.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <variant>
#include <string>
#include "Position.h"

enum token_type {
    IDENTIFIER_TYPE,
    INTEGER_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    WHILE_TYPE,
    IF_TYPE,
    ELSIF_TYPE,
    ELSE_TYPE,
    FUNC_TYPE,
    FIGURE_TYPE,
    RETURN_TYPE,
    FOR_TYPE,
    VV_TYPE,
    TRUE_TYPE,
    FALSE_TYPE,
    IS_TYPE,
    IN_TYPE,
    TO_TYPE,
    DOT_TYPE,
    NEGATION_TYPE,
    EQ_TYPE,
    NEQ_TYPE,
    LEQ_TYPE,
    LESS_TYPE,
    GEQ_TYPE,
    GREATER_TYPE,
    AND_TYPE,
    OR_TYPE,
    L_BRACKET_TYPE,
    R_BRACKET_TYPE,
    L_SQR_BRACKET_TYPE,
    R_SQR_BRACKET_TYPE,
    L_CURL_BRACKET_TYPE,
    R_CURL_BRACKET_TYPE,
    MINUS_TYPE,
    PLUS_TYPE,
    MULTIPLY_TYPE,
    DIVIDE_TYPE,
    ASSIGN_TYPE,
    COMMA_TYPE,
    SEMICOLON_TYPE,
    COLON_TYPE,
    COMMENT_TYPE,
    EOF_TYPE,
    ERR_TYPE,
    DOUBLE_KEYWORD_TYPE,
    INT_KEYWORD_TYPE,
    STRING_KEYWORD_TYPE,
};

struct Token
{
private:
    unsigned short int token_type;
    std::variant<int, double, std::string> value;
    Position pos;
public:
    Token();
    Token(Position pos, unsigned short int token_type);
    Token(Position pos, int value, unsigned short int token_type);
    Token(Position pos, double value, unsigned short int token_type);
    Token(Position pos, std::string value, unsigned short int token_type);

    unsigned short getTokenType() const;

    void setTokenType(unsigned short tokenType);

    const std::variant<int, double, std::string> &getValue() const;

    void setValue(const std::variant<int, double, std::string> &value);

    const Position &getPos() const;

    void setPos(const Position &pos);
};



#endif //LEXER_TOKEN_H
