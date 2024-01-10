//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORINTERPTER_H
#define LEXER_VISITORINTERPTER_H

#include "Visitor.h"

//figura i punkt
class FunctionCallContext;

class Scope;

class Variable;

class Value;

//class NonMutableValue;
class IntValue;
class DoubleValue;
class StringValue;
class BoolValue;
class PointValue;
class NoneValue;

//class MutableValue;
class ListValue;
class FigureValue;

using value_type = std::variant<int, double, std::wstring, bool, std::monostate, std::pair<double, double>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;


struct ValueVisitor {
    Value * operator()(std::unique_ptr<Value> & value) {return value.get();};
    Value * operator()(std::shared_ptr<Value> & value) {return value.get();};
    void visit(IntValue * value);
    void visit(DoubleValue * value);
    void visit(StringValue * value);
    void visit(BoolValue * value);
    void visit(PointValue * value);
    void visit(NoneValue * value);
    void visitMutable(ListValue * value);
    void visitMutable(FigureValue * value);
    void setType(IntValue * value, variable_type & vt);
    void setType(DoubleValue * value, variable_type & vt);
    void setType(StringValue * value, variable_type & vt);
    void setType(BoolValue * value, variable_type & vt);
    void setType(PointValue * value, variable_type & vt);
    void setType(NoneValue * value, variable_type & vt);
    void setType(ListValue * value, variable_type & vt);
    void setType(FigureValue * value, variable_type & vt);
    variable_type getType(IntValue * value);
    variable_type getType(DoubleValue * value);
    variable_type getType(StringValue * value);
    variable_type getType(BoolValue * value);
    variable_type getType(PointValue * value);
    variable_type getType(NoneValue * value);
    variable_type getType(ListValue * value);
    variable_type getType(FigureValue * value);
    void setValue(IntValue * value, value_type & toSet);
    void setValue(DoubleValue * value, value_type & toSet);
    void setValue(StringValue * value, value_type & toSet);
    void setValue(BoolValue * value, value_type & toSet);
    void setValue(PointValue * value, value_type & toSet);
    void setValue(NoneValue * value, value_type & toSet);
    void setValue(ListValue * value, value_type & toSet);
    void setValue(FigureValue * value, value_type & toSet);
    value_type getValue(IntValue * value);
    value_type getValue(DoubleValue * value);
    value_type getValue(StringValue * value);
    value_type getValue(BoolValue * value);
    value_type getValue(PointValue * value);
    value_type getValue(NoneValue * value);
    value_type getValue(ListValue * value);
    value_type getValue(FigureValue * value);
};

class Value {
public:
    virtual ~Value()=default;
    virtual void accept(ValueVisitor & vv)=0;
    virtual variable_type getType(ValueVisitor & vv)=0;
    virtual variable_type setType(ValueVisitor & vv, variable_type & vt)=0;
    virtual value_type getValue(ValueVisitor & vv)=0;
    virtual void setValue(ValueVisitor & vv, value_type & toSet)=0;
};

class Variable {
private:
    const std::wstring name;
    std::variant<std::unique_ptr<Value>, std::shared_ptr<Value>> value;
public:
    Value * getValue() {
        return std::visit(ValueVisitor{}, value);
    }
    void setValue(std::variant<std::unique_ptr<Value>, std::shared_ptr<Value>> & value) {
        this->value = std::move(value);
    }
};

class IntValue : public Value  {
private:
    int value;
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};
class DoubleValue : public Value {
private:
    double value;
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};
class StringValue : public Value {
private:
    std::wstring value;
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};
class BoolValue : public Value {
private:
    bool value;
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};
class PointValue : public Value {
private:
    double x;
    double y;
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};
class NoneValue : public Value {
public:
    void accept(ValueVisitor & vv) {vv.visit(this);}
};

class ListValue : public Value {
private:
    std::vector<std::variant<std::unique_ptr<Value>, std::shared_ptr<Value>>> values;
public:
    void accept(ValueVisitor & vv) {vv.visitMutable(this);}
};
class FigureValue : public Value {
private:
    std::vector<Variable> values;
public:
    void accept(ValueVisitor & vv) {vv.visitMutable(this);}
};

class VisitorInterpreter : public Visitor {
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

#endif //LEXER_VISITORINTERPTER_H
