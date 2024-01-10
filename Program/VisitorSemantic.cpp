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
    s->expression->accept(*this);
}

void VisitorInterpreter::visit(ReturnStatement * s) {
    s->expression->accept(*this);
}

void VisitorInterpreter::visit(ConditionAndBlock * cb) {
    cb->condition->accept(*this);

    cb->block->accept(*this);
}

void VisitorInterpreter::visit(IdentifierExpressionStatement * s) {
    s->identifierExpression->accept(*this);
}
void VisitorInterpreter::visit(IdentifierStatementAssign * s) {
    s->identifierExpression->accept(*this);
    s->expression->accept(*this);
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