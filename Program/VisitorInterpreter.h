//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORINTERPTER_H
#define LEXER_VISITORINTERPTER_H

#include "Visitor.h"
#include <stack>
#include "map"

//figura i punkt
class FunctionCallContext;

class Scope;

class Variable;

class ListValue;
class FigureValue;

using value_type = std::variant<int, double, std::wstring, bool, std::monostate, std::pair<double, double>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;

class ListValue : public std::enable_shared_from_this<ListValue>{
private:
    std::vector<value_type> values;
public:
    ListValue(std::vector<value_type> values): values(std::move(values)) {}
    value_type & operator[](size_t index) {
        return values[index];
    }
    unsigned int len() {
        return values.size();
    }
    ListValue operator+(const ListValue & lv) {
        std::vector<value_type> copy_values = this->values;
        copy_values.insert(values.end(), lv.values.begin(), lv.values.end());
        return ListValue(std::move(copy_values));
    }
};

class FigureValue : public std::enable_shared_from_this<FigureValue>{
private:
    const std::wstring name;
    std::map<std::wstring, std::pair<double, double>> points;
    ListValue border = ListValue(std::vector<value_type>({0, 0, 0}));
public:
    FigureValue()=default;
    FigureValue(std::map<std::wstring, std::pair<double, double>> points): points(std::move(points)){};
    FigureValue(std::map<std::wstring, std::pair<double, double>> points, ListValue border)
        : points(std::move(points)), border(std::move(border)){};
    std::map<std::wstring, std::pair<double, double>> & getPoints() {return points;};
    ListValue & getBorder() {return border;};
    void setBorder(ListValue border) {this->border = std::move(border);};
};

class Scope {
protected:
    std::map<std::wstring, value_type> variables;
public:
    std::map<std::wstring, value_type> & getVariables() {return variables;};
};

class FunctionCallContext{
private:
    std::vector<Scope> scopes;
public:
    std::vector<Scope> & getScopes() {return scopes;};
};

class VisitorInterpreter : public Visitor {
private:
    ErrorHandler * errorHandler;
    Scope figureScope = Scope();
    std::stack<FunctionCallContext> functionContexts;
    std::optional<value_type> returnValue = std::nullopt;
    std::optional<value_type> lastResult = std::nullopt;
    std::optional<std::wstring> currentlyAnalyzedFigure = std::nullopt;
    bool lastConditionTrue = false;
public:
    void visit(ExpressionOr * e);
    void visit(ExpressionAnd * e);
    void visit(ExpressionCompEq * e);
    void visit(ExpressionCompNeq * e);
    void visit(ExpressionCompLeq * e);
    void visit(ExpressionCompGeq * e);
    void visit(ExpressionCompGreater * e);
    void visit(ExpressionCompLess * e);
    void visit(ExpressionAdd * e);
    void visit(ExpressionSub * e);
    void visit(ExpressionMul * e);
    void visit(ExpressionDiv * e);
    void visit(ExpressionIs * e);
    void visit(ExpressionTo * e);
    void visit(ExpressionNeg * e);
    void visit(ExpressionNegMinus * e);
    void visit(ExpressionValueList * e);
    void visit(ExpressionValuePoint * e);
    void visit(ExpressionValueLiteral * e);
    void visit(ExpressionValueBrackets * e);

    void visit(WhileStatement * s);
    void visit(IfStatement * s);
    void visit(ForStatement * s);
    void visit(ForRangeStatement * s);
    void visit(DeclarationStatement * s);
    void visit(DeclarationAssignStatement * s);
    void visit(ReturnStatement * s);

    void visit(ConditionAndBlock * cb);

    void visit(ObjectAccessExpression * s);
    void visit(IdentifierExpressionStatement * s);
    void visit(IdentifierStatementAssign * s);
    void visit(IdentifierListIndexExpression * s);
    void visit(IdentifierFunctionCallExpression * s);
    void visit(IdentifierExpression * s);

    void visit(CodeBlock * cb);
    void visit(Parameter * p);
    void visit(FigureParameter * p);
    void visit(FigureDeclaration * fd);
    void visit(FuncDeclaration * fd);
    void visit(Program * p);

    void handleRuntimeError(const Position & pos, const std::wstring & errorMsg);
    Scope & getFigureScope() {return this->figureScope;}
    Scope & getCurrentScope() {return this->functionContexts.top().getScopes().back();}
    Scope & addNewScope();
    void popScope();
    std::map<std::wstring, value_type> & getCurrentScopeVariables();
    value_type & consumeLastResult();
    void consumeReturnValue();
    bool consumeConditionTrue();

    bool ensureTypesMatch(value_type & value1, value_type & value2);
    void operationTypeEqualityCheck(value_type & value1, value_type & value2, const Position & position, const std::wstring operation);
    void operationLegalityCheck(value_type & value1, value_type & value2, const Position & position);
};

struct TypeVisitor {
    std::wstring operator()(int & visited) {return L"int";}
    std::wstring operator()(double & visited) {return L"double";}
    std::wstring operator()(std::wstring & visited) {return L"string";}
    std::wstring operator()(bool & visited) {return L"bool";}
    std::wstring operator()(std::monostate & visited) {return L"None";}
    std::wstring operator()(std::pair<double, double> & visited) {return L"point";}
    std::wstring operator()(std::shared_ptr<ListValue> visited) {return L"list";}
    std::wstring operator()(std::shared_ptr<FigureValue> & visited) {return L"figure";}
};

struct AllowedInComparisonVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return true;}
    bool operator()(bool & visited) {return true;}
    bool operator()(std::monostate & visited) {return true;}
    bool operator()(std::pair<double, double> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedAdditionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return true;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> visited) {return true;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedSubtractionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedMultiplicationVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedDivisionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};
using AllowedInOperationVisitor = std::variant<AllowedInComparisonVisitor, AllowedAdditionVisitor, AllowedDivisionVisitor, AllowedMultiplicationVisitor, AllowedSubtractionVisitor>;

//using value_type = std::variant<int, double, std::wstring, bool, std::monostate, std::pair<double, double>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;
value_type operator+(const value_type & value1, const value_type & value2) {
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
            return std::get<std::pair<double, double>>(value1) + std::get<std::pair<double, double>>(value2);
        } case 6: {
            ListValue * list1 = std::get<std::shared_ptr<ListValue>>(value1).get();
            ListValue * list2 = std::get<std::shared_ptr<ListValue>>(value2).get();
            return (*list1 + *list2).shared_from_this();
        } case 7: {
            std::wcerr << L"ERR: Addition between FigureValue illegal";
            throw;
        }
    }
}

value_type operator-(const value_type & value1, const value_type & value2) {
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
            return std::get<std::pair<double, double>>(value1) - std::get<std::pair<double, double>>(value2);
        } case 6: {
            std::wcerr << L"ERR: Subtraction between ListValue illegal";
            throw;
        } case 7: {
            std::wcerr << L"ERR: Subtraction between FigureValue illegal";
            throw;
        }
    }
}

value_type operator/(const value_type & value1, const value_type & value2) {
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
}

value_type operator*(const value_type & value1, const value_type & value2) {
    if (value1.index() != value2.index()) {
        std::wcerr << L"ERR: Multiplication between two different types";
        throw;
    }
    switch (value1.index()){
        case 0: {
            return std::get<int>(value1)*std::get<int>(value2);
        } case 1: {
            return std::get<double>(value1)*std::get<double>(value2);
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
}

#endif //LEXER_VISITORINTERPTER_H
