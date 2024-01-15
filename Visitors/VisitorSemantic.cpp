//
// Created by mpkow on 14.12.2023.
//

#include "VisitorSemantic.h"

void VisitorSemantic::visit(ExpressionOr * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionAnd * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompEq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompNeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompLeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompGeq * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompGreater * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionCompLess * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionAdd * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionSub * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionMul * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionDiv * e) {
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
}
void VisitorSemantic::visit(ExpressionIs * e) {
    e->expression->accept(*this);
}
void VisitorSemantic::visit(ExpressionTo * e) {
    e->expression->accept(*this);
}
void VisitorSemantic::visit(ExpressionNeg * e) {
    e->expression->accept(*this);
}
void VisitorSemantic::visit(ExpressionNegMinus * e) {
    e->expression->accept(*this);
}
void VisitorSemantic::visit(ExpressionValueList * e) {
    for (auto const & expression : e->expressions) {
        expression->accept(*this);
    }
}
void VisitorSemantic::visit(ExpressionValuePoint * e) {
    e->xCoord->accept(*this);

    e->yCoord->accept(*this);
}
void VisitorSemantic::visit(ExpressionValueLiteral * e) {
}
void VisitorSemantic::visit(ExpressionValueBrackets * e) {
    e->expression->accept(*this);
}





void VisitorSemantic::visit(WhileStatement * s) {
    this->addNewScope();
    s->conditionAndBlock->accept(*this);
    this->popScope();
}
void VisitorSemantic::visit(IfStatement * s) {
    this->addNewScope();
    s->ifConditionAndBlock->accept(*this);
    this->popScope();

    for (auto const & condAndBlock : s->elsifConditionsAndBlocks) {
        this->addNewScope();
        condAndBlock->accept(*this);
        this->popScope();
    }

    this->addNewScope();
    if (auto & elseCodeBlock = s->elseCodeBlock) {
        elseCodeBlock->accept(*this);
    }
    this->popScope();
}
void VisitorSemantic::visit(ForStatement * s) {
    s->expression->accept(*this);
    s->block->accept(*this);
}
void VisitorSemantic::visit(ForRangeStatement * s) {
    s->leftExpression->accept(*this);
    s->rightExpression->accept(*this);
    s->block->accept(*this);
}
void VisitorSemantic::visit(DeclarationStatement * s) {
    found_type foundType = this->findVariable(s->identifierName);
    if (foundType == NOT_FOUND) {
        this->insertVariableNameToCurrentScope(s->identifierName);
    } else {
        this->handleDeclarationError(s->position, s->identifierName, foundType);
    }
}

void VisitorSemantic::visit(DeclarationAssignStatement * s) {
    found_type foundType = this->findVariable(s->identifierName);
    if (foundType == NOT_FOUND) {
        this->insertVariableNameToCurrentScope(s->identifierName);
    } else {
        this->handleDeclarationError(s->position, s->identifierName, foundType);
    }
    s->expression->accept(*this);
}

void VisitorSemantic::visit(ReturnStatement * s) {
    s->expression->accept(*this);
}

void VisitorSemantic::visit(ConditionAndBlock * cb) {
    cb->condition->accept(*this);

    cb->block->accept(*this);
}

void VisitorSemantic::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
}
void VisitorSemantic::visit(IdentifierStatementAssign * s) {
    s->identifierExpression->accept(*this);
    s->expression->accept(*this);
}
void VisitorSemantic::visit(ObjectAccessExpression * e) {
    e->leftExpression->accept(*this);
    this->objectAccess = true;
    e->rightExpression->accept(*this);
    this->objectAccess = false;
}
void VisitorSemantic::visit(IdentifierListIndexExpression * e) {
    e->leftExpression->accept(*this);

    auto & expression = e->indexExpression;
    expression->accept(*this);
}
void VisitorSemantic::visit(IdentifierFunctionCallExpression * e) {
    this->functionCall = true;
    e->identifierExpression->accept(*this);
    this->functionCall = false;

    for (auto const & expression : e->expressions) {
        expression->accept(*this);
    }
}
void VisitorSemantic::visit(IdentifierExpression * e) {
    found_type ft = this->findVariable(e->identifierName);

    if (this->functionCall) {
        if (ft != FIGURE_FOUND && ft != FUNCTION_FOUND && ft != LIST_METHOD_FOUND && ft != FIGURE_METHOD_FOUND) {
            this->handleSemanticError(e->position, L"Identifier to function or method " + e->identifierName + L" not found");
        }
        if ((ft == LIST_METHOD_FOUND || ft == FIGURE_METHOD_FOUND) && !this->objectAccess) {
            this->handleSemanticError(e->position, e->identifierName + L" is a method not a function.");
        }
    } else if (this->objectAccess) {
        if (ft != IDENTIFIER_FOUND && ft != NOT_FOUND && ft != COLOR_FOUND) {//NOT_FOUND dla elementów figur, można też przeszukać wszysytkie parametry figur i odłożyć na mapę
            this->handleSemanticError(e->position, L"Identifier " + e->identifierName + L" is not a method or member of figure or point.");
        }
    } else if (ft != IDENTIFIER_FOUND) {
        this->handleSemanticError(e->position, L"Identifier " + e->identifierName + L" not found.");
    }
}




void VisitorSemantic::visit(CodeBlock * cb) {
    for (auto const & statement : cb->statements) {
        statement->accept(*this);
    }
}

void VisitorSemantic::visit(Parameter * p) {
    found_type type = findVariable(p->name);
    if (type != NOT_FOUND) {
        this->handleDeclarationError(p->position, p->name, type);
    } else {
        this->insertVariableNameToCurrentScope(p->name);
    }
}

