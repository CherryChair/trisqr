//
// Created by mpkow on 14.12.2023.
//

#include "VisitorInterpreter.h"

void VisitorInterpreter::visit(ExpressionOr * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<bool>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression on left to 'or' evaluated to non boolean.");
    }
    if(std::get<bool>(leftExpressionValue)) {
        this->lastResult = true;
        return;
    }
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<bool>(rightExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression right to 'or' evaluated to non boolean.");
    }
    this->lastResult = std::get<bool>(rightExpressionValue);
}
void VisitorInterpreter::visit(ExpressionAnd * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<bool>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression left to 'and' evaluated to non boolean.");
    }
    if(!std::get<bool>(leftExpressionValue)) {
        this->lastResult = false;
        return;
    }
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<bool>(rightExpressionValue)) {
        this->handleRuntimeError(e->position, L"Expression right to 'and' evaluated to non boolean.");
    }
    this->lastResult = std::get<bool>(rightExpressionValue);
}
void VisitorInterpreter::visit(ExpressionCompEq * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    if (leftExpressionValue == rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}

void VisitorInterpreter::visit(ExpressionCompNeq * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Comparison");
    if (leftExpressionValue != rightExpressionValue) {
        this->lastResult = true;
    } else {
        this->lastResult = false;
    }
}
void VisitorInterpreter::visit(ExpressionCompLeq * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
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
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
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
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
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
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
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
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Addition");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInAdditionVisitor(), L"addition");
    this->lastResult = leftExpressionValue + rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionSub * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Subtraction");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInSubtractionVisitor(), L"subtraction");
    this->lastResult = leftExpressionValue - rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionMul * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Multiplication");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInMultiplicationVisitor(), L"multiplication");
    this->lastResult = leftExpressionValue * rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionDiv * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    operationTypeEqualityCheck(leftExpressionValue, rightExpressionValue, e->position, L"Division");
    operationLegalityCheck(leftExpressionValue, e->position, AllowedInDivisionVisitor(), L"division");
    this->lastResult = leftExpressionValue / rightExpressionValue;
}
void VisitorInterpreter::visit(ExpressionIs * e) {
    e->expression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    bool typesMatch = std::visit(TypeMatchVisitor(e->checkedType), expressionValue);
    this->lastResult = typesMatch;
}
void VisitorInterpreter::visit(ExpressionTo * e) {
    e->expression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    variable_type conversionType = e->conversionType;
    interpreter_value conversedValue = std::visit(ConversionVisitor(conversionType), expressionValue);
    if (std::holds_alternative<std::monostate>(conversedValue)) {
        this->handleRuntimeError(e->position, L"Conversion from " + std::visit(TypeVisitor{}, expressionValue) + L" to" +
            variable_type_representation.at(conversionType) + L" is illegal.");
    }
    this->lastResult = conversedValue;
}
void VisitorInterpreter::visit(ExpressionNeg * e) {
    e->expression->accept(*this);
    interpreter_value expression = this->consumeLastResultAndAccessedObject();
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
    interpreter_value expression = this->consumeLastResultAndAccessedObject();
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
    std::vector<AssignableValue> values;
    for (auto & expression : e->expressions) {
        expression->accept(*this);
        interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
        values.push_back(AssignableValue(expressionValue));
    }
    std::shared_ptr<ListValue> value = std::make_shared<ListValue>(std::move(values));
    this->lastResult = value;
}
void VisitorInterpreter::visit(ExpressionValuePoint * e) {
    e->xCoord->accept(*this);
    interpreter_value xCoordExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<double>(xCoordExpressionValue)) {
        this->handleRuntimeError(e->position, L"Left coord of point is not double.");
    }

    e->yCoord->accept(*this);
    interpreter_value yCoordExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<double>(yCoordExpressionValue)) {
        this->handleRuntimeError(e->position, L"Right coord of point is not double.");
    }
    this->lastResult = std::make_shared<PointValue>(std::get<double>(xCoordExpressionValue), std::get<double>(yCoordExpressionValue));
}
void VisitorInterpreter::visit(ExpressionValueLiteral * e) {
    std::visit([this](auto & value){this->lastResult = value;}, e->value);
}
void VisitorInterpreter::visit(ExpressionValueBrackets * e) {
    e->expression->accept(*this);
}

