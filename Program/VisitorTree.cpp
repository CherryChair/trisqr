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


void VisitorTree::visit(ExpressionOr * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionOr:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionAnd * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionAnd:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompEq * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompEq:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompNeq * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompNeq:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompLeq * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompLeq:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompGeq * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompGeq:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompGreater * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompGreater:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionCompLess * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionCompLess:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionAdd * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionAdd:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionSub * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionSub:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionMul * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionMul:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionDiv * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionDiv:");
    e->getLeftExpression()->accept(*this);
    e->getRightExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionIs * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionIs:");
    e->getExpression()->accept(*this);
    tree.push_back(tab_string + L"is type: " + variable_type_representation.at(e->getCheckedType()));
    this->tabs--;
}
void VisitorTree::visit(ExpressionTo * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionTo:");
    e->getExpression()->accept(*this);
    tree.push_back(tab_string + L"to type: " + variable_type_representation.at(e->getConversionType()));
    this->tabs--;
}
void VisitorTree::visit(ExpressionNeg * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionNeg:");
    e->getExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionNegMinus * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionNegMinus:");
    e->getExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionValueList * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueList:");
    auto expressions = e->getExpressions();
    for (auto expression : expressions) {
        expression->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(ExpressionValuePoint * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValuePoint:");
    e->getXCoord()->accept(*this);

    e->getYCoord()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ExpressionValueLiteral * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueLiteral:");
    switch (e->getValue().index()){
        case 0: {
            int value = std::get<int>(e->getValue());
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 1: {
            double value = std::get<double>(e->getValue());
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 2: {
            std::wstring value = std::get<std::wstring>(e->getValue());
            tree.push_back(tab_string + L"value: " + value);
            break;
        }
        case 3: {
            bool value = std::get<bool>(e->getValue());
            tree.push_back(tab_string + L"value: " + std::to_wstring(value));
            break;
        }
        case 4: {
            tree.push_back(tab_string + L"value: none");
        }
    }
//    std::visit([](auto & x) -> void {std::wcout << x;}, e->getValue());
    this->tabs--;
}
void VisitorTree::visit(ExpressionValueBrackets * e) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ExpressionValueBrackets:");
    e->getExpression()->accept(*this);
    this->tabs--;
}





void VisitorTree::visit(WhileStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"WhileStatement:");
    s->getConditionAndBlock()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(IfStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IfStatement:");
    s->getIfConditionAndBlock()->accept(*this);
    auto elsifCondAndBlock = s->getElsifConditionsAndBlocks();
    if (!elsifCondAndBlock.empty()) {
        for (auto condAndBlock : elsifCondAndBlock) {
            condAndBlock->accept(*this);
        }
    } else {
        tree.push_back(tab_string + L"null");
    }

    if (auto elseCodeBlock = s->getElseCodeBlock()) {
        elseCodeBlock->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(ForStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ForStatement:");
    tree.push_back(tab_string + L"ForStatement.VariableName:" + s->getIdentifier());
    s->getExpression()->accept(*this);
    s->getBlock()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(ForRangeStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ForRangeStatement:");
    tree.push_back(tab_string + L"ForRangeStatement.VariableName:" + s->getIdentifier());
    s->getLeftExpression()->accept(*this);
    s->getRightExpression()->accept(*this);
    s->getBlock()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(DeclarationStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"DeclarationStatement:");
    tree.push_back(tab_string + L"DeclarationStatement.VariableName:" + s->getIdentifierName());
    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(ReturnStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ReturnStatement:");
    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}

void VisitorTree::visit(ConditionAndBlock * cb) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ConditionAndBlock:");
    cb->getCondition()->accept(*this);

    cb->getBlock()->accept(*this);
    this->tabs--;
}

void VisitorTree::visit(IdentifierExpressionStatement * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierExpressionStatement:");
    s->getIdentifierExpression()->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(IdentifierStatementAssign * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierStatementAssign:");
    s->getIdentifierStatement()->accept(*this);

    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(ObjectAccessExpression * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"ObjectAccessExpression:");
    s->getLeftExpression()->accept(*this);

    if (auto rightStatement = s->getRightExpression()) {
        rightStatement->accept(*this);
    } else {
        tree.push_back(tab_string + L"null");
    }
    this->tabs--;
}
void VisitorTree::visit(IdentifierListIndexExpression * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierListIndexExpression:");
    s->getLeftExpression()->accept(*this);

    auto expression = s->getIndexExpression();
    expression->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(IdentifierFunctionCallExpression * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierFunctionCallExpression:");
    s->getIdentifierExpression()->accept(*this);

    auto expressions = s->getExpressions();
    for (auto expression : expressions) {
        expression->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(IdentifierExpression * s) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"IdentifierExpression:");
    tree.push_back(tab_string + L"Name: " + s->getIdentifierName());
    this->tabs--;
}






void VisitorTree::visit(CodeBlock* cb) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"CodeBlock:");
    auto statements = cb->getStatements();
    for (auto statement : statements) {
        statement->accept(*this);
    }
    this->tabs--;
}



void VisitorTree::visit(Parameter* p) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Param:");
    tree.push_back(tab_string + L"Name: " + p->getName());
    this->tabs--;
}
void VisitorTree::visit(FigureParameter* p) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"FigureParam:");
    tree.push_back(tab_string + L"Name: " + p->getName());
    auto value = p->getValue();
    value->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(FigureDeclaration* fd) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Figure:");
    tree.push_back(tab_string + L"Name: " + fd->getName());
    auto params = fd->getParams();
    for (auto param : params) {
        param->accept(*this);
    }
    this->tabs--;
}
void VisitorTree::visit(FuncDeclaration* fd) {
    this->tabs++;
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Func:");
    tree.push_back(tab_string + L"Name: " + fd->getName());
    auto params = fd->getParams();
    auto codeBlock = fd->getCodeBlock();
    for (auto param : params) {
        param->accept(*this);
    }
    codeBlock->accept(*this);
    this->tabs--;
}
void VisitorTree::visit(Program* p) {
    std::wstring tab_string = std::wstring(this->tabs, '\t');
    tree.push_back(tab_string + L"Program:");
    auto figures = p->getFigures();
    auto functions = p->getFunctions();
    for(auto figure: figures) {
        figure.second->accept(*this);
    }
    for(auto function: functions) {
        function.second->accept(*this);
    }
}

void VisitorTree::printTree(std::wostream & os) {
    for(auto element: this->tree) {
        os << element << std::endl;
    }
}