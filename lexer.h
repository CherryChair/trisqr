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
#include "ErrorHandler.h"

static const std::unordered_map<wchar_t, wchar_t> escape_characters= {
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


class Lexer
{
private:
    Position pos;
    static const std::unordered_map<std::wstring, unsigned short int> keywordMap;
    static const std::unordered_map<wchar_t, unsigned short int> oneCharMap;
    wchar_t character;
    unsigned short int bufferLen = 0;
    int max_string_chars = 2048;
    int max_identifier_chars = 64;
    int max_analyzed_chars = 8096;
    std::wstring endline_char = L"";
    std::wistream is;
    ErrorHandler errorHandler;
    bool Lexer::tryMoveEndline();
    bool moveNewline();
    std::optional<Token> tryBuildIdentifierOrKeyword();
    std::optional<Token> tryBuildNumber();
    std::optional<Token> tryBuildCompOrAssignOrNegate();
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
    std::optional<Token> buildToken(unsigned int type, std::wstring value);
    bool moveToNextCharacter();
public:
    Lexer(std::wstreambuf & sr, ErrorHandler & errorHandler): is(& sr), errorHandler(errorHandler){pos.characterNum=0; pos.line=1; moveToNextCharacter();};
    Lexer(std::wstreambuf & sr, ErrorHandler & errorHandler, int max_string_chars, int max_identifier_chars): is(& sr), errorHandler(errorHandler), max_string_chars(max_string_chars), max_identifier_chars(max_identifier_chars){pos.characterNum=0; pos.line=1; moveToNextCharacter();};
    ~Lexer();
    std::optional<Token> nextToken();

};

#endif //LEXER_LEXER_H
