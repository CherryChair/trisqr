//
// Created by mpkow on 24.04.2023.
//

#ifndef LEXER_LEXER_H
#define LEXER_LEXER_H

#include <istream>
#include <string>
#include <variant>
#include <streambuf>
#include <sstream>
#include <iostream>
#include <limits>
#include <climits>
#include <unordered_map>
#include <optional>
#include "Token.h"

//Error constants
#define ERR_MAX_LEN_EXCEEDED -1
#define ERR_NOT_CLOSED_STRING -2
#define ERR_WRONG_ENDLINE_CHAR -3
#define ERR_WRONG_LOGICAL_OPERATOR -4
#define ERR_INT_TOO_BIG -5
#define ERR_UNRECOGNIZED_CHARACTER -6
#define ERR_NON_ASCII_CHAR -7

//Type constants



static const std::unordered_map<short int, std::string> error_mesages= {
        {ERR_MAX_LEN_EXCEEDED, "Maximal length of token exceeded."},
        {ERR_NOT_CLOSED_STRING, "String is not closed."},
        {ERR_WRONG_ENDLINE_CHAR, "Inconsistent newline characters."},
        {ERR_WRONG_LOGICAL_OPERATOR, "Wrong logical operator."},
        {ERR_INT_TOO_BIG, "Number is too big."},
        {ERR_UNRECOGNIZED_CHARACTER, "Character not recognized."},
        {ERR_NON_ASCII_CHAR, "Non ascii char in source."},
};

static const std::unordered_map<char, char> escape_characters= {
        {'"','\"'},
        {'\'','\''},
        {'?','\?'},
        {'a', '\a'},
        {'\\', '\\'},
        {'b', '\b'},
        {'f', '\f'},
        {'n', '\n'},
        {'r', '\r'},
        {'t', '\t'},
        {'v', '\v'},
};

static const std::unordered_map<char, std::string> escape_sequences= {
        {'\?', "\\?"},
        { '\a', "\\a",},
        { '\b', "\\b",},
        { '\f', "\\f",},
        { '\n', "\\n",},
        { '\r', "\\r",},
        { '\t', "\\t",},
        { '\v', "\\v",},
};

