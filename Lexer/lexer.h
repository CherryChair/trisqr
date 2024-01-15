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
#include "../ErrorHandler/ErrorHandler.h"

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
    Position token_position;
    static const std::unordered_map<std::wstring, unsigned short int> keywordMap;
    static const std::unordered_map<wchar_t, unsigned short int> oneCharMap;
    wchar_t character = ' ';
    int max_string_chars = 1024;
    int max_identifier_chars = 64;
    int max_comment_length = 2048;
    int max_analyzed_chars = 8096;
    std::wstring endline_char = L"";
    std::wistream is;
    ErrorHandler * errorHandler;
    bool tryMoveEndline();
    bool moveNewline();
    std::optional<Token> tryBuildIdentifierOrKeyword();
    std::optional<Token> tryBuildNumber();
    std::optional<Token> tryBuildCompOrAssignOrNegate();
    std::optional<Token> tryBuildEOF();
    std::optional<Token> tryBuildString();
    std::optional<Token> tryBuildComment();
    std::optional<Token> tryBuildAndOrOr();
    std::optional<Token> tryBuildOther();
    std::optional<Token> handleIntegerError(int value_before_dot);
    std::optional<Token> handleDoubleError(int value_before_dot, int value_after_dot);
    std::optional<Token> handleIdentiferError(std::wstring & identifier);
    unsigned int nextInCompEq(unsigned int type1, unsigned int type2);
    std::optional<Token> buildToken(unsigned int type);
//    std::optional<Token> buildToken(unsigned int type, Position position, int value);
//    std::optional<Token> buildToken(unsigned int type, Position position, double value);
//    std::optional<Token> buildToken(unsigned int type, Position position, std::wstring value);

    template<typename T>
    std::optional<Token> buildToken(unsigned int type, T value);
    bool moveToNextCharacter();
public:
    Lexer(std::wstreambuf & sr, ErrorHandler * errorHandler): is(& sr), errorHandler(errorHandler){pos.characterNum=0; pos.line=1;};
    Lexer(std::wstreambuf &sr, ErrorHandler * errorHandler, int max_string_chars, int max_identifier_chars,
          int maxCommentLength, int maxAnalyzedChars)
            : is(& sr), errorHandler(errorHandler), max_string_chars(max_string_chars), max_identifier_chars(max_identifier_chars),
              max_comment_length(maxCommentLength), max_analyzed_chars(maxAnalyzedChars) { pos.characterNum=0; pos.line=1;};
    ~Lexer();
    std::optional<Token> nextToken();

};

#endif //LEXER_LEXER_H
