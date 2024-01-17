//
// Created by mpkow on 24.04.2023.
//



#include "gtest/gtest.h"
#include "../Lexer/lexer.h"
#include "../Program/Program.h"
#include "../Parser/Parser.h"
#include <codecvt>
#include <locale>

bool basic_test(std::wstring a, std::unique_ptr<Program> & program) {
    std::wstringbuf ss(a);
    ErrorHandler * eh = new ErrorHandler();
    Lexer * lexer = new Lexer(ss, eh);
    Parser * parser = new Parser(lexer, eh);
    auto parsedProgram = parser->parse();
    return  *parsedProgram == *program;
}

TEST(BasicParserTests, ParsingTest) {
    std::wstring toParse = L"func main() {\n";
    toParse += L"\tvv toParse = 1 + 2;\n";
    toParse += L"\ttoParse = '1 + 2';\n";
    toParse += L"\tprint(toParse to str);\n";
    toParse += L"}\n";

    Position dummyPosition = Position({1,1});
    std::unique_ptr<IdentifierExpression> identifierExpression4 = std::make_unique<IdentifierExpression>(L"toParse", dummyPosition);
    std::unique_ptr<IdentifierExpression> identifierExpression3 = std::make_unique<IdentifierExpression>(L"print", dummyPosition);
    std::unique_ptr<IdentifierExpression> identifierExpression2 = std::make_unique<IdentifierExpression>(L"toParse", dummyPosition);
    std::unique_ptr<ExpressionValueLiteral> stringExpression = std::make_unique<ExpressionValueLiteral>((std::wstring)L"1 + 2", dummyPosition);
    std::unique_ptr<ExpressionValueLiteral> intExpression2 = std::make_unique<ExpressionValueLiteral>(2, dummyPosition);
    std::unique_ptr<ExpressionValueLiteral> intExpression1 = std::make_unique<ExpressionValueLiteral>(1, dummyPosition);
    std::unique_ptr<ExpressionTo> toExpression = std::make_unique<ExpressionTo>(std::move(identifierExpression4), STRING_VARIABLE, dummyPosition);
    std::vector<std::unique_ptr<Expression>> functionCallParams;
    functionCallParams.push_back(std::move(toExpression));
    std::unique_ptr<IdentifierFunctionCallExpression> functionCallExpression = std::make_unique<IdentifierFunctionCallExpression>(std::move(identifierExpression3), std::move(functionCallParams), dummyPosition);
    std::unique_ptr<ExpressionAdd> addExpression = std::make_unique<ExpressionAdd>(std::move(intExpression1), std::move(intExpression2), dummyPosition);
    std::unique_ptr<IdentifierExpressionStatement> expressionStatement = std::make_unique<IdentifierExpressionStatement>(std::move(functionCallExpression), dummyPosition);
    std::unique_ptr<IdentifierStatementAssign> assignStatement = std::make_unique<IdentifierStatementAssign>(std::move(identifierExpression2), std::move(stringExpression), dummyPosition);
    std::unique_ptr<DeclarationAssignStatement> declAssignStatement = std::make_unique<DeclarationAssignStatement>(L"toParse", std::move(addExpression), dummyPosition);
    std::vector<std::unique_ptr<Statement>> statements;
    statements.push_back(std::move(declAssignStatement));
    statements.push_back(std::move(assignStatement));
    statements.push_back(std::move(expressionStatement));
    std::unique_ptr<CodeBlock> codeBlock = std::make_unique<CodeBlock>(std::move(statements), dummyPosition);
    std::vector<std::unique_ptr<Parameter>> params;
    std::unique_ptr<FuncDeclaration> funcDeclaration = std::make_unique<FuncDeclaration>(L"main", std::move(params), std::move(codeBlock), dummyPosition);
    std::unordered_map<std::wstring, std::unique_ptr<FuncDeclaration>> functions;
    functions[L"main"] = std::move(funcDeclaration);
    std::unordered_map<std::wstring, std::unique_ptr<FigureDeclaration>> figures;
    std::unique_ptr<Program> p = std::make_unique<Program>(std::move(functions), std::move(figures));

    bool result = basic_test(toParse, p);
    ASSERT_TRUE(result);
}

TEST(BasicParserTests, FailedEqualityParsingTest) {
    std::wstring toParse = L"func main() {\n";
    toParse += L"\tvv toParse = 1 + 2;\n";
    toParse += L"\ttoParse = '1 + 2';\n";
    toParse += L"\tprint(toParse to str);\n";
    toParse += L"}\n";

    std::unordered_map<std::wstring, std::unique_ptr<FuncDeclaration>> functions;
    std::unordered_map<std::wstring, std::unique_ptr<FigureDeclaration>> figures;
    std::unique_ptr<Program> p = std::make_unique<Program>(std::move(functions), std::move(figures));

    basic_test(toParse, p);
    bool result = basic_test(toParse, p);
    ASSERT_FALSE(result);
}