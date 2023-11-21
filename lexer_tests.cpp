//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../lexer.h"
#include <codecvt>
#include <locale>

void basic_test(std::wstring a, token_type tkn_type) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    EXPECT_EQ(lexer->nextToken()->getTokenType(), tkn_type);
    ASSERT_EQ(lexer->nextToken()->getTokenType(), EOF_TYPE);
}

TEST(BasicTests, IfTest) {
    basic_test(L"if", IF_TYPE);
}

TEST(BasicTests, WhileTest) {
    basic_test(L"while", WHILE_TYPE);
}

TEST(BasicTests, ElsifTest) {
    basic_test(L"elsif", ELSIF_TYPE);
}

TEST(BasicTests, ElseTest) {
    basic_test(L"else", ELSE_TYPE);
}

TEST(BasicTests, funcTest) {
    basic_test(L"func", FUNC_TYPE);
}

TEST(BasicTests, figureTest) {
    basic_test(L"figure", FIGURE_TYPE);
}

TEST(BasicTests, returnTest) {
    basic_test(L"return", RETURN_TYPE);
}

TEST(BasicTests, forTest) {
    basic_test(L"for", FOR_TYPE);
}

TEST(BasicTests, rangeTest) {
    basic_test(L"range", RANGE_TYPE);
}

TEST(BasicTests, vvTest) {
    basic_test(L"vv", VV_TYPE);
}

TEST(BasicTests, trueTest) {
    basic_test(L"true", TRUE_TYPE);
}

TEST(BasicTests, falseTest) {
    basic_test(L"false", FALSE_TYPE);
}

TEST(BasicTests, isTest) {
    basic_test(L"is", IS_TYPE);
}

TEST(BasicTests, inTest) {
    basic_test(L"in", IN_TYPE);
}

TEST(BasicTests, toTest) {
    basic_test(L"to", TO_TYPE);
}

TEST(BasicTests, dotTest) {
    basic_test(L".", DOT_TYPE);
}

TEST(BasicTests, negationTest) {
    basic_test(L"!", NEGATION_TYPE);
}

TEST(BasicTests, eqTest) {
    basic_test(L"==", EQ_TYPE);
}

TEST(BasicTests, neqTest) {
    basic_test(L"!=", NEQ_TYPE);
}

TEST(BasicTests, leqTest) {
    basic_test(L"<=", LEQ_TYPE);
}

TEST(BasicTests, lessTest) {
    basic_test(L"<", LESS_TYPE);
}

TEST(BasicTests, geqTest) {
    basic_test(L">=", GEQ_TYPE);
}

TEST(BasicTests, graterTest) {
    basic_test(L">", GREATER_TYPE);
}

TEST(BasicTests, andTest) {
    basic_test(L"&&", AND_TYPE);
}

TEST(BasicTests, orTest) {
    std::wstring a = L"||";
    basic_test(a, OR_TYPE);
}

TEST(BasicTests, lbracketTest) {
    std::wstring a = L"(";
    basic_test(a, L_BRACKET_TYPE);

}

TEST(BasicTests, rbracketTest) {
    std::wstring a = L")";
    basic_test(a, R_BRACKET_TYPE);

}

TEST(BasicTests, lsqrbracketTest) {
    std::wstring a = L"[";
    basic_test(a, L_SQR_BRACKET_TYPE);
}

TEST(BasicTests, rsqrbracketTest) {
    std::wstring a = L"]";
    basic_test(a, R_SQR_BRACKET_TYPE);
}

TEST(BasicTests, lcbracketTest) {
    std::wstring a = L"{";
    basic_test(a, L_CURL_BRACKET_TYPE);
}

TEST(BasicTests, rcbracketTest) {
    std::wstring a = L"}";
    basic_test(a, R_CURL_BRACKET_TYPE);
}

TEST(BasicTests, minusTest) {
    std::wstring a = L"-";
    basic_test(a, MINUS_TYPE);
}

TEST(BasicTests, plusTest) {
    std::wstring a = L"+";
    basic_test(a, PLUS_TYPE);
}

TEST(BasicTests, multTest) {
    std::wstring a = L"*";
    basic_test(a, MULTIPLY_TYPE);
}

