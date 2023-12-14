//
// Created by mpkow on 15.05.2023.
//

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "lexer.h"
#include "Program/Program.h"

#ifndef LEXER_PARSER_H
#define LEXER_PARSER_H


class Parser {
public:
    Program * parse();
    bool getSemanticError() {return this->semantic_error;};
    bool getSyntaxError() {return this->blocking_syntax_error;};
private:
    bool blocking_syntax_error = false;
    bool semantic_error = false;
    Lexer * lexer;
    ErrorHandler * errorHandler;
    std::optional<Token> token;

    bool consumeIf(unsigned int token_type);

    FuncDeclaration * parseFuncDecl();
    FigureDeclaration * parseFigureDecl();
    std::vector<Parameter *> parseFunctionParams();
    Parameter * parseParam();
    CodeBlock * parseCodeBlock();
    Statement * parseStatement();
    Statement * parseWhileStatement();
    Statement * parseIfStatement();
    Statement * parseForStatement();
    Statement * parseDeclarationStatement();
    Statement * parseIdentifierOrAssignmentStatement();
    Statement * parseIdentifierDotStatement();
    Statement * parseIdentifierListCallStatement();
    Statement * parseIdentifierFunctionCallStatement();
    Statement * parseIdentifierStatement();
    Statement * parseReturnStatement();
    ConditionAndBlock * parseConditionAndBlock(const std::wstring & statement_type, token_type tokenType);
    Expression * parseExpression();
    Expression * parseExpressionAnd();
    Expression * parseExpressionComp();
    Expression * parseExpressionAdd();
    Expression * parseExpressionMul();
    Expression * parseExpressionIs();
    Expression * parseExpressionTo();
    Expression * parseExpressionNeg();
    Expression * parseAccessedValue();
    Expression * parseExpressionValueList();
    Expression * parseExpressionValueLiteral();

    nullptr_t handleSyntaxError(const Position &position, const std::wstring &message);
    void handleSemanticError(const Position &position, const std::wstring &message);

};


#endif //LEXER_PARSER_H
