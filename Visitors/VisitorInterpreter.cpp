//
// Created by mpkow on 14.12.2023.
//

#include "VisitorInterpreter.h"

void VisitorInterpreter::visit(ExpressionOr * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, leftExpressionValue, BOOL_VARIABLE, L"Expression on left to 'or' evaluated to non boolean.");
    if(std::get<bool>(leftExpressionValue)) {
        this->lastResult = true;
        return;
    }
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, leftExpressionValue, BOOL_VARIABLE, L"Expression right to 'or' evaluated to non boolean.");
    this->lastResult = std::get<bool>(rightExpressionValue);
}
void VisitorInterpreter::visit(ExpressionAnd * e) {
    e->leftExpression->accept(*this);
    interpreter_value leftExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, leftExpressionValue, BOOL_VARIABLE, L"Expression left to 'and' evaluated to non boolean.");
    if(!std::get<bool>(leftExpressionValue)) {
        this->lastResult = false;
        return;
    }
    e->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, leftExpressionValue, BOOL_VARIABLE, L"Expression right to 'and' evaluated to non boolean.");
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
    auto expressionType = std::visit(TypeVisitor{}, expression);
    expressionType[0] = std::towupper(expressionType[0]);
    this->requireExpressionType(e->position, expression, BOOL_VARIABLE, expressionType + L" expression can't be negated with !.");
    bool expressionValue = std::get<bool>(expression);
    this->lastResult = !expressionValue;
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
    this->requireExpressionType(e->position, xCoordExpressionValue, DOUBLE_VARIABLE, L"Left coord of point is not double.");
    e->yCoord->accept(*this);
    interpreter_value yCoordExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, yCoordExpressionValue, DOUBLE_VARIABLE, L"Right coord of point is not double.");
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
    this->requireExpressionType(e->position, leftExpressionValue, LIST_VARIABLE, std::visit(TypeVisitor{}, leftExpressionValue) + L" is not subscriptable.");
    e->indexExpression->accept(*this);
    interpreter_value indexExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(e->position, indexExpressionValue, INT_VARIABLE, std::visit(TypeVisitor{}, indexExpressionValue) + L" value in index. Index must be int.");
    ListValue * listValue = std::get<std::shared_ptr<ListValue>>(leftExpressionValue).get();
    int index = std::get<int>(indexExpressionValue);
    if (index >= listValue->len()) {
        this->handleRuntimeError(e->position, L"Index out of range.");
    }
    this->accessedObject = AssignableValue((*listValue)[index]);//3)//4)
}
void VisitorInterpreter::visit(IdentifierFunctionCallExpression * e) {//parsowanie różnych struktur metod, wywaołań funkcji albo metody, context
    e->identifierExpression->accept(*this);
    interpreter_value identifierExpression = this->lastResult.value();
    std::wstring functionName = std::get<std::wstring>(identifierExpression);
    std::queue<interpreter_value> fParams;
    if (internalListFunctions.find(functionName) != internalListFunctions.end()) {
        ListValue * listValue = std::get<std::shared_ptr<ListValue>>(this->consumeLastResultAndAccessedObject()).get();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            fParams.push(this->consumeLastResultAndAccessedObject());
        }
        functionCallParams = fParams;
        internalListFunctions.at(functionName)(listValue);
    } else if (internalFigureFunctions.find(functionName) != internalFigureFunctions.end()) {
        FigureValue * figureValue = std::get<std::shared_ptr<FigureValue>>(this->consumeLastResultAndAccessedObject()).get();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            fParams.push(this->consumeLastResultAndAccessedObject());
        }
        functionCallParams = fParams;
        internalFigureFunctions.at(functionName)(figureValue);
    } else if (internalFunctions.find(functionName) != internalFunctions.end()) {
        this->consumeLastResultAndAccessedObject();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            fParams.push(this->consumeLastResultAndAccessedObject());
        }
        functionCallParams = fParams;
        internalFunctions.at(functionName)();
    } else if (this->getFigureScope().getVariables().find(functionName) != this->getFigureScope().getVariables().end()){
        this->consumeLastResultAndAccessedObject();
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            fParams.push(this->consumeLastResultAndAccessedObject());
        }
        functionCallParams = fParams;
        this->createNewFigure(functionName);
    } else {
        this->consumeLastResultAndAccessedObject();
        FuncDeclaration * function = functionDeclarations[functionName];
        for (auto & expression : e->expressions) {
            expression->accept(*this);
            fParams.push(this->consumeLastResultAndAccessedObject());
        }
        functionCallParams = fParams;
        function->accept(*this);
    }
    this->accessedObject = AssignableValue(this->consumeLastResultAndAccessedObject()); //2)//3)
}



