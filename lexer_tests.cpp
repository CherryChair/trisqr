//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../lexer.h"

void basic_test(std::string a, token_type tkn_type) {
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), tkn_type);
}

TEST(BasicTests, IfTest) {
    basic_test("if", IF_TYPE);
}

TEST(BasicTests, WhileTest) {
    basic_test("while", WHILE_TYPE);
}

TEST(BasicTests, ElsifTest) {
    basic_test("elsif", ELSIF_TYPE);
}

TEST(BasicTests, ElseTest) {
    basic_test("else", ELSE_TYPE);
}

TEST(BasicTests, funcTest) {
    basic_test("func", FUNC_TYPE);
}

TEST(BasicTests, figureTest) {
    basic_test("figure", FIGURE_TYPE);
}

TEST(BasicTests, returnTest) {
    basic_test("return", RETURN_TYPE);
}

TEST(BasicTests, forTest) {
    basic_test("for", FOR_TYPE);
}

TEST(BasicTests, rangeTest) {
    basic_test("range", RANGE_TYPE);
}

TEST(BasicTests, vvTest) {
    basic_test("vv", VV_TYPE);
}

TEST(BasicTests, trueTest) {
    basic_test("true", TRUE_TYPE);
}

TEST(BasicTests, falseTest) {
    basic_test("false", FALSE_TYPE);
}

TEST(BasicTests, isTest) {
    basic_test("is", IS_TYPE);
}

TEST(BasicTests, inTest) {
    basic_test("in", IN_TYPE);
}

TEST(BasicTests, toTest) {
    basic_test("to", TO_TYPE);
}

TEST(BasicTests, dotTest) {
    basic_test(".", DOT_TYPE);
}

TEST(BasicTests, negationTest) {
    basic_test("!", NEGATION_TYPE);
}

TEST(BasicTests, eqTest) {
    basic_test("==", EQ_TYPE);
}

TEST(BasicTests, neqTest) {
    basic_test("!=", NEQ_TYPE);
}

TEST(BasicTests, leqTest) {
    basic_test("<=", LEQ_TYPE);
}

TEST(BasicTests, lessTest) {
    basic_test("<", LESS_TYPE);
}

TEST(BasicTests, geqTest) {
    basic_test(">=", GEQ_TYPE);
}

TEST(BasicTests, graterTest) {
    basic_test(">", GREATER_TYPE);
}

TEST(BasicTests, andTest) {
    basic_test("&&", AND_TYPE);
}

TEST(BasicTests, orTest) {
    std::string a = "||";
    basic_test(a, OR_TYPE);
}

TEST(BasicTests, lbracketTest) {
    std::string a = "(";
    basic_test(a, L_BRACKET_TYPE);

}

TEST(BasicTests, rbracketTest) {
    std::string a = ")";
    basic_test(a, R_BRACKET_TYPE);

}

TEST(BasicTests, lsqrbracketTest) {
    std::string a = "[";
    basic_test(a, L_SQR_BRACKET_TYPE);
}

TEST(BasicTests, rsqrbracketTest) {
    std::string a = "]";
    basic_test(a, R_SQR_BRACKET_TYPE);
}

TEST(BasicTests, lcbracketTest) {
    std::string a = "{";
    basic_test(a, L_CURL_BRACKET_TYPE);
}

TEST(BasicTests, rcbracketTest) {
    std::string a = "}";
    basic_test(a, R_CURL_BRACKET_TYPE);
}

TEST(BasicTests, minusTest) {
    std::string a = "-";
    basic_test(a, MINUS_TYPE);
}

TEST(BasicTests, plusTest) {
    std::string a = "+";
    basic_test(a, PLUS_TYPE);
}

TEST(BasicTests, multTest) {
    std::string a = "*";
    basic_test(a, MULTIPLY_TYPE);
}

TEST(BasicTests, divTest) {
    std::string a = "/";
    basic_test(a, DIVIDE_TYPE);
}

TEST(BasicTests, assgnTest) {
    std::string a = "=";
    basic_test(a, ASSIGN_TYPE);
}

TEST(BasicTests, commaTest) {
    std::string a = ",";
    basic_test(a, COMMA_TYPE);
}

TEST(BasicTests, semicolonTest) {
    std::string a = ";";
    basic_test(a, SEMICOLON_TYPE);
}

TEST(BasicTests, colonTest) {
    std::string a = ":";
    basic_test(a, COLON_TYPE);
}

TEST(BasicTests, commentTest) {
    std::string a = "# @*(je8901  <PSA{l-s a)C";
    basic_test(a, COMMENT_TYPE);
}

TEST(BasicTests, EOFTest) {
    std::string a = "";
    basic_test(a, EOF_TYPE);
}

TEST(BasicTests, intKwrdTest) {
    std::string a = "int";
    basic_test(a, INT_KEYWORD_TYPE);
}

TEST(BasicTests, doubleKwrdTest) {
    std::string a = "double";
    basic_test(a, DOUBLE_KEYWORD_TYPE);
}

TEST(BasicTests, stringKwrdTest) {
    std::string a = "str";
    basic_test(a, STRING_KEYWORD_TYPE);
}


Lexer * prepareLexer(std::string a) {
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    return new Lexer(ss, eh);
}

TEST(TypeSpecificTests, doubleTest) {
    std::string a = "2.3455";
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), DOUBLE_TYPE);
    ASSERT_EQ(std::get<double>(tkn->getValue()), 2.3455);

}

TEST(TypeSpecificTests, intTest) {
    std::string a = "23455";
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), INTEGER_TYPE);
    ASSERT_EQ(std::get<int>(tkn->getValue()), 23455);
}

