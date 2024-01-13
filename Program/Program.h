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
#include <unordered_set>
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

class ObjectAccessExpression;
class IdentifierStatementAssign;
class IdentifierListIndexExpression;
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
    LIST_VARIABLE,
    FIGURE_VARIABLE
};

static const std::unordered_map<short int, std::wstring> variable_type_representation= {
        {STRING_VARIABLE,   L"string"},
        {INT_VARIABLE,      L"int"},
        {DOUBLE_VARIABLE,   L"double"},
        {BOOL_VARIABLE,     L"bool"},
        {NONE_VARIABLE,     L"none"},
        {FIGURE_VARIABLE,   L"figure"},
        {POINT_VARIABLE,    L"point"},
        {LIST_VARIABLE,     L"list"},
};

static const std::unordered_set<std::wstring> special_keywords = {
        L"Circle",
        L"circ",
        L"area",
        L"scale",
        L"rotate",
        L"transport",
        L"copy",
        L"color",
        L"len",
        L"append",
        L"delete",
        L"print",
        L"input",
        L"draw"
};

static const std::unordered_set<std::wstring> special_list_keywords = {
        L"len",
        L"append",
        L"delete",
};

static const std::unordered_set<std::wstring> special_figure_keywords = {
        L"circ",
        L"area",
        L"scale",
        L"rotate",
        L"transport",
        L"copy",
        L"color",
};

static const std::unordered_set<std::wstring> special_function_keywords = {
        L"Circle",
        L"print",
        L"input",
        L"draw"
};

template<typename T>
bool operator==(const std::vector<std::unique_ptr<T>> &v1, const std::vector<std::unique_ptr<T>> &v2) {
    if (v1.size() != v2.size()){
        return false;
    }
    for (int i=0; i<v1.size(); i++) {
        if (*(v1[i]) != *(v2[i])) {
            return false;
        }
    }
    return true;
}

template<typename T>
bool operator!=(const std::vector<std::unique_ptr<T>> &v1, const std::vector<std::unique_ptr<T>> &v2) {
    return !(v1 == v2);
}

class Visitable {
public:
    virtual void accept(Visitor& visitor) = 0;
    virtual ~Visitable() = default;
    Position position;
};

class Statement : public Visitable {
public:
    virtual ~Statement() = default;
    virtual bool isEqual(const Statement* obj) const=0;
};

class Expression : public Visitable {
public:
    virtual ~Expression() = default;
    virtual bool isEqual(const Expression* obj) const=0;
};


class CodeBlock : public Visitable {
public:
    std::vector<std::unique_ptr<Statement>> statements;
    explicit CodeBlock(std::vector<std::unique_ptr<Statement>> statements, const Position & position) : statements(std::move(statements)) {this->position = position;}

    CodeBlock() {}
    CodeBlock(const CodeBlock&) =delete;
    CodeBlock& operator=(const CodeBlock&) =delete;
    CodeBlock(CodeBlock&&) =default;
    CodeBlock& operator=(CodeBlock&&) =default;
//    ~CodeBlock()=default;

    void accept(Visitor& visitor);

};

bool operator==(const CodeBlock& lhs, const CodeBlock& rhs);
bool operator!=(const CodeBlock& lhs, const CodeBlock& rhs);

extern bool operator==(const Expression& lhs, const Expression& rhs);

extern bool operator!=(const Expression& lhs, const Expression& rhs);

bool operator==(const Statement& lhs, const Statement& rhs);

bool operator!=(const Statement& lhs, const Statement& rhs);

