//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORSEMANTIC_H
#define LEXER_VISITORSEMANTIC_H

#include "Visitor.h"



class VisitorSemantic : public Visitor {
public:
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
};

#endif //LEXER_VISITORSEMANTIC_H
