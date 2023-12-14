//
// Created by mpkow on 14.12.2023.
//

#ifndef LEXER_VISITORTREE_H
#define LEXER_VISITORTREE_H

#include "Visitor.h"

class VisitorTree : public Visitor {
public:
    void visit(Expression * e);
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
    void visit(ReturnStatement * s);
    void visit(Statement * s);

    void visit(ConditionAndBlock * cb);

    void visit(IdentifierDotStatement * s);
    void visit(IdentifierStatementAssign * s);
    void visit(IdentifierStatementListCall * s);
    void visit(IdentifierStatementFunctionCall * s);
    void visit(IdentifierStatement * s);

    void visit(CodeBlock* cb);
    void visit(Parameter* p);
    void visit(FigureParameter* p);
    void visit(FigureDeclaration* fd);
    void visit(FuncDeclaration* fd);
    void visit(Program* p);
};


#endif //LEXER_VISITORTREE_H