//
// Created by mpkow on 14.12.2023.
//

#include "VisitorInterpreter.h"

void VisitorInterpreter::visit(ExpressionOr * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<bool>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression on left to 'or' evaluated to non boolean.");
    }
    if(std::get<bool>(leftExpressionValue)) {
        this->lastResult = true;
    }
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<bool>(rightExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression right to 'or' evaluated to non boolean.");
    }
    if(std::get<bool>(rightExpressionValue)) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionAnd * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<bool>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression left to 'and' evaluated to non boolean.");
    }
    if(!std::get<bool>(leftExpressionValue)) {
        this->lastResult = false;
        return;
    }
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<bool>(rightExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression right to 'and' evaluated to non boolean.");
    }
    if(!std::get<bool>(rightExpressionValue)) {
        this->lastResult = false;
    } else {
        this->lastResult = true;
    }
}
void VisitorInterpreter::visit(ExpressionCompEq * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    if (leftExpressionValue == rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}

void VisitorInterpreter::visit(ExpressionCompNeq * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    if (leftExpressionValue != rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionCompLeq * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInComparisonVisitor(), L"comparison");
    if (leftExpressionValue <= rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionCompGeq * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInComparisonVisitor(), L"comparison");
    if (leftExpressionValue >= rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionCompGreater * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInComparisonVisitor(), L"comparison");
    if (leftExpressionValue > rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionCompLess * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInComparisonVisitor(), L"comparison");
    if (leftExpressionValue < rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionAdd * e) {

    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Addition");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInAdditionVisitor(), L"addition");
    this->lastResult = leftExpressionValue + rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionSub * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Subtraction");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInSubtractionVisitor(), L"subtraction");
    this->lastResult = leftExpressionValue - rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionMul * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Multiplication");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInMultiplicationVisitor(), L"multiplication");
    this->lastResult = leftExpressionValue * rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionDiv * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    e->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Division");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInDivisionVisitor(), L"division");
    this->lastResult = leftExpressionValue / rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionIs * e) {
    e->expression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    bool typesMatch = std::visit(TypeMatchVisitor(e->checkedType), expressionValue);
    this->lastResult = typesMatch;
}
void VisitorInterpreter::visit(ExpressionTo * e) {
    e->expression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    variable_type conversionType = e->conversionType;
    interpeter_value conversedValue = std::visit(ConversionVisitor(conversionType), expressionValue);
    if (std::holds_alternative<std::monostate>(conversedValue)) {
        this->handleRuntimeError(e->position, L"Conversion from " + std::visit(TypeVisitor{}, expressionValue) + L" to" +
            variable_type_representation.at(conversionType) + L" is illegal.");
    }
    this->lastResult = conversedValue;
}
void VisitorInterpreter::visit(ExpressionNeg * e) {
    e->expression->accept(*this);
    interpeter_value & expression = this->consumeLastResult();
    if (std::holds_alternative<bool>(expression)) {
        bool expressionValue = std::get<bool>(expression);
        this->lastResult = !expressionValue;
    } else {
        auto expressionType = std::visit(TypeVisitor{}, expression);
        expressionType[0] = std::towupper(expressionType[0]);
        this->handleRuntimeError(e->position, expressionType + L" expression can't be negated with !.");
    }
}
void VisitorInterpreter::visit(ExpressionNegMinus * e) {
    e->expression->accept(*this);
    interpeter_value & expression = this->consumeLastResult();
    if (std::holds_alternative<int>(expression)) {
        int expressionValue = std::get<int>(expression);
        this->lastResult = -expressionValue;
    } else if (std::holds_alternative<double>(expression)) {
        double expressionValue = std::get<double>(expression);
        this->lastResult = -expressionValue;
    } else {
        auto expressionType = std::visit(TypeVisitor{}, expression);
        expressionType[0] = std::towupper(expressionType[0]);
        this->handleRuntimeError(e->position, expressionType + L" expression can't be negated with minus.");
    }
}
void VisitorInterpreter::visit(ExpressionValueList * e) {
    std::vector<interpeter_value> values;
    for (auto & expression : e->expressions) {
        expression->accept(*this);
        interpeter_value & expressionValue = this->consumeLastResult();
        values.push_back(expressionValue);
    }
    std::shared_ptr<ListValue> value = std::make_shared<ListValue>(std::move(values));
    this->lastResult = value;
}
void VisitorInterpreter::visit(ExpressionValuePoint * e) {
    e->xCoord->accept(*this);
    interpeter_value & xCoordExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<double>(xCoordExpressionValue)) {
        this->handleRuntimeError(e->position, L"Left coord of point is not double.");
    }

    e->yCoord->accept(*this);
    interpeter_value & yCoordExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<double>(yCoordExpressionValue)) {
        this->handleRuntimeError(e->position, L"Left coord of point is not double.");
    }
    this->lastResult = std::pair<double, double>(std::get<double>(xCoordExpressionValue), std::get<double>(yCoordExpressionValue));
}
void VisitorInterpreter::visit(ExpressionValueLiteral * e) {
    std::visit([this](auto & value){this->lastResult = value;}, e->value);
}
void VisitorInterpreter::visit(ExpressionValueBrackets * e) {
    e->expression->accept(*this);
}