void VisitorInterpreter::visit(ObjectAccessExpression * e) {
    e->leftExpression->accept(*this); //1)//2)//3)//4)
    e->rightExpression->accept(*this);
}
void VisitorInterpreter::visit(IdentifierListIndexExpression * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();//3)//4)
    if (!std::holds_alternative<std::shared_ptr<ListValue>>(leftExpressionValue)) {
        this->handleRuntimeError(e->position, std::visit(TypeVisitor{}, leftExpressionValue) + L" is not subscriptable.");
    }
    e->indexExpression->accept(*this);
    interpreter_value indexExpressionValue = this->consumeLastResultAndAccessedObject();
    if (!std::holds_alternative<int>(indexExpressionValue)) {
        this->handleRuntimeError(e->position, std::visit(TypeVisitor{}, indexExpressionValue) + L" value in index. Index must be int.");
    }
    ListValue * listValue = std::get<std::shared_ptr<ListValue>>(leftExpressionValue).get();
    int index = std::get<int>(indexExpressionValue);
    if (index >= listValue->len()) {
        this->handleRuntimeError(e->position, L"Index out of range.");
    }
    this->accessedObject = AssignableValue((*listValue)[index]);//3)//4)
}
void VisitorInterpreter::visit(IdentifierFunctionCallExpression * e) {
    //getFunctionDeclAndGoToIt
    e->identifierExpression->accept(*this);
//    if in special_function do ble ble
//    if in nomalfucntiondo ble ble
    interpreter_value identifierExpression = this->lastResult.value();
    std::wstring functionName = std::get<std::wstring>(identifierExpression);
    if (internalListFunctions.find(functionName) != internalListFunctions.end()) {
        ListValue * listValue = std::get<std::shared_ptr<ListValue>>(this->consumeLastResultAndAccessedObject()).get();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            functionCallParams.push(this->consumeLastResultAndAccessedObject());
        }
        internalListFunctions.at(functionName)(listValue);
    } else if (internalFigureFunctions.find(functionName) != internalFigureFunctions.end()) {
        FigureValue * figureValue = std::get<std::shared_ptr<FigureValue>>(this->consumeLastResultAndAccessedObject()).get();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            functionCallParams.push(this->consumeLastResultAndAccessedObject());
        }
        internalFigureFunctions.at(functionName)(figureValue);
    } else if (internalFunctions.find(functionName) != internalFunctions.end()) {
        this->consumeLastResultAndAccessedObject();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            functionCallParams.push(this->consumeLastResultAndAccessedObject());
        }
        internalFunctions.at(functionName)();
    } else {
        this->consumeLastResultAndAccessedObject();
        FuncDeclaration * function = functionDeclarations[functionName];
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            functionCallParams.push(this->consumeLastResultAndAccessedObject());
        }
        function->accept(*this);
    }
    //wynik funkcji, potencjalnie po lewej assignable, albo ciągniemy dalej kropką
    this->accessedObject = AssignableValue(this->consumeLastResultAndAccessedObject()); //2)//3)
}



