//
// Created by mpkow on 14.12.2023.
//

#ifndef LEXER_VISITORTREE_H
#define LEXER_VISITORTREE_H

#include "Visitor.h"


class VisitorTree : public Visitor {
private:
    std::vector<std::wstring> tree;
    unsigned int tabs = 0;
public:
    void visit(std::unique_ptr<ExpressionOr> & e);
    void visit(std::unique_ptr<ExpressionAnd> & e);
    void visit(std::unique_ptr<ExpressionCompEq> & e);
    void visit(std::unique_ptr<ExpressionCompNeq> & e);
    void visit(std::unique_ptr<ExpressionCompLeq> & e);
    void visit(std::unique_ptr<ExpressionCompGeq> & e);
    void visit(std::unique_ptr<ExpressionCompGreater> & e);
    void visit(std::unique_ptr<ExpressionCompLess> & e);
    void visit(std::unique_ptr<ExpressionAdd> & e);
    void visit(std::unique_ptr<ExpressionSub> & e);
    void visit(std::unique_ptr<ExpressionMul> & e);
    void visit(std::unique_ptr<ExpressionDiv> & e);
    void visit(std::unique_ptr<ExpressionIs> & e);
    void visit(std::unique_ptr<ExpressionTo> & e);
    void visit(std::unique_ptr<ExpressionNeg> & e);
    void visit(std::unique_ptr<ExpressionNegMinus> & e);
    void visit(std::unique_ptr<ExpressionValueList> & e);
    void visit(std::unique_ptr<ExpressionValuePoint> & e);
    void visit(std::unique_ptr<ExpressionValueLiteral> & e);
    void visit(std::unique_ptr<ExpressionValueBrackets> & e);

    void visit(std::unique_ptr<WhileStatement> & s);
    void visit(std::unique_ptr<IfStatement> & s);
    void visit(std::unique_ptr<ForStatement> & s);
    void visit(std::unique_ptr<ForRangeStatement> & s);
    void visit(std::unique_ptr<DeclarationStatement> & s);
    void visit(std::unique_ptr<ReturnStatement> & s);

    void visit(std::unique_ptr<ConditionAndBlock> & cb);

    void visit(std::unique_ptr<ObjectAccessExpression> & s);
    void visit(std::unique_ptr<IdentifierExpressionStatement> & s);
    void visit(std::unique_ptr<IdentifierStatementAssign> & s);
    void visit(std::unique_ptr<IdentifierListIndexExpression> & s);
    void visit(std::unique_ptr<IdentifierFunctionCallExpression> & s);
    void visit(std::unique_ptr<IdentifierExpression> & s);

    void visit(std::unique_ptr<CodeBlock> & cb);
    void visit(std::unique_ptr<Parameter> & p);
    void visit(std::unique_ptr<FigureParameter> & p);
    void visit(std::unique_ptr<FigureDeclaration> & fd);
    void visit(std::unique_ptr<FuncDeclaration> & fd);
    void visit(std::unique_ptr<Program> & p);
    void printTree(std::wostream& output);
};


#endif //LEXER_VISITORTREE_H