void VisitorInterpreter::visit(IdentifierExpression * e) {
    this->funcCallPosition = e->position;
    if(this->accessedObject) {
        std::shared_ptr<interpreter_value> accessedValue = this->getAccessedObject();
        if (std::holds_alternative<std::shared_ptr<ListValue>>(*accessedValue)) {
            if (special_list_keywords.find(e->identifierName) != special_list_keywords.end()) {
                this->lastResult = e->identifierName;
            } else {
                this->handleRuntimeError(e->position, L"List does not have method or member " + e->identifierName + L".");
            }
        } else if (std::holds_alternative<std::shared_ptr<FigureValue>>(*accessedValue)) {
            FigureValue * figure = std::get<std::shared_ptr<FigureValue>>(*accessedValue).get();
            std::map<std::wstring, AssignableValue> & figurePoints = figure->getPoints();
            auto point = figurePoints.find(e->identifierName);
            if (point != figure->getPoints().end()){
                this->accessedObject = AssignableValue(point->second);
            } else if (special_figure_keywords.find(e->identifierName) != special_figure_keywords.end()) {
                if (e->identifierName == L"color") {
                    this->accessedObject = figure->getColor();
                } else {
                    this->lastResult = e->identifierName;
                }
            } else if (e->identifierName == L"r") {
                if (std::holds_alternative<std::monostate>(*(figure->getRadius().value))) {
                    this->handleRuntimeError(e->position, L"Figure is not a circle and does not have point 'r'.");
                }
                this->accessedObject = figure->getRadius();
            } else {
                this->handleRuntimeError(e->position, L"Figure does not have point " + e->identifierName + L".");
            }
        } else if (std::holds_alternative<std::shared_ptr<PointValue>>(*accessedValue)) {
            if (e->identifierName == L"x") {
                this->accessedObject = std::get<std::shared_ptr<PointValue>>(*accessedValue)->getX();
            } else if (e->identifierName == L"y") {
                this->accessedObject = std::get<std::shared_ptr<PointValue>>(*accessedValue)->getY();
            } else {
                this->handleRuntimeError(e->position, L"Point coordinates can only be accesed by x or y.");
            }
        } else {
            this->handleRuntimeError(e->position, L"Object" + std::visit(TypeVisitor{}, *accessedValue) + L" does not have member " + e->identifierName);
        }
    } else if (this->functionDeclarations.find(e->identifierName) != this->functionDeclarations.end() || special_keywords.find(e->identifierName) != special_keywords.end() ||
                this->getFigureScope().getVariables().find(e->identifierName) != this->getFigureScope().getVariables().end()){
        this->lastResult = e->identifierName;
        //2) //3)
    } else {
        this->accessedObject = this->findVariableInScopes(e->identifierName); //1) //4)
        this->lastResult = e->identifierName;
    }
}





