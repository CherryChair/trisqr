//
// Created by mpkow on 10.01.2024.
//

#ifndef LEXER_VISITORINTERPTER_H
#define LEXER_VISITORINTERPTER_H

#include "Visitor.h"
#include <stack>
#include <cwctype>
#include <map>
#include <functional>
#include <queue>

//figura i punkt
class FunctionCallContext;

class Scope;

class AssignableValue;

class ListValue;
class FigureValue;
class PointValue;

using interpreter_value = std::variant<int, double, std::wstring, bool, std::monostate, std::shared_ptr<PointValue>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;

struct AllowedInComparisonVisitor;
struct AllowedInAdditionVisitor;
struct AllowedInSubtractionVisitor;
struct AllowedInMultiplicationVisitor;
struct AllowedInDivisionVisitor;

using AllowedInOperationVisitor = std::variant<AllowedInComparisonVisitor, AllowedInAdditionVisitor, AllowedInDivisionVisitor, AllowedInMultiplicationVisitor, AllowedInSubtractionVisitor>;

struct PrintVisitor;

class AssignableValue {
public:
    std::shared_ptr<interpreter_value> value;
    AssignableValue() : value(std::make_shared<interpreter_value>(std::monostate())){};
    AssignableValue(interpreter_value && value) : value(std::make_shared<interpreter_value>(value)){};
    AssignableValue(interpreter_value & value) : value(std::make_shared<interpreter_value>(value)){};
};

class PointValue : public std::enable_shared_from_this<PointValue> {
private:
    AssignableValue x;
    AssignableValue y;
public:
    PointValue(double x, double y) : x(AssignableValue(x)), y(AssignableValue(y)) {};
    AssignableValue & getX() {return this->x;}
    AssignableValue & getY() {return this->y;}
};

class ListValue : public std::enable_shared_from_this<ListValue>{
private:
    std::vector<AssignableValue> values;
public:
    ListValue(std::vector<AssignableValue> values): values(std::move(values)) {}
    AssignableValue & operator[](size_t index) {
        return values[index];
    }
    void remove(int i) {
        values.erase(values.begin()+i);
    }
    unsigned int len() {
        return values.size();
    }
    ListValue operator+(const ListValue & lv) {
        std::vector<AssignableValue> copy_values = this->values;
        copy_values.insert(values.end(), lv.values.begin(), lv.values.end());
        return ListValue(std::move(copy_values));
    }
    void append(AssignableValue & value) {
        this->values.push_back(value);
    }
    std::vector<AssignableValue> & getValues() {
        return this->values;
    }
};

class FigureValue : public std::enable_shared_from_this<FigureValue>{
private:
    const std::wstring name;
    std::unordered_map<std::wstring, std::shared_ptr<PointValue>> points;
    ListValue border = ListValue(std::vector<AssignableValue>({AssignableValue(0), AssignableValue(0), AssignableValue(0)}));
public:
    FigureValue()=default;
    FigureValue(std::unordered_map<std::wstring, std::shared_ptr<PointValue>> points): points(std::move(points)){};
    FigureValue(std::unordered_map<std::wstring, std::shared_ptr<PointValue>> points, ListValue border)
        : points(std::move(points)), border(std::move(border)){};
    std::unordered_map<std::wstring, std::shared_ptr<PointValue>> & getPoints() {return points;};
    ListValue & getBorder() {return border;};
    void setBorder(ListValue border) {this->border = std::move(border);};
};

class Scope {
protected:
    std::unordered_map<std::wstring, AssignableValue> variables;
public:
    std::unordered_map<std::wstring, AssignableValue> & getVariables() {return variables;};
};

class FunctionCallContext{
private:
    std::vector<Scope> scopes;
public:
    std::vector<Scope> & getScopes() {return scopes;};
};

