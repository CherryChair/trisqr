//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../lexer.h"


TEST(BasicTests, IfTest) {
    std::string a = "if";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, IF_TYPE);
}

TEST(BasicTests, WhileTest) {
    std::string a = "while";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, WHILE_TYPE);
}

TEST(BasicTests, ElsifTest) {
    std::string a = "elsif";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, ELSIF_TYPE);
}

TEST(BasicTests, ElseTest) {
    std::string a = "else";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, ELSE_TYPE);
}

TEST(BasicTests, funcTest) {
    std::string a = "func";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, FUNC_TYPE);
}

TEST(BasicTests, returnTest) {
    std::string a = "return";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, RETURN_TYPE);
}

TEST(BasicTests, foraTest) {
    std::string a = "fora";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, FORA_TYPE);
}

TEST(BasicTests, foriTest) {
    std::string a = "fori";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, FORI_TYPE);
}

TEST(BasicTests, vvTest) {
    std::string a = "vv";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, VV_TYPE);
}

TEST(BasicTests, trueTest) {
    std::string a = "true";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, TRUE_TYPE);
}

TEST(BasicTests, falseTest) {
    std::string a = "false";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, FALSE_TYPE);
}

TEST(BasicTests, isTest) {
    std::string a = "is";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, IS_TYPE);
}

TEST(BasicTests, inTest) {
    std::string a = "in";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, IN_TYPE);
}

TEST(BasicTests, toTest) {
    std::string a = "to";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, TO_TYPE);
}

TEST(BasicTests, dotTest) {
    std::string a = ".";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, DOT_TYPE);
}

TEST(BasicTests, negationTest) {
    std::string a = "!";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, NEGATION_TYPE);
}

TEST(BasicTests, eqTest) {
    std::string a = "==";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, EQ_TYPE);
}

TEST(BasicTests, neqTest) {
    std::string a = "!=";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, NEQ_TYPE);
}

TEST(BasicTests, leqTest) {
    std::string a = "<=";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, LEQ_TYPE);
}

TEST(BasicTests, lessTest) {
    std::string a = "<";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, LESS_TYPE);
}

TEST(BasicTests, geqTest) {
    std::string a = ">=";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, GEQ_TYPE);
}

TEST(BasicTests, graterTest) {
    std::string a = ">";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, GRATER_TYPE);
}

TEST(BasicTests, andTest) {
    std::string a = "&&";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, AND_TYPE);
}

TEST(BasicTests, orTest) {
    std::string a = "||";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, OR_TYPE);
}

TEST(BasicTests, lbracketTest) {
    std::string a = "(";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, L_BRACKET_TYPE);
}

TEST(BasicTests, rbracketTest) {
    std::string a = ")";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, R_BRACKET_TYPE);
}

TEST(BasicTests, lsqrbracketTest) {
    std::string a = "[";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, L_SQR_BRACKET_TYPE);
}

TEST(BasicTests, rsqrbracketTest) {
    std::string a = "]";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, R_SQR_BRACKET_TYPE);
}

TEST(BasicTests, lcbracketTest) {
    std::string a = "{";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, L_CURL_BRACKET_TYPE);
}

TEST(BasicTests, rcbracketTest) {
    std::string a = "}";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, R_CURL_BRACKET_TYPE);
}

TEST(BasicTests, minusTest) {
    std::string a = "-";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, MINUS_TYPE);
}

TEST(BasicTests, plusTest) {
    std::string a = "+";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, PLUS_TYPE);
}

TEST(BasicTests, multTest) {
    std::string a = "*";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, MULTIPLY_TYPE);
}

TEST(BasicTests, divTest) {
    std::string a = "/";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, DIVIDE_TYPE);
}

TEST(BasicTests, assgnTest) {
    std::string a = "=";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, ASSIGN_TYPE);
}

TEST(BasicTests, commaTest) {
    std::string a = ",";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, COMMA_TYPE);
}

TEST(BasicTests, semicolonTest) {
    std::string a = ";";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, SEMICOLON_TYPE);
}

TEST(BasicTests, commentTest) {
    std::string a = "# @*(je8901  <PSA{l-s a)C";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, COMMENT_TYPE);
}

TEST(BasicTests, newline1Test) {
    std::string a = "\n";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    ASSERT_EQ(tkn->token_type, NEWLINE_TYPE);
}

TEST(BasicTests, newline2Test) {
    std::string a = "\r";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    ASSERT_EQ(tkn->token_type, NEWLINE_TYPE);
}

TEST(BasicTests, newline3Test) {
    std::string a = "\r\n";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    ASSERT_EQ(tkn->token_type, NEWLINE_TYPE);
}

TEST(BasicTests, newline4Test) {
    std::string a = "\n\r";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, NEWLINE_TYPE);
}

TEST(BasicTests, EOFTest) {
    std::string a = "";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, EOF_TYPE);
}

TEST(BasicTests, intKwrdTest) {
    std::string a = "int";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, INT_KEYWORD_TYPE);
}

TEST(BasicTests, doubleKwrdTest) {
    std::string a = "double";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, DOUBLE_KEYWORD_TYPE);
}

TEST(BasicTests, stringKwrdTest) {
    std::string a = "str";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->token_type, STRING_KEYWORD_TYPE);
}

TEST(TypeSpecificTests, doubleTest) {
    std::string a = "2.3455";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    EXPECT_EQ(tkn->token_type, DOUBLE_TYPE);
    ASSERT_EQ(std::get<double>(tkn->value), 2.3455);

}

TEST(TypeSpecificTests, intTest) {
    std::string a = "23455";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    EXPECT_EQ(tkn->token_type, INTEGER_TYPE);
    ASSERT_EQ(std::get<int>(tkn->value), 23455);
}

