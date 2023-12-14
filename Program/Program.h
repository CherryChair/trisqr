//
// Created by mpkow on 16.05.2023.
//

#ifndef LEXER_PROGRAM_H
#define LEXER_PROGRAM_H

#include "Visitor.h"
#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "../lexer.h"

class Expression;
class ExpressionOr;
class ExpressionAnd;
class ExpressionCompEq;
class ExpressionCompNeq;
class ExpressionCompLeq;
class ExpressionCompGeq;
class ExpressionCompGreater;
class ExpressionCompLess;
class ExpressionAdd;
class ExpressionSub;
class ExpressionMul;
class ExpressionDiv;
class ExpressionIs;
class ExpressionTo;
class ExpressionNeg;
class ExpressionNegMinus;
class ExpressionValueList;
class ExpressionValuePoint;
class ExpressionValueLiteral;
class ExpressionValueBrackets;

class WhileStatement;
class IfStatement;
class DeclarationStatement;
class ReturnStatement;
class Statement;

class ConditionAndBlock;

class IdentifierDotStatement;
class IdentifierStatementAssign;
class IdentifierStatementListCall;
class IdentifierStatementFunctionCall;
class IdentifierStatement;

class CodeBlock;
class Parameter;
class FigureDeclaration;
class FuncDeclaration;
class Program;

enum variable_type {
    STRING_VARIABLE,
    BOOL_VARIABLE,
    INT_VARIABLE,
    DOUBLE_VARIABLE,
    NONE_VARIABLE,
    POINT_VARIABLE,
    FIGURE_VARIABLE
};


class Visitable {
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Visitable() = default;
    Position getPosition() {return this->position;}
protected:
    Position position;
};

class Statement : public Visitable {
public:
    Statement(){}
    virtual ~Statement() = default;
};

class Expression : public Visitable {
public:
    virtual ~Expression() = default;
};

