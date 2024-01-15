//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORSEMANTIC_H
#define LEXER_VISITORSEMANTIC_H

#include "Visitor.h"
#include <stack>


enum found_type {
    LIST_METHOD_FOUND,
    FIGURE_METHOD_FOUND,
    COLOR_FOUND,
    FIGURE_FOUND,
    FUNCTION_FOUND,
    IDENTIFIER_FOUND,
    NOT_FOUND,
};

static const std::unordered_map<found_type, std::wstring> found_type_representation= {
        {LIST_METHOD_FOUND,   L"list method"},
        {FIGURE_METHOD_FOUND, L"figure method"},
        {COLOR_FOUND,         L"figure color"},
        {FIGURE_FOUND,        L"figure"},
        {FUNCTION_FOUND,      L"function"},
        {IDENTIFIER_FOUND,    L"variable"},
        {NOT_FOUND,           L"not found"},
};

class ScopeSem {
protected:
    std::unordered_set<std::wstring> variables;
public:
    std::unordered_set<std::wstring> & getVariables() {return variables;};
};

class FunctionContextSem{
private:
    std::vector<ScopeSem> scopes;
public:
    std::vector<ScopeSem> & getScopes() {return scopes;};
};

class VisitorSemantic : public Visitor {
private:
    ScopeSem figureScope = ScopeSem();
    std::stack<FunctionContextSem> functionContexts;
    std::unordered_set<std::wstring> functions;
    std::unordered_set<std::wstring> figures;
    ErrorHandler * errorHandler;
    bool semanticError = false;
    bool objectAccess = false;
    bool functionCall = false;
public:
    VisitorSemantic(ErrorHandler * eh): errorHandler(eh){};
    void visit(ExpressionOr * e);
    void visit(ExpressionAnd * e);
    void visit(ExpressionCompEq * e);
    void visit(ExpressionCompNeq * e);
    void visit(ExpressionCompLeq * e);
    void visit(ExpressionCompGeq * e);
    void visit(ExpressionCompGreater * e);
    void visit(ExpressionCompLess * e);
    void visit(ExpressionAdd * e);
    void visit(ExpressionSub * e);
    void visit(ExpressionMul * e);
    void visit(ExpressionDiv * e);
    void visit(ExpressionIs * e);
    void visit(ExpressionTo * e);
    void visit(ExpressionNeg * e);
    void visit(ExpressionNegMinus * e);
    void visit(ExpressionValueList * e);
    void visit(ExpressionValuePoint * e);
    void visit(ExpressionValueLiteral * e);
    void visit(ExpressionValueBrackets * e);

    void visit(WhileStatement * s);
    void visit(IfStatement * s);
    void visit(ForStatement * s);
    void visit(ForRangeStatement * s);
    void visit(DeclarationStatement * s);
    void visit(DeclarationAssignStatement * s);
    void visit(ReturnStatement * s);

    void visit(ConditionAndBlock * cb);

    void visit(ObjectAccessExpression * s);
    void visit(IdentifierExpressionStatement * s);
    void visit(IdentifierStatementAssign * s);
    void visit(IdentifierListIndexExpression * s);
    void visit(IdentifierFunctionCallExpression * s);
    void visit(IdentifierExpression * s);

    void visit(CodeBlock * cb);
    void visit(Parameter * p);
    void visit(FigureParameter * p);
    void visit(FigureDeclaration * fd);
    void visit(FuncDeclaration * fd);
    void visit(Program * p);

    ScopeSem & addNewScope();
    void popScope();
    found_type findVariable(const std::wstring & variableName);
    void handleSemanticError(const Position & pos, const std::wstring & errorMsg);
    void handleDeclarationError(const Position &pos, const std::wstring & name, found_type foundType);
    void insertVariableNameToCurrentScope(const std::wstring & name);
};

#endif //LEXER_VISITORSEMANTIC_H
