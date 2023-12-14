//
// Created by mpkow on 16.05.2023.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

#include <variant>
#include <string>
#include <iostream>
#include <unordered_map>
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
    RANGE_TYPE,
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
    CRITICAL_ERR_TYPE,
    DOUBLE_KEYWORD_TYPE,
    INT_KEYWORD_TYPE,
    STRING_KEYWORD_TYPE,
    NONE_KEYWORD_TYPE,
    BOOL_KEYWORD_TYPE,
    POINT_KEYWORD_TYPE,
};

static const std::unordered_map<unsigned short int, std::wstring> type_map= {
        {IDENTIFIER_TYPE, L"IDENTIFIER_TYPE"},
        {INTEGER_TYPE, L"INTEGER_TYPE"},
        {DOUBLE_TYPE, L"DOUBLE_TYPE"},
        {STRING_TYPE, L"STRING_TYPE"},
        {WHILE_TYPE, L"WHILE_TYPE"},
        {IF_TYPE, L"IF_TYPE"},
        {ELSIF_TYPE, L"ELSIF_TYPE"},
        {ELSE_TYPE, L"ELSE_TYPE"},
        {FUNC_TYPE, L"FUNC_TYPE"},
        {FIGURE_TYPE, L"FIGURE_TYPE"},
        {RETURN_TYPE, L"RETURN_TYPE"},
        {FOR_TYPE, L"FOR_TYPE"},
        {RANGE_TYPE, L"RANGE_TYPE"},
        {VV_TYPE, L"VV_TYPE"},
        {TRUE_TYPE, L"TRUE_TYPE"},
        {FALSE_TYPE, L"FALSE_TYPE"},
        {IS_TYPE, L"IS_TYPE"},
        {IN_TYPE, L"IN_TYPE"},
        {TO_TYPE, L"TO_TYPE"},
        {DOT_TYPE, L"DOT_TYPE"},
        {NEGATION_TYPE, L"NEGATION_TYPE"},
        {EQ_TYPE, L"EQ_TYPE"},
        {NEQ_TYPE, L"NEQ_TYPE"},
        {LEQ_TYPE, L"LEQ_TYPE"},
        {LESS_TYPE, L"LESS_TYPE"},
        {GEQ_TYPE, L"GEQ_TYPE"},
        {GREATER_TYPE, L"GREATER_TYPE"},
        {AND_TYPE, L"AND_TYPE"},
        {OR_TYPE, L"OR_TYPE"},
        {L_BRACKET_TYPE, L"L_BRACKET_TYPE"},
        {R_BRACKET_TYPE, L"R_BRACKET_TYPE"},
        {L_SQR_BRACKET_TYPE, L"L_SQR_BRACKET_TYPE"},
        {R_SQR_BRACKET_TYPE, L"R_SQR_BRACKET_TYPE"},
        {L_CURL_BRACKET_TYPE, L"L_CURL_BRACKET_TYPE"},
        {R_CURL_BRACKET_TYPE, L"R_CURL_BRACKET_TYPE"},
        {MINUS_TYPE, L"MINUS_TYPE"},
        {PLUS_TYPE, L"PLUS_TYPE"},
        {MULTIPLY_TYPE, L"MULTIPLY_TYPE"},
        {DIVIDE_TYPE, L"DIVIDE_TYPE"},
        {ASSIGN_TYPE, L"ASSIGN_TYPE"},
        {COMMA_TYPE,          L"COMMA_TYPE"},
        {SEMICOLON_TYPE,      L"SEMICOLON_TYPE"},
        {COLON_TYPE,          L"COLON_TYPE"},
        {COMMENT_TYPE,        L"COMMENT_TYPE"},
        {EOF_TYPE,            L"EOF_TYPE"},
        {ERR_TYPE,            L"ERR_TYPE"},
        {CRITICAL_ERR_TYPE,   L"CRITICAL_ERR_TYPE"},
        {DOUBLE_KEYWORD_TYPE, L"DOUBLE_KEYWORD_TYPE"},
        {INT_KEYWORD_TYPE,    L"INT_KEYWORD_TYPE"},
        {STRING_KEYWORD_TYPE, L"STRING_KEYWORD_TYPE"},
        {NONE_KEYWORD_TYPE,   L"NONE_KEYWORD_TYPE"},
        {BOOL_KEYWORD_TYPE,   L"BOOL_KEYWORD_TYPE"},
        {POINT_KEYWORD_TYPE,  L"POINT_KEYWORD_TYPE"},
};

struct Token
{
private:
    unsigned short int token_type;
    std::variant<int, double, std::wstring> value;
    Position pos;
public:
    Token();
    Token(Position pos, unsigned short int token_type);
    Token(Position pos, int value, unsigned short int token_type);
    Token(Position pos, double value, unsigned short int token_type);
    Token(Position pos, std::wstring value, unsigned short int token_type);

    unsigned short getTokenType() const;

    void setTokenType(unsigned short tokenType);

    const std::variant<int, double, std::wstring> &getValue() const;

    void setValue(const std::variant<int, double, std::wstring> &value);

    const Position &getPos() const;

    void setPos(const Position &pos);

};

void printToken(Token token);

#endif //LEXER_TOKEN_H