void VisitorInterpreter::visit(WhileStatement * s) {
    this->addNewScope();
    s->conditionAndBlock->accept(*this);
    this->popScope();
    while(this->consumeConditionTrue()) {
        this->addNewScope();
        s->conditionAndBlock->accept(*this);
        this->popScope();
    }
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
    this->requireExpressionType(s->position, expressionValue, LIST_VARIABLE, L"Iterated variable is not list");
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
    this->requireExpressionType(s->position, leftExpressionValue, INT_VARIABLE, L"Left range parameter is not int");
    int startOfRange = std::get<int>(leftExpressionValue);
    s->rightExpression->accept(*this);
    interpreter_value rightExpressionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(s->position, leftExpressionValue, INT_VARIABLE, L"Right range parameter is not int");
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
    if (accessedObject->type == NORMAL_VALUE){
    } else if (accessedObject->type == POINT_COORD_VALUE) {
        this->requireExpressionType(s->position, expressionValue, DOUBLE_VARIABLE, L"Assigning value of type " +
                std::visit(TypeVisitor{}, expressionValue) + L" to point coordinate.");
    } else if (accessedObject->type == FIGURE_POINT_VALUE) {
        this->requireExpressionType(s->position, expressionValue, POINT_VARIABLE, L"Assigning value of type " +
                std::visit(TypeVisitor{}, expressionValue) + L" to figure point.");
    } else if (accessedObject->type == COLOR_VALUE) {
        this->requireExpressionType(s->position, expressionValue, LIST_VARIABLE, L"Assigning value of type " +
                std::visit(TypeVisitor{}, expressionValue) + L" to figure color.");
        for (auto & el : std::get<std::shared_ptr<ListValue>>(expressionValue)->getValues()) {
            this->requireExpressionType(s->position, *(el.value), INT_VARIABLE, L"Assigned color list element is not integer.");
            int elementValue = std::get<int>(*(el.value));
            if (elementValue < 0 || elementValue > 255) {
                this->handleRuntimeError(s->position, L"Assigned rgb value is out of range (0,255).");
            }
        }
    } else if (accessedObject->type == RADIUS_VALUE) {
        this->requireExpressionType(s->position, expressionValue, DOUBLE_VARIABLE, L"Assigning value of type " +
                std::visit(TypeVisitor{}, expressionValue) + L" to figure radius.");
    } else {
            this->requireExpressionType(s->position, expressionValue, INT_VARIABLE, L"Assigning value of type " +
                    std::visit(TypeVisitor{}, expressionValue) + L" to color parameter.");
    }
    *assignableValue = expressionValue;
}


void VisitorInterpreter::visit(ConditionAndBlock * cb) {

    cb->condition->accept(*this);
    interpreter_value conditionValue = this->consumeLastResultAndAccessedObject();
    this->requireExpressionType(cb->position, conditionValue, BOOL_VARIABLE, L"Condition evaluated to non boolean value.");
    if(std::get<bool>(conditionValue)) {
        cb->block->accept(*this);
        this->lastConditionTrue = true;
    }
}



