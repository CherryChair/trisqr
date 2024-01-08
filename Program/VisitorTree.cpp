//
// Created by mpkow on 14.12.2023.
//

#include "VisitorTree.h"

static const std::unordered_map<short int, std::wstring> variable_type_representation= {
        {STRING_VARIABLE,   L"string"},
        {INT_VARIABLE,      L"int"},
        {DOUBLE_VARIABLE,   L"double"},
        {BOOL_VARIABLE,     L"bool"},
        {NONE_VARIABLE,     L"none"},
        {FIGURE_VARIABLE,   L"figure"},
        {POINT_VARIABLE,    L"point"},
};


void VisitorTree::visit(std::unique_ptr<ExpressionOr> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionOr:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionAnd> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionAnd:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompEq> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompEq:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompNeq> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompNeq:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompLeq> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompLeq:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompGeq> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompGeq:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompGreater> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompGreater:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionCompLess> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompLess:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionAdd> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionAdd:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionSub> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionSub:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionMul> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionMul:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionDiv> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionDiv:");
    e->leftExpression->accept(*this);
    e->rightExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionIs> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionIs:");
    e->expression->accept(*this);
    tree.push_back(tab_string + L"is type: " + variable_type_representation.at(e->checkedType));
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionTo> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionTo:");
    e->expression->accept(*this);
    tree.push_back(tab_string + L"to type: " + variable_type_representation.at(e->conversionType));
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionNeg> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionNeg:");
    e->expression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionNegMinus> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionNegMinus:");
    e->expression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionValueList> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueList:");
    auto expressions = e->expressions;
    for (auto & expression : expressions) {//TODO źle
        expression->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionValuePoint> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValuePoint:");
    e->xCoord->accept(*this);

    e->yCoord->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionValueLiteral> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueLiteral:");
    switch (e->value.index()){
        case 0: {
            int value = std::get<int>(e->value);
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 1: {
            double value = std::get<double>(e->value);
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 2: {
            std::wstring value = std::get<std::wstring>(e->value);
            tree.push_back(tab_string + L"value: " + value);
            break;
        }
        case 3: {
            bool value = std::get<bool>(e->value);
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 4: {
            tree.push_back(tab_string + L"value: none");
        }
    }
//    std::visit([](auto & x) -> void {std::wcout << x;}, e->value);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ExpressionValueBrackets> & e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueBrackets:");
    e->expression->accept(*this);
    this->tabs--;
}





void VisitorTree::visit(std::unique_ptr<WhileStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"WhileStatement:");
    s->conditionAndBlock->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<IfStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IfStatement:");
    s->ifConditionAndBlock->accept(*this);
    auto elsifCondAndBlock = s->elsifConditionsAndBlocks;
    if (!elsifCondAndBlock.empty()) {
        for (auto & condAndBlock : elsifCondAndBlock) {
            condAndBlock->accept(*this);
        }
    } else {
        tree.push_back(tab_string + L"null");
    }

    if (auto & elseCodeBlock = s->elseCodeBlock) {
        elseCodeBlock->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ForStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ForStatement:");
    tree.push_back(tab_string + L"ForStatement.VariableName:" + s->identifier);
    s->expression->accept(*this);
    s->block->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ForRangeStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ForRangeStatement:");
    tree.push_back(tab_string + L"ForRangeStatement.VariableName:" + s->identifier);
    s->leftExpression->accept(*this);
    s->rightExpression->accept(*this);
    s->block->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<DeclarationStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"DeclarationStatement:");
    tree.push_back(tab_string + L"DeclarationStatement.VariableName:" + s->identifierName);
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ReturnStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ReturnStatement:");
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}

void VisitorTree::visit(std::unique_ptr<ConditionAndBlock> & cb) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ConditionAndBlock:");
    cb->condition->accept(*this);

    cb->condition->accept(*this);
    this->tabs--;
}

void VisitorTree::visit(std::unique_ptr<IdentifierExpressionStatement> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierExpressionStatement:");
    s->identifierExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<IdentifierStatementAssign> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierStatementAssign:");
    s->identifierStatement->accept(*this);

    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<ObjectAccessExpression> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ObjectAccessExpression:");
    s->leftExpression->accept(*this);

    if (auto & rightStatement = s->rightExpression) {
        rightStatement->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<IdentifierListIndexExpression> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierListIndexExpression:");
    s->leftExpression->accept(*this);

    auto & expression = s->indexExpression;
    expression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<IdentifierFunctionCallExpression> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierFunctionCallExpression:");
    s->identifierExpression->accept(*this);

    auto expressions = s->expressions;
    for (auto & expression : expressions) {
        expression->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<IdentifierExpression> & s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierExpression:");
    tree.push_back(tab_string + L"Name: " + s->identifierName);
    this->tabs--;
}






void VisitorTree::visit(std::unique_ptr<CodeBlock> & cb) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"CodeBlock:");
    auto statements = cb->statements;
    for (auto & statement : statements) {
        statement->accept(*this);
    }
    this->tabs--;
}



void VisitorTree::visit(std::unique_ptr<Parameter> & p) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Param:");
    tree.push_back(tab_string + L"Name: " + p->name);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<FigureParameter> & p) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"FigureParam:");
    tree.push_back(tab_string + L"Name: " + p->name);
    p->valueExpression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<FigureDeclaration> & fd) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Figure:");
    tree.push_back(tab_string + L"Name: " + fd->name);
    auto params = fd->params;
    for (auto & param : params) {
        param->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<FuncDeclaration> & fd) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Func:");
    tree.push_back(tab_string + L"Name: " + fd->name);
    auto params = fd->params;
    for (auto & param : params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(std::unique_ptr<Program> & p) {
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Program:");
    auto & figures = p->figures;
    auto & functions = p->functions;
    for(auto & figure: figures) {
        figure.second->accept(*this);
    }
    for(auto & function: functions) {
        function.second->accept(*this);
    }
}

void VisitorTree::printTree(std::wostream & os) {
    for(auto element: this->tree) {
        os << element << std::endl;
    }
}