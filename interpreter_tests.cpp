//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../lexer.h"
#include "../Program/Program.h"
#include "../Parser.h"
#include <codecvt>
#include <locale>
#include <fstream>
#include "../Program/VisitorInterpreter.h"

void basic_test(std::string filename) {
    std::wfilebuf ss;
    ss.open(filename, std::ios_base::in);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    Parser * parser = new Parser(lexer, eh);
    auto program = parser->parse();
    testing::internal::CaptureStdout();
    VisitorInterpreter vi = VisitorInterpreter(eh);
    program->accept(vi);
    std::wstring delimiter = L"\n";
    size_t pos = 0;
    std::wstring token;
    std::wstring_convert<std::codecvt_utf8_utf16<wchar_t>> converter;
    std::wstring output = converter.from_bytes(testing::internal::GetCapturedStdout());
    while ((pos = output.find(delimiter)) != std::string::npos) {
        token = output.substr(0, pos);
        EXPECT_EQ(L"PASS", token);
        output.erase(0, pos + delimiter.length());
    }

}

TEST(BasicInterpreterTests, ConditionTest) {
    basic_test("../../parser_condition_tests.trisqr");
}
