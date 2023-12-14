//
// Created by mpkow on 17.05.2023.
//

#ifndef LEXER_VISITOR_H
#define LEXER_VISITOR_H

#include "Program.h"

class Visitor {
public:
    virtual void visit(Expression * e) = 0;
    virtual void visit(ExpressionOr * eor) = 0;
    virtual void visit(ExpressionAnd *) = 0;
    virtual void visit(ExpressionCompEq *) = 0;
    virtual void visit(ExpressionCompNeq *) = 0;
    virtual void visit(ExpressionCompLeq *) = 0;
    virtual void visit(ExpressionCompGeq *) = 0;
    virtual void visit(ExpressionCompGreater *) = 0;
    virtual void visit(ExpressionCompLess *) = 0;
    virtual void visit(ExpressionAdd *) = 0;
    virtual void visit(ExpressionSub *) = 0;
    virtual void visit(ExpressionMul *) = 0;
    virtual void visit(ExpressionDiv *) = 0;
    virtual void visit(ExpressionIs *) = 0;
    virtual void visit(ExpressionTo *) = 0;
    virtual void visit(ExpressionNeg *) = 0;
    virtual void visit(ExpressionNegMinus *) = 0;
    virtual void visit(ExpressionValueList *) = 0;
    virtual void visit(ExpressionValuePoint *) = 0;
    virtual void visit(ExpressionValueLiteral *) = 0;
    virtual void visit(ExpressionValueBrackets *) = 0;

    virtual void visit(WhileStatement *) = 0;
    virtual void visit(IfStatement *) = 0;
    virtual void visit(ForStatement *) = 0;
    virtual void visit(ForRangeStatement *) = 0;
    virtual void visit(DeclarationStatement *) = 0;
    virtual void visit(ReturnStatement *) = 0;
    virtual void visit(Statement *) = 0;

    virtual void visit(ConditionAndBlock *)= 0 ;

    virtual void visit(IdentifierDotStatement *) = 0;
    virtual void visit(IdentifierStatementAssign *) = 0;
    virtual void visit(IdentifierStatementListCall *) = 0;
    virtual void visit(IdentifierStatementFunctionCall *) = 0;
    virtual void visit(IdentifierStatement *) = 0;

    virtual void visit(CodeBlock*) = 0;
    virtual void visit(Parameter*) = 0;
    virtual void visit(FigureParameter*) = 0;
    virtual void visit(FigureDeclaration*) = 0;
    virtual void visit(FuncDeclaration*) = 0;
    virtual void visit(Program*) = 0;
};


#endif //LEXER_VISITOR_H