TEST(BasicTests, divTest) {
    std::wstring a = L"/";
    basic_test(a, DIVIDE_TYPE);
}

TEST(BasicTests, assgnTest) {
    std::wstring a = L"=";
    basic_test(a, ASSIGN_TYPE);
}

TEST(BasicTests, commaTest) {
    std::wstring a = L",";
    basic_test(a, COMMA_TYPE);
}

TEST(BasicTests, semicolonTest) {
    std::wstring a = L";";
    basic_test(a, SEMICOLON_TYPE);
}

TEST(BasicTests, colonTest) {
    std::wstring a = L":";
    basic_test(a, COLON_TYPE);
}

TEST(BasicTests, commentTest) {
    std::wstring a = L"# @*(je8901  <PSA{l-s a)C";
    basic_test(a, COMMENT_TYPE);
}

TEST(BasicTests, EOFTest) {
    std::wstring a = L"";
    basic_test(a, EOF_TYPE);
}

TEST(BasicTests, intKwrdTest) {
    std::wstring a = L"int";
    basic_test(a, INT_KEYWORD_TYPE);
}

TEST(BasicTests, doubleKwrdTest) {
    std::wstring a = L"double";
    basic_test(a, DOUBLE_KEYWORD_TYPE);
}

TEST(BasicTests, stringKwrdTest) {
    std::wstring a = L"str";
    basic_test(a, STRING_KEYWORD_TYPE);
}

TEST(BasicTests, nonASCIITest) {
basic_test(L"'ąćęłóśźż'", STRING_TYPE);
}

Lexer * prepareLexer(std::wstring a) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    return new Lexer(ss, eh);
}

TEST(TypeSpecificTests, doubleTest) {
    std::wstring a = L"2.3455";
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), DOUBLE_TYPE);
    ASSERT_EQ(std::get<double>(tkn->getValue()), 2.3455);

}

TEST(TypeSpecificTests, intTest) {
    std::wstring a = L"23455";
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), INTEGER_TYPE);
    ASSERT_EQ(std::get<int>(tkn->getValue()), 23455);
}

TEST(TypeSpecificTests, stringTest) {
    std::wstring a = L"'dasdqd  while 12.31as zxc'";
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), STRING_TYPE);
    ASSERT_EQ(std::get<std::wstring>(tkn->getValue()), L"dasdqd  while 12.31as zxc");
}


TEST(TypeSpecificTests, stringWithNonASCIITest) {
    std::wstring a = L"'ąćęłóźż dasdqd  while 12.31as zxc'";
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), STRING_TYPE);
    ASSERT_EQ(std::get<std::wstring>(tkn->getValue()), L"ąćęłóźż dasdqd  while 12.31as zxc");
}

TEST(TypeSpecificTests, identifierTest) {
    std::wstring a = L"variable";
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn = lexer->nextToken();
    EXPECT_EQ(tkn->getTokenType(), IDENTIFIER_TYPE);
    ASSERT_EQ(std::get<std::wstring>(tkn->getValue()), L"variable");
}

void CombinationTest(std::wstring a, unsigned short int expected_values[]) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
}

TEST(CombinationsTests, simpleHelloWorldTest) {
    std::wstring a = L"func HelloWorld(){\r\n print('Hello world!');\r\nif(1.23 to int==1){\r\n       for   in (  0,   11   )    }";
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
    std::wstring a = L"func #HelloWorld(){\r\n print('Hell#o world#!#');\r\nif(1.23 t#o int==1){\r\n       for   in (  0,   11   #)    }";
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

void ErrorTest(std::wstring a, unsigned short int expected_values[], std::wstring expected_errors, int max_identifier_chars, int max_string_chars) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    testing::internal::CaptureStderr();
    Lexer * lexer = new Lexer(ss, eh, max_string_chars, max_identifier_chars, 1024, 2048);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        i++;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring output = converter.from_bytes(testing::internal::GetCapturedStderr());
    EXPECT_EQ(expected_errors, output);
}

