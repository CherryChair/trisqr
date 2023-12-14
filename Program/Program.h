//
// Created by mpkow on 16.05.2023.
//
#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "../lexer.h"

#ifndef LEXER_PROGRAM_H
#define LEXER_PROGRAM_H

class Expression;
class ExpressionOr;
class ExpressionAnd;
class ExpressionComp;
class ExpressionAdd;
class ExpressionMul;
class ExpressionIs;
class ExpressionTo;
class ExpressionNeg;
class ExpressionValueList;
class ExpressionValuePoint;
class ExpressionValueLiteral;
class ExpressionValueBrackets;

class WhileStatement;
class IfStatement;
class DeclarationStatement;
class ReturnStatement;
class Statement;

struct ConditionAndBlock;

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

class Statement {
protected:
    Position position;
public:
    Statement(){}
};

class Expression {
protected:
    Position position;
};

class ExpressionOr : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionOr(Expression * leftExpression, Expression * rightExpression, const Position & position)
        : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
};

class ExpressionAnd : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionAnd(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
};

class ExpressionComp : public Expression{
private:
    Expression * leftExpression;
    token_type compOperatorType;
    Expression * rightExpression;
public:
    ExpressionComp(Expression * leftExpression, Expression * rightExpression, token_type compOperatorType, const Position & position)
            : leftExpression(leftExpression), compOperatorType(compOperatorType), rightExpression(rightExpression) {this->position = position;}
};

class ExpressionAdd : public Expression{
private:
    Expression * leftExpression;
    token_type addOperatorType;
    Expression * rightExpression;
public:
    ExpressionAdd(Expression * leftExpression, Expression * rightExpression, token_type addOperatorType, const Position & position)
            : leftExpression(leftExpression), addOperatorType(addOperatorType), rightExpression(rightExpression) {this->position = position;}
};

class ExpressionMul : public Expression{
private:
    Expression * leftExpression;
    token_type mulOperatorType;
    Expression * rightExpression;
public:
    ExpressionMul(Expression * leftExpression, Expression * rightExpression, token_type mulOperatorType, const Position & position)
            : leftExpression(leftExpression), mulOperatorType(mulOperatorType), rightExpression(rightExpression) {this->position = position;}
};

class ExpressionIs : public Expression{
private:
    Expression * expression;
    token_type checkedType;
public:
    ExpressionIs(Expression * expression, token_type checkedType, const Position & position)
            : expression(expression), checkedType(checkedType) {this->position = position;}
};

class ExpressionTo : public Expression{
private:
    Expression * expression;
    token_type conversionType;
public:
    ExpressionTo(Expression * expression, token_type conversionType, const Position & position)
            : expression(expression), conversionType(conversionType) {this->position = position;}
};

class ExpressionNeg : public Expression{
private:
    Expression * expression;
    token_type negationType;
public:
    ExpressionNeg(Expression * expression, token_type negationType, const Position & position)
            : expression(expression), negationType(negationType) {this->position = position;}
};

class ExpressionValueList : public Expression {
private:
    std::vector<Expression *> expressions;
public:
    ExpressionValueList(std::vector<Expression *> expressions, const Position & position)
        : expressions(expressions) {this->position = position;};
};

class ExpressionValuePoint : public Expression {
private:
    Expression * xCoord;
    Expression * yCoord;
public:
    ExpressionValuePoint(Expression * xCoord, Expression * yCoord, const Position & position)
    : xCoord(xCoord), yCoord(yCoord) {this->position = position;};
};

class ExpressionValueLiteral : public Expression {
private:
    std::variant<int, double, std::wstring, bool, std::monostate> value;
public:
    template<typename T>
    ExpressionValueLiteral(T value, const Position & position) : value(value) {this->position = position;};
};

class ExpressionValueBrackets : public Expression {
private:
    Expression * expression;
public:
    ExpressionValueBrackets(Expression * expression, const Position & position)
    : expression(expression) {this->position = position;};
};

struct ConditionAndBlock {
    Expression * condition;
    CodeBlock * block;
    ConditionAndBlock(Expression * condition, CodeBlock * block) : condition(condition), block(block) {};
};

class WhileStatement : public Statement {
private:
    ConditionAndBlock * conditionAndBlock;
public:
    WhileStatement(ConditionAndBlock * conditionAndBlock, const Position & position) : conditionAndBlock(conditionAndBlock) {this->position = position;};
};

