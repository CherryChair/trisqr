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

//Error constants
#define ERR_MAX_LEN_EXCEEDED -1
#define ERR_NOT_CLOSED_STRING -2
#define ERR_WRONG_ENDLINE_CHAR -3
#define ERR_WRONG_LOGICAL_OPERATOR -4
#define ERR_INT_TOO_BIG -5
#define ERR_UNRECOGNIZED_CHARACTER -6
#define ERR_NON_ASCII_CHAR -7

//Type constants
#define IDENTIFIER_TYPE 0

#define INTEGER_TYPE 1
#define DOUBLE_TYPE 2
#define STRING_TYPE 3

#define WHILE_TYPE 4
#define IF_TYPE 5
#define ELSIF_TYPE 6
#define ELSE_TYPE 7
#define FUNC_TYPE 8
#define RETURN_TYPE 9
#define FORA_TYPE 10
#define FORI_TYPE 11
#define VV_TYPE 12
#define TRUE_TYPE 13
#define FALSE_TYPE 14
#define IS_TYPE 15
#define IN_TYPE 16
#define TO_TYPE 17

#define DOT_TYPE 18
#define NEGATION_TYPE 19

#define EQ_TYPE 20
#define NEQ_TYPE 21
#define LEQ_TYPE 22
#define LESS_TYPE 23
#define GEQ_TYPE 24
#define GRATER_TYPE 25

#define AND_TYPE 26
#define OR_TYPE 27

#define L_BRACKET_TYPE 28
#define R_BRACKET_TYPE 29
#define L_SQR_BRACKET_TYPE 31
#define R_SQR_BRACKET_TYPE 32
#define L_CURL_BRACKET_TYPE 33
#define R_CURL_BRACKET_TYPE 34

#define MINUS_TYPE 35
#define PLUS_TYPE 36

#define MULTIPLY_TYPE 37
#define DIVIDE_TYPE 38

#define ASSIGN_TYPE 39

#define COMMA_TYPE 40
#define SEMICOLON_TYPE 41
#define COMMENT_TYPE 42
#define NEWLINE_TYPE 43
#define EOF_TYPE 44

#define ERR_TYPE 45

#define DOUBLE_KEYWORD_TYPE 46
#define INT_KEYWORD_TYPE 47
#define STRING_KEYWORD_TYPE 48

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
        {RETURN_TYPE, "RETURN_TYPE"},
        {FORA_TYPE, "FORA_TYPE"},
        {FORI_TYPE, "FORI_TYPE"},
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
        {COMMENT_TYPE, "COMMENT_TYPE"},
        {NEWLINE_TYPE, "NEWLINE_TYPE"},
        {EOF_TYPE, "EOF_TYPE"},
        {ERR_TYPE, "ERR_TYPE"},
        {DOUBLE_KEYWORD_TYPE, "DOUBLE_KEYWORD_TYPE"},
        {INT_KEYWORD_TYPE, "INT_KEYWORD_TYPE"},
        {STRING_KEYWORD_TYPE, "STRING_KEYWORD_TYPE"},
};

struct Position
{
    unsigned int line;
    unsigned int characterNum;
};

struct Token
{
    unsigned short int token_type;
    std::variant<int, double, std::string> value;
    Position pos;

    Token();
    Token(Position pos, unsigned short int token_type);
    Token(Position pos, int value, unsigned short int token_type);
    Token(Position pos, double value, unsigned short int token_type);
    Token(Position pos, std::string value, unsigned short int token_type);
};

class Lexer
{
private:
    Position pos;
    static const std::unordered_map<std::string, unsigned short int> keywordMap;
    char character;
    unsigned short int bufferLen = 0;
    Token token;
    std::string endline_char = "";
    std::string endline_char_representation = "";
    std::istream is;
    Token* tryBuildIdentifierOrKeyword();
    Token* tryBuildNumber();
    Token* tryBuildCompOrAssign();
    Token* tryBuildEndlineChar();
    Token* tryBuildEOF();
    Token* tryBuildString();
    Token* tryBuildEndOfExpression();
    Token* tryBuildNegationOrNeq();
    Token* tryBuildComment();
    Token* tryBuildAndOrOr();
    Token* tryBuildMultiplicationOrAddition();
    Token* tryBuildOther();
    unsigned int nextInCompEq(unsigned int type1, unsigned int type2);
    Token* buildToken(unsigned int type);
    Token* buildToken(unsigned int type, int value);
    Token* buildToken(unsigned int type, double value);
    Token* buildToken(unsigned int type, std::string value);
    Token* buildNewlineToken();
    void moveToNextCharacter();
    void error(int error_type);
public:
    Lexer(std::streambuf & sr): is(& sr){pos.characterNum=0; pos.line=1; moveToNextCharacter();};
    ~Lexer();
    Token* nextToken();
};

void printToken(Token * token);

#endif //LEXER_LEXER_H
