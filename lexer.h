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
#define ERR_TWO_DOTS_IN_NUM -2
#define ERR_NOT_CLOSED_STRING -3
#define ERR_WRONG_ENDLINE_CHAR -4
#define ERR_WRONG_LOGICAL_OPERATOR -5


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

static const std::unordered_map<unsigned short int, std::string> type_map= {
        {0, "IDENTIFIER_TYPE"},
        {1, "INTEGER_TYPE"},
        {2, "DOUBLE_TYPE"},
        {3, "STRING_TYPE"},
        {4, "WHILE_TYPE"},
        {5, "IF_TYPE"},
        {6, "ELSIF_TYPE"},
        {7, "ELSE_TYPE"},
        {8, "FUNC_TYPE"},
        {9, "RETURN_TYPE"},
        {10, "FORA_TYPE"},
        {11, "FORI_TYPE"},
        {12, "VV_TYPE"},
        {13, "TRUE_TYPE"},
        {14, "FALSE_TYPE"},
        {15, "IS_TYPE"},
        {16, "IN_TYPE"},
        {17, "TO_TYPE"},
        {18, "DOT_TYPE"},
        {19, "NEGATION_TYPE"},
        {20, "EQ_TYPE"},
        {21, "NEQ_TYPE"},
        {22, "LEQ_TYPE"},
        {23, "LESS_TYPE"},
        {24, "GEQ_TYPE"},
        {25, "GRATER_TYPE"},
        {26, "AND_TYPE"},
        {27, "OR_TYPE"},
        {28, "L_BRACKET_TYPE"},
        {29, "R_BRACKET_TYPE"},
        {31, "L_SQR_BRACKET_TYPE"},
        {32, "R_SQR_BRACKET_TYPE"},
        {33, "L_CURL_BRACKET_TYPE"},
        {34, "R_CURL_BRACKET_TYPE"},
        {35, "MINUS_TYPE"},
        {36, "PLUS_TYPE"},
        {37, "MULTIPLY_TYPE"},
        {38, "DIVIDE_TYPE"},
        {39, "ASSIGN_TYPE"},
        {40, "COMMA_TYPE"},
        {41, "SEMICOLON_TYPE"},
        {42, "COMMENT_TYPE"},
        {43, "NEWLINE_TYPE"},
        {44, "EOF_TYPE"},
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
    std::streambuf & sr;
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
    bool moveToNextCharacter();
    void error(int error_type);
public:
    Lexer(std::streambuf & sr): sr(sr), is(& sr){pos.characterNum=0; pos.line=1; moveToNextCharacter();};
    ~Lexer();
    Token* nextToken();
};

void printToken(Token * token);

#endif //LEXER_LEXER_H
