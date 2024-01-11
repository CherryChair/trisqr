//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORINTERPTER_H
#define LEXER_VISITORINTERPTER_H

#include "Visitor.h"
#include <stack>
#include <cwctype>
#include "map"
#include <functional>
#include <queue>

//figura i punkt
class FunctionCallContext;

class Scope;

class Variable;

class ListValue;
class FigureValue;

using interpeter_value = std::variant<int, double, std::wstring, bool, std::monostate, std::pair<double, double>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;

struct AllowedInComparisonVisitor;
struct AllowedInAdditionVisitor;
struct AllowedInSubtractionVisitor;
struct AllowedInMultiplicationVisitor;
struct AllowedInDivisionVisitor;

using AllowedInOperationVisitor = std::variant<AllowedInComparisonVisitor, AllowedInAdditionVisitor, AllowedInDivisionVisitor, AllowedInMultiplicationVisitor, AllowedInSubtractionVisitor>;


class ListValue : public std::enable_shared_from_this<ListValue>{
private:
    std::vector<interpeter_value> values;
public:
    ListValue(std::vector<interpeter_value> values): values(std::move(values)) {}
    interpeter_value & operator[](size_t index) {
        return values[index];
    }
    unsigned int len() {
        return values.size();
    }
    ListValue operator+(const ListValue & lv) {
        std::vector<interpeter_value> copy_values = this->values;
        copy_values.insert(values.end(), lv.values.begin(), lv.values.end());
        return ListValue(std::move(copy_values));
    }
};

class FigureValue : public std::enable_shared_from_this<FigureValue>{
private:
    const std::wstring name;
    std::map<std::wstring, std::pair<double, double>> points;
    ListValue border = ListValue(std::vector<interpeter_value>({0, 0, 0}));
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
    std::map<std::wstring, interpeter_value> variables;
public:
    std::map<std::wstring, interpeter_value> & getVariables() {return variables;};
};

class FunctionCallContext{
private:
    std::vector<Scope> scopes;
public:
    std::vector<Scope> & getScopes() {return scopes;};
};

class VisitorInterpreter : public Visitor {
private:
    Position funcCallPosition;
    std::unordered_map<std::wstring, FuncDeclaration *> functionDeclarations;
    std::unordered_map<std::wstring, FigureDeclaration *> figureDeclarations;
    std::queue<interpeter_value> functionCallParams;
    ErrorHandler * errorHandler;
    Scope figureScope = Scope();
    std::stack<FunctionCallContext> functionContexts;
    std::optional<interpeter_value> returnValue = std::nullopt;
    std::optional<interpeter_value> lastResult = std::nullopt;
    std::optional<std::wstring> currentlyAnalyzedFigure = std::nullopt;
    bool lastConditionTrue = false;
public:
    VisitorInterpreter(ErrorHandler * eh): errorHandler(eh){};
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
    void visit(IdentifierFunctionCallExpression * e);
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
    std::map<std::wstring, interpeter_value> & getCurrentScopeVariables();
    interpeter_value consumeLastResult();
    void consumeReturnValue();
    bool consumeConditionTrue();