TEST(errorTests, errorNewlineTest) {
    std::wstring a = L"1.23 to int; \n\r\nvv \r \r\nvv vv a;  \r\n\n\r\r\nlak";
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
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 2, character 1: \\n << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 3, character 4: \\r << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 4, character 2: \\r\\n << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 5, character 11: \\r\\n << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 7, character 1: \\r\\n << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, notClosedStringTest) {
    std::wstring a = L"1.2'3 to int; \n\r\n\r vv a;  \r\n";
    unsigned short int expected_values[1000] {
            DOUBLE_TYPE,
            ERR_TYPE,
            VV_TYPE,
            IDENTIFIER_TYPE,
            SEMICOLON_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +L"\n" + L"Line 1, character 4: '3 to int;  << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_ENDLINE_CHAR) +L"\n" + L"Line 3, character 9: \\r\\n << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, notClosedLongStringTest) {
    std::wstring a = L"vv a = 'vv if while for func main []psad[]p#  assa() {}././.;.;[lopk,o\\'oijiojmddmdkopasdk opaskop aksop";
    unsigned short int expected_values[1000] {
            VV_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +L"\n" + L"Line 1, character 8: 'vv if while for func main []psad[]p#  assa() {}././.;.;[lopk,o\'... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, longIntTest) {
    std::wstring a = L"2147483648 3147483647 9999999999 2147483647";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            INTEGER_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 1: 2147483648 << error\n"+
                                   L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 12: 3147483647 << error\n"+
                                   L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 23: 9999999999 << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, longDoubleTest) {
    std::wstring a = L"2.2147483648 2147483648.2147483648 2.1111111111222222222233333333334444444444555555555566666666667777777777888888888999999999900000000000 "
                     "1111111111222222222233333333334444444444555555555566666666667777777777888888888999999999900000000000.12938120930921389091283";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 1: 2.2147483648 << error\n"+
                                   L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 14: 2147483648 << error\n"+
                                   L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 36: 2.11111111112 << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_INT_TOO_BIG) +L"\n" + L"Line 1, character 139: 11111111112 << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, maxStringLengthErrorTest) {
    std::wstring a = L"'abcdef'";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_STRING_LEN_EXCEEDED) +L"\n" + L"Line 1, character 1: 'abcde << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 5);
}

