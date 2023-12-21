//
// Created by mpkow on 16.05.2023.
//

#ifndef LEXER_PROGRAM_H
#define LEXER_PROGRAM_H

#include <vector>
#include <variant>
#include <unordered_map>
#include <string>
#include <optional>
#include "../lexer.h"


class Visitor;

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
class ForStatement;
class DeclarationStatement;
class ReturnStatement;
class Statement;

class ConditionAndBlock;

class IdentifierDotExpression;
class IdentifierStatementAssign;
class IdentifierListCallExpression;
class IdentifierFunctionCallExpression;
class IdentifierExpression;

class CodeBlock;
class Parameter;
class FigureParameter;
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
    Expression(){}
    virtual ~Expression() = default;
};

class ExpressionOr : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionOr(Expression * leftExpression, Expression * rightExpression, const Position & position)
        : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);

    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionAnd : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionAnd(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);

    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompEq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompEq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompNeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompNeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompGeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompGeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompLeq : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompLeq(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompGreater : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompGreater(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionCompLess : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionCompLess(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionAdd : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionAdd(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionSub : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionSub(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionMul : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionMul(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionDiv : public Expression{
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    ExpressionDiv(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class ExpressionIs : public Expression{
private:
    Expression * expression;
    variable_type checkedType;
public:
    ExpressionIs(Expression * expression, variable_type checkedType, const Position & position)
            : expression(expression), checkedType(checkedType) {this->position = position;}
    void accept(Visitor& visitor);

    Expression *getExpression() const {
        return expression;
    }

    variable_type getCheckedType() const {
        return checkedType;
    }
};

class ExpressionTo : public Expression {
private:
    Expression * expression;
    variable_type conversionType;
public:
    ExpressionTo(Expression * expression, variable_type conversionType, const Position & position)
            : expression(expression), conversionType(conversionType) {this->position = position;}
    void accept(Visitor& visitor);

    Expression *getExpression() const {
        return expression;
    }

    variable_type getConversionType() const {
        return conversionType;
    }
};

class ExpressionNeg : public Expression {
private:
    Expression * expression;
public:
    ExpressionNeg(Expression * expression, const Position & position)
            : expression(expression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getExpression() const {
        return expression;
    }
};

class ExpressionNegMinus : public Expression {
private:
    Expression * expression;
public:
    ExpressionNegMinus(Expression * expression, const Position & position)
            : expression(expression) {this->position = position;}
    void accept(Visitor& visitor);
    Expression *getExpression() const {
        return expression;
    }
};

class ExpressionValueList : public Expression {
private:
    std::vector<Expression *> expressions;
public:
    ExpressionValueList(std::vector<Expression *> expressions, const Position & position)
        : expressions(expressions) {this->position = position;};
    void accept(Visitor& visitor);

    std::vector<Expression *> &getExpressions() {
        return expressions;
    }
};

class ExpressionValuePoint : public Expression {
private:
    Expression * xCoord;
    Expression * yCoord;
public:
    ExpressionValuePoint(Expression * xCoord, Expression * yCoord, const Position & position)
    : xCoord(xCoord), yCoord(yCoord) {this->position = position;};
    void accept(Visitor& visitor);

    Expression *getXCoord() const {
        return xCoord;
    }

    Expression *getYCoord() const {
        return yCoord;
    }
};

class ExpressionValueLiteral : public Expression {
private:
    std::variant<int, double, std::wstring, bool, std::monostate> value;
public:
    template<typename T>
    ExpressionValueLiteral(T value, const Position & position) : value(value) {this->position = position;};
    void accept(Visitor& visitor);

    const std::variant<int, double, std::wstring, bool, std::monostate> &getValue() const {
        return value;
    }
};

class ExpressionValueBrackets : public Expression {
private:
    Expression * expression;
public:
    ExpressionValueBrackets(Expression * expression, const Position & position)
    : expression(expression) {this->position = position;};
    void accept(Visitor& visitor);

    Expression *getExpression() const {
        return expression;
    }
};

class ConditionAndBlock : public Visitable{
private:
    Expression * condition;
    CodeBlock * block;
public:
    ConditionAndBlock(Expression * condition, CodeBlock * block) : condition(condition), block(block) {};
    void accept(Visitor& visitor);

    Expression *getCondition() const {
        return condition;
    }

    CodeBlock *getBlock() const {
        return block;
    }

};

class WhileStatement : public Statement {
private:
    ConditionAndBlock * conditionAndBlock;
public:
    WhileStatement(ConditionAndBlock * conditionAndBlock, const Position & position) : conditionAndBlock(conditionAndBlock) {this->position = position;};
    void accept(Visitor& visitor);

    ConditionAndBlock *getConditionAndBlock() const {
        return conditionAndBlock;
    }
};

class IfStatement : public Statement {
private:
    ConditionAndBlock * ifConditionAndBlock;
    std::vector<ConditionAndBlock*> elsifConditionsAndBlocks;
    CodeBlock * elseCodeBlock;
public:
    IfStatement(ConditionAndBlock * ifConditionAndBlock, std::vector<ConditionAndBlock*> elsifConditionsAndBlocks, CodeBlock * elseCodeBlock, const Position & position)
            : ifConditionAndBlock(ifConditionAndBlock), elsifConditionsAndBlocks(elsifConditionsAndBlocks), elseCodeBlock(elseCodeBlock){ this->position = position;};
    void accept(Visitor& visitor);

    ConditionAndBlock *getIfConditionAndBlock() const {
        return ifConditionAndBlock;
    }

    std::vector<ConditionAndBlock *> &getElsifConditionsAndBlocks() {
        return elsifConditionsAndBlocks;
    }

    CodeBlock *getElseCodeBlock() const {
        return elseCodeBlock;
    }
};

class ForStatement : public Statement {
private:
    const std::wstring identifier;
    Expression * expression;
    CodeBlock * block;
public:
    ForStatement(const std::wstring & identifier, Expression * expression, CodeBlock * block, const Position & position) :
            identifier(identifier), expression(expression), block(block) {this->position = position;};
    void accept(Visitor& visitor);

    const std::wstring &getIdentifier() const {
        return identifier;
    }

    Expression *getExpression() const {
        return expression;
    }

    CodeBlock *getBlock() const {
        return block;
    }
};

class ForRangeStatement : public Statement {
private:
    const std::wstring identifier;
    Expression * leftExpression;
    Expression * rightExpression;
    CodeBlock * block;
public:
    ForRangeStatement(const std::wstring & identifier, Expression * leftExpression, Expression * rightExpression, CodeBlock * block, const Position & position) :
            identifier(identifier), leftExpression(leftExpression), rightExpression(rightExpression), block(block) {this->position = position;};
    void accept(Visitor& visitor);

    const std::wstring &getIdentifier() const {
        return identifier;
    }

    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }

    CodeBlock *getBlock() const {
        return block;
    }
};

class DeclarationStatement : public Statement {
private:
    const std::wstring identifierName;
    Expression * expression;
public:
    DeclarationStatement(const std::wstring & identifierName, Expression * expression, const Position & position) : identifierName(identifierName), expression(expression) {this->position=position;};
    void accept(Visitor& visitor);

    const std::wstring &getIdentifierName() const {
        return identifierName;
    }

    Expression *getExpression() const {
        return expression;
    }
};

class IdentifierExpression : public Expression {
private:
    const std::wstring identifierName;
public:
    IdentifierExpression(const std::wstring & identifierName, const Position & position)
            : identifierName(identifierName) {this->position=position;};
    void accept(Visitor& visitor);

    const std::wstring &getIdentifierName() const {
        return identifierName;
    }
};

class IdentifierFunctionCallExpression : public Expression {
private:
    Expression * identifierExpression;
    std::vector<Expression *> expressions;
public:
    IdentifierFunctionCallExpression(Expression * identifierExpression, std::vector<Expression *> expressions,
                                     const Position & position)
            : identifierExpression(identifierExpression), expressions(expressions) { this->position=position;};
    void accept(Visitor& visitor);

    Expression *getIdentifierExpression() const {
        return identifierExpression;
    }

    std::vector<Expression *> &getExpressions() {
        return expressions;
    }
};

class IdentifierListCallExpression : public Expression {
private:
    Expression * identifierExpression;
    std::vector<Expression *> expressions;
public:
    IdentifierListCallExpression(Expression * identifierExpression, std::vector<Expression *> expressions, const Position & position)
            : identifierExpression(identifierExpression), expressions(expressions) { this->position=position;};
    void accept(Visitor& visitor);

    Expression *getIdentifierExpression() const {
        return identifierExpression;
    }

    std::vector<Expression *> &getExpressions(){
        return expressions;
    }
};

class IdentifierDotExpression : public Expression {
private:
    Expression * leftExpression;
    Expression * rightExpression;
public:
    IdentifierDotExpression(Expression * leftExpression, Expression * rightExpression, const Position & position)
            : leftExpression(leftExpression), rightExpression(rightExpression) { this->position=position;};
    void accept(Visitor& visitor);

    Expression *getLeftExpression() const {
        return leftExpression;
    }

    Expression *getRightExpression() const {
        return rightExpression;
    }
};

class IdentifierStatementAssign : public Statement {//osobne identifierstatemewnt z expression
private:
    Expression * identifierExpression;
    Expression * expression;
public:
    IdentifierStatementAssign(Expression * identifierExpression, Expression * expression, const Position & position)
            : identifierExpression(identifierExpression), expression(expression) { this->position=position;};
    void accept(Visitor& visitor);

    Expression *getIdentifierExpression() const {
        return identifierExpression;
    }

    Expression *getExpression() const {
        return expression;
    }
};

class ReturnStatement : public Statement {
private:
    Expression * expression;
public:
    ReturnStatement(Expression * expression, const Position & position) : expression(expression) {this->position=position;};
    void accept(Visitor& visitor);

    Expression *getExpression() const {
        return expression;
    }
};


class CodeBlock : public Visitable {
private:
    std::vector<Statement*> statements;
public:
    CodeBlock(const std::vector<Statement*> statements) : statements(statements) {}

    CodeBlock() {}

    std::vector<Statement *> &getStatements() {
        return statements;
    }

    void accept(Visitor& visitor);
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
    void accept(Visitor& visitor);
};

class FigureParameter : public Parameter {
private:
    Expression* value;
public:
    FigureParameter(const std::wstring & name, Expression * value) : value(value) {this->name = name;};
    void accept(Visitor& visitor);

    Expression *getValue() const {
        return value;
    }
};

class FuncDeclaration : public Visitable{
private:
    std::wstring name;
    std::vector<Parameter *> params;
    CodeBlock * codeBlock;
public:

    FuncDeclaration(const std::wstring &name, std::vector<Parameter *> params, CodeBlock * codeBlock, const Position & position) : name(
            name), params(params), codeBlock(codeBlock) {this->position = position;}

    FuncDeclaration() {}

    std::wstring getName(){
        return name;
    }
    void accept(Visitor& visitor);

    const std::vector<Parameter *> &getParams() const {
        return params;
    }

    CodeBlock *getCodeBlock() const {
        return codeBlock;
    }
};

class FigureDeclaration : public Visitable {
private:
    std::wstring name;
    std::vector<Parameter *> params;
public:
    FigureDeclaration(const std::wstring &name, std::vector<Parameter *> params, const Position & position) : name(
            name), params(params)  {this->position = position;}

    FigureDeclaration() {}

    const std::wstring &getName() const {
        return name;
    }
    void accept(Visitor& visitor);

    std::vector<Parameter *> &getParams() {
        return params;
    }

};

class Program : public Visitable {
private:
    std::unordered_map<std::wstring, FuncDeclaration *> functions;
    std::unordered_map<std::wstring, FigureDeclaration *> figures;
public:
    Program(std::unordered_map<std::wstring, FuncDeclaration*> functions, std::unordered_map<std::wstring, FigureDeclaration *> figures) : functions(functions), figures(figures) {}

    Program() {}
    void accept(Visitor& visitor);

    std::unordered_map<std::wstring, FuncDeclaration *> &getFunctions() {
        return functions;
    }

    std::unordered_map<std::wstring, FigureDeclaration *> &getFigures() {
        return figures;
    }
};


#endif //LEXER_PROGRAM_H
