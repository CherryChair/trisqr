//
// Created by mpkow on 17.05.2023.
//

#ifndef LEXER_VISITOR_H
#define LEXER_VISITOR_H

#include "Program.h"

class Visitor {
public:
    virtual void visit(ExpressionOr * e) = 0;
    virtual void visit(ExpressionAnd * e) = 0;
    virtual void visit(ExpressionCompEq * e) = 0;
    virtual void visit(ExpressionCompNeq * e) = 0;
    virtual void visit(ExpressionCompLeq * e) = 0;
    virtual void visit(ExpressionCompGeq * e) = 0;
    virtual void visit(ExpressionCompGreater * e) = 0;
    virtual void visit(ExpressionCompLess * e) = 0;
    virtual void visit(ExpressionAdd * e) = 0;
    virtual void visit(ExpressionSub * e) = 0;
    virtual void visit(ExpressionMul * e) = 0;
    virtual void visit(ExpressionDiv * e) = 0;
    virtual void visit(ExpressionIs * e) = 0;
    virtual void visit(ExpressionTo * e) = 0;
    virtual void visit(ExpressionNeg * e) = 0;
    virtual void visit(ExpressionNegMinus * e) = 0;
    virtual void visit(ExpressionValueList * e) = 0;
    virtual void visit(ExpressionValuePoint * e) = 0;
    virtual void visit(ExpressionValueLiteral * e) = 0;
    virtual void visit(ExpressionValueBrackets * e) = 0;

    virtual void visit(WhileStatement * s) = 0;
    virtual void visit(IfStatement * s) = 0;
    virtual void visit(ForStatement * s) = 0;
    virtual void visit(ForRangeStatement * s) = 0;
    virtual void visit(DeclarationStatement * s) = 0;
    virtual void visit(ReturnStatement * s) = 0;

    virtual void visit(ConditionAndBlock * cb)= 0 ;

    virtual void visit(ObjectAccessExpression * s) = 0;
    virtual void visit(IdentifierExpressionStatement * s) = 0;
    virtual void visit(IdentifierStatementAssign * s) = 0;
    virtual void visit(IdentifierListIndexExpression * s) = 0;
    virtual void visit(IdentifierFunctionCallExpression * s) = 0;
    virtual void visit(IdentifierExpression * s) = 0;

    virtual void visit(CodeBlock* cb) = 0;
    virtual void visit(Parameter* p) = 0;
    virtual void visit(FigureParameter* p) = 0;
    virtual void visit(FigureDeclaration* fd) = 0;
    virtual void visit(FuncDeclaration* fd) = 0;
    virtual void visit(Program* p) = 0;
};


#endif //LEXER_VISITOR_H
