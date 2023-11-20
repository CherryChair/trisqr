//
// Created by mpkow on 18.11.2023.
//

#ifndef LEXER_LEXER_ERROR_TYPES_H
#define LEXER_LEXER_ERROR_TYPES_H

enum lexer_error_types {
    ERR_MAX_IDENTIFIER_LEN_EXCEEDED,
    ERR_NOT_CLOSED_STRING,
    ERR_MAX_STRING_LEN_EXCEEDED,
    ERR_WRONG_ENDLINE_CHAR,
    ERR_WRONG_LOGICAL_OPERATOR,
    ERR_INT_TOO_BIG,
    ERR_UNRECOGNIZED_CHARACTER,
    ERR_MAX_ANALYZED_CHARS_EXCEEDED,
    ERR_MAX_COMMENT_LENGTH_EXCEEDED,
};

#endif //LEXER_LEXER_ERROR_TYPES_H
