//
// Created by mpkow on 16.05.2023.
//

#ifndef LEXER_TOKEN_H
#define LEXER_TOKEN_H

enum token_type {
    IDENTIFIER_TYPE,
    INTEGER_TYPE,
    DOUBLE_TYPE,
    STRING_TYPE,
    WHILE_TYPE,
    IF_TYPE,
    ELSIF_TYPE,
    ELSE_TYPE,
    FUNC_TYPE,
    RETURN_TYPE,
    FORA_TYPE,
    FORI_TYPE,
    VV_TYPE,
    TRUE_TYPE,
    FALSE_TYPE,
    IS_TYPE,
    IN_TYPE,
    TO_TYPE,
    DOT_TYPE,
    NEGATION_TYPE,
    EQ_TYPE,
    NEQ_TYPE,
    LEQ_TYPE,
    LESS_TYPE,
    GEQ_TYPE,
    GRATER_TYPE,
    AND_TYPE,
    OR_TYPE,
    L_BRACKET_TYPE,
    R_BRACKET_TYPE,
    L_SQR_BRACKET_TYPE,
    R_SQR_BRACKET_TYPE,
    L_CURL_BRACKET_TYPE,
    R_CURL_BRACKET_TYPE,
    MINUS_TYPE,
    PLUS_TYPE,
    MULTIPLY_TYPE,
    DIVIDE_TYPE,
    ASSIGN_TYPE,
    COMMA_TYPE,
    SEMICOLON_TYPE,
    COMMENT_TYPE,
    EOF_TYPE,
    ERR_TYPE,
    DOUBLE_KEYWORD_TYPE,
    INT_KEYWORD_TYPE,
    STRING_KEYWORD_TYPE,
};

struct Position
{
    unsigned int line;
    unsigned int characterNum;
};

struct Token
{
private:
    unsigned short int token_type;
    std::variant<int, double, std::string> value;
    Position pos;
public:
    Token(){};
    Token(Position pos, unsigned short int token_type) : pos(pos), token_type(token_type){};
    Token(Position pos, int value, unsigned short int token_type) : pos(pos), value(value), token_type(token_type){};
    Token(Position pos, double value, unsigned short int token_type)  : pos(pos), value(value), token_type(token_type){};
    Token(Position pos, std::string value, unsigned short int token_type)  : pos(pos), value(value), token_type(token_type){}

    unsigned short getTokenType() const {
        return token_type;
    }

    void setTokenType(unsigned short tokenType) {
        token_type = tokenType;
    }

    const std::variant<int, double, std::string> &getValue() const {
        return value;
    }

    void setValue(const std::variant<int, double, std::string> &value) {
        Token::value = value;
    }

    const Position &getPos() const {
        return pos;
    }

    void setPos(const Position &pos) {
        Token::pos = pos;
    };
};



#endif //LEXER_TOKEN_H