void VisitorInterpreter::visit(ObjectAccessExpression * s) {
    s->leftExpression->accept(*this);

    if (auto & rightStatement = s->rightExpression) {
        rightStatement->accept(*this);
    } else {
    }
}
void VisitorInterpreter::visit(IdentifierListIndexExpression * e) {
    e->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<std::shared_ptr<ListValue>>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, std::visit(TypeVisitor{}, leftExpressionValue) + L" is not subscriptable.");
    }

    e->indexExpression->accept(*this);
    interpeter_value & indexExpressionValue = this->consumeLastResult();
    if (!std::holds_alternative<int>(indexExpressionValue)) {
        this->handleRuntimeError(e->position, std::visit(TypeVisitor{}, indexExpressionValue) + L" value in index. Index must be int.");
    }
    ListValue * listValue = std::get<std::shared_ptr<ListValue>>(leftExpressionValue).get();
    int index = std::get<int>(indexExpressionValue);
    this->lastResult = (*listValue)[index];
}
void VisitorInterpreter::visit(IdentifierFunctionCallExpression * s) {
    //getFunctionDeclAndGoToIt
    s->identifierExpression->accept(*this);

    for (auto & expression : s->expressions) {
        expression->accept(*this);
    }
}
void VisitorInterpreter::visit(IdentifierExpression * s) {
    //getValueFormScope
}





void VisitorInterpreter::visit(WhileStatement * s) {
    this->addNewScope();
    s->conditionAndBlock->accept(*this);
    this->popScope();
}
void VisitorInterpreter::visit(IfStatement * s) {
    this->addNewScope();
    s->ifConditionAndBlock->accept(*this);
    this->popScope();
    if(this->consumeConditionTrue()) {
        return;
    }
    for (auto & condAndBlock : s->elsifConditionsAndBlocks) {
        this->addNewScope();
        condAndBlock->accept(*this);
        this->popScope();
        if(this->consumeConditionTrue()) {
            return;
        }
        if (this->returnValue) {
            return;
        }
    }
    if (auto & elseCodeBlock = s->elseCodeBlock) {
        this->addNewScope();
        elseCodeBlock->accept(*this);
        this->popScope();
    }
}
void VisitorInterpreter::visit(ForStatement * s) {
    s->expression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    if(!std::holds_alternative<std::shared_ptr<ListValue>>(expressionValue)) {
        this->handleRuntimeError(s->position, L"Iterated variable is not list");
    }
    ListValue* iteratedList = std::get<std::shared_ptr<ListValue>>(expressionValue).get();
    for(size_t i=0; i<iteratedList->len(); i++) {
        this->addNewScope();
        this->getCurrentScopeVariables()[s->identifier] = (*iteratedList)[i];
        s->block->accept(*this);
        this->popScope();
        if (this->returnValue) {
            return;
        }
    }
}
void VisitorInterpreter::visit(ForRangeStatement * s) {
    s->leftExpression->accept(*this);
    interpeter_value & leftExpressionValue = this->consumeLastResult();
    if(!std::holds_alternative<int>(leftExpressionValue)) {
        this->handleRuntimeError(s->position, L"Left range parameter is not int");
    }
    int startOfRange = std::get<int>(leftExpressionValue);
    s->rightExpression->accept(*this);
    interpeter_value & rightExpressionValue = this->consumeLastResult();
    if(!std::holds_alternative<int>(rightExpressionValue)) {
        this->handleRuntimeError(s->position, L"Left range parameter is not int");
    }
    int endOfRange = std::get<int>(rightExpressionValue);
    for(int i=startOfRange; i<endOfRange; i++) {
        this->addNewScope();
        this->getCurrentScopeVariables()[s->identifier] = interpeter_value(i);
        s->block->accept(*this);
        this->popScope();
        if (this->returnValue) {
            return;
        }
    }
}
void VisitorInterpreter::visit(DeclarationStatement * s) {
    this->getCurrentScopeVariables()[s->identifierName] = std::monostate();
}

void VisitorInterpreter::visit(DeclarationAssignStatement * s) {
    s->expression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    this->getCurrentScopeVariables()[s->identifierName] = expressionValue;
}

void VisitorInterpreter::visit(ReturnStatement * s) {
    s->expression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    this->returnValue = expressionValue;
}

void VisitorInterpreter::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
    this->consumeLastResult();
}

void VisitorInterpreter::visit(IdentifierStatementAssign * s) {
    s->identifierExpression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    s->expression->accept(*this);
}


