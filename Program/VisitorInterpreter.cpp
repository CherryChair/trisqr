//
// Created by mpkow on 14.12.2023.
//

#include "VisitorInterpreter.h"

std::unique_ptr<Value> ValueVisitor::setType(IntValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(DoubleValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(StringValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(BoolValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(PointValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(NoneValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(ListValue * value, variable_type & vt){

}
std::unique_ptr<Value> ValueVisitor::setType(FigureValue * value, variable_type & vt){

}
variable_type ValueVisitor::getType(IntValue * value){
    return INT_VARIABLE;
}
variable_type ValueVisitor::getType(DoubleValue * value){
    return DOUBLE_VARIABLE;
}
variable_type ValueVisitor::getType(StringValue * value){
    return STRING_VARIABLE;
}
variable_type ValueVisitor::getType(BoolValue * value){
    return BOOL_VARIABLE;
}
variable_type ValueVisitor::getType(PointValue * value){
    return POINT_VARIABLE;
}
variable_type ValueVisitor::getType(NoneValue * value){
    return NONE_VARIABLE;
}
variable_type ValueVisitor::getType(ListValue * value){

}
variable_type ValueVisitor::getType(FigureValue * value){

}
void ValueVisitor::setValue(IntValue * value, value_type & toSet){
    if (std::holds_alternative<int>(toSet)) {
        value->setValue(std::get<int>(toSet));
    } else {
        //errorHandler
        throw;
    }
}
void ValueVisitor::setValue(DoubleValue * value, value_type & toSet){
    if (std::holds_alternative<double>(toSet)) {
        value->setValue(std::get<double>(toSet));
    } else {
        //errorHandler
        throw;
    }
}
void ValueVisitor::setValue(StringValue * value, value_type & toSet){
    if (std::holds_alternative<std::wstring>(toSet)) {
        value->setValue(std::get<std::wstring>(toSet));
    } else {
        //errorHandler
        throw;
    }
}
void ValueVisitor::setValue(BoolValue * value, value_type & toSet){
    if (std::holds_alternative<bool>(toSet)) {
        value->setValue(std::get<bool>(toSet));
    } else {
        //errorHandler
        throw;
    }
}
void ValueVisitor::setValue(PointValue * value, value_type & toSet){
    if (std::holds_alternative<std::pair<double, double>>(toSet)) {
        value->setValue(std::get<std::pair<double, double>>(toSet));
    } else {
        //errorHandler
        throw;
    }
}
void ValueVisitor::setValue(NoneValue * value, value_type & toSet){
    throw;
}
void ValueVisitor::setValue(ListValue * value, value_type & toSet){
    throw;
}
void ValueVisitor::setValue(FigureValue * value, value_type & toSet){
    throw;
}
value_type ValueVisitor::getValue(IntValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(DoubleValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(StringValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(BoolValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(PointValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(NoneValue * value){
    return std::monostate();
}
value_type ValueVisitor::getValue(ListValue * value){
    return value->getValue();
}
value_type ValueVisitor::getValue(FigureValue * value){
    return value->getValue();
}



void VisitorInterpreter::visit(ExpressionOr * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionAnd * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompEq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompNeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompLeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompGeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompGreater * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionCompLess * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionAdd * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionSub * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionMul * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionDiv * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionIs * e) {
    e->expression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionTo * e) {
    e->expression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionNeg * e) {
    e->expression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionNegMinus * e) {
    e->expression->accept(*this);
}
void VisitorInterpreter::visit(ExpressionValueList * e) {
    for (auto const & expression : e->expressions) {
        expression->accept(*this);
    }
}
void VisitorInterpreter::visit(ExpressionValuePoint * e) {
    e->xCoord->accept(*this);

    e->yCoord->accept(*this);
}
void VisitorInterpreter::visit(ExpressionValueLiteral * e) {
    switch (e->value.index()){
        case 0: {
            int value = std::get<int>(e->value);
            break;
        }
        case 1: {
            double value = std::get<double>(e->value);
            break;
        }
        case 2: {
            std::wstring value = std::get<std::wstring>(e->value);
            break;
        }
        case 3: {
            bool value = std::get<bool>(e->value);
            break;
        }
        case 4: {
        }
    }
//    std::visit([](auto & x) -> void {std::wcout << x;}, e->value);
}
void VisitorInterpreter::visit(ExpressionValueBrackets * e) {
    e->expression->accept(*this);
}





void VisitorInterpreter::visit(WhileStatement * s) {
    s->conditionAndBlock->accept(*this);
}
void VisitorInterpreter::visit(IfStatement * s) {
    s->ifConditionAndBlock->accept(*this);
    for (auto const & condAndBlock : s->elsifConditionsAndBlocks) {
        condAndBlock->accept(*this);
    }

    if (auto & elseCodeBlock = s->elseCodeBlock) {
        elseCodeBlock->accept(*this);
    } else {
    }
}
void VisitorInterpreter::visit(ForStatement * s) {
    s->expression->accept(*this);
    s->block->accept(*this);
}
void VisitorInterpreter::visit(ForRangeStatement * s) {
    s->leftExpression->accept(*this);
    s->rightExpression->accept(*this);
    s->block->accept(*this);
}
void VisitorInterpreter::visit(DeclarationStatement * s) {
}

void VisitorInterpreter::visit(DeclarationAssignStatement * s) {
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}

void VisitorInterpreter::visit(ReturnStatement * s) {
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}

void VisitorInterpreter::visit(ConditionAndBlock * cb) {
    cb->condition->accept(*this);

    cb->condition->accept(*this);
}

void VisitorInterpreter::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
}
void VisitorInterpreter::visit(IdentifierStatementAssign * s) {
    s->identifierExpression->accept(*this);

    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}
void VisitorInterpreter::visit(ObjectAccessExpression * s) {
    s->leftExpression->accept(*this);

    if (auto & rightStatement = s->rightExpression) {
        rightStatement->accept(*this);
    } else {
    }
}
void VisitorInterpreter::visit(IdentifierListIndexExpression * s) {
    s->leftExpression->accept(*this);

    auto & expression = s->indexExpression;
    expression->accept(*this);
}
void VisitorInterpreter::visit(IdentifierFunctionCallExpression * s) {
    s->identifierExpression->accept(*this);

    for (auto const & expression : s->expressions) {
        expression->accept(*this);
    }
}
void VisitorInterpreter::visit(IdentifierExpression * s) {

}




void VisitorInterpreter::visit(CodeBlock * cb) {
    for (auto const & statement : cb->statements) {
        statement->accept(*this);
    }
}

void VisitorInterpreter::visit(Parameter * p) {
}

void VisitorInterpreter::visit(FigureParameter * p) {
    p->valueExpression->accept(*this);
}
void VisitorInterpreter::visit(FigureDeclaration * fd) {
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
}
void VisitorInterpreter::visit(FuncDeclaration * fd) {
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
}
void VisitorInterpreter::visit(Program * p) {
    for(auto const & figure: p->figures) {
        figure.second->accept(*this);
    }
    for(auto const & function: p->functions) {
        function.second->accept(*this);
    }
}
