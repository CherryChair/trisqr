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
    tree.push_back(L"ExpressionOr:");
    tree.push_back(L"BEGIN ExpressionOr.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionOr.LeftExpression");
    tree.push_back(L"BEGIN ExpressionOr.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionOr.RightExpression");
    tree.push_back(L"END ExpressionOr");
}
void VisitorTree::visit(ExpressionAnd * e) {
    tree.push_back(L"ExpressionAnd:");
    tree.push_back(L"BEGIN ExpressionAnd.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionAnd.LeftExpression");
    tree.push_back(L"BEGIN ExpressionAnd.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionAnd.RightExpression");
    tree.push_back(L"END ExpressionAnd");
}
void VisitorTree::visit(ExpressionCompEq * e) {
    tree.push_back(L"ExpressionCompEq:");
    tree.push_back(L"BEGIN ExpressionCompEq.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompEq.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompEq.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompEq.RightExpression");
    tree.push_back(L"END ExpressionCompEq");
}
void VisitorTree::visit(ExpressionCompNeq * e) {
    tree.push_back(L"ExpressionCompNeq:");
    tree.push_back(L"BEGIN ExpressionCompNeq.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompNeq.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompNeq.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompNeq.RightExpression");
    tree.push_back(L"END ExpressionCompNeq");
}
void VisitorTree::visit(ExpressionCompLeq * e) {
    tree.push_back(L"ExpressionCompLeq:");
    tree.push_back(L"BEGIN ExpressionCompLeq.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompLeq.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompLeq.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompLeq.RightExpression");
    tree.push_back(L"END ExpressionCompLeq");
}
void VisitorTree::visit(ExpressionCompGeq * e) {
    tree.push_back(L"ExpressionCompGeq:");
    tree.push_back(L"BEGIN ExpressionCompGeq.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompGeq.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompGeq.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompGeq.RightExpression");
    tree.push_back(L"END ExpressionCompGeq");
}
void VisitorTree::visit(ExpressionCompGreater * e) {
    tree.push_back(L"ExpressionCompGreater:");
    tree.push_back(L"BEGIN ExpressionCompGreater.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompGreater.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompGreater.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompGreater.RightExpression");
    tree.push_back(L"END ExpressionCompGreater");
}
void VisitorTree::visit(ExpressionCompLess * e) {
    tree.push_back(L"ExpressionCompLess:");
    tree.push_back(L"BEGIN ExpressionCompLess.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompLess.LeftExpression");
    tree.push_back(L"BEGIN ExpressionCompLess.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionCompLess.RightExpression");
    tree.push_back(L"END ExpressionCompLess");
}
void VisitorTree::visit(ExpressionAdd * e) {
    tree.push_back(L"ExpressionAdd:");
    tree.push_back(L"BEGIN ExpressionAdd.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionAdd.LeftExpression");
    tree.push_back(L"BEGIN ExpressionAdd.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionAdd.RightExpression");
    tree.push_back(L"END ExpressionAdd");
}
void VisitorTree::visit(ExpressionSub * e) {
    tree.push_back(L"ExpressionSub:");
    tree.push_back(L"BEGIN ExpressionSub.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionSub.LeftExpression");
    tree.push_back(L"BEGIN ExpressionSub.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionSub.RightExpression");
    tree.push_back(L"END ExpressionSub");
}
void VisitorTree::visit(ExpressionMul * e) {
    tree.push_back(L"ExpressionMul:");
    tree.push_back(L"BEGIN ExpressionMul.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionMul.LeftExpression");
    tree.push_back(L"BEGIN ExpressionMul.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionMul.RightExpression");
    tree.push_back(L"END ExpressionMul");
}
void VisitorTree::visit(ExpressionDiv * e) {
    tree.push_back(L"ExpressionDiv:");
    tree.push_back(L"BEGIN ExpressionDiv.LeftExpression");
    e->getLeftExpression()->accept(*this);
    tree.push_back(L"END ExpressionDiv.LeftExpression");
    tree.push_back(L"BEGIN ExpressionDiv.RightExpression");
    e->getRightExpression()->accept(*this);
    tree.push_back(L"END ExpressionDiv.RightExpression");
    tree.push_back(L"END ExpressionDiv");
}
void VisitorTree::visit(ExpressionIs * e) {
    tree.push_back(L"ExpressionIs:");
    tree.push_back(L"BEGIN ExpressionIs.Expression");
    e->getExpression()->accept(*this);
    tree.push_back(L"END ExpressionIs.Expression");
    tree.push_back(L"is type: " + variable_type_representation.at(e->getCheckedType()));
    tree.push_back(L"END ExpressionIs");
}
void VisitorTree::visit(ExpressionTo * e) {
    tree.push_back(L"ExpressionTo:");
    tree.push_back(L"BEGIN ExpressionTo.Expression");
    e->getExpression()->accept(*this);
    tree.push_back(L"END ExpressionTo.Expression");
    tree.push_back(L"to type: " + variable_type_representation.at(e->getConversionType()));
    tree.push_back(L"END ExpressionTo");
}
void VisitorTree::visit(ExpressionNeg * e) {
    tree.push_back(L"ExpressionNeg:");
    tree.push_back(L"BEGIN ExpressionNeg.Expression");
    e->getExpression()->accept(*this);
    tree.push_back(L"END ExpressionNeg.Expression");
    tree.push_back(L"END ExpressionNeg");
}
void VisitorTree::visit(ExpressionNegMinus * e) {
    tree.push_back(L"ExpressionNegMinus:");
    tree.push_back(L"BEGIN ExpressionNegMinus.Expression");
    e->getExpression()->accept(*this);
    tree.push_back(L"END ExpressionNegMinus.Expression");
    tree.push_back(L"END ExpressionNegMinus");
}
void VisitorTree::visit(ExpressionValueList * e) {
    tree.push_back(L"ExpressionValueList:");
    auto expressions = e->getExpressions();
    tree.push_back(L"BEGIN ExpressionValueList.Expressions");
    for (auto expression : expressions) {
        expression->accept(*this);
    }
    tree.push_back(L"END ExpressionValueList.Expressions");
    tree.push_back(L"END ExpressionValueList");
}
void VisitorTree::visit(ExpressionValuePoint * e) {
    tree.push_back(L"ExpressionValuePoint:");
    tree.push_back(L"BEGIN ExpressionValuePoint.XCoord");
    e->getXCoord()->accept(*this);
    tree.push_back(L"END ExpressionValuePoint.XCoord");

    tree.push_back(L"BEGIN ExpressionValuePoint.YCoord");
    e->getYCoord()->accept(*this);
    tree.push_back(L"END ExpressionValuePoint.YCoord");
    tree.push_back(L"END ExpressionValuePoint");
}
void VisitorTree::visit(ExpressionValueLiteral * e) {
    tree.push_back(L"ExpressionValueLiteral:");
    switch (e->getValue().index()){
        case 0: {
            int value = std::get<int>(e->getValue());
            tree.push_back(L"value: " + std::to_wstring(value));
            break;
        }
        case 1: {
            double value = std::get<double>(e->getValue());
            tree.push_back(L"value: " + std::to_wstring(value));
            break;
        }
        case 2: {
            std::wstring value = std::get<std::wstring>(e->getValue());
            tree.push_back(L"value: " + value);
            break;
        }
        case 3: {
            bool value = std::get<bool>(e->getValue());
            tree.push_back(L"value: " + std::to_wstring(value));
            break;
        }
        case 4: {
            tree.push_back(L"value: none");
        }
    }
//    std::visit([](auto & x) -> void {std::wcout << x;}, e->getValue());
    tree.push_back(L"END ExpressionValueLiteral");
}
void VisitorTree::visit(ExpressionValueBrackets * e) {
    tree.push_back(L"ExpressionValueBrackets:");
    tree.push_back(L"BEGIN ExpressionValueBrackets.Expression");
    e->getExpression()->accept(*this);
    tree.push_back(L"END ExpressionValueBrackets.Expression");
    tree.push_back(L"END ExpressionValueBrackets");
}





