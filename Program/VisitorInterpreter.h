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
    std::unique_ptr<Value> setType(IntValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(DoubleValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(StringValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(BoolValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(PointValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(NoneValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(ListValue * value, variable_type & vt);
    std::unique_ptr<Value> setType(FigureValue * value, variable_type & vt);
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
    virtual variable_type getType(ValueVisitor & vv)=0;
    virtual void setType(ValueVisitor & vv, variable_type & vt)=0;
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
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    void setValue(int & toSet) {this->value=toSet;};
    int getValue() {return value;}
};
class DoubleValue : public Value {
private:
    double value;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    void setValue(double & toSet) {this->value=toSet;};
    double getValue() {return value;}
};
class StringValue : public Value {
private:
    std::wstring value;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    void setValue(std::wstring & toSet) {this->value=toSet;};
    std::wstring getValue() {return value;}
};
class BoolValue : public Value {
private:
    bool value;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    void setValue(bool & toSet) {this->value=toSet;};
    bool getValue() {return value;}
};
class PointValue : public Value {
private:
    double x;
    double y;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    void setValue(std::pair<double, double> & toSet) {this->x=toSet.first;this->y=toSet.second;};
    std::pair<double, double> getValue() {return std::pair<double, double>(x, y);}
};
class NoneValue : public Value {
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
};

class ListValue : public Value, public std::enable_shared_from_this<ListValue> {
private:
    std::vector<std::variant<std::unique_ptr<Value>, std::shared_ptr<Value>>> values;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    std::shared_ptr<ListValue> getValue() {return shared_from_this();}
};
class FigureValue : public Value, public std::enable_shared_from_this<FigureValue> {
private:
    std::vector<Variable> values;
public:
    variable_type getType(ValueVisitor & vv) {return vv.getType(this);};
    void setType(ValueVisitor & vv, variable_type & vt) {vv.setType(this, vt);};
    value_type getValue(ValueVisitor & vv) {return vv.getValue(this);};
    void setValue(ValueVisitor & vv, value_type & toSet) {vv.setValue(this, toSet);};
    std::shared_ptr<FigureValue> getValue() {return shared_from_this();}
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