    bool ensureTypesMatch(interpeter_value & value1, interpeter_value & value2);
    void operationTypeEqualityCheck(interpeter_value & value1, interpeter_value & value2, const Position & position, const std::wstring operation);
    void operationLegalityCheck(interpeter_value &value1, const Position &position,
                                AllowedInOperationVisitor &&allowedInOperationVisitor,
                                const std::wstring &operation);
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

struct AllowedInAdditionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return true;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> visited) {return true;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInSubtractionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInMultiplicationVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInDivisionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::pair<double, double> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct TypeMatchVisitor {
    variable_type type;
    TypeMatchVisitor(variable_type type) : type(type) {};
    bool operator()(int & visited) {return type == INT_VARIABLE;}
    bool operator()(double & visited) {return type == DOUBLE_VARIABLE;}
    bool operator()(std::wstring & visited) {return type == STRING_VARIABLE;}
    bool operator()(bool & visited) {return type == BOOL_VARIABLE;}
    bool operator()(std::monostate & visited) {return type == NONE_VARIABLE;}
    bool operator()(std::pair<double, double> & visited) {return type == POINT_VARIABLE;}
    bool operator()(std::shared_ptr<ListValue> visited) {return type == LIST_VARIABLE;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return type == FIGURE_VARIABLE;}
};

struct IntConversionVisitor {
    variable_type type;
    IntConversionVisitor(variable_type type) : type(type) {};
    interpeter_value operator()(int & visited) {return type == INT_VARIABLE;}
    interpeter_value operator()(double & visited) {return type == DOUBLE_VARIABLE;}
    interpeter_value operator()(std::wstring & visited) {return type == STRING_VARIABLE;}
    interpeter_value operator()(bool & visited) {return type == BOOL_VARIABLE;}
    interpeter_value operator()(std::monostate & visited) {return type == NONE_VARIABLE;}
    interpeter_value operator()(std::pair<double, double> & visited) {return type == POINT_VARIABLE;}
    interpeter_value operator()(std::shared_ptr<ListValue> visited) {return type == LIST_VARIABLE;}
    interpeter_value operator()(std::shared_ptr<FigureValue> & visited) {return type == FIGURE_VARIABLE;}
};

//using value = std::variant<int, double, std::wstring, bool, std::monostate, std::pair<double, double>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;
interpeter_value operator+(const interpeter_value & value1, const interpeter_value & value2) {
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

interpeter_value operator-(const interpeter_value & value1, const interpeter_value & value2) {
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

interpeter_value operator/(const interpeter_value & value1, const interpeter_value & value2) {
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

interpeter_value operator*(const interpeter_value & value1, const interpeter_value & value2) {
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

static const std::unordered_map<variable_type, std::function<interpeter_value (int value)>> int_conversion_map= {
        {INT_VARIABLE, [](int value){ return value;}},
        {DOUBLE_VARIABLE, [](int value){ return (double)value;}},
        {BOOL_VARIABLE, [](int value){ if(value == 0) return false; return true;}},
        {STRING_VARIABLE, [](int value){ return std::to_wstring(value);}},
        {NONE_VARIABLE, [](int value){ return std::monostate();}},
        {POINT_VARIABLE, [](int value){ return std::monostate();}},
        {LIST_VARIABLE, [](int value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](int value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (double value)>> double_conversion_map= {
        {INT_VARIABLE, [](double value){ return (int)value;}},
        {DOUBLE_VARIABLE, [](double value){ return value;}},
        {BOOL_VARIABLE, [](double value){ if(value == 0.0) return false; return true;}},
        {STRING_VARIABLE, [](double value){ return std::to_wstring(value);}},
        {NONE_VARIABLE, [](double value){ return std::monostate();}},
        {POINT_VARIABLE, [](double value){ return std::monostate();}},
        {LIST_VARIABLE, [](double value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](double value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (bool value)>> bool_conversion_map= {
        {INT_VARIABLE, [](bool value){ return (int)value;}},
        {DOUBLE_VARIABLE, [](bool value){ return (double)value;}},
        {BOOL_VARIABLE, [](bool value){ return value;}},
        {STRING_VARIABLE, [](bool value){ if (value) return L"true"; return L"false";}},
        {NONE_VARIABLE, [](bool value){ return std::monostate();}},
        {POINT_VARIABLE, [](bool value){ return std::monostate();}},
        {LIST_VARIABLE, [](bool value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](bool value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (std::wstring value)>> string_conversion_map= {
        {INT_VARIABLE, [](std::wstring value){ return std::stoi(value);}},
        {DOUBLE_VARIABLE, [](std::wstring value){ return std::stod(value);}},
        {BOOL_VARIABLE, [](std::wstring value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::wstring value){ return value;}},
        {NONE_VARIABLE, [](std::wstring value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::wstring value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::wstring value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::wstring value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (std::monostate value)>> none_conversion_map= {
        {INT_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {NONE_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::monostate value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (std::pair<double, double> value)>> point_conversion_map= {
        {INT_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {NONE_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::pair<double, double> value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (std::shared_ptr<ListValue> value)>> list_conversion_map= {
        {INT_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {NONE_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::shared_ptr<ListValue> value){ return std::monostate();}},
};

static const std::unordered_map<variable_type, std::function<interpeter_value (std::shared_ptr<FigureValue> value)>> figure_conversion_map= {
        {INT_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {NONE_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::shared_ptr<FigureValue> value){ return std::monostate();}},
};

struct ConversionVisitor {
    variable_type type;
    Position position;
    ConversionVisitor(variable_type & type) : type(type) {};
    interpeter_value operator()(int & visited) {return int_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(double & visited) {return double_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(std::wstring & visited) {return string_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(bool & visited) {return bool_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(std::monostate & visited) {return none_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(std::pair<double, double> & visited) {return point_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(std::shared_ptr<ListValue> & visited) {return list_conversion_map.at(this->type)(visited);};
    interpeter_value operator()(std::shared_ptr<FigureValue> & visited) {return figure_conversion_map.at(this->type)(visited);};
};

#endif //LEXER_VISITORINTERPTER_H
