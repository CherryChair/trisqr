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

static const std::unordered_map<short int, std::wstring> error_mesages= {
    {ERR_MAX_IDENTIFIER_LEN_EXCEEDED,     L"Maximal length of leftExpression exceeded"},
        {ERR_NOT_CLOSED_STRING,           L"String is not closed."},
        {ERR_WRONG_ENDLINE_CHAR,          L"Inconsistent newline characters."},
        {ERR_WRONG_LOGICAL_OPERATOR,      L"Unfinished logical operator."},
        {ERR_INT_TOO_BIG,                 L"Number is too big."},
        {ERR_UNRECOGNIZED_CHARACTER,      L"Character not recognized."},
        {ERR_MAX_ANALYZED_CHARS_EXCEEDED, L"Maximal length of analyzed chars exceeded."},
        {ERR_MAX_STRING_LEN_EXCEEDED,     L"Maximal length of string exceeded."},
        {ERR_MAX_COMMENT_LENGTH_EXCEEDED, L"Maximal length of comment exceeded."},
        {ERR_INVALID_SYNTAX,              L"Invalid syntax."},
        {ERR_SEMANTIC,                    L"Semantic error."},
        {ERR_RUNTIME,                     L"Runtime error."},
        {ERR_INTERPRETER,                 L"Internal interpreter error."},
};

static const std::unordered_map<wchar_t, std::wstring> escape_sequences= {
        {'\?', L"\\?"},
        { '\a', L"\\a",},
        { '\b', L"\\b",},
        { '\f', L"\\f",},
        { '\n', L"\\n",},
        { '\r', L"\\r",},
        { '\t', L"\\t",},
        { '\v', L"\\v",},
};

class ErrorHandler {
private:
    int line_max_char_displayed = 64;
public:
    ErrorHandler() {};
    ErrorHandler(int line_max_char_displayed): line_max_char_displayed(line_max_char_displayed) {};
    void onLexerError(int error_type, Position position, std::wstring value);
    void onSyntaxError(Position position, std::wstring value);
    void onSemanticError(Position position, std::wstring value);
    void onRuntimeError(Position position, std::wstring value);
    void onInterpreterError(Position position, std::wstring value);
    void onInterpreterError(std::wstring value);
    void displayError(std::wstring error_type, int error_subtype, Position position, std::wstring value, bool escape);
};


#endif //LEXER_ERRORHANDLER_H
