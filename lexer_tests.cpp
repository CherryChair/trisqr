//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../lexer.h"


TEST(BasicTests, IfTest) {
    std::string a = "if";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), IF_TYPE);
}

TEST(BasicTests, WhileTest) {
    std::string a = "while";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), WHILE_TYPE);
}

TEST(BasicTests, ElsifTest) {
    std::string a = "elsif";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), ELSIF_TYPE);
}

TEST(BasicTests, ElseTest) {
    std::string a = "else";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), ELSE_TYPE);
}

TEST(BasicTests, funcTest) {
    std::string a = "func";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), FUNC_TYPE);
}

TEST(BasicTests, figureTest) {
    std::string a = "figure";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), FIGURE_TYPE);
}

TEST(BasicTests, returnTest) {
    std::string a = "return";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), RETURN_TYPE);
}

TEST(BasicTests, forTest) {
    std::string a = "for";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), FOR_TYPE);
}

TEST(BasicTests, vvTest) {
    std::string a = "vv";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), VV_TYPE);
}

TEST(BasicTests, trueTest) {
    std::string a = "true";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), TRUE_TYPE);
}

TEST(BasicTests, falseTest) {
    std::string a = "false";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), FALSE_TYPE);
}

TEST(BasicTests, isTest) {
    std::string a = "is";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), IS_TYPE);
}

TEST(BasicTests, inTest) {
    std::string a = "in";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), IN_TYPE);
}

TEST(BasicTests, toTest) {
    std::string a = "to";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), TO_TYPE);
}

TEST(BasicTests, dotTest) {
    std::string a = ".";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), DOT_TYPE);
}

TEST(BasicTests, negationTest) {
    std::string a = "!";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), NEGATION_TYPE);
}

TEST(BasicTests, eqTest) {
    std::string a = "==";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), EQ_TYPE);
}

TEST(BasicTests, neqTest) {
    std::string a = "!=";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), NEQ_TYPE);
}

TEST(BasicTests, leqTest) {
    std::string a = "<=";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), LEQ_TYPE);
}

TEST(BasicTests, lessTest) {
    std::string a = "<";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), LESS_TYPE);
}

TEST(BasicTests, geqTest) {
    std::string a = ">=";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), GEQ_TYPE);
}

TEST(BasicTests, graterTest) {
    std::string a = ">";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), GRATER_TYPE);
}

TEST(BasicTests, andTest) {
    std::string a = "&&";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), AND_TYPE);
}

TEST(BasicTests, orTest) {
    std::string a = "||";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), OR_TYPE);
}

TEST(BasicTests, lbracketTest) {
    std::string a = "(";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), L_BRACKET_TYPE);
}

TEST(BasicTests, rbracketTest) {
    std::string a = ")";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), R_BRACKET_TYPE);
}

TEST(BasicTests, lsqrbracketTest) {
    std::string a = "[";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), L_SQR_BRACKET_TYPE);
}

TEST(BasicTests, rsqrbracketTest) {
    std::string a = "]";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), R_SQR_BRACKET_TYPE);
}

TEST(BasicTests, lcbracketTest) {
    std::string a = "{";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), L_CURL_BRACKET_TYPE);
}

TEST(BasicTests, rcbracketTest) {
    std::string a = "}";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), R_CURL_BRACKET_TYPE);
}

TEST(BasicTests, minusTest) {
    std::string a = "-";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), MINUS_TYPE);
}

TEST(BasicTests, plusTest) {
    std::string a = "+";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), PLUS_TYPE);
}

TEST(BasicTests, multTest) {
    std::string a = "*";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), MULTIPLY_TYPE);
}

TEST(BasicTests, divTest) {
    std::string a = "/";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), DIVIDE_TYPE);
}

TEST(BasicTests, assgnTest) {
    std::string a = "=";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), ASSIGN_TYPE);
}

TEST(BasicTests, commaTest) {
    std::string a = ",";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), COMMA_TYPE);
}

TEST(BasicTests, semicolonTest) {
    std::string a = ";";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), SEMICOLON_TYPE);
}

TEST(BasicTests, colonTest) {
    std::string a = ":";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), COLON_TYPE);
}

