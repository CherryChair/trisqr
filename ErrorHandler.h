//
// Created by mpkow on 15.05.2023.
//

#include <string>
#include <unordered_map>
#include "Position.h"
#include "lexer_error_types.h"

#ifndef LEXER_ERRORHANDLER_H
#define LEXER_ERRORHANDLER_H

//Type constants

static const std::unordered_map<short int, std::string> error_mesages= {
        {ERR_MAX_IDENTIFIER_LEN_EXCEEDED, "Maximal length of identifier exceeded."},
        {ERR_NOT_CLOSED_STRING,           "String is not closed."},
        {ERR_WRONG_ENDLINE_CHAR,          "Inconsistent newline characters."},
        {ERR_WRONG_LOGICAL_OPERATOR,      "Unfinished logical operator."},
        {ERR_INT_TOO_BIG,                 "Number is too big."},
        {ERR_UNRECOGNIZED_CHARACTER,      "Character not recognized."},
        {ERR_MAX_STRING_LEN_EXCEEDED,     "Maximal length of string exceeded."},
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

class ErrorHandler {
private:
    int line_max_char_displayed = 64;
public:
    ErrorHandler() {};
    ErrorHandler(int line_max_char_displayed): line_max_char_displayed(line_max_char_displayed) {};
    void onLexerError(int error_type, Position position, std::string value);
};


#endif //LEXER_ERRORHANDLER_H