void VisitorSemantic::visit(FigureParameter * p) {
    found_type type = findVariable(p->name);
    if (type == COLOR_FOUND) {
    } else if (type != NOT_FOUND) {
        this->handleDeclarationError(p->position, p->name, type);
    }
    if (figureScopeSem.getVariables().find(p->name) != figureScopeSem.getVariables().end()) {
        this->handleSemanticError(p->position, L"Memeber of figure " + p->name + L" redefined.");
    }
    figureScopeSem.getVariables().insert(p->name);
    p->valueExpression->accept(*this);
}

void VisitorSemantic::visit(FigureDeclaration * fd) {
    lastFigurePos = fd->position;
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
    this->figureScopeSem.getVariables().clear();
    this->lastFigurePos = fd->position;
}

void VisitorSemantic::visit(FuncDeclaration * fd) {
    lastFuncPos = fd->position;
    this->addNewScope();
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
    this->popScope();
    this->lastFuncPos = fd->position;
}

void VisitorSemantic::visit(Program * p) {
    for(auto const & figure: p->figures) {
        if (figuresDeclNum.find(figure.first) == figuresDeclNum.end()) {
            figuresDeclNum[figure.first] = 1;
        } else {
            figuresDeclNum[figure.first] += 1;
        }
    }
    for(auto const & function: p->functions) {
        if (functionsDeclNum.find(function.first) == functionsDeclNum.end()) {
            functionsDeclNum[function.first] = 1;
        } else {
            functionsDeclNum[function.first] += 1;
        }
    }
    for(auto const & figure: p->figures) {
        figure.second->accept(*this);
        checkFunctionOrFigure(figure.first, figuresDeclNum, functionsDeclNum, L"figure", L"function", this->lastFigurePos);
    }
    for(auto const & function: p->functions) {
        function.second->accept(*this);
        checkFunctionOrFigure(function.first, functionsDeclNum, figuresDeclNum, L"function", L"figure", this->lastFuncPos);
    }
    if (semanticError) {
        throw;
    }
}

void
VisitorSemantic::checkFunctionOrFigure(const std::wstring &name, std::unordered_map<std::wstring, int> &multiplesSet,
                                       std::unordered_map<std::wstring, int> &presenceSet,
                                       const std::wstring &objectName, const std::wstring &comparedToObjectName,
                                       const Position & position)
{
    std::wstring uObjectName = name;
    uObjectName[0] = std::toupper(uObjectName[0]);
    if (multiplesSet[name] > 1) {
        this->handleSemanticError(position, L"Multiple declarations of " + objectName + L" " + name);
    }
    if (presenceSet.find(name) != presenceSet.end()) {
        this->handleSemanticError(position, uObjectName + L" name same as " + comparedToObjectName + L" " + name);
    }
    if (checkIfSpecialFunction(name)) {
        this->handleSemanticError(position, uObjectName + L" name same as standard function " + name);
    }
    if (checkIfMethod(name)) {
        this->handleSemanticError(position, uObjectName +L" name same as standard method " + name);
    }
}

found_type VisitorSemantic::findVariable(const std::wstring & variableName) {
    if (special_function_keywords.find(variableName) != special_function_keywords.find(variableName)) {
        return FUNCTION_FOUND;
    }
    if (special_list_keywords.find(variableName) != special_list_keywords.find(variableName)) {
        return LIST_METHOD_FOUND;
    }
    if (special_figure_keywords.find(variableName) != special_figure_keywords.find(variableName)) {
        if (variableName == L"color") {
            return COLOR_FOUND;
        } else {
            return FIGURE_METHOD_FOUND;
        }
    }
    if (functionsDeclNum.find(variableName) != functionsDeclNum.end()) {
        return FUNCTION_FOUND;
    }
    if (figuresDeclNum.find(variableName) != figuresDeclNum.end()) {
        return FIGURE_FOUND;
    }
    auto & currentScopeSems = this->functionContexts.getScopes();
    for (auto iter = currentScopeSems.rbegin(); iter != currentScopeSems.rend(); iter++) {
        auto & currentScopeSemVariables = iter->getVariables();
        if (currentScopeSemVariables.find(variableName) != currentScopeSemVariables.end()) {
            return IDENTIFIER_FOUND;
        }

    }
    return NOT_FOUND;
}

bool VisitorSemantic::checkIfSpecialFunction(const std::wstring & variableName) {
    return special_function_keywords.find(variableName) != special_function_keywords.find(variableName);
}

bool VisitorSemantic::checkIfMethod(const std::wstring & variableName) {
    if (special_list_keywords.find(variableName) != special_list_keywords.find(variableName)) {
        return true;
    }
    if (special_figure_keywords.find(variableName) != special_figure_keywords.find(variableName)) {
        if (variableName != L"color") {
            return true;
        }
    }
    return false;
}

ScopeSem &VisitorSemantic::addNewScope() {
    this->functionContexts.getScopes().push_back(ScopeSem());
    return this->functionContexts.getScopes().back();
}

void VisitorSemantic::popScope() {
    this->functionContexts.getScopes().pop_back();
}

void VisitorSemantic::handleDeclarationError(const Position &pos, const std::wstring & name, found_type foundType) {
    this->errorHandler->onSemanticError(pos, L"Redeclaration of " + found_type_representation.at(foundType) + name + L".");
    semanticError = true;
}

void VisitorSemantic::handleSemanticError(const Position &pos, const std::wstring &errorMsg) {
    this->errorHandler->onSemanticError(pos, errorMsg);
    semanticError = true;
}

void VisitorSemantic::insertVariableNameToCurrentScope(const std::wstring &name) {
    this->functionContexts.getScopes().back().getVariables().insert(name);
}