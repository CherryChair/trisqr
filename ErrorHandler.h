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
        {ERR_MAX_LEN_EXCEEDED, "Maximal length of token exceeded."},
        {ERR_NOT_CLOSED_STRING, "String is not closed."},
        {ERR_WRONG_ENDLINE_CHAR, "Inconsistent newline characters."},
        {ERR_WRONG_LOGICAL_OPERATOR, "Wrong logical operator."},
        {ERR_INT_TOO_BIG, "Number is too big."},
        {ERR_UNRECOGNIZED_CHARACTER, "Character not recognized."},
        {ERR_NON_ASCII_CHAR, "Non ascii char in source."},
};

class ErrorHandler {
public:
    ErrorHandler() {}

private:
    void onLexerError(int error_type);
    void onLexerError(int error_type, Position position);
    void onLexerError(int error_type, Position position, std::string value);
};


#endif //LEXER_ERRORHANDLER_H
