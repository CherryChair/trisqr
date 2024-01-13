//
// Created by mpkow on 16.05.2023.
//

#include "Program.h"
#include "../Visitors/Visitor.h"


void ExpressionOr::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionAnd::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompEq::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompNeq::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompLeq::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompGeq::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompGreater::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionCompLess::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionAdd::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionSub::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionMul::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionDiv::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionIs::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionTo::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionNeg::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionNegMinus::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionValueList::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionValuePoint::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionValueLiteral::accept(Visitor & visitor) {visitor.visit(this);}
void ExpressionValueBrackets::accept(Visitor & visitor) {visitor.visit(this);}

void WhileStatement::accept(Visitor & visitor) {visitor.visit(this);}
void IfStatement::accept(Visitor & visitor) {visitor.visit(this);}
void ForStatement::accept(Visitor & visitor) {visitor.visit(this);}
void ForRangeStatement::accept(Visitor & visitor) {visitor.visit(this);}
void DeclarationStatement::accept(Visitor & visitor) {visitor.visit(this);}
void DeclarationAssignStatement::accept(Visitor & visitor) {visitor.visit(this);}
void ReturnStatement::accept(Visitor & visitor) {visitor.visit(this);}

void ConditionAndBlock::accept(Visitor & visitor) {visitor.visit(this);}

void ObjectAccessExpression::accept(Visitor & visitor) {visitor.visit(this);}
void IdentifierExpressionStatement::accept(Visitor & visitor) {visitor.visit(this);}
void IdentifierStatementAssign::accept(Visitor & visitor) {visitor.visit(this);}
void IdentifierListIndexExpression::accept(Visitor & visitor) {visitor.visit(this);}
void IdentifierFunctionCallExpression::accept(Visitor & visitor) {visitor.visit(this);}
void IdentifierExpression::accept(Visitor & visitor) {visitor.visit(this);}

void CodeBlock::accept(Visitor & visitor) {visitor.visit(this);}
void Parameter::accept(Visitor & visitor) {visitor.visit(this);}
void FigureParameter::accept(Visitor & visitor) {visitor.visit(this);}
void FigureDeclaration::accept(Visitor & visitor) {visitor.visit(this);}
void FuncDeclaration::accept(Visitor & visitor) {visitor.visit(this);}
void Program::accept(Visitor & visitor) {visitor.visit(this);}

bool operator==(const Parameter &lhs, const Parameter &rhs) {
    return typeid(lhs) == typeid(rhs)
           && lhs.isEqual(&rhs);
}

bool operator!=(const Parameter &lhs, const Parameter &rhs) {
    return !(lhs == rhs);
}

bool operator==(const Expression &lhs, const Expression &rhs) {
    return typeid(lhs) == typeid(rhs)
           && lhs.isEqual(&rhs);
}

bool operator!=(const Expression &lhs, const Expression &rhs) {
    return !(lhs == rhs);
}

bool operator==(const Statement &lhs, const Statement &rhs) {
    return typeid(lhs) == typeid(rhs)
           && lhs.isEqual(&rhs);
}

bool operator!=(const Statement &lhs, const Statement &rhs) {
    return !(lhs == rhs);
}

bool operator==(const CodeBlock &lhs, const CodeBlock &rhs) {
    return lhs.statements == (rhs.statements);
}

bool operator!=(const CodeBlock &lhs, const CodeBlock &rhs) {
    return !(lhs == rhs);
}

bool operator==(const FuncDeclaration &lhs, const FuncDeclaration &rhs) {
    return lhs.name == rhs.name && lhs.params == rhs.params && *(lhs.codeBlock) == *(rhs.codeBlock);
}

bool operator!=(const FuncDeclaration &lhs, const FuncDeclaration &rhs) {
    return !(lhs == rhs);
}
