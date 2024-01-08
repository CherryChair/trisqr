//
// Created by mpkow on 17.05.2023.
//

#ifndef LEXER_VISITOR_H
#define LEXER_VISITOR_H

#include "Program.h"

class Visitor {
public:
    virtual void visit(std::unique_ptr<ExpressionOr> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionAnd> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompEq> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompNeq> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompLeq> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompGeq> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompGreater> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionCompLess> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionAdd> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionSub> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionMul> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionDiv> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionIs> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionTo> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionNeg> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionNegMinus> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionValueList> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionValuePoint> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionValueLiteral> & e) = 0;
    virtual void visit(std::unique_ptr<ExpressionValueBrackets> & e) = 0;

    virtual void visit(std::unique_ptr<WhileStatement> & s) = 0;
    virtual void visit(std::unique_ptr<IfStatement> & s) = 0;
    virtual void visit(std::unique_ptr<ForStatement> & s) = 0;
    virtual void visit(std::unique_ptr<ForRangeStatement> & s) = 0;
    virtual void visit(std::unique_ptr<DeclarationStatement> & s) = 0;
    virtual void visit(std::unique_ptr<ReturnStatement> & s) = 0;

    virtual void visit(std::unique_ptr<ConditionAndBlock> & cb)= 0 ;

    virtual void visit(std::unique_ptr<ObjectAccessExpression> & s) = 0;
    virtual void visit(std::unique_ptr<IdentifierExpressionStatement> & s) = 0;
    virtual void visit(std::unique_ptr<IdentifierStatementAssign> & s) = 0;
    virtual void visit(std::unique_ptr<IdentifierListIndexExpression> & s) = 0;
    virtual void visit(std::unique_ptr<IdentifierFunctionCallExpression> & s) = 0;
    virtual void visit(std::unique_ptr<IdentifierExpression> & s) = 0;

    virtual void visit(std::unique_ptr<CodeBlock> & cb) = 0;
    virtual void visit(std::unique_ptr<Parameter> & p) = 0;
    virtual void visit(std::unique_ptr<FigureParameter> & p) = 0;
    virtual void visit(std::unique_ptr<FigureDeclaration> & fd) = 0;
    virtual void visit(std::unique_ptr<FuncDeclaration> & fd) = 0;
    virtual void visit(std::unique_ptr<Program> & p) = 0;
};


#endif //LEXER_VISITOR_H