class ExpressionOr : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionOr(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
        : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionOr*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionAnd : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionAnd(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionAnd*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompEq : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompEq(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompEq*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompNeq : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompNeq(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompNeq*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompGeq : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompGeq(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompGeq*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompLeq : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompLeq(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompLeq*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompGreater : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompGreater(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompGreater*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionCompLess : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionCompLess(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionCompLess*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionAdd : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionAdd(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionAdd*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionSub : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionSub(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionSub*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionMul : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionMul(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionMul*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionDiv : public Expression{
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ExpressionDiv(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionDiv*>(comparedExpression);
        return *leftExpression == *(expr->leftExpression) && *rightExpression == *(expr->rightExpression);
    }
};

class ExpressionIs : public Expression{
public:
    std::unique_ptr<Expression> expression;
    variable_type checkedType;
    ExpressionIs(std::unique_ptr<Expression> expression, variable_type checkedType, const Position & position)
            : expression(std::move(expression)), checkedType(checkedType) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionIs*>(comparedExpression);
        return *expression == *(expr->expression) && checkedType == (expr->checkedType);
    }
};

class ExpressionTo : public Expression {
public:
    std::unique_ptr<Expression> expression;
    variable_type conversionType;
    ExpressionTo(std::unique_ptr<Expression> expression, variable_type conversionType, const Position & position)
            : expression(std::move(expression)), conversionType(conversionType) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionTo*>(comparedExpression);
        return *expression == *(expr->expression) && conversionType == (expr->conversionType);
    }
};

class ExpressionNeg : public Expression {
public:
    std::unique_ptr<Expression> expression;
    ExpressionNeg(std::unique_ptr<Expression> expression, const Position & position)
            : expression(std::move(expression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionNeg*>(comparedExpression);
        return *expression == *(expr->expression);
    }
};

class ExpressionNegMinus : public Expression {
public:
    std::unique_ptr<Expression> expression;
    ExpressionNegMinus(std::unique_ptr<Expression> expression, const Position & position)
            : expression(std::move(expression)) {this->position = position;}
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionNegMinus*>(comparedExpression);
        return *expression == *(expr->expression);
    }
};

class ExpressionValueList : public Expression {
public:
    std::vector<std::unique_ptr<Expression>> expressions;
    ExpressionValueList(std::vector<std::unique_ptr<Expression>> expressions, const Position & position)
        : expressions(std::move(expressions)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionValueList*>(comparedExpression);
        return expressions == expr->expressions;
    }
};

class ExpressionValuePoint : public Expression {
public:
    std::unique_ptr<Expression> xCoord;
    std::unique_ptr<Expression> yCoord;
    ExpressionValuePoint(std::unique_ptr<Expression> xCoord, std::unique_ptr<Expression> yCoord, const Position & position)
    : xCoord(std::move(xCoord)), yCoord(std::move(yCoord)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionValuePoint*>(comparedExpression);
        return *(xCoord) == *(expr->xCoord) && *(yCoord) == *(expr->yCoord);
    }
};

class ExpressionValueLiteral : public Expression {
public:
    std::variant<int, double, std::wstring, bool, std::monostate> value;
    template<typename T>
    ExpressionValueLiteral(T value, const Position & position) : value(value) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionValueLiteral*>(comparedExpression);
        return value == expr->value;
    }
};

class ExpressionValueBrackets : public Expression {
public:
    std::unique_ptr<Expression> expression;
    ExpressionValueBrackets(std::unique_ptr<Expression> expression, const Position & position)
    : expression(std::move(expression)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ExpressionValueBrackets*>(comparedExpression);
        return *(expression) == *(expr->expression);
    }
};

class ConditionAndBlock : public Visitable{
public:
    std::unique_ptr<Expression> condition;
    std::unique_ptr<CodeBlock> block;
    ConditionAndBlock(std::unique_ptr<Expression> condition, std::unique_ptr<CodeBlock> block) : condition(std::move(condition)), block(std::move(block)) {};
    void accept(Visitor& visitor);
    bool operator==(const ConditionAndBlock & rhs) {
        return *(condition) == *(rhs.condition) && *(block) == *(rhs.block);
    }
    bool operator!=(const ConditionAndBlock & rhs) {
        return !(*this == rhs);
    }
};

class WhileStatement : public Statement {
public:
    std::unique_ptr<ConditionAndBlock> conditionAndBlock;
    WhileStatement(std::unique_ptr<ConditionAndBlock> conditionAndBlock, const Position & position) : conditionAndBlock(std::move(conditionAndBlock)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const WhileStatement*>(comparedExpression);
        return *(conditionAndBlock) == *(stmnt->conditionAndBlock);
    }
};

class IfStatement : public Statement {
public:
    std::unique_ptr<ConditionAndBlock> ifConditionAndBlock;
    std::vector<std::unique_ptr<ConditionAndBlock>> elsifConditionsAndBlocks;
    std::unique_ptr<CodeBlock> elseCodeBlock;
    IfStatement(std::unique_ptr<ConditionAndBlock> ifConditionAndBlock, std::vector<std::unique_ptr<ConditionAndBlock>> elsifConditionsAndBlocks, std::unique_ptr<CodeBlock> elseCodeBlock, const Position & position)
            : ifConditionAndBlock(std::move(ifConditionAndBlock)), elsifConditionsAndBlocks(std::move(elsifConditionsAndBlocks)), elseCodeBlock(std::move(elseCodeBlock)){ this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
            auto stmnt = dynamic_cast<const IfStatement*>(comparedExpression);
            if (*(ifConditionAndBlock) != *(stmnt->ifConditionAndBlock)) {
                return false;
            }
            if (elsifConditionsAndBlocks != stmnt->elsifConditionsAndBlocks) {
                return false;
            }
            if ((elseCodeBlock == nullptr || stmnt->elseCodeBlock == nullptr) && (elseCodeBlock.get() != stmnt->elseCodeBlock.get())){
                return false;
            }
            if (*(elseCodeBlock) != *(stmnt->elseCodeBlock)) {
                return false;
            }
            return true;
    }
};

class ForStatement : public Statement {
public:
    const std::wstring identifier;
    std::unique_ptr<Expression> expression;
    std::unique_ptr<CodeBlock> block;
    ForStatement(const std::wstring & identifier, std::unique_ptr<Expression> expression, std::unique_ptr<CodeBlock> block, const Position & position) :
            identifier(identifier), expression(std::move(expression)), block(std::move(block)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const ForStatement*>(comparedExpression);
        return identifier == stmnt->identifier && *(expression) == *(stmnt->expression) && *(block) == *(stmnt->block);
    }
};

class ForRangeStatement : public Statement {
public:
    const std::wstring identifier;
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    std::unique_ptr<CodeBlock> block;
    ForRangeStatement(const std::wstring & identifier, std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, std::unique_ptr<CodeBlock> block, const Position & position) :
            identifier(identifier), leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)), block(std::move(block)) {this->position = position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const ForRangeStatement*>(comparedExpression);
        return identifier == stmnt->identifier && *(leftExpression) == *(stmnt->leftExpression) && *(rightExpression) == *(stmnt->rightExpression) &&
            *(block) == *(stmnt->block);
    }

};

class DeclarationStatement : public Statement {
public:
    const std::wstring identifierName;
    DeclarationStatement(const std::wstring & identifierName, const Position & position) : identifierName(identifierName) {this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const DeclarationStatement*>(comparedExpression);
        return identifierName == stmnt->identifierName;
    }
};

class DeclarationAssignStatement : public Statement {
public:
    const std::wstring identifierName;
    std::unique_ptr<Expression> expression;
    DeclarationAssignStatement(const std::wstring & identifierName, std::unique_ptr<Expression> expression, const Position & position) : identifierName(identifierName), expression(std::move(expression)) {this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const DeclarationAssignStatement*>(comparedExpression);
        return identifierName == stmnt->identifierName && *(expression) == *(stmnt->expression);
    }
};

class IdentifierExpression : public Expression {
public:
    const std::wstring identifierName;
    IdentifierExpression(const std::wstring & identifierName, const Position & position)
            : identifierName(identifierName) {this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const IdentifierExpression*>(comparedExpression);
        return identifierName == expr->identifierName;
    }
};

class IdentifierFunctionCallExpression : public Expression {
public:
    std::unique_ptr<Expression> identifierExpression;
    std::vector<std::unique_ptr<Expression>> expressions;
    IdentifierFunctionCallExpression(std::unique_ptr<Expression> identifierExpression, std::vector<std::unique_ptr<Expression>> expressions,
                                     const Position & position)
            : identifierExpression(std::move(identifierExpression)), expressions(std::move(expressions)) { this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const IdentifierFunctionCallExpression*>(comparedExpression);
        return *(identifierExpression) == *(expr->identifierExpression) && expressions == expr->expressions;
    }
};

class IdentifierListIndexExpression : public Expression {
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> indexExpression;
    IdentifierListIndexExpression(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> indexExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), indexExpression(std::move(indexExpression)) { this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const IdentifierListIndexExpression*>(comparedExpression);
        return *(leftExpression) == *(expr->leftExpression) && *(indexExpression) == *(expr->indexExpression);
    }
};

class ObjectAccessExpression : public Expression {
public:
    std::unique_ptr<Expression> leftExpression;
    std::unique_ptr<Expression> rightExpression;
    ObjectAccessExpression(std::unique_ptr<Expression> leftExpression, std::unique_ptr<Expression> rightExpression, const Position & position)
            : leftExpression(std::move(leftExpression)), rightExpression(std::move(rightExpression)) { this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Expression* comparedExpression) const override {
        auto expr = dynamic_cast<const ObjectAccessExpression*>(comparedExpression);
        return *(leftExpression) == *(expr->leftExpression) && *(rightExpression) == *(expr->rightExpression);
    }
};

class IdentifierStatementAssign : public Statement {
public:
    std::unique_ptr<Expression> identifierExpression;
    std::unique_ptr<Expression> expression;
    IdentifierStatementAssign(std::unique_ptr<Expression> identifierExpression, std::unique_ptr<Expression> expression, const Position & position)
            : identifierExpression(std::move(identifierExpression)), expression(std::move(expression)) { this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const IdentifierStatementAssign*>(comparedExpression);
        return *(identifierExpression) == *(stmnt->identifierExpression) && *(expression) == *(stmnt->expression);
    }
};

class IdentifierExpressionStatement : public Statement {
public:
    std::unique_ptr<Expression> identifierExpression;
    IdentifierExpressionStatement(std::unique_ptr<Expression> identifierExpression, const Position & position) : identifierExpression(std::move(identifierExpression))
    {
        this->position=position;
    };
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const IdentifierExpressionStatement*>(comparedExpression);
        return *(identifierExpression) == *(stmnt->identifierExpression);
    }

};

class ReturnStatement : public Statement {
public:
    std::unique_ptr<Expression> expression;
    ReturnStatement(std::unique_ptr<Expression> expression, const Position & position) : expression(std::move(expression)){this->position=position;};
    void accept(Visitor& visitor);
    virtual bool isEqual(const Statement* comparedExpression) const override {
        auto stmnt = dynamic_cast<const ReturnStatement*>(comparedExpression);
        return *(expression) == *(stmnt->expression);
    }
};


class Parameter : public Visitable {
public:
    std::wstring name;
    Parameter(const std::wstring &name, const Position & position) : name(name) {this->position = position;}
    Parameter() {}
    virtual ~Parameter() =default;

    const std::wstring &getName() const {
        return name;
    }
    void accept(Visitor& visitor);
    bool operator==(const Parameter & rhs) {
        return name == rhs.name;
    }
    virtual bool isEqual(const Parameter* comparedParameter) const {
        auto param = dynamic_cast<const Parameter*>(comparedParameter);
        return name == param->name;
    };
};



class FigureParameter : public Parameter {
public:
    std::unique_ptr<Expression> valueExpression;
    FigureParameter(const std::wstring & name, std::unique_ptr<Expression> valueExpression, const Position & position) : valueExpression(std::move(valueExpression)) {this->name = name; this->position=position;};
    void accept(Visitor& visitor);

    virtual bool isEqual(const Parameter* comparedParameter) const override {
        auto param = dynamic_cast<const FigureParameter*>(comparedParameter);
        return name == param->name && *(valueExpression) == *(param->valueExpression);
    };
};

bool operator==(const Parameter& lhs, const Parameter& rhs);

bool operator!=(const Parameter& lhs, const Parameter& rhs);

class FuncDeclaration : public Visitable{
public:
    std::wstring name;
    std::vector<std::unique_ptr<Parameter>> params;
    std::unique_ptr<CodeBlock> codeBlock;

    FuncDeclaration(const std::wstring &name, std::vector<std::unique_ptr<Parameter>> params, std::unique_ptr<CodeBlock> codeBlock, const Position & position) : name(
            name), params(std::move(params)), codeBlock(std::move(codeBlock)) {this->position = position;}

    FuncDeclaration() {}

    void accept(Visitor& visitor);

};

bool operator==(const FuncDeclaration & lhs, const FuncDeclaration & rhs);
bool operator!=(const FuncDeclaration & lhs, const FuncDeclaration & rhs);

class FigureDeclaration : public Visitable {
public:
    std::wstring name;
    std::vector<std::unique_ptr<Parameter>> params;
    FigureDeclaration(const std::wstring &name, std::vector<std::unique_ptr<Parameter>> params, const Position & position) : name(
            name), params(std::move(params))  {this->position = position;}

    FigureDeclaration() {}

    void accept(Visitor& visitor);
    bool operator==(const FigureDeclaration & rhs) const {
        return name == rhs.name && params == rhs.params;
    }
    bool operator!=(const FigureDeclaration & rhs) const {
        return !(*this == rhs);
    }
};

class Program : public Visitable {
public:
    std::unordered_map<std::wstring, std::unique_ptr<FuncDeclaration>> functions;
    std::unordered_map<std::wstring, std::unique_ptr<FigureDeclaration>> figures;
    Program(std::unordered_map<std::wstring, std::unique_ptr<FuncDeclaration>> functions, std::unordered_map<std::wstring, std::unique_ptr<FigureDeclaration>> figures):
        functions(std::move(functions)), figures(std::move(figures)){}

    Program() {}
    void accept(Visitor& visitor);
    std::unordered_map<std::wstring, FuncDeclaration *> getFuncDeclarations() const{
        std::unordered_map<std::wstring, FuncDeclaration *> functionDeclarations;
        for(auto & func : this->functions) {
            functionDeclarations[func.first] = func.second.get();
        }
        return functionDeclarations;
    };

    std::unordered_map<std::wstring, FigureDeclaration *> getFigureDeclarations() const {
        std::unordered_map<std::wstring, FigureDeclaration *> figureDeclarations;
        for(auto & figure : this->figures) {
            figureDeclarations[figure.first] = figure.second.get();
        }
        return figureDeclarations;
    };

    bool operator==(const Program & rhs) {
        auto functions = getFuncDeclarations();
        auto figures = getFigureDeclarations();
        auto functions_rhs = rhs.getFuncDeclarations();
        auto figures_rhs = rhs.getFigureDeclarations();
        if (functions.size() != functions_rhs.size()){
            return false;
        }
        for (auto & element : functions) {
            auto index = functions_rhs.find(element.first);
            if (index == functions_rhs.end() || *(index->second) != *(element.second)) {
                return false;
            }
        }
        if (figures.size() != figures_rhs.size()){
            return false;
        }
        for (auto & element : figures) {
            auto index = figures_rhs.find(element.first);
            if (index == figures_rhs.end() || *(index->second) != *(element.second)) {
                return false;
            }
        }
        return true;
    }
    bool operator!=(const Program & rhs) {
        return !(*this == rhs);
    }

};

bool operator==(const Parameter &lhs, const Parameter &rhs);
bool operator!=(const Parameter &lhs, const Parameter &rhs);




#endif //LEXER_PROGRAM_H