TEST(errorTests, maxStringLengthTest) {
    std::wstring a = L"'abcde'";
    unsigned short int expected_values[1000] {
            STRING_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"";
    ErrorTest(a, expected_values, expected_errors, 64, 5);
}

TEST(errorTests, wrongLogicalOperatorTest) {
    std::wstring a = L"if (1.33 to int == 1 & true |& false &= m) {\n    a = a+1;\n}";
    unsigned short int expected_values[1000] {
            IF_TYPE,
            L_BRACKET_TYPE,
            DOUBLE_TYPE,
            TO_TYPE,
            INT_KEYWORD_TYPE,
            EQ_TYPE,
            INTEGER_TYPE,
            AND_TYPE,
            TRUE_TYPE,
            OR_TYPE,
            AND_TYPE,
            FALSE_TYPE,
            AND_TYPE,
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
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +L"\n" + L"Line 1, character 22: &  << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +L"\n" + L"Line 1, character 29: |& << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +L"\n" + L"Line 1, character 30: &  << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_WRONG_LOGICAL_OPERATOR) +L"\n" + L"Line 1, character 38: &= << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, maxIdentifierLenExceeded) {
    std::wstring a = L"a123456789";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_IDENTIFIER_LEN_EXCEEDED) +L"\n" + L"Line 1, character 1: a1234 << error\n";
    ErrorTest(a, expected_values, expected_errors, 5, 1024);
}

TEST(errorTests, unrecognizedErrorAndEscaping) {
    std::wstring a = L"\?\f\"\t\a\v\b";
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
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +L"\n" + L"Line 1, character 1: \\? << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +L"\n" + L"Line 1, character 3: \" << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +L"\n" + L"Line 1, character 5: \\a << error\n" +
                                   L"LEX_ERR: " + error_mesages.at(ERR_UNRECOGNIZED_CHARACTER) +L"\n" + L"Line 1, character 7: \\b << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, stringErrorAndEscaping) {
    std::wstring a = L"'\?\"\a\b\f\t\v";
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_NOT_CLOSED_STRING) +L"\n" + L"Line 1, character 1: '\\?\"\\a\\b\\f\\t\\v << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, commentLenExceeded) {
    std::wstring a = L"#" + std::wstring(1025, 'a');
    unsigned short int expected_values[1000] {
            ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_COMMENT_LENGTH_EXCEEDED) +L"\n" + L"Line 1, character 1: #" +
                                   std::wstring(63, 'a') + L"... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, commentAnalyzedLenExceeded) {
    std::wstring a = L"#" + std::wstring(2047, 'a');
    unsigned short int expected_values[1000] {
            CRITICAL_ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_ANALYZED_CHARS_EXCEEDED) +L"\n" + L"Line 1, character 1: #" +
                                   std::wstring(63, 'a') + L"... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, stringAnalyzedLenExceeded) {
    std::wstring a = L"'" + std::wstring(2048, 'a');
    unsigned short int expected_values[1000] {
            CRITICAL_ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_ANALYZED_CHARS_EXCEEDED) +L"\n" + L"Line 1, character 1: '" +
                                   std::wstring(63, 'a') + L"... << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, intAnalyzedLenExceeded) {
    std::wstring a = std::wstring(2048, '1');
    unsigned short int expected_values[1000] {
            CRITICAL_ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_ANALYZED_CHARS_EXCEEDED) +L"\n" + L"Line 1, character 1: " +
                                   std::wstring(11, '1') + L" << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

TEST(errorTests, doubleAnalyzedLenExceeded) {
    std::wstring a = L"123123." + std::wstring(2041, '1');
    unsigned short int expected_values[1000] {
            CRITICAL_ERR_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"LEX_ERR: " + error_mesages.at(ERR_MAX_ANALYZED_CHARS_EXCEEDED) +L"\n" + L"Line 1, character 1: " +
                                   L"123123.11111111111 << error\n";
    ErrorTest(a, expected_values, expected_errors, 64, 1024);
}

void PositionTest(std::wstring a, unsigned short int expected_values[], Position expected_positions[], std::wstring expected_errors, int max_identifier_chars, int max_string_chars) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    testing::internal::CaptureStderr();
    Lexer * lexer = new Lexer(ss, eh, max_string_chars, max_identifier_chars, 1024, 2048);
    std::optional<Token> tkn;
    int i= 0;
    while((tkn = lexer->nextToken()) && tkn->getTokenType() != EOF_TYPE){
        EXPECT_EQ(tkn->getTokenType(), expected_values[i]);
        EXPECT_EQ(tkn->getPos().characterNum, expected_positions[i].characterNum);
        EXPECT_EQ(tkn->getPos().line, expected_positions[i].line);
        i++;
    }
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring output = converter.from_bytes(testing::internal::GetCapturedStderr());
    EXPECT_EQ(expected_errors, output);
}

TEST(PositionTests, largePostionTest) {
    std::wstring a = L"\n\rvv a  = 3.3 ;   \n\r  \n\r   if ( a != 5.4)  { \n\rfigure && ||   \n\r}";
    unsigned short int expected_values[1000] {
            VV_TYPE,
            IDENTIFIER_TYPE,
            ASSIGN_TYPE,
            DOUBLE_TYPE,
            SEMICOLON_TYPE,
            IF_TYPE,
            L_BRACKET_TYPE,
            IDENTIFIER_TYPE,
            NEQ_TYPE,
            DOUBLE_TYPE,
            R_BRACKET_TYPE,
            L_CURL_BRACKET_TYPE,
            FIGURE_TYPE,
            AND_TYPE,
            OR_TYPE,
            R_CURL_BRACKET_TYPE,
            EOF_TYPE
    };
    std::wstring expected_errors = L"";
    Position expected_positions[1000] {
            {2, 1},//vv
            {2,4},//a
            {2,7},//=
            {2,9},//3.3
            {2,13},//;
            {4,4},//if
            {4, 7},//(
            {4,9},//a
            {4,11},// !=
            {4,14},//5.4
            {4,17},//)
            {4,20},//{
            {5,1},//figure
            {5,8},//&&
            {5,11},//||
            {6,1},//}
    };
    PositionTest(a, expected_values, expected_positions, expected_errors,  64, 1024);
}