void VisitorInterpreter::visit(CodeBlock * cb) {
    // addNewScope()
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
    currentFigure->getPoints()[p->getName()] = AssignableValue(expressionValue);
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
            return (*list1 + *list2);
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
    switch (value1.index()){// wizytator int  int
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

void VisitorInterpreter::createNewFigure(const std::wstring &name) {
    interpreter_value createdFigureTemplate = *(this->getFigureScope().getVariables().at(name).value);
    FigureValue * createdFigure = std::get<std::shared_ptr<FigureValue>> (createdFigureTemplate).get();
    if (this->functionCallParams.empty()) {
        internalFigureFunctions.at(L"copy")(createdFigure);
        return;
    }
    int pointNumber = createdFigure->getPoints().size();
    this->requireArgNumBetween(name, pointNumber, pointNumber+1, std::to_wstring(pointNumber) +
        L" point arguments and optionally [int r, int g, int b] color argument.");
    std::map<std::wstring, AssignableValue> newFigurePoints;
    for (auto & point : createdFigure->getPoints()) {
        this->requireArgType(L"point of figure", POINT_VARIABLE);
        interpreter_value pointParam = this->functionCallParams.front();
        auto & pointParamValue = std::get<std::shared_ptr<PointValue>>(pointParam);
        double xCoord = std::get<double>(*(pointParamValue->getX().value));
        double yCoord = std::get<double>(*(pointParamValue->getY().value));
        newFigurePoints[point.first] = AssignableValue(std::make_shared<PointValue>(xCoord, yCoord));
        this->functionCallParams.pop();
    }
    std::shared_ptr<ListValue> color = this->consumeColorParam();
    if (color) {
        this->lastResult = std::make_shared<FigureValue>(std::move(newFigurePoints), AssignableValue(color));
    } else {
        this->lastResult = std::make_shared<FigureValue>(std::move(newFigurePoints));
    }
}

std::shared_ptr<ListValue> VisitorInterpreter::consumeColorParam() {
    if (!functionCallParams.empty()) {
        this->requireArgType(L"figure colors", LIST_VARIABLE);
        interpreter_value passedColor = this->functionCallParams.front();
        this->functionCallParams.pop();
        std::shared_ptr<ListValue> colorList = std::get<std::shared_ptr<ListValue>>(passedColor);
        if (colorList->len() != 3) {
            this->handleRuntimeError(this->funcCallPosition, L"Array of wrong size passed as color");
        }
        std::vector<int> rgb = std::vector<int>(3);
        for (int i=0; i<3; i++) {
            interpreter_value colorValue = *((*colorList)[i].value);
            if (!std::holds_alternative<int>(colorValue)) {
                this->handleRuntimeError(this->funcCallPosition, L"Argument " + std::to_wstring(i) + L" of color isn't of type int.");
            }
            int intVal = std::get<int>(colorValue);
            if (intVal < 0 || intVal > 255) {
                this->handleRuntimeError(this->funcCallPosition, L"Argument " + std::to_wstring(i) + L" out of rgb values range." +
                                                                 L" It's value is " + std::to_wstring(intVal) + L".");
            }
            rgb[i] = intVal;
        }
        return std::make_shared<ListValue>(std::vector<AssignableValue>({AssignableValue(rgb[0]), AssignableValue(rgb[1]), AssignableValue(rgb[2])}));
    }
    return nullptr;
}

void VisitorInterpreter::do_drawing(cairo_t *cr, gpointer user_data) {
    cairo_set_line_width(cr, 4.0);
    VisitorInterpreter * visitor = (VisitorInterpreter *) user_data;
    for (auto figure : visitor->figuresToDraw) {
        auto & points = figure->getPoints();
        interpreter_value rgbValue = *(figure->getColor().value);
        std::shared_ptr<ListValue> rgb = std::get<std::shared_ptr<ListValue>>(rgbValue);
        double r = (double)std::get<int>(*(rgb->getValues()[0].value));
        double g = (double)std::get<int>(*(rgb->getValues()[1].value));
        double b = (double)std::get<int>(*(rgb->getValues()[2].value));
        cairo_set_source_rgb(cr, r/255.0, g/255.0, b/255.0);
        PointValue * previousPoint = std::get<std::shared_ptr<PointValue>>(*(points.rbegin()->second.value)).get();
        double p_x;
        double p_y;
        auto radius = figure->getRadius().value;
        if (!std::holds_alternative<std::monostate>(*radius)) {
            p_x = std::get<double>(*(previousPoint->getX().value));
            p_y = std::get<double>(*(previousPoint->getY().value));
            auto centre = visitor->mapCoords(std::pair<double, double>(p_x, p_y));
            cairo_arc(cr, centre.first, centre.second, std::get<double>(*radius) * visitor->scalingFactor, 0, 2 * M_PI);
        } else {
            PointValue * currentPoint;
            double c_x;
            double c_y;
            for(auto point: points) {
                currentPoint = std::get<std::shared_ptr<PointValue>>(*(point.second.value)).get();
                p_x = std::get<double>(*(previousPoint->getX().value));
                p_y = std::get<double>(*(previousPoint->getY().value));
                c_x = std::get<double>(*(currentPoint->getX().value));
                c_y = std::get<double>(*(currentPoint->getY().value));
                previousPoint = currentPoint;
                auto pointA = visitor->mapCoords(std::pair<double, double>(p_x, p_y));
                auto pointB = visitor->mapCoords(std::pair<double, double>(c_x, c_y));
                cairo_move_to(cr, pointA.first, pointA.second);
                cairo_line_to(cr, pointB.first, pointB.second);
            }
        }
        cairo_stroke(cr);
    }

    cairo_set_source_rgb(cr, 0, 0, 0);
}

gboolean VisitorInterpreter::on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data) {
    do_drawing(cr, user_data);

    return FALSE;
}

std::pair<int, int> VisitorInterpreter::mapCoords(std::pair<double, double> coords) {
    coords.first -= lbPaneCorner.first;
    coords.second -= lbPaneCorner.second;
    coords.first *= scalingFactor;
    coords.second *= scalingFactor;
    coords.second = (double)(actualPaneResolution.second) - coords.second;
    return std::pair<int, int>((int)coords.first, (int)coords.second);
}

void VisitorInterpreter::requireExpressionType(const Position &position, const interpreter_value &expressionValue, variable_type vt,
                           const std::wstring &errorMessage) {
    requiredTypeErrorMap.at(vt)(position, expressionValue, errorMessage);
}

VisitorInterpreter::VisitorInterpreter(ErrorHandler * eh): errorHandler(eh), funcCallPosition(Position({1, 1})),
    internalFunctions(
    {
            {L"print", [this](){
                this->requireArgNum(L"print()", 1, L"1 argument");
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                std::wcout << std::visit(PrintVisitor{}, value);
                this->lastResult = std::monostate();
            }},
            {L"printn", [this](){
                this->requireArgNum(L"printn()", 1, L"1 argument");
                this->internalFunctions.at(L"print")();
                std::wcout << std::endl;
            }},
            {L"draw", [this](){
                this->requireArgNum(L"draw()", 3, L"(list figureList, point lbCorner, point ruCorner) arguments");
                this->requireArgType(L"figure list", LIST_VARIABLE);
                interpreter_value figureListParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                ListValue * figureList = std::get<std::shared_ptr<ListValue>>(figureListParam).get();

                this->requireArgType(L"left bottom corner", POINT_VARIABLE);
                interpreter_value lbCornerParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * lbCorner = std::get<std::shared_ptr<PointValue>>(lbCornerParam).get();
                double lb_x = std::get<double>(*(lbCorner->getX().value));
                double lb_y = std::get<double>(*(lbCorner->getY().value));

                this->requireArgType(L"right upper corner", POINT_VARIABLE);
                interpreter_value ruCornerParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * ruCorner = std::get<std::shared_ptr<PointValue>>(ruCornerParam).get();
                double ru_x = std::get<double>(*(ruCorner->getX().value));
                double ru_y = std::get<double>(*(ruCorner->getY().value));

                this->lbPaneCorner = std::pair<double, double>(lb_x, lb_y);
                this->ruPaneCorner = std::pair<double, double>(ru_x, ru_y);
                //potencjalnie cairo_rotate i cairo_transforma zamist tych rzeczy

                if (lb_x >=  ru_x) {
                    this->handleRuntimeError(this->funcCallPosition, L"Wrong pane corner, left x must be less than right x");
                }

                if (lb_y >=  ru_y) {
                    this->handleRuntimeError(this->funcCallPosition, L"Wrong pane corner, left y must be less than right y");
                }

                double paneXSize = ruPaneCorner.first - lbPaneCorner.first;
                double paneYSize = ruPaneCorner.second - lbPaneCorner.second;


                if ((double)maxResolutionH/(double)maxResolutionW >= paneYSize/paneXSize) {
                    actualPaneResolution.first = maxResolutionW;
                    actualPaneResolution.second = (int)((double)maxResolutionW*((double)paneYSize/(double)paneXSize));
                    scalingFactor = (double) actualPaneResolution.first/paneXSize;
                } else {
                    actualPaneResolution.first = (int)((double)maxResolutionH*((double)paneXSize/(double)paneYSize));
                    actualPaneResolution.second = maxResolutionH;
                    scalingFactor = (double) actualPaneResolution.second/paneYSize;
                }


                auto & valueList = figureList->getValues();

                for (auto element : valueList) {
                    interpreter_value value = *(element.value);
                    if (std::holds_alternative<std::shared_ptr<FigureValue>>(value)) {
                        this->figuresToDraw.push_back(std::get<std::shared_ptr<FigureValue>>(value).get());
                    } else {
                        this->handleRuntimeError(this->funcCallPosition, L"List contains other elements than figures.");
                    }
                }

                GtkWidget *window;
                GtkWidget *darea;


                gtk_init(NULL, NULL);

                window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

                darea = gtk_drawing_area_new();
                gtk_container_add(GTK_CONTAINER(window), darea);

                g_signal_connect(G_OBJECT(darea), "draw",
                                 G_CALLBACK(on_draw_event), this);
                g_signal_connect(window, "destroy",
                                 G_CALLBACK(gtk_main_quit), NULL);

                gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_WINDOW(window), this->actualPaneResolution.first, this->actualPaneResolution.second);
                gtk_window_set_title(GTK_WINDOW(window), "GTK window");

                gtk_widget_show_all(window);

                gtk_main();

                this->figuresToDraw.clear();

                this->lastResult = std::monostate();
            }},
            {L"input", [this](){
                this->requireArgNum(L"input()", 0, L"no arguments");
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                std::wstring result;
                std::wcin >> result;
                this->lastResult = result;
            }},
            {L"Circle", [this](){
                this->requireArgNumBetween(L"Circle()", 0, 3, L"(point centre, double radius, list color) arguments");
                std::shared_ptr<PointValue> centrePoint = std::make_shared<PointValue>(0, 0);
                double radius = 1.0;
                if (!this->functionCallParams.empty()) {
                    this->requireArgType(L"circle centre", POINT_VARIABLE);
                    interpreter_value passedCentrePoint = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    auto passedCentrePointValue = std::get<std::shared_ptr<PointValue>>(passedCentrePoint);
                    double xCoord = std::get<double>(*(passedCentrePointValue->getX().value));
                    double yCoord = std::get<double>(*(passedCentrePointValue->getY().value));
                    centrePoint = std::make_shared<PointValue>(xCoord, yCoord);
                    if (!this->functionCallParams.empty()) {
                        this->requireArgType(L"radius", DOUBLE_VARIABLE);
                        interpreter_value passedRadius = this->functionCallParams.front();
                        this->functionCallParams.pop();
                        radius = std::get<double>(passedRadius);


                        std::shared_ptr<ListValue> colorParam = this->consumeColorParam();
                        if (colorParam) {
                            this->lastResult = std::make_shared<FigureValue>(AssignableValue(centrePoint), radius, AssignableValue(colorParam));
                            return;
                        }
                    }
                }
                this->lastResult = std::make_shared<FigureValue>(AssignableValue(centrePoint), radius);
            }},
        }
    ),
    internalListFunctions(
        {
            {L"append", [this](ListValue * listValue){
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                while(!(funcCallParams.empty())) {
                    AssignableValue value = AssignableValue(funcCallParams.front());
                    listValue->append(value);
                    funcCallParams.pop();
                }
                this->lastResult = listValue->shared_from_this();
            }},
            {L"delete", [this](ListValue * listValue){
                this->requireArgNum(L".delete()", 1, L"(int index) argument");
                this->requireArgType(L"removed index", INT_VARIABLE);
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                int removedIndex = std::get<int>(value);
                if (listValue->len() <= removedIndex) {
                    this->handleRuntimeError(this->funcCallPosition, L"Removed index out of range");
                }
                listValue->remove(removedIndex);
                this->lastResult = listValue->shared_from_this();
            }},
            {L"len", [this](ListValue * listValue){
                this->requireArgNum(L".len()", 0, L"no arguments");
                this->lastResult = (int) listValue->len();
            }},
        }
    ),
    internalFigureFunctions(
            {
                {L"circ", [this](FigureValue * figureValue){
                    this->requireArgNum(L".circ()", 0, L"no arguments");
                    auto & points = figureValue->getPoints();
                    auto radius = figureValue->getRadius().value;
                    if (!std::holds_alternative<std::monostate>(*radius)) {
                        double rVal = std::get<double>(*radius);
                        this->lastResult = 2.0 * M_PI * rVal;
                        return;
                    }
                    if (points.size() == 1) {
                        this->lastResult = 0.0;
                        return;
                    }
                    std::vector<PointValue *> orderedPoints;
                    for (auto & namedPoint : points) {
                        orderedPoints.push_back(std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value)).get());
                    }
                    double circ = 0.0;
                    PointValue * prevPoint;
                    PointValue * currentPoint;
                    double p1_x;
                    double p1_y;
                    double p2_x;
                    double p2_y;
                    for (int i = 1; i<orderedPoints.size(); i++) {
                        prevPoint = orderedPoints[i - 1];
                        currentPoint = orderedPoints[i];
                        p1_x = std::get<double>(*(currentPoint->getX().value));
                        p1_y = std::get<double>(*(currentPoint->getY().value));
                        p2_x = std::get<double>(*(prevPoint->getX().value));
                        p2_y = std::get<double>(*(prevPoint->getY().value));
                        circ += sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
                    }
                    p1_x = std::get<double>(*(orderedPoints[0]->getX().value));
                    p1_y = std::get<double>(*(orderedPoints[0]->getY().value));
                    p2_x = std::get<double>(*(orderedPoints.back()->getX().value));
                    p2_y = std::get<double>(*(orderedPoints.back()->getY().value));
                    circ += sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
                    this->lastResult = circ;
                }},
                {L"area", [this](FigureValue * figureValue){
                    this->requireArgNum(L".area()", 0, L"no arguments");
                    auto & points = figureValue->getPoints();
                    auto radius = figureValue->getRadius().value;
                    if (!std::holds_alternative<std::monostate>(*radius)) {
                        double rVal = std::get<double>(*radius);
                        this->lastResult = M_PI_2 * rVal * rVal;
                        return;
                    }
                    if (points.size() == 1) {
                        this->lastResult = 0.0;
                        return;
                    }
                    std::vector<PointValue *> orderedPoints;
                    for (auto & namedPoint : points) {
                        orderedPoints.push_back(std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value)).get());
                    }
                    double area = 0.0;
                    PointValue * prevPoint;
                    PointValue * currentPoint;
                    double p1_x;
                    double p1_y;
                    double p2_x;
                    double p2_y;
                    for (int i = 1; i<orderedPoints.size(); i++) {
                        prevPoint = orderedPoints[i - 1];
                        currentPoint = orderedPoints[i];
                        p1_x = std::get<double>(*(currentPoint->getX().value));
                        p1_y = std::get<double>(*(currentPoint->getY().value));
                        p2_x = std::get<double>(*(prevPoint->getX().value));
                        p2_y = std::get<double>(*(prevPoint->getY().value));
                        area += p1_x*p2_y - p1_y*p2_x;
                    }
                    p1_x = std::get<double>(*(orderedPoints[0]->getX().value));
                    p1_y = std::get<double>(*(orderedPoints[0]->getY().value));
                    p2_x = std::get<double>(*(orderedPoints.back()->getX().value));
                    p2_y = std::get<double>(*(orderedPoints.back()->getY().value));
                    area += p1_x*p2_y - p1_y*p2_x;
                    area /= 2.0;
                    this->lastResult = area;
                }},
                {L"scale", [this](FigureValue * figureValue){
                    this->requireArgNum(L".scale()", 1, L"(double scale) argument");
                    this->requireArgType(L"scale", DOUBLE_VARIABLE);
                    auto & points = figureValue->getPoints();
                    interpreter_value scaleParam = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    double scale = std::get<double>(scaleParam);
                    double p1_x;
                    double p1_y;

                    for (auto & namedPoint : points) {
                        std::shared_ptr<PointValue> pointValue = std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value));
                        p1_x = std::get<double>(*(pointValue->getX().value));
                        p1_y = std::get<double>(*(pointValue->getY().value));
                        p1_x *= scale;
                        p1_y *= scale;
                        *(pointValue->getX().value) = p1_x;
                        *(pointValue->getY().value) = p1_y;
                    }
                    auto radius = figureValue->getRadius().value;
                    if (!std::holds_alternative<std::monostate>(*radius)) {
                        figureValue->setRadius(std::get<double>(*radius)*scale);
                    }
                    this->lastResult = figureValue->shared_from_this();
                }},
                {L"rotate", [this](FigureValue * figureValue){
                    this->requireArgNum(L".rotate()", 2, L"(point rotationPoint, double angle) arguments");
                    this->requireArgType(L"rotation point", POINT_VARIABLE);
                    auto & points = figureValue->getPoints();
                    interpreter_value rotationPoint = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    PointValue * rotationPointVal = std::get<std::shared_ptr<PointValue>>(rotationPoint).get();
                    double rotation_point_x = std::get<double>(*(rotationPointVal->getX().value));
                    double rotation_point_y = std::get<double>(*(rotationPointVal->getY().value));
                    this->requireArgType(L"rotation angle", DOUBLE_VARIABLE);
                    interpreter_value angleParam = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    double angle = std::get<double>(angleParam);
                    double p1_x;
                    double p1_y;
                    double sin_rot = sin(angle);
                    double cos_rot = cos(angle);

                    for (auto & namedPoint : points) {
                        std::shared_ptr<PointValue> pointValue = std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value));
                        p1_x = std::get<double>(*(pointValue->getX().value));
                        p1_y = std::get<double>(*(pointValue->getY().value));
                        p1_x -= rotation_point_x;
                        p1_y -= rotation_point_y;
                        p1_x = p1_x * cos_rot - p1_y * sin_rot;
                        p1_y = p1_x * sin_rot + p1_y * cos_rot;
                        p1_x += rotation_point_x;
                        p1_y += rotation_point_y;
                        *(pointValue->getX().value) = p1_x;
                        *(pointValue->getY().value) = p1_y;
                    }
                    this->lastResult = figureValue->shared_from_this();
                }},
                {L"transport", [this](FigureValue * figureValue){
                    this->requireArgNum(L".transport()", 1, L"(point transportVector) argument");
                    this->requireArgType(L"transport vector", POINT_VARIABLE);
                    interpreter_value transportVector = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    PointValue * transportVectorVal = std::get<std::shared_ptr<PointValue>>(transportVector).get();
                    double transport_x = std::get<double>(*(transportVectorVal->getX().value));
                    double transport_y = std::get<double>(*(transportVectorVal->getY().value));
                    auto & points = figureValue->getPoints();
                    double p1_x;
                    double p1_y;

                    for (auto & namedPoint : points) {
                        std::shared_ptr<PointValue> pointValue = std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value));
                        p1_x = std::get<double>(*(pointValue->getX().value));
                        p1_y = std::get<double>(*(pointValue->getY().value));
                        p1_x += transport_x;
                        p1_y += transport_y;
                        *(pointValue->getX().value) = p1_x;
                        *(pointValue->getY().value) = p1_y;
                    }
                    this->lastResult = figureValue->shared_from_this();
                }},
                {L"copy", [this](FigureValue * figureValue){
                    this->requireArgNum(L".copy()", 0, L"no arguments");
                    auto & points = figureValue->getPoints();
                    std::map<std::wstring, AssignableValue> newFigurePoints;
                    auto color = std::get<std::shared_ptr<ListValue>>(*(figureValue->getColor().value))->getValues();
                    int r = std::get<int>(*(color[0].value));
                    int g = std::get<int>(*(color[1].value));
                    int b = std::get<int>(*(color[2].value));
                    ListValue newColor = ListValue(std::vector<AssignableValue>({AssignableValue(r), AssignableValue(g), AssignableValue(b)}));

                    for (auto & namedPoint : points) {
                        std::shared_ptr<PointValue> pointValue = std::get<std::shared_ptr<PointValue>>(*(namedPoint.second.value));
                        double p1_x = std::get<double>(*(pointValue->getX().value));
                        double p1_y = std::get<double>(*(pointValue->getY().value));
                        std::shared_ptr<PointValue> newPoint = std::make_shared<PointValue>(p1_x, p1_y);
                        newFigurePoints[namedPoint.first] = AssignableValue(newPoint);
                    }
                    this->lastResult = std::make_shared<FigureValue>(newFigurePoints, AssignableValue(std::make_shared<ListValue>(newColor)));
                }},
            }
        ),
        requiredTypeErrorMap(
            {
                    {INT_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<int>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {DOUBLE_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<double>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {BOOL_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<bool>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {NONE_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<std::monostate>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {STRING_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<std::wstring>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {POINT_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<std::shared_ptr<PointValue>>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {FIGURE_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<std::shared_ptr<FigureValue>>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
                    {LIST_VARIABLE, [this](const Position &position, const interpreter_value &expressionValue,const std::wstring &errorMessage) {
                        if (!std::holds_alternative<std::shared_ptr<ListValue>>(expressionValue)) {
                            this->handleRuntimeError(position, errorMessage);
                        }
                    }},
            }
        )
{
};