static const std::unordered_map<unsigned short int, std::string> type_map= {
        {ERR_MAX_LEN_EXCEEDED, "ERR_MAX_LEN_EXCEEDED"},
        {ERR_NOT_CLOSED_STRING, "ERR_NOT_CLOSED_STRING"},
        {ERR_WRONG_ENDLINE_CHAR, "ERR_WRONG_ENDLINE_CHAR"},
        {ERR_WRONG_LOGICAL_OPERATOR, "ERR_WRONG_LOGICAL_OPERATOR"},
        {ERR_INT_TOO_BIG, "ERR_INT_TOO_BIG"},
        {ERR_UNRECOGNIZED_CHARACTER, "ERR_UNRECOGNIZED_CHARACTER"},
        {ERR_NON_ASCII_CHAR, "ERR_NON_ASCII_CHAR"},
        {IDENTIFIER_TYPE, "IDENTIFIER_TYPE"},
        {INTEGER_TYPE, "INTEGER_TYPE"},
        {DOUBLE_TYPE, "DOUBLE_TYPE"},
        {STRING_TYPE, "STRING_TYPE"},
        {WHILE_TYPE, "WHILE_TYPE"},
        {IF_TYPE, "IF_TYPE"},
        {ELSIF_TYPE, "ELSIF_TYPE"},
        {ELSE_TYPE, "ELSE_TYPE"},
        {FUNC_TYPE, "FUNC_TYPE"},
        {FIGURE_TYPE, "FIGURE_TYPE"},
        {RETURN_TYPE, "RETURN_TYPE"},
        {FOR_TYPE, "FORA_TYPE"},
        {VV_TYPE, "VV_TYPE"},
        {TRUE_TYPE, "TRUE_TYPE"},
        {FALSE_TYPE, "FALSE_TYPE"},
        {IS_TYPE, "IS_TYPE"},
        {IN_TYPE, "IN_TYPE"},
        {TO_TYPE, "TO_TYPE"},
        {DOT_TYPE, "DOT_TYPE"},
        {NEGATION_TYPE, "NEGATION_TYPE"},
        {EQ_TYPE, "EQ_TYPE"},
        {NEQ_TYPE, "NEQ_TYPE"},
        {LEQ_TYPE, "LEQ_TYPE"},
        {LESS_TYPE, "LESS_TYPE"},
        {GEQ_TYPE, "GEQ_TYPE"},
        {GRATER_TYPE, "GRATER_TYPE"},
        {AND_TYPE, "AND_TYPE"},
        {OR_TYPE, "OR_TYPE"},
        {L_BRACKET_TYPE, "L_BRACKET_TYPE"},
        {R_BRACKET_TYPE, "R_BRACKET_TYPE"},
        {L_SQR_BRACKET_TYPE, "L_SQR_BRACKET_TYPE"},
        {R_SQR_BRACKET_TYPE, "R_SQR_BRACKET_TYPE"},
        {L_CURL_BRACKET_TYPE, "L_CURL_BRACKET_TYPE"},
        {R_CURL_BRACKET_TYPE, "R_CURL_BRACKET_TYPE"},
        {MINUS_TYPE, "MINUS_TYPE"},
        {PLUS_TYPE, "PLUS_TYPE"},
        {MULTIPLY_TYPE, "MULTIPLY_TYPE"},
        {DIVIDE_TYPE, "DIVIDE_TYPE"},
        {ASSIGN_TYPE, "ASSIGN_TYPE"},
        {COMMA_TYPE, "COMMA_TYPE"},
        {SEMICOLON_TYPE, "SEMICOLON_TYPE"},
        {COLON_TYPE, "COLON_TYPE"},
        {COMMENT_TYPE, "COMMENT_TYPE"},
        {EOF_TYPE, "EOF_TYPE"},
        {ERR_TYPE, "ERR_TYPE"},
        {DOUBLE_KEYWORD_TYPE, "DOUBLE_KEYWORD_TYPE"},
        {INT_KEYWORD_TYPE, "INT_KEYWORD_TYPE"},
        {STRING_KEYWORD_TYPE, "STRING_KEYWORD_TYPE"},
};





class Lexer
{
private:
    Position pos;
    static const std::unordered_map<std::string, unsigned short int> keywordMap;
    static const std::unordered_map<char, unsigned short int> Lexer::oneCharMap;
    char character;
    unsigned short int bufferLen = 0;
    Token token;
    std::string endline_char = "";
    std::istream is;
    bool Lexer::tryMoveEndline();
    bool moveNewline();
    std::optional<Token> tryBuildIdentifierOrKeyword();
    std::optional<Token> tryBuildNumber();
    std::optional<Token> tryBuildCompOrAssign();
    std::optional<Token> tryBuildEOF();
    std::optional<Token> tryBuildString();
    std::optional<Token> tryBuildNegationOrNeq();
    std::optional<Token> tryBuildComment();
    std::optional<Token> tryBuildAndOrOr();
    std::optional<Token> tryBuildOther();
    unsigned int nextInCompEq(unsigned int type1, unsigned int type2);
    std::optional<Token> buildToken(unsigned int type);
    std::optional<Token> buildToken(unsigned int type, int value);
    std::optional<Token> buildToken(unsigned int type, double value);
    std::optional<Token> buildToken(unsigned int type, std::string value);
    bool moveToNextCharacter();
    void error(int error_type);
public:
    Lexer(std::streambuf & sr): is(& sr){pos.characterNum=0; pos.line=1; moveToNextCharacter();};
    ~Lexer();
    std::optional<Token> nextToken();
};

void printToken(Token token);

#endif //LEXER_LEXER_H