TEST(BasicTests, commentTest) {
    std::string a = "# @*(je8901  <PSA{l-s a)C";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), COMMENT_TYPE);
}

TEST(BasicTests, EOFTest) {
    std::string a = "";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), EOF_TYPE);
}

TEST(BasicTests, intKwrdTest) {
    std::string a = "int";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), INT_KEYWORD_TYPE);
}

TEST(BasicTests, doubleKwrdTest) {
    std::string a = "double";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), DOUBLE_KEYWORD_TYPE);
}

TEST(BasicTests, stringKwrdTest) {
    std::string a = "str";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), STRING_KEYWORD_TYPE);
}

TEST(TypeSpecificTests, doubleTest) {
    std::string a = "2.3455";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), DOUBLE_TYPE);
    ASSERT_EQ(std::get<double>(tkn->getValue()), 2.3455);

}

TEST(TypeSpecificTests, intTest) {
    std::string a = "23455";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), INTEGER_TYPE);
    ASSERT_EQ(std::get<int>(tkn->getValue()), 23455);
}

TEST(TypeSpecificTests, stringTest) {
    std::string a = "'dasdqd  while 12.31as zxc'";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), STRING_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->getValue()), "dasdqd  while 12.31as zxc");
}

TEST(TypeSpecificTests, identifierTest) {
    std::string a = "variable";
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), IDENTIFIER_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->getValue()), "variable");
}

TEST(CombinationsTests, simpleHelloWorldTest) {
    std::string a = "func HelloWorld(){\r\n print('Hello world!');\r\nif(1.23 to int==1){\r\n       for   in (  0,   11   )    }";
    unsigned short int expected_values[1000] {
            FUNC_TYPE,
            IDENTIFIER_TYPE,
            L_BRACKET_TYPE,
            R_BRACKET_TYPE,
            L_CURL_BRACKET_TYPE,
            IDENTIFIER_TYPE,
            L_BRACKET_TYPE,
            STRING_TYPE,
            R_BRACKET_TYPE,
            SEMICOLON_TYPE,
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            EQ_TYPE,
            INTEGER_TYPE,
            R_BRACKET_TYPE,
            L_CURL_BRACKET_TYPE,
            FOR_TYPE,
            IN_TYPE,
            L_BRACKET_TYPE,
            INTEGER_TYPE,
            COMMA_TYPE,
            INTEGER_TYPE,
            R_BRACKET_TYPE,
            R_CURL_BRACKET_TYPE,
            EOF_TYPE
    };
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
}

TEST(CombinationsTests, simpleHelloWorldTestWithComments) {
    std::string a = "func #HelloWorld(){\r\n print('Hell#o world#!#');\r\nif(1.23 t#o int==1){\r\n       for   in (  0,   11   #)    }";
    unsigned short int expected_values[1000] {
            FUNC_TYPE,
            COMMENT_TYPE,
            IDENTIFIER_TYPE,
            L_BRACKET_TYPE,
            STRING_TYPE,
            R_BRACKET_TYPE,
            SEMICOLON_TYPE,
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            IDENTIFIER_TYPE,
            COMMENT_TYPE,
            FOR_TYPE,
            IN_TYPE,
            L_BRACKET_TYPE,
            INTEGER_TYPE,
            COMMA_TYPE,
            INTEGER_TYPE,
            COMMENT_TYPE,
            EOF_TYPE
    };
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
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
            VV_TYPE,
            IDENTIFIER_TYPE,
            SEMICOLON_TYPE,
            EOF_TYPE
    };
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
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
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    unsigned short int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
}

TEST(errorTests, notClosedLongStringTest) {
    std::string a = "vv a = 'vv if while for func main []psad[]p#  assa() {}././.;.;[lopk,opp\\'oijiojmddmdkopasdk opaskop aksop";
    unsigned short int expected_values[1000] {
            VV_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            (unsigned short int) ERR_NOT_CLOSED_STRING,
            EOF_TYPE
    };
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
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
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
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
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
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
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            IDENTIFIER_TYPE,
            PLUS_TYPE,
            INTEGER_TYPE,
            SEMICOLON_TYPE,
            R_CURL_BRACKET_TYPE,
            EOF_TYPE
    };
    std::stringbuf ss(a);
    Lexer * lexer = new Lexer(ss);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
}