TEST(TypeSpecificTests, stringTest) {
    std::string a = "'dasdqd  while 12.31as zxc'";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    EXPECT_EQ(tkn->token_type, STRING_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->value), "dasdqd  while 12.31as zxc");
}

TEST(TypeSpecificTests, identifierTest) {
    std::string a = "variable";
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn = lexer->nextToken();
    EXPECT_EQ(tkn->token_type, IDENTIFIER_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->value), "variable");
}

TEST(CombinationsTests, simpleHelloWorldTest) {
    std::string a = "func HelloWorld(){\r\n print('Hello world!');\r\nif(1.23 to int==1){\r\n       fori   in (  0,   11   )    }";
    unsigned short int expected_values[1000] {
        FUNC_TYPE,
        IDENTIFIER_TYPE,
        L_BRACKET_TYPE,
        R_BRACKET_TYPE,
        L_CURL_BRACKET_TYPE,
        NEWLINE_TYPE,
        IDENTIFIER_TYPE,
        L_BRACKET_TYPE,
        STRING_TYPE,
        R_BRACKET_TYPE,
        SEMICOLON_TYPE,
        NEWLINE_TYPE,
        IF_TYPE,
        L_BRACKET_TYPE,
        DOUBLE_TYPE,
        TO_TYPE,
        INT_KEYWORD_TYPE,
        EQ_TYPE,
        INTEGER_TYPE,
        R_BRACKET_TYPE,
        L_CURL_BRACKET_TYPE,
        NEWLINE_TYPE,
        FORI_TYPE,
        IN_TYPE,
        L_BRACKET_TYPE,
        INTEGER_TYPE,
        COMMA_TYPE,
        INTEGER_TYPE,
        R_BRACKET_TYPE,
        R_CURL_BRACKET_TYPE,
        EOF_TYPE
        };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(CombinationsTests, simpleHelloWorldTestWithComments) {
    std::string a = "func #HelloWorld(){\r\n print('Hell#o world#!#');\r\nif(1.23 t#o int==1){\r\n       fori   in (  0,   11   #)    }";
    unsigned short int expected_values[1000] {
            FUNC_TYPE,
            COMMENT_TYPE,
            NEWLINE_TYPE,
            IDENTIFIER_TYPE,
            L_BRACKET_TYPE,
            STRING_TYPE,
            R_BRACKET_TYPE,
            SEMICOLON_TYPE,
            NEWLINE_TYPE,
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            IDENTIFIER_TYPE,
            COMMENT_TYPE,
            NEWLINE_TYPE,
            FORI_TYPE,
            IN_TYPE,
            L_BRACKET_TYPE,
            INTEGER_TYPE,
            COMMA_TYPE,
            INTEGER_TYPE,
            COMMENT_TYPE,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}


TEST(errorTests, errorNewlineTest) {
    std::string a = "1.23 to int; \n\r\n \r vv a;  \r\n";
    unsigned short int expected_values[1000] {
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            SEMICOLON_TYPE,
            NEWLINE_TYPE,
            (unsigned short int) ERR_WRONG_ENDLINE_CHAR,
            (unsigned short int) ERR_WRONG_ENDLINE_CHAR,
            VV_TYPE,
            IDENTIFIER_TYPE,
            SEMICOLON_TYPE,
            (unsigned short int) ERR_WRONG_ENDLINE_CHAR,
            (unsigned short int) ERR_WRONG_ENDLINE_CHAR,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(errorTests, notClosedStringTest) {
    std::string a = "1.2'3 to int; \n\r\n \r vv a;  \r\n";
    unsigned short int expected_values[1000] {
            DOUBLE_TYPE,
            (unsigned short int)ERR_NOT_CLOSED_STRING,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    unsigned short int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(errorTests, notClosedLongStringTest) {
    std::string a = "vv a = 'vv if while fora fori func main []psad[]p#  assa() {}././.;.;[lopk,opp\\'oijiojmddmdkopasdk opaskop aksop";
    unsigned short int expected_values[1000] {
            VV_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            (unsigned short int) ERR_NOT_CLOSED_STRING,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(errorTests, longIntTest) {
    std::string a = "2147483648 3147483647 9999999999 2147483647";
    unsigned short int expected_values[1000] {
            (unsigned short int) ERR_INT_TOO_BIG,
            (unsigned short int) ERR_INT_TOO_BIG,
            (unsigned short int) ERR_INT_TOO_BIG,
            INTEGER_TYPE,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(errorTests, longDoubleTest) {
    std::string a = "2.2147483648 2147483648.2147483648";
    unsigned short int expected_values[1000] {
            (unsigned short int) ERR_INT_TOO_BIG,
            (unsigned short int) ERR_INT_TOO_BIG,
            DOT_TYPE,
            (unsigned short int) ERR_INT_TOO_BIG,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}

TEST(errorTests, wrongLogicalOperatorTest) {
    std::string a = "if (1.33 to int == 1 & true) {\n    a = a+1;\n}";
    unsigned short int expected_values[1000] {
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            EQ_TYPE,
            INTEGER_TYPE,
            (unsigned short int)ERR_WRONG_LOGICAL_OPERATOR,
            TRUE_TYPE,
            R_BRACKET_TYPE,
            L_CURL_BRACKET_TYPE,
            NEWLINE_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            IDENTIFIER_TYPE,
            PLUS_TYPE,
            INTEGER_TYPE,
            SEMICOLON_TYPE,
            NEWLINE_TYPE,
            R_CURL_BRACKET_TYPE,
            EOF_TYPE
    };
    a += EOF;
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    Token * tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->token_type != EOF_TYPE){
        EXPECT_EQ(tkn->token_type, expected_values[i]);
        i++;
    }
}