class ExpressionOr : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionOr(Expression * leftExpression, Expression * rightExpression, const Position & position)
        : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionAnd : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionAnd(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompEq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompEq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompNeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompNeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompGeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompGeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompLeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompLeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompGreater : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompGreater(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionCompLess : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompLess(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionAdd : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionAdd(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionSub : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionSub(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionMul : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionMul(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionDiv : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionDiv(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionIs : public Expression{
private:
    Expression * expression;
    variable_type checkedType;
public:
    ExpressionIs(Expression * expression, variable_type checkedType, const Position & position)
            : expression(expression), checkedType(checkedType) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionTo : public Expression {
private:
    Expression * expression;
    variable_type conversionType;
public:
    ExpressionTo(Expression * expression, variable_type conversionType, const Position & position)
            : expression(expression), conversionType(conversionType) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionNeg : public Expression {
private:
    Expression * expression;
public:
    ExpressionNeg(Expression * expression, const Position & position)
            : expression(expression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionNegMinus : public Expression {
private:
    Expression * expression;
public:
    ExpressionNegMinus(Expression * expression, const Position & position)
            : expression(expression) {this->position = position;}
    virtual void accept(Visitor& visitor);
};

class ExpressionValueList : public Expression {
private:
    std::vector<Expression *> expressions;
public:
    ExpressionValueList(std::vector<Expression *> expressions, const Position & position)
        : expressions(expressions) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class ExpressionValuePoint : public Expression {
private:
    Expression * xCoord;
    Expression * yCoord;
public:
    ExpressionValuePoint(Expression * xCoord, Expression * yCoord, const Position & position)
    : xCoord(xCoord), yCoord(yCoord) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class ExpressionValueLiteral : public Expression {
private:
    std::variant<int, double, std::wstring, bool, std::monostate> value;
public:
    template<typename T>
    ExpressionValueLiteral(T value, const Position & position) : value(value) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class ExpressionValueBrackets : public Expression {
private:
    Expression * expression;
public:
    ExpressionValueBrackets(Expression * expression, const Position & position)
    : expression(expression) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class ConditionAndBlock : public Visitable{
private:
    Expression * condition;
    CodeBlock * block;
public:
    ConditionAndBlock(Expression * condition, CodeBlock * block) : condition(condition), block(block) {};
    virtual void accept(Visitor& visitor);
};

class WhileStatement : public Statement {
private:
    ConditionAndBlock * conditionAndBlock;
public:
    WhileStatement(ConditionAndBlock * conditionAndBlock, const Position & position) : conditionAndBlock(conditionAndBlock) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class IfStatement : public Statement {
private:
    ConditionAndBlock * ifConditionAndBlock;
    std::vector<ConditionAndBlock*> elsifConditionsAndBlocks;
    ConditionAndBlock * elseConditionAndBlock;
public:
    IfStatement(ConditionAndBlock * ifConditionAndBlock, std::vector<ConditionAndBlock*> elsifConditionsAndBlocks, ConditionAndBlock * elseConditionAndBlock, const Position & position)
            : ifConditionAndBlock(ifConditionAndBlock), elsifConditionsAndBlocks(elsifConditionsAndBlocks), elseConditionAndBlock(elseConditionAndBlock){this->position = position;};
    virtual void accept(Visitor& visitor);
};

class ForStatement : public Statement {
private:
    const std::wstring identifier;
    Expression * expression;
    CodeBlock * block;
public:
    ForStatement(const std::wstring & identifier, Expression * expression, CodeBlock * block, const Position & position) :
            identifier(identifier), expression(expression), block(block) {this->position = position;};
    virtual void accept(Visitor& visitor);
};

class DeclarationStatement : public Statement {
private:
    const std::wstring identifierName;
    Expression * expression;
public:
    DeclarationStatement(const std::wstring & identifierName, Expression * expression, const Position & position) : identifierName(identifierName), expression(expression) {this->position=position;};
    virtual void accept(Visitor& visitor);
};

class IdentifierStatement : public Statement {
private:
    const std::wstring identifierName;
public:
    IdentifierStatement(const std::wstring & identifierName, const Position & position)
            : identifierName(identifierName) {this->position=position;};
    virtual void accept(Visitor& visitor);
};

class IdentifierStatementFunctionCall : public Statement {
private:
    Statement * identifier;
    std::vector<Expression *> expressions;
public:
    IdentifierStatementFunctionCall(Statement * identifier, std::vector<Expression *> expressions,
                                    const Position & position)
            : identifier(identifier), expressions(expressions) {this->position=position;};
    virtual void accept(Visitor& visitor);
};

class IdentifierStatementListCall : public Statement {
private:
    Statement * leftStatement;
    std::vector<Expression *> expressions;
public:
    IdentifierStatementListCall(Statement * leftStatement, std::vector<Expression *> expressions, const Position & position)
            : leftStatement(leftStatement), expressions(expressions) {this->position=position;};
    virtual void accept(Visitor& visitor);
};

class IdentifierDotStatement : public Statement, public Expression {
private:
    Statement * leftStatement;
    Statement * rightStatement;
public:
    IdentifierDotStatement(Statement * leftStatement, Statement * rightStatement, const Position & position)
            : leftStatement(leftStatement), rightStatement(rightStatement) {Expression::position=position; Statement::position=position;};
    virtual void accept(Visitor& visitor);
};

class IdentifierStatementAssign : public Statement {
private:
    Statement * identifierStatement;
    Expression * expression;
public:
    IdentifierStatementAssign(Statement * identifierStatement, Expression * expression, const Position & position)
            : identifierStatement(identifierStatement), expression(expression) {this->position=position;};
    virtual void accept(Visitor& visitor);
};

class ReturnStatement : public Statement {
private:
    Expression * expression;
public:
    ReturnStatement(Expression * expression, const Position & position) : expression(expression) {this->position=position;};
    virtual void accept(Visitor& visitor);
};


class CodeBlock : public Visitable {
public:
    CodeBlock(const std::vector<Statement*> statements) : statements(statements) {}

    CodeBlock() {}

private:
    std::vector<Statement*> statements;
    virtual void accept(Visitor& visitor);
};

class Parameter : public Visitable {
protected:
    std::wstring name;
public:
    Parameter(const std::wstring &name) : name(name) {}
    Parameter() {}
    virtual ~Parameter() =default;

    const std::wstring &getName() const {
        return name;
    }
    virtual void accept(Visitor& visitor);
};

class FigureParameter : public Parameter {
private:
    Expression* value;
public:
    FigureParameter(const std::wstring & name, Expression * value) : value(value) {this->name = name;};
    virtual void accept(Visitor& visitor);
};

class FuncDeclaration : public Visitable{
public:

    FuncDeclaration(const std::wstring &name, std::vector<Parameter *> params, CodeBlock * statements, const Position & position) : name(
            name), params(params), statements(statements) {this->position = position;}

    FuncDeclaration() {}

    std::wstring getName(){
        return name;
    }
    virtual void accept(Visitor& visitor);

private:
    std::wstring name;
    std::vector<Parameter *> params;
    CodeBlock * statements;
};

class FigureDeclaration : public Visitable {
public:

    FigureDeclaration(const std::wstring &name, std::vector<Parameter *> params, const Position & position) : name(
            name), params(params)  {this->position = position;}

    FigureDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }
    virtual void accept(Visitor& visitor);

private:
    std::wstring name;
    std::vector<Parameter *> params;
};

class Program {
public:
    Program(std::unordered_map<std::wstring, FuncDeclaration*> functions, std::unordered_map<std::wstring, FigureDeclaration *> figures) : functions(functions), figures(figures) {}

    Program() {}
    virtual void accept(Visitor& visitor);

private:
    std::unordered_map<std::wstring, FuncDeclaration *> functions;
    std::unordered_map<std::wstring, FigureDeclaration *> figures;
};


#endif //LEXER_PROGRAM_H