void VisitorTree::visit(WhileStatement * s) {
    tree.push_back(L"WhileStatement:");
    tree.push_back(L"BEGIN WhileStatement.ConditionAndBlock");
    s->getConditionAndBlock()->accept(*this);
    tree.push_back(L"END WhileStatement.ConditionAndBlock");
    tree.push_back(L"END WhileStatement");
}
void VisitorTree::visit(IfStatement * s) {
    tree.push_back(L"IfStatement:");
    tree.push_back(L"BEGIN IfStatement.IfConditionAndBlock");
    s->getIfConditionAndBlock()->accept(*this);
    tree.push_back(L"END IfStatement.IfConditionAndBlock");
    tree.push_back(L"BEGIN IfStatement.ElsifConditionsAndBlocks");
    auto elsifCondAndBlock = s->getElsifConditionsAndBlocks();
    if (!elsifCondAndBlock.empty()) {
        for (auto condAndBlock : elsifCondAndBlock) {
            condAndBlock->accept(*this);
        }
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END IfStatement.ElsifConditionsAndBlocks");
    tree.push_back(L"BEGIN IfStatement.ElseCodeBlock");

    if (auto elseCodeBlock = s->getElseCodeBlock()) {
        elseCodeBlock->accept(*this);
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END IfStatement.ElseCodeBlock");
    tree.push_back(L"END IfStatement");
}
void VisitorTree::visit(ForStatement * s) {
    tree.push_back(L"ForStatement:");
    tree.push_back(L"ForStatement.VariableName:" + s->getIdentifier());
    tree.push_back(L"BEGIN ForStatement.Expression");
    s->getExpression()->accept(*this);
    tree.push_back(L"END ForStatement.Expression");
    tree.push_back(L"BEGIN ForStatement.CodeBlock");
    s->getBlock()->accept(*this);
    tree.push_back(L"END ForStatement.CodeBlock");
    tree.push_back(L"END ForStatement");
}
void VisitorTree::visit(ForRangeStatement * s) {
    tree.push_back(L"ForRangeStatement:");
    tree.push_back(L"ForRangeStatement.VariableName:" + s->getIdentifier());
    tree.push_back(L"BEGIN ForRangeStatement.LeftExpression");
    s->getLeftExpression()->accept(*this);
    tree.push_back(L"END ForRangeStatement.LeftExpression");
    tree.push_back(L"BEGIN ForRangeStatement.RightExpression");
    s->getRightExpression()->accept(*this);
    tree.push_back(L"END ForRangeStatement.RightExpression");
    tree.push_back(L"BEGIN ForRangeStatement.CodeBlock");
    s->getBlock()->accept(*this);
    tree.push_back(L"END ForRangeStatement.CodeBlock");
    tree.push_back(L"END ForRangeStatement");
}
void VisitorTree::visit(DeclarationStatement * s) {
    tree.push_back(L"DeclarationStatement:");
    tree.push_back(L"DeclarationStatement.VariableName:" + s->getIdentifierName());
    tree.push_back(L"BEGIN DeclarationStatement.Expression");
    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END DeclarationStatement.Expression");
    tree.push_back(L"END DeclarationStatement");
}
void VisitorTree::visit(ReturnStatement * s) {
    tree.push_back(L"ReturnStatement:");
    tree.push_back(L"BEGIN ReturnStatement.Expression");
    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END ReturnStatement.Expression");
    tree.push_back(L"END ReturnStatement");
}

void VisitorTree::visit(ConditionAndBlock * cb) {
    tree.push_back(L"ConditionAndBlock:");
    tree.push_back(L"BEGIN ConditionAndBlock.Condition");
    cb->getCondition()->accept(*this);
    tree.push_back(L"END ConditionAndBlock.Condition");

    tree.push_back(L"BEGIN ConditionAndBlock.CodeBlock");
    cb->getBlock()->accept(*this);
    tree.push_back(L"END ConditionAndBlock.CodeBlock");
    tree.push_back(L"END ConditionAndBlock");
}


void VisitorTree::visit(IdentifierStatementAssign * s) {
    tree.push_back(L"IdentifierStatementAssign:");
    tree.push_back(L"BEGIN IdentifierStatementAssign.IdentifierExpression");
    s->getIdentifierExpression()->accept(*this);
    tree.push_back(L"END IdentifierStatementAssign.IdentifierExpression");

    tree.push_back(L"BEGIN IdentifierStatementAssign.Expression");
    if (auto expression = s->getExpression()) {
        expression->accept(*this);
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END IdentifierStatementAssign.Expression");
    tree.push_back(L"END IdentifierStatementAssign");
}
void VisitorTree::visit(IdentifierDotExpression * s) {
    tree.push_back(L"IdentifierDotExpression:");
    tree.push_back(L"BEGIN IdentifierDotExpression.LeftStatement");
    s->getLeftExpression()->accept(*this);
    tree.push_back(L"END IdentifierDotExpression.LeftStatement");

    tree.push_back(L"BEGIN IdentifierDotExpression.RightStatement");
    if (auto rightStatement = s->getRightExpression()) {
        rightStatement->accept(*this);
    } else {
        tree.push_back(L"null");
    }
    tree.push_back(L"END IdentifierDotExpression.RightStatement");
    tree.push_back(L"END IdentifierDotExpression");
}
void VisitorTree::visit(IdentifierListCallExpression * s) {
    tree.push_back(L"IdentifierListCallExpression:");
    tree.push_back(L"BEGIN IdentifierListCallExpression.Identifier");
    s->getIdentifierExpression()->accept(*this);
    tree.push_back(L"END IdentifierListCallExpression.Identifier");

    auto expressions = s->getExpressions();
    tree.push_back(L"BEGIN IdentifierListCallExpression.Expressions");
    for (auto expression : expressions) {
        expression->accept(*this);
    }
    tree.push_back(L"END IdentifierListCallExpression.Expressions");
    tree.push_back(L"END IdentifierListCallExpression");
}
void VisitorTree::visit(IdentifierFunctionCallExpression * s) {
    tree.push_back(L"IdentifierFunctionCallExpression:");
    tree.push_back(L"BEGIN IdentifierFunctionCallExpression.Identifier");
    s->getIdentifierExpression()->accept(*this);
    tree.push_back(L"END IdentifierFunctionCallExpression.Identifier");

    auto expressions = s->getExpressions();
    tree.push_back(L"BEGIN IdentifierFunctionCallExpression.Expressions");
    for (auto expression : expressions) {
        expression->accept(*this);
    }
    tree.push_back(L"END IdentifierFunctionCallExpression.Expressions");
    tree.push_back(L"END IdentifierFunctionCallExpression");
}
void VisitorTree::visit(IdentifierExpression * s) {
    tree.push_back(L"IdentifierExpression:");
    tree.push_back(L"Name: " + s->getIdentifierName());
    tree.push_back(L"END IdentifierExpression");
}






void VisitorTree::visit(CodeBlock* cb) {
    tree.push_back(L"CodeBlock:");
    auto statements = cb->getStatements();
    tree.push_back(L"BEGIN CodeBlock.Statements");
    for (auto statement : statements) {
        statement->accept(*this);
    }
    tree.push_back(L"END CodeBlock.Statements");
    tree.push_back(L"END CodeBlock");
}



void VisitorTree::visit(Parameter* p) {
    tree.push_back(L"Param:");
    tree.push_back(L"Name: " + p->getName());
    tree.push_back(L"END Param");
}
void VisitorTree::visit(FigureParameter* p) {
    tree.push_back(L"FigureParam:");
    tree.push_back(L"Name: " + p->getName());
    auto value = p->getValue();
    tree.push_back(L"BEGIN FigureParam.Expression");
    value->accept(*this);
    tree.push_back(L"END FigureParam.Expression");
    tree.push_back(L"END FigureParam");
}
void VisitorTree::visit(FigureDeclaration* fd) {
    tree.push_back(L"Figure:");
    tree.push_back(L"Name: " + fd->getName());
    auto params = fd->getParams();
    tree.push_back(L"BEGIN Figure.Params");
    for (auto param : params) {
        param->accept(*this);
    }
    tree.push_back(L"END Figure.Params");
    tree.push_back(L"END Figure");
}
void VisitorTree::visit(FuncDeclaration* fd) {
    tree.push_back(L"Func:");
    tree.push_back(L"Name: " + fd->getName());
    auto params = fd->getParams();
    auto codeBlock = fd->getCodeBlock();
    tree.push_back(L"BEGIN Func.Params");
    for (auto param : params) {
        param->accept(*this);
    }
    tree.push_back(L"END Func.Params");
    tree.push_back(L"BEGIN Func.CodeBlock");
    codeBlock->accept(*this);
    tree.push_back(L"END Func.CodeBlock");
    tree.push_back(L"END Func");
}
void VisitorTree::visit(Program* p) {
    tree.push_back(L"Program:");
    auto figures = p->getFigures();
    auto functions = p->getFunctions();
    tree.push_back(L"BEGIN Program.Figures");
    for(auto figure: figures) {
        figure.second->accept(*this);
    }
    tree.push_back(L"END Program.Figures");
    tree.push_back(L"BEGIN Program.Functions");
    for(auto function: functions) {
        function.second->accept(*this);
    }
    tree.push_back(L"END Program.Functions");
    tree.push_back(L"END Program");
}

void VisitorTree::printTree() {
    for(auto element: this->tree) {
        std::wcout << element << std::endl;
    }
}