void VisitorInterpreter::visit(ConditionAndBlock * cb) {

    cb->condition->accept(*this);
    interpeter_value & conditionValue = this->consumeLastResult();
    if(!std::holds_alternative<bool>(conditionValue)) {
        this->handleRuntimeError(cb->position, L"Condition evaluated to non boolean value.");
    }
    if(std::get<bool>(conditionValue)) {
        cb->block->accept(*this);
        this->lastConditionTrue = true;
    }
}





void VisitorInterpreter::visit(CodeBlock * cb) {
    for (auto & statement : cb->statements) {
        statement->accept(*this);
        if(this->returnValue) {
            return;
        }
    }
}

void VisitorInterpreter::visit(Parameter * p) {
    this->getCurrentScope().getVariables()[p->getName()] = functionCallParams.back();
    functionCallParams.pop_back();
}

void VisitorInterpreter::visit(FigureParameter * p) {
    auto & figureScope = this->getFigureScope();
    p->valueExpression->accept(*this);
    interpeter_value & expressionValue = this->consumeLastResult();
    if(!std::holds_alternative<std::pair<double, double>>(expressionValue)) {
        this->handleRuntimeError(p->position, L"Point does not have default value in form (double, double)");
    }
    interpeter_value & lastFigure = this->getFigureScope().getVariables()[this->currentlyAnalyzedFigure.value()]; //todo co jak usuniemy coś i kopiujemy przez referencję interpreter_value &
    FigureValue * currentFigure = std::get<std::shared_ptr<FigureValue>>(lastFigure).get();
    currentFigure->getPoints()[p->getName()] = std::get<std::pair<double, double>>(expressionValue);
}
void VisitorInterpreter::visit(FigureDeclaration * fd) {
    auto & figureScope = this->getFigureScope();
    std::shared_ptr<FigureValue> figureDecl = std::make_shared<FigureValue>(FigureValue());
    this->currentlyAnalyzedFigure = fd->name;
    figureScope.getVariables()[fd->name] = figureDecl;
    for (auto & param : fd->params) {
        param->accept(*this);
    }
    this->currentlyAnalyzedFigure = L"";
}
void VisitorInterpreter::visit(FuncDeclaration * fd) {
    this->functionContexts.push(FunctionCallContext());
    this->addNewScope();
    for (auto & param : fd->params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
    this->popScope();
    this->functionContexts.pop();
    this->consumeReturnValue();
}
void VisitorInterpreter::visit(Program * p) {
    auto mainFunc = p->functions.find(L"main");
    if (mainFunc != p->functions.end()) {
        for(auto & figure: p->figures) {
            figure.second->accept(*this);
        }
        mainFunc->second->accept(*this);
    }
}

void VisitorInterpreter::handleRuntimeError(const Position &pos, const std::wstring &errorMsg) {
    this->errorHandler->onRuntimeError(pos, errorMsg);
    throw;
}

Scope &VisitorInterpreter::addNewScope() {
    this->functionContexts.top().getScopes().push_back(Scope());
    return this->functionContexts.top().getScopes().back();
}

void VisitorInterpreter::popScope() {
    this->functionContexts.top().getScopes().pop_back();
}

void VisitorInterpreter::consumeReturnValue() {
    if (returnValue) {
        this->lastResult = this->returnValue;
        this->returnValue = std::nullopt;
    } else {
        this->lastResult = std::monostate();
    }
}

bool VisitorInterpreter::consumeConditionTrue() {
    if(this->lastConditionTrue) {
        this->lastConditionTrue = false;
        return true;
    }
    return false;
}

interpeter_value &VisitorInterpreter::consumeLastResult() {
    std::optional<interpeter_value> retVal = lastResult;
    if (!retVal) {
        this->errorHandler->onInterpreterError(L"Expression didn't evaluate properly.");
        throw;
    }
    lastResult = std::nullopt;
    return retVal.value();
}

std::map<std::wstring, interpeter_value> &VisitorInterpreter::getCurrentScopeVariables() {
    return this->functionContexts.top().getScopes().back().getVariables();
}

bool VisitorInterpreter::ensureTypesMatch(interpeter_value &value1, interpeter_value &value2) {
    if (value1.index() != value2.index()) {
        return false;
    }
    return true;
}

void VisitorInterpreter::operationLegalityCheck(interpeter_value &value1, const Position &position,
                                                AllowedInOperationVisitor &&allowedInOperationVisitor,
                                                const std::wstring &operation) {
    bool allowed = std::visit([&value1](auto & allowedIn) -> bool{return std::visit(allowedIn, value1);}, allowedInOperationVisitor);
    if (!allowed) {
        this->handleRuntimeError(position, L"Expressions of type " + std::visit(TypeVisitor{}, value1) +
                                           L" are not allowed in comparison");
    }
}

void VisitorInterpreter::operationTypeEqualityCheck(interpeter_value &value1, interpeter_value &value2, const Position &position, const std::wstring operation) {
    if (!this->ensureTypesMatch(value1, value2)) {
        this->handleRuntimeError(position, operation + L" between " + std::visit(TypeVisitor{}, value1) +
                                           L" and " + std::visit(TypeVisitor{}, value2));
    }
}
