//
// Created by mpkow on 15.05.2023.
//

#include <string>

#ifndef LEXER_ERRORHANDLER_H
#define LEXER_ERRORHANDLER_H


class ErrorHandler {
public:
    ErrorHandler() {}

private:
    void onLexerError(int error_type);
    void onLexerError(int error_type, std::string value);
    void onParserError(int error_type);
    void onParserError(int error_type, std::string value);
};


#endif //LEXER_ERRORHANDLER_H
