//
// Created by mpkow on 14.12.2023.
//

#include "VisitorSemantic.h"

static const std::unordered_map<short int, std::wstring> variable_type_representation= {
        {STRING_VARIABLE,   L"string"},
        {INT_VARIABLE,      L"int"},
        {DOUBLE_VARIABLE,   L"double"},
        {BOOL_VARIABLE,     L"bool"},
        {NONE_VARIABLE,     L"none"},
        {FIGURE_VARIABLE,   L"figure"},
        {POINT_VARIABLE,    L"point"},
};


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
void VisitorSemantic::visit(ExpressionValueBrackets * e) {
    e->expression->accept(*this);
}





void VisitorSemantic::visit(WhileStatement * s) {
    s->conditionAndBlock->accept(*this);
}
void VisitorSemantic::visit(IfStatement * s) {
    s->ifConditionAndBlock->accept(*this);
    for (auto const & condAndBlock : s->elsifConditionsAndBlocks) {
        condAndBlock->accept(*this);
    }

    if (auto & elseCodeBlock = s->elseCodeBlock) {
        elseCodeBlock->accept(*this);
    } else {
    }
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
}

void VisitorSemantic::visit(DeclarationAssignStatement * s) {
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}

void VisitorSemantic::visit(ReturnStatement * s) {
    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}

void VisitorSemantic::visit(ConditionAndBlock * cb) {
    cb->condition->accept(*this);

    cb->condition->accept(*this);
}

void VisitorSemantic::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
}
void VisitorSemantic::visit(IdentifierStatementAssign * s) {
    s->identifierExpression->accept(*this);

    if (auto & expression = s->expression) {
        expression->accept(*this);
    } else {
    }
}
void VisitorSemantic::visit(ObjectAccessExpression * s) {
    s->leftExpression->accept(*this);

    if (auto & rightStatement = s->rightExpression) {
        rightStatement->accept(*this);
    } else {
    }
}
void VisitorSemantic::visit(IdentifierListIndexExpression * s) {
    s->leftExpression->accept(*this);

    auto & expression = s->indexExpression;
    expression->accept(*this);
}
void VisitorSemantic::visit(IdentifierFunctionCallExpression * s) {
    s->identifierExpression->accept(*this);

    for (auto const & expression : s->expressions) {
        expression->accept(*this);
    }
}
void VisitorSemantic::visit(IdentifierExpression * s) {

}




void VisitorSemantic::visit(CodeBlock * cb) {
    for (auto const & statement : cb->statements) {
        statement->accept(*this);
    }
}

void VisitorSemantic::visit(Parameter * p) {
}

void VisitorSemantic::visit(FigureParameter * p) {
    p->valueExpression->accept(*this);
}
void VisitorSemantic::visit(FigureDeclaration * fd) {
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
}
void VisitorSemantic::visit(FuncDeclaration * fd) {
    for (auto const & param : fd->params) {
        param->accept(*this);
    }
    fd->codeBlock->accept(*this);
}
void VisitorSemantic::visit(Program * p) {
    for(auto const & figure: p->figures) {
        figure.second->accept(*this);
    }
    for(auto const & function: p->functions) {
        function.second->accept(*this);
    }
}