TEST(TypeSpecificTests, stringTest) {
    std::string a = "'dasdqd  while 12.31as zxc'";
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), STRING_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->getValue()), "dasdqd  while 12.31as zxc");
}

TEST(TypeSpecificTests, identifierTest) {
    std::string a = "variable";
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), IDENTIFIER_TYPE);
    ASSERT_EQ(std::get<std::string>(tkn->getValue()), "variable");
}

void CombinationTest(std::string a, unsigned short int expected_values[]) {
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
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
    CombinationTest(a, expected_values);
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
    CombinationTest(a, expected_values);
}

void ErrorTest(std::string a, unsigned short int expected_values[], std::string expected_errors, int max_identifier_chars, int max_string_chars) {
    std::stringbuf ss(a);
    ErrorHandler eh = ErrorHandler();
    testing::internal::CaptureStderr();
    Lexer * lexer = new Lexer(ss, eh, max_string_chars, max_identifier_chars);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
    std::string output = testing::internal::GetCapturedStderr();
    EXPECT_EQ(expected_errors, output);
}

TEST(errorTests, errorNewlineTest) {
    std::string a = "1.23 to int; \n\r\nvv \r \r\nvv vv a;  \r\n\n\r\r\nlak";
    unsigned short int expected_values[1000] {
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            SEMICOLON_TYPE,
            VV_TYPE,
            VV_TYPE,
            VV_TYPE,
            IDENTIFIER_TYPE,
            SEMICOLON_TYPE,
            IDENTIFIER_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 2, character 1: \\n << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 2, character 5: \\r << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 2, character 7: \\r\\n << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 2, character 19: \\r\\n << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 3, character 1: \\r\\n << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, notClosedStringTest) {
    std::string a = "1.2'3 to int; \n\r\n\r vv a;  \r\n";
    unsigned short int expected_values[1000] {
            DOUBLE_TYPE,
            ERR_TYPE,
            VV_TYPE,
            IDENTIFIER_TYPE,
            SEMICOLON_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +"\n" + "Line 1, character 4: '3 to int;  << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +"\n" + "Line 3, character 9: \\r\\n << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, notClosedLongStringTest) {
    std::string a = "vv a = 'vv if while for func main []psad[]p#  assa() {}././.;.;[lopk,o\\'oijiojmddmdkopasdk opaskop aksop";
    unsigned short int expected_values[1000] {
            VV_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +"\n" + "Line 1, character 8: 'vv if while for func main []psad[]p#  assa() {}././.;.;[lopk,o\'... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, longIntTest) {
    std::string a = "2147483648 3147483647 9999999999 2147483647";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            INTEGER_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 1: 2147483648 << error\n"+
                                  "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 12: 3147483647 << error\n"+
                                  "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 23: 9999999999 << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, longDoubleTest) {
    std::string a = "2.2147483648 2147483648.2147483648 2.1111111111222222222233333333334444444444555555555566666666667777777777888888888999999999900000000000 "
                    "1111111111222222222233333333334444444444555555555566666666667777777777888888888999999999900000000000.12938120930921389091283";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 1: 2.2147483648 << error\n"+
                                  "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 14: 2147483648.2147483648 << error\n"+
                                  "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 36: 2.11111111112222222222333333333344444444445555555555666666666677... << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +"\n" + "Line 1, character 139: 1111111111222222222233333333334444444444555555555566666666667777... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, maxStringLengthErrorTest) {
    std::string a = "'abcdef'";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_MAX_STRING_LEN_EXCEEDED) +"\n" + "Line 1, character 1: 'abcdef' << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 5);
}

TEST(errorTests, maxStringLengthTest) {
    std::string a = "'abcde'";
    unsigned short int expected_values[1000] {
            STRING_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "";
    ErrorTest(a, expected_values, expected_errors, 64, 5);
}

TEST(errorTests, wrongLogicalOperatorTest) {
    std::string a = "if (1.33 to int == 1 & true |& false &= m) {\n    a = a+1;\n}";
    unsigned short int expected_values[1000] {
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            EQ_TYPE,
            INTEGER_TYPE,
            ERR_TYPE,
            TRUE_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            FALSE_TYPE,
            ERR_TYPE,
            ASSIGN_TYPE,
            IDENTIFIER_TYPE,
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
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +"\n" + "Line 1, character 22: &  << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +"\n" + "Line 1, character 29: |& << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +"\n" + "Line 1, character 30: &  << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +"\n" + "Line 1, character 38: &= << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}


TEST(errorTests, unrecognizedCharTest) {
    std::string a = "if ł 'Michał'";
    unsigned short int expected_values[1000] {
            IF_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            STRING_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 4: \xC5 << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 5: \x82 << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, maxIdentifierLenExceeded) {
    std::string a = "a123456789";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_MAX_IDENTIFIER_LEN_EXCEEDED) +"\n" + "Line 1, character 1: a123456789 << error\n";
    ErrorTest(a, expected_values, expected_errors, 5, 1024);
}

TEST(errorTests, unrecognizedErrorAndEscaping) {
    std::string a = "\?\"\a\b\f\t\v";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 1: \\? << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 2: \" << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 3: \\a << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 4: \\b << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 5: \\f << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 6: \\t << error\n" +
                                  "LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +"\n" + "Line 1, character 7: \\v << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, stringErrorAndEscaping) {
    std::string a = "'\?\"\a\b\f\t\v";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::string expected_errors = "LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +"\n" + "Line 1, character 1: '\\?\"\\a\\b\\f\\t\\v << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}