void VisitorInterpreter::visit(IdentifierExpression * e) {
    this->funcCallPosition = e->position;
    if(this->accessedObject) {
        std::shared_ptr<interpreter_value> accessedValue = this->getAccessedObject();
        if (std::holds_alternative<std::shared_ptr<ListValue>>(*accessedValue)) {
            if (special_list_keywords.find(e->identifierName) != special_list_keywords.end()) {
                this->lastResult = e->identifierName;
            }
        } else if (std::holds_alternative<std::shared_ptr<FigureValue>>(*accessedValue)) {
            FigureValue * figure = std::get<std::shared_ptr<FigureValue>>(*accessedValue).get();
            std::unordered_map<std::wstring, std::shared_ptr<PointValue>> & figurePoints = figure->getPoints();
            auto point = figurePoints.find(e->identifierName);
            if (point != figure->getPoints().end()){
                this->accessedObject = AssignableValue(point->second);
                this->figurePointAssigned = true;
            } else if (special_figure_keywords.find(e->identifierName) != special_figure_keywords.end()) {
                this->lastResult = e->identifierName;
            } else if (e->identifierName == L"color") {
                this->accessedObject = AssignableValue(figure->getColor().shared_from_this());
                this->figureColorAssigned = true; // TODO to będzie zmieniane w innych funkcjach, trzeba wymyślić sposób, może umieszczać w scopie
            }
        } else if (std::holds_alternative<std::shared_ptr<PointValue>>(*accessedValue)) {
            this->pointCoordAssigned = true;
            if (e->identifierName == L"x") {
                this->accessedObject = std::get<std::shared_ptr<PointValue>>(*accessedValue)->getX();
            }
            if (e->identifierName == L"y") {
                this->accessedObject = std::get<std::shared_ptr<PointValue>>(*accessedValue)->getY();
            }
        } else {
            this->handleRuntimeError(e->position, L"Object" + std::visit(TypeVisitor{}, *accessedValue) + L" does not have member " + e->identifierName);
        }
    } else if (this->functionDeclarations.find(e->identifierName) != this->functionDeclarations.end() || special_keywords.find(e->identifierName) != special_keywords.end()){
        this->lastResult = e->identifierName;
        //2) //3)
    } else {
        this->accessedObject = this->findVariableInScopes(e->identifierName); //1) //4)
        this->lastResult = e->identifierName; // może niekonieczne zapisywanie lastResult, będziemy przezrzucać wyżej z assignable value do lastResult
    }
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
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
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
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    if(!std::holds_alternative<int>(leftExpressionValue)) {
        this->handleRuntimeError(s->position, L"Left range parameter is not int");
    }
    int startOfRange = std::get<int>(leftExpressionValue);
    s->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    if(!std::holds_alternative<int>(rightExpressionValue)) {
        this->handleRuntimeError(s->position, L"Left range parameter is not int");
    }
    int endOfRange = std::get<int>(rightExpressionValue);
    for(int i=startOfRange; i<endOfRange; i++) {
        this->addNewScope();
        this->getCurrentScopeVariables()[s->identifier] = interpreter_value(i);
        s->block->accept(*this);
        this->popScope();
        if (this->returnValue) {
            return;
        }
    }
}
void VisitorInterpreter::visit(DeclarationStatement * s) {
    this->getCurrentScopeVariables()[s->identifierName] = AssignableValue();
}

void VisitorInterpreter::visit(DeclarationAssignStatement * s) {
    s->expression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    this->getCurrentScopeVariables()[s->identifierName] = expressionValue;
}

void VisitorInterpreter::visit(ReturnStatement * s) {
    s->expression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    this->returnValue = expressionValue;
}

void VisitorInterpreter::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
    this->consumeLastResultAndAccessedObject();
}

void VisitorInterpreter::visit(IdentifierStatementAssign * s) {
    s->expression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    s->identifierExpression->accept(*this);
    std::shared_ptr<interpreter_value> assignableValue = this->getAccessedObject();
    this->consumeLastResultAndAccessedObject();
    if (this->pointCoordAssigned) {
        if (!std::holds_alternative<double>(expressionValue)){
            this->handleRuntimeError(s->position, L"Assigning value of type " + std::visit(TypeVisitor{}, expressionValue) + L" to point coordinate.");
        }
    } else if (this->figurePointAssigned) {
        if (!std::holds_alternative<std::shared_ptr<PointValue>>(expressionValue)){
            this->handleRuntimeError(s->position, L"Assigning value of type " + std::visit(TypeVisitor{}, expressionValue) + L" to figure point.");
        }
    } else if (this->figureColorAssigned) {
        if (!std::holds_alternative<std::shared_ptr<PointValue>>(expressionValue)){
            this->handleRuntimeError(s->position, L"Assigning value of type " + std::visit(TypeVisitor{}, expressionValue) + L" to figure point.");
        } // kolorem zajmę się później jak będzie czas
    }
    *assignableValue = expressionValue;
//    this->consumeLastResultAndAccessedObject();
    //logika z przypisywaniem punktowi złej wartości itd.
 // problem ze zmiennymi zagnieżdżonymi . albo elemet listy
    //pierwsze liczymy wartośc po prawej, potem otrzymujemy obiekt po lewej
    this->pointCoordAssigned = false;
    this->figurePointAssigned = false;
    this->figureColorAssigned = false;
}