class IfStatement : public Statement {
private:
    ConditionAndBlock * ifConditionAndBlock;
    std::vector<ConditionAndBlock*> elsifConditionsAndBlocks;
    ConditionAndBlock * elseConditionAndBlock;
public:
    IfStatement(ConditionAndBlock * ifConditionAndBlock, std::vector<ConditionAndBlock*> elsifConditionsAndBlocks, ConditionAndBlock * elseConditionAndBlock, const Position & position)
            : ifConditionAndBlock(ifConditionAndBlock), elsifConditionsAndBlocks(elsifConditionsAndBlocks), elseConditionAndBlock(elseConditionAndBlock){this->position = position;};
};

class ForStatement : public Statement {
private:
    const std::wstring identifier;
    Expression * expression;
    CodeBlock * block;
public:
    ForStatement(const std::wstring & identifier, Expression * expression, CodeBlock * block, const Position & position) :
            identifier(identifier), expression(expression), block(block) {this->position = position;};
};

class DeclarationStatement : public Statement {
private:
    const std::wstring identifierName;
    Expression * expression;
public:
    DeclarationStatement(const std::wstring & identifierName, Expression * expression, const Position & position) : identifierName(identifierName), expression(expression) {this->position=position;};
};

class IdentifierStatement : public Statement {
private:
    const std::wstring identifierName;
public:
    IdentifierStatement(const std::wstring & identifierName, const Position & position)
            : identifierName(identifierName) {this->position=position;};
};

class IdentifierStatementFunctionCall : public Statement {
private:
    Statement * identifier;
    std::vector<Expression *> expressions;
public:
    IdentifierStatementFunctionCall(Statement * identifier, std::vector<Expression *> expressions,
                                    const Position & position)
            : identifier(identifier), expressions(expressions) {this->position=position;};
};

class IdentifierStatementListCall : public Statement {
private:
    Statement * leftStatement;
    std::vector<Expression *> expressions;
public:
    IdentifierStatementListCall(Statement * leftStatement, std::vector<Expression *> expressions, const Position & position)
            : leftStatement(leftStatement), expressions(expressions) {this->position=position;};
};

class IdentifierDotStatement : public Statement, public Expression {
private:
    Statement * leftStatement;
    Statement * rightStatement;
public:
    IdentifierDotStatement(Statement * leftStatement, Statement * rightStatement, const Position & position)
            : leftStatement(leftStatement), rightStatement(rightStatement) {Expression::position=position; Statement::position=position;};
};

class IdentifierStatementAssign : public Statement {
private:
    Statement * identifierStatement;
    Expression * expression;
public:
    IdentifierStatementAssign(Statement * identifierStatement, Expression * expression, const Position & position)
            : identifierStatement(identifierStatement), expression(expression) {this->position=position;};
};

class ReturnStatement : public Statement {
private:
    Expression * expression;
public:
    ReturnStatement(Expression * expression, const Position & position) : expression(expression) {this->position=position;};
};


class CodeBlock {
public:
    CodeBlock(const std::vector<Statement*> statements) : statements(statements) {}

    CodeBlock() {}

private:
    std::vector<Statement*> statements;
};

class Parameter {
private:
    const std::wstring name;
public:
    Parameter(const std::wstring &name) : name(name) {}

    const std::wstring &getName() const {
        return name;
    }
};

class FuncDeclaration {
public:

    FuncDeclaration(const std::wstring &name, std::vector<Parameter *> params, CodeBlock * statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FuncDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter *> params;
    CodeBlock * statements;
};

class FigureDeclaration {
public:

    FigureDeclaration(const std::wstring &name, std::vector<Parameter *> params, CodeBlock * statements, const Position & position) : name(
            name), params(params), statements(statements), position(position) {}

    FigureDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }

private:
    Position position;
    std::wstring name;
    std::vector<Parameter *> params;
    CodeBlock * statements;
};

class Program {
public:
    Program(const std::unordered_map<std::wstring, FuncDeclaration> &functions, const std::unordered_map<std::wstring, FigureDeclaration> &figures) : functions(functions), figures(figures) {}

    Program() {}

private:
    std::unordered_map<std::wstring, FuncDeclaration> functions;
    std::unordered_map<std::wstring, FigureDeclaration> figures;
};


#endif //LEXER_PROGRAM_H