struct PrintVisitor {
    std::unordered_set<std::shared_ptr<ListValue>> visitedLists;
    std::wstring operator()(int & visited) {return std::to_wstring(visited);}
    std::wstring operator()(double & visited) {return std::to_wstring(visited);}
    std::wstring operator()(std::wstring & visited) {return visited;}
    std::wstring operator()(bool & visited) { if (visited) return L"true"; return L"false";}
    std::wstring operator()(std::monostate & visited) {return L"None";}
    std::wstring operator()(std::shared_ptr<PointValue> & visited) {
        std::wstring result = L"(" + std::to_wstring(std::get<double>(*(visited.get()->getX().value)));
        result += L", " + std::to_wstring(std::get<double>(*(visited.get()->getY().value))) + L")";
        return result;
    }
    std::wstring operator()(std::shared_ptr<ListValue> & visited) {
        if (visitedLists.find(visited) != visitedLists.end()) {
            return L"[...]";
        }
        std::wstring result = L"[";
        visitedLists.insert(visited);
        for (auto & element : visited->getValues()) {
            std::wstring quotes = L"";
            if (std::holds_alternative<std::wstring>(*element.value)) {
                quotes = L"'";
            }
            result += quotes + std::visit(*this, *(element.value)) + quotes + L", ";
        }
        if (!visited->getValues().empty()) {
            result.erase(result.end()-2, result.end());
        }
        result += L"]";
        return result;
    }
    std::wstring operator()(std::shared_ptr<FigureValue> & visited) {
        std::wstring result = L"{\n";
        for (auto & element : visited->getPoints()) {
            auto point  = *(element.second);
            result += L"\t" + element.first + L": " + (*this)(element.second) + L", ";
        }
        result += L"}";
        return result;
    }
};

class VisitorInterpreter : public Visitor {
private:
    Position funcCallPosition;
    std::unordered_map<std::wstring, FuncDeclaration *> functionDeclarations;
    const std::unordered_map<std::wstring, std::function<void()>> internalFunctions = {
            {L"print", [this](){
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                if (funcCallParams.empty()) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too few arguments print() requires 1 string argument.");
                }
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                if (funcCallParams.size() > 1) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too many arguments print() requires 1 string argument.");
                }
                std::wcout << std::visit(PrintVisitor{}, value);
                this->lastResult = std::monostate();
            }},
            {L"printn", [this](){
                this->internalFunctions.at(L"print")();
                std::wcout << std::endl;
            }},
            {L"draw", [this](){
                //rysuj listę figur za pomocą allegro
            }},
            {L"input", [this](){
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                if (!funcCallParams.empty()) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too many arguments input() requires no arguments.");
                }
                std::wstring result;
                std::wcin >> result;
                this->lastResult = result;
            }},
    };

    const std::unordered_map<std::wstring, std::function<void(ListValue *)>> internalListFunctions= {
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
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                if (funcCallParams.empty()) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too few arguments .delete() requires 1 int argument.");
                }
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                if (funcCallParams.size() > 1) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too many arguments .delete() requires 1 int argument.");
                }
                if (!std::holds_alternative<int>(value)) {
                    this->handleRuntimeError(this->funcCallPosition, L"Removed element index is not int");
                }
                int removedIndex = std::get<int>(value);
                if (listValue->len() <= removedIndex) {
                    this->handleRuntimeError(this->funcCallPosition, L"Removed index out of range");
                }
                listValue->remove(removedIndex);
                this->lastResult = listValue->shared_from_this();
            }},
            {L"len", [this](ListValue * listValue){
                if (!this->functionCallParams.empty()) {
                    this->handleRuntimeError(this->funcCallPosition, L"Too many arguments .delete() requires 0 arguments.");
                }
                this->lastResult = (int) listValue->len();
            }},
    };

    const std::unordered_map<std::wstring, std::function<void(FigureValue *)>> internalFigureFunctions= {
            {L"circ", [this](FigureValue * figureValue){}},
            {L"area", [this](FigureValue * figureValue){}},
            {L"scale", [this](FigureValue * figureValue){}},
            {L"rotate", [this](FigureValue * figureValue){}},
            {L"transport", [this](FigureValue * figureValue){}},
            {L"copy", [this](FigureValue * figureValue){}},
    };
    std::queue<interpreter_value> functionCallParams;
    ErrorHandler * errorHandler;
    Scope figureScope = Scope();
    std::stack<FunctionCallContext> functionContexts;
    bool figurePointAssigned = false;
    bool figureColorAssigned = false;
    bool pointCoordAssigned = false;
    std::optional<interpreter_value> returnValue = std::nullopt;
    std::optional<AssignableValue> accessedObject = std::nullopt;
    std::optional<std::wstring> currentlyAnalyzedFigure = std::nullopt;
    bool lastConditionTrue = false;
public:
    std::optional<interpreter_value> lastResult = std::nullopt; // private ale temp public
    VisitorInterpreter(ErrorHandler * eh): errorHandler(eh), funcCallPosition(Position({1, 1})){};
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
    std::queue<interpreter_value> & getFunctionCallParams() {return this->functionCallParams;}
    Scope & getFigureScope() {return this->figureScope;}
    Scope & getCurrentScope() {return this->functionContexts.top().getScopes().back();}
    Scope & addNewScope();
    void popScope();
    std::unordered_map<std::wstring, AssignableValue> & getCurrentScopeVariables();
    AssignableValue & findVariableInScopes(const std::wstring & variableName);
    interpreter_value consumeLastResultAndAccessedObject();
    std::shared_ptr<interpreter_value> getAccessedObject();
    void consumeReturnValue();
    bool consumeConditionTrue();

    bool ensureTypesMatch(interpreter_value & value1, interpreter_value & value2);
    void operationTypeEqualityCheck(interpreter_value & value1, interpreter_value & value2, const Position & position, const std::wstring & operation);
    void operationLegalityCheck(interpreter_value &value1, const Position &position,
                                AllowedInOperationVisitor &&allowedInOperationVisitor,
                                const std::wstring &operation);
};

struct TypeVisitor {
    std::wstring operator()(int & visited) {return L"int";}
    std::wstring operator()(double & visited) {return L"double";}
    std::wstring operator()(std::wstring & visited) {return L"string";}
    std::wstring operator()(bool & visited) {return L"bool";}
    std::wstring operator()(std::monostate & visited) {return L"None";}
    std::wstring operator()(std::shared_ptr<PointValue> & visited) {return L"point";}
    std::wstring operator()(std::shared_ptr<ListValue> & visited) {return L"list";}
    std::wstring operator()(std::shared_ptr<FigureValue> & visited) {return L"figure";}
};

struct AllowedInComparisonVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return true;}
    bool operator()(bool & visited) {return true;}
    bool operator()(std::monostate & visited) {return true;}
    bool operator()(std::shared_ptr<PointValue> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInAdditionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return true;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::shared_ptr<PointValue> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return true;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInSubtractionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::shared_ptr<PointValue> & visited) {return true;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInMultiplicationVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::shared_ptr<PointValue> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return false;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
};

struct AllowedInDivisionVisitor {
    bool operator()(int & visited) {return true;}
    bool operator()(double & visited) {return true;}
    bool operator()(std::wstring & visited) {return false;}
    bool operator()(bool & visited) {return false;}
    bool operator()(std::monostate & visited) {return false;}
    bool operator()(std::shared_ptr<PointValue> & visited) {return false;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return false;}
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
    bool operator()(std::shared_ptr<PointValue> & visited) {return type == POINT_VARIABLE;}
    bool operator()(std::shared_ptr<ListValue> & visited) {return type == LIST_VARIABLE;}
    bool operator()(std::shared_ptr<FigureValue> & visited) {return type == FIGURE_VARIABLE;}
};

interpreter_value operator+(const interpreter_value & value1, const interpreter_value & value2);

interpreter_value operator-(const interpreter_value & value1, const interpreter_value & value2);

interpreter_value operator/(const interpreter_value & value1, const interpreter_value & value2);

interpreter_value operator*(const interpreter_value & value1, const interpreter_value & value2);

inline static const std::unordered_map<variable_type, std::function<interpreter_value (int value)>> int_conversion_map= {
        {INT_VARIABLE, [](int value){ return value;}},
        {DOUBLE_VARIABLE, [](int value){ return (double)value;}},
        {BOOL_VARIABLE, [](int value){ if(value == 0) return false; return true;}},
        {STRING_VARIABLE, [](int value){ return std::to_wstring(value);}},
        {NONE_VARIABLE, [](int value){ return std::monostate();}},
        {POINT_VARIABLE, [](int value){ return std::monostate();}},
        {LIST_VARIABLE, [](int value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](int value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (double value)>> double_conversion_map= {
        {INT_VARIABLE, [](double value){ return (int)value;}},
        {DOUBLE_VARIABLE, [](double value){ return value;}},
        {BOOL_VARIABLE, [](double value){ if(value == 0.0) return false; return true;}},
        {STRING_VARIABLE, [](double value){ return std::to_wstring(value);}},
        {NONE_VARIABLE, [](double value){ return std::monostate();}},
        {POINT_VARIABLE, [](double value){ return std::monostate();}},
        {LIST_VARIABLE, [](double value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](double value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (bool value)>> bool_conversion_map= {
        {INT_VARIABLE, [](bool value){ return (int)value;}},
        {DOUBLE_VARIABLE, [](bool value){ return (double)value;}},
        {BOOL_VARIABLE, [](bool value){ return value;}},
        {STRING_VARIABLE, [](bool value){ if (value) return L"true"; return L"false";}},
        {NONE_VARIABLE, [](bool value){ return std::monostate();}},
        {POINT_VARIABLE, [](bool value){ return std::monostate();}},
        {LIST_VARIABLE, [](bool value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](bool value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (std::wstring & value)>> string_conversion_map= {
        {INT_VARIABLE, [](std::wstring & value){ return std::stoi(value);}},
        {DOUBLE_VARIABLE, [](std::wstring & value){ return std::stod(value);}},
        {BOOL_VARIABLE, [](std::wstring & value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::wstring & value){ return value;}},
        {NONE_VARIABLE, [](std::wstring & value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::wstring & value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::wstring & value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::wstring & value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (std::monostate value)>> none_conversion_map= {
        {INT_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::monostate value){ return PrintVisitor{}(value);}},
        {NONE_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::monostate value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::monostate value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (std::shared_ptr<PointValue> & value)>> point_conversion_map= {
        {INT_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::shared_ptr<PointValue> & value){ return PrintVisitor{}(value);}},
        {NONE_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::shared_ptr<PointValue> & value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (std::shared_ptr<ListValue> & value)>> list_conversion_map= {
        {INT_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::shared_ptr<ListValue> & value){ return PrintVisitor{}(value);}},
        {NONE_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::shared_ptr<ListValue> & value){ return std::monostate();}},
};

inline static const std::unordered_map<variable_type, std::function<interpreter_value (std::shared_ptr<FigureValue> & value)>> figure_conversion_map= {
        {INT_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {DOUBLE_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {BOOL_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {STRING_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return PrintVisitor{}(value);}},
        {NONE_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {POINT_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {LIST_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
        {FIGURE_VARIABLE, [](std::shared_ptr<FigureValue> & value){ return std::monostate();}},
};

struct ConversionVisitor {
    variable_type type;
    ConversionVisitor(variable_type & type) : type(type) {};
    interpreter_value operator()(int & visited) {return int_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(double & visited) {return double_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::wstring & visited) {return string_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(bool & visited) {return bool_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::monostate & visited) {return none_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<PointValue> & visited) {return point_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<ListValue> & visited) {return list_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<FigureValue> & visited) {return figure_conversion_map.at(this->type)(visited);};
};

#endif //LEXER_VISITORINTERPTER_H