void VisitorInterpreter::visit(ConditionAndBlock * cb) {

    cb->condition->accept(*this);
    interpreter_value conditionValue = this->consumeLastResultAndAccessedObject();
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
    if(!functionCallParams.empty()) {
        this->getCurrentScope().getVariables()[p->getName()] = AssignableValue(functionCallParams.front());
        functionCallParams.pop();
    } else {
        this->getCurrentScope().getVariables()[p->getName()] = AssignableValue();
    }
}

void VisitorInterpreter::visit(FigureParameter * p) {
    p->valueExpression->accept(*this);
    interpreter_value expressionValue = this->consumeLastResultAndAccessedObject();
    if(!std::holds_alternative<std::shared_ptr<PointValue>>(expressionValue)) {
        this->handleRuntimeError(p->position, L"Point does not have default value in form (double, double)");
    }
    AssignableValue & lastFigure = this->getFigureScope().getVariables()[this->currentlyAnalyzedFigure.value()];
    FigureValue * currentFigure = std::get<std::shared_ptr<FigureValue>>(*(lastFigure.value)).get();
    currentFigure->getPoints()[p->getName()] = std::get<std::shared_ptr<PointValue>>(expressionValue);
}
void VisitorInterpreter::visit(FigureDeclaration * fd) {
    std::shared_ptr<FigureValue> figureDecl = std::make_shared<FigureValue>(FigureValue());
    this->currentlyAnalyzedFigure = fd->name;
    this->figureScope.getVariables()[fd->name] = AssignableValue(figureDecl);
    for (auto & param : fd->params) {
        param->accept(*this);
    }
    this->currentlyAnalyzedFigure = L"";
}
void VisitorInterpreter::visit(FuncDeclaration * fd) {
    this->functionContexts.push(FunctionCallContext());
    this->addNewScope();
    if (fd->params.size() < functionCallParams.size()) {
        this->handleRuntimeError(this->funcCallPosition, L"Too many params for function call");
    }
    for (auto & param : fd->params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
    this->popScope();
    this->functionContexts.pop();
    this->consumeReturnValue();
}
void VisitorInterpreter::visit(Program * p) {
    this->functionDeclarations = p->getFuncDeclarations();
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
    this->accessedObject = std::nullopt;
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

interpreter_value VisitorInterpreter::consumeLastResultAndAccessedObject() {
    std::optional<interpreter_value> retVal = this->lastResult;
    if (this->accessedObject) {
        retVal = *(this->accessedObject.value().value);
        this->accessedObject = std::nullopt;
    }
    if (!retVal) {
        this->errorHandler->onInterpreterError(L"Expression didn't evaluate properly.");
        throw;
    }
    this->lastResult = std::nullopt;
    return retVal.value();
}

std::shared_ptr<interpreter_value> VisitorInterpreter::getAccessedObject() {
    if (!this->accessedObject) {
        this->errorHandler->onInterpreterError(L"Expression object access didn't evaluate properly.");
        throw;
    }
    return this->accessedObject->value;
}

std::unordered_map<std::wstring, AssignableValue> &VisitorInterpreter::getCurrentScopeVariables() {
    return this->functionContexts.top().getScopes().back().getVariables();
}

AssignableValue & VisitorInterpreter::findVariableInScopes(const std::wstring & variableName) {
    auto & currentScopes = this->functionContexts.top().getScopes();
    for (auto iter = currentScopes.rbegin(); iter != currentScopes.rend(); iter++) {
        auto & currentScopeVariables = iter->getVariables();
        auto variableIndex = currentScopeVariables.find(variableName);
        if (variableIndex != currentScopeVariables.end()) {
            return variableIndex->second;
        }
    }
    this->handleRuntimeError(this->funcCallPosition, L"Variable not in function call context.");
}

bool VisitorInterpreter::ensureTypesMatch(interpreter_value &value1, interpreter_value &value2) {
    if (value1.index() != value2.index()) {
        return false;
    }
    return true;
}

void VisitorInterpreter::operationLegalityCheck(interpreter_value &value1, const Position &position,
                                                AllowedInOperationVisitor &&allowedInOperationVisitor,
                                                const std::wstring &operation) {
    bool allowed = std::visit([&value1](auto & allowedIn) -> bool{return std::visit(allowedIn, value1);}, allowedInOperationVisitor);
    if (!allowed) {
        this->handleRuntimeError(position, L"Expressions of type " + std::visit(TypeVisitor{}, value1) +
                                           L" are not allowed in comparison");
    }
}

void VisitorInterpreter::operationTypeEqualityCheck(interpreter_value &value1, interpreter_value &value2, const Position &position, const std::wstring & operation) {
    if (!this->ensureTypesMatch(value1, value2)) {
        this->handleRuntimeError(position, operation + L" between " + std::visit(TypeVisitor{}, value1) +
                                           L" and " + std::visit(TypeVisitor{}, value2));
    }
}

interpreter_value operator+(const interpreter_value & value1, const interpreter_value & value2) {
    if (value1.index() != value2.index()) {
        std::wcerr << L"ERR: Addition between two different types";
        throw;
    }
    switch (value1.index()){
        case 0: {
            return std::get<int>(value1) + std::get<int>(value2);
        } case 1: {
            return std::get<double>(value1) + std::get<double>(value2);
        } case 2: {
            return std::get<std::wstring>(value1) + std::get<std::wstring>(value2);
        } case 3: {
            std::wcerr << L"ERR: Addition between two boolean illegal";
            throw;
        } case 4: {
            std::wcerr << L"ERR: Addition between monostate illegal";
            throw;
        } case 5: {
            PointValue pair1 = *(std::get<std::shared_ptr<PointValue>>(value1));
            PointValue pair2 = *(std::get<std::shared_ptr<PointValue>>(value2));
            auto p1_x = std::get<double>(*(pair1.getX().value));
            auto p1_y = std::get<double>(*(pair1.getY().value));
            auto p2_x = std::get<double>(*(pair2.getX().value));
            auto p2_y = std::get<double>(*(pair2.getY().value));
            return std::make_shared<PointValue>( p1_x + p2_x, p1_y + p2_y);
        } case 6: {
            ListValue * list1 = std::get<std::shared_ptr<ListValue>>(value1).get();
            ListValue * list2 = std::get<std::shared_ptr<ListValue>>(value2).get();
            return (*list1 + *list2).shared_from_this();
        } case 7: {
            std::wcerr << L"ERR: Addition between FigureValue illegal";
            throw;
        }
    }
    return std::monostate();
}

interpreter_value operator-(const interpreter_value & value1, const interpreter_value & value2) {
    if (value1.index() != value2.index()) {
        std::wcerr << L"ERR: Subtraction between two different types";
        throw;
    }
    switch (value1.index()){
        case 0: {
            return std::get<int>(value1) - std::get<int>(value2);
        } case 1: {
            return std::get<double>(value1) - std::get<double>(value2);
        } case 2: {
            std::wcerr << L"ERR: Subtraction between two strings illegal";
            throw;
        } case 3: {
            std::wcerr << L"ERR: Subtraction between two boolean illegal";
            throw;
        } case 4: {
            std::wcerr << L"ERR: Subtraction between monostate illegal";
            throw;
        } case 5: {
            PointValue pair1 = *(std::get<std::shared_ptr<PointValue>>(value1));
            PointValue pair2 = *(std::get<std::shared_ptr<PointValue>>(value2));
            auto p1_x = std::get<double>(*(pair1.getX().value));
            auto p1_y = std::get<double>(*(pair1.getY().value));
            auto p2_x = std::get<double>(*(pair2.getX().value));
            auto p2_y = std::get<double>(*(pair2.getY().value));
            return std::make_shared<PointValue>( p1_x - p2_x, p1_y - p2_y);
        } case 6: {
            std::wcerr << L"ERR: Subtraction between ListValue illegal";
            throw;
        } case 7: {
            std::wcerr << L"ERR: Subtraction between FigureValue illegal";
            throw;
        }
    }
    return std::monostate();
}

interpreter_value operator/(const interpreter_value & value1, const interpreter_value & value2) {
    if (value1.index() != value2.index()) {
        std::wcerr << L"ERR: Division between two different types";
        throw;
    }
    switch (value1.index()){
        case 0: {
            return std::get<int>(value1)/std::get<int>(value2);
        } case 1: {
            return std::get<double>(value1)/std::get<double>(value2);
        } case 2: {
            std::wcerr << L"ERR: Division between two strings illegal";
            throw;
        } case 3: {
            std::wcerr << L"ERR: Division between two boolean illegal";
            throw;
        } case 4: {
            std::wcerr << L"ERR: Division between two monostates illegal";
            throw;
        } case 5: {
            std::wcerr << L"ERR: Division between points illegal";
            throw;
        } case 6: {
            std::wcerr << L"ERR: Division between ListValue illegal";
            throw;
        } case 7: {
            std::wcerr << L"ERR: Division between FigureValue illegal";
            throw;
        }
    }
    return std::monostate();
}

interpreter_value operator*(const interpreter_value & value1, const interpreter_value & value2) {
    if (value1.index() != value2.index()) {
        std::wcerr << L"ERR: Multiplication between two different types";
        throw;
    }
    switch (value1.index()){
        case 0: {
            return std::get<int>(value1) * std::get<int>(value2);
        } case 1: {
            return std::get<double>(value1) * std::get<double>(value2);
        } case 2: {
            std::wcerr << L"ERR: Multiplication between two strings illegal";
            throw;
        } case 3: {
            std::wcerr << L"ERR: Multiplication between two boolean illegal";
            throw;
        } case 4: {
            std::wcerr << L"ERR: Multiplication between two monostates illegal";
            throw;
        } case 5: {
            std::wcerr << L"ERR: Multiplication between points illegal";
            throw;
        } case 6: {
            std::wcerr << L"ERR: Multiplication between ListValue illegal";
            throw;
        } case 7: {
            std::wcerr << L"ERR: Multiplication between FigureValue illegal";
            throw;
        }
    }
    return std::monostate();
}

void VisitorInterpreter::requireArgNum(const std::wstring & name, int argNum, const std::wstring & argList) {
    std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
    if (funcCallParams.size() < argNum) {
        this->handleRuntimeError(this->funcCallPosition, L"Too few arguments " + name + L" requires " + argList + L".");
    } else if (funcCallParams.size() > argNum) {
        this->handleRuntimeError(this->funcCallPosition, L"Too many arguments " + name + L" requires " + argList + L".");
    }
}

void VisitorInterpreter::requireArgNumBetween(const std::wstring & name, int argNumLower, int argNumUpper, const std::wstring & argList) {
    std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
    if (funcCallParams.size() < argNumLower) {
        this->handleRuntimeError(this->funcCallPosition, L"Too few arguments " + name + L" takes " + argList + L".");
    } else if (funcCallParams.size() > argNumUpper) {
        this->handleRuntimeError(this->funcCallPosition, L"Too many arguments " + name + L" takes " + argList + L".");
    }
}

void VisitorInterpreter::requireArgType(const std::wstring & name, variable_type vt) {
    std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
    if (!std::visit(TypeMatchVisitor(vt), funcCallParams.front())) {
        this->handleRuntimeError(this->funcCallPosition, L"Wrong argument type, " + name + L" must be " + variable_type_representation.at(vt) +
            L" type but is " + std::visit(TypeVisitor{}, funcCallParams.front()) + L".");
    }
}