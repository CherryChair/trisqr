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
#include <math.h>
#include <cairomm-1.0/cairomm/cairomm.h>
#include <gtk/gtk.h>

//figura i punkt
class FunctionCallContext;

class Scope;

class AssignableValue;

class ListValue;
class FigureValue;
class PointValue;

using interpreter_value = std::variant<int, double, std::wstring, bool, std::monostate, std::shared_ptr<PointValue>, std::shared_ptr<ListValue>, std::shared_ptr<FigureValue>>;
//TODO bez shared_ptr, sprawdzać mutowalność w AssignableValue

struct AllowedInComparisonVisitor;
struct AllowedInAdditionVisitor;
struct AllowedInSubtractionVisitor;
struct AllowedInMultiplicationVisitor;
struct AllowedInDivisionVisitor;

using AllowedInOperationVisitor = std::variant<AllowedInComparisonVisitor, AllowedInAdditionVisitor, AllowedInDivisionVisitor, AllowedInMultiplicationVisitor, AllowedInSubtractionVisitor>;

struct PrintVisitor;

enum assignable_value_type {
    FIGURE_POINT_VALUE,
    POINT_COORD_VALUE,
    COLOR_PARAM_VALUE,
    COLOR_VALUE,
    RADIUS_VALUE,
    NORMAL_VALUE,
};

class AssignableValue {
public:
    assignable_value_type type = NORMAL_VALUE;
    std::shared_ptr<interpreter_value> value = nullptr;//TODO raw_pointer
    AssignableValue() : value(std::make_shared<interpreter_value>(std::monostate())){};
    explicit AssignableValue(interpreter_value && value) : value(std::make_shared<interpreter_value>(value)){};
    explicit AssignableValue(interpreter_value & value) : value(std::make_shared<interpreter_value>(value)){};
    AssignableValue(interpreter_value && value, assignable_value_type type) : value(std::make_shared<interpreter_value>(value)), type(type){};
    AssignableValue(interpreter_value & value, assignable_value_type type) : value(std::make_shared<interpreter_value>(value)), type(type){};
};

class PointValue : public std::enable_shared_from_this<PointValue> {
private:
    AssignableValue x;
    AssignableValue y;
public:
    PointValue(double x, double y) : x(AssignableValue(x, POINT_COORD_VALUE)), y(AssignableValue(y, POINT_COORD_VALUE)) {};
    AssignableValue & getX() {return this->x;}
    AssignableValue & getY() {return this->y;}
};

class ListValue : public std::enable_shared_from_this<ListValue>{
private:
    std::vector<AssignableValue> values;
public:
    explicit ListValue(std::vector<AssignableValue> values): values(std::move(values)) {}
    AssignableValue & operator[](size_t index) {
        return values[index];
    }
    void remove(int i) {
        values.erase(values.begin()+i);
    }
    unsigned int len() {
        return values.size();
    }
    std::shared_ptr<ListValue> operator+(ListValue & lv) {
        std::vector<AssignableValue> copy_values = this->values;
        for (auto el : lv.getValues()) {
            copy_values.push_back(el);
        }
        return std::make_shared<ListValue>(copy_values);
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
    std::map<std::wstring, AssignableValue> points;
    AssignableValue color;
    AssignableValue radius;
public:
    FigureValue() {initColor();};
    explicit FigureValue(std::map<std::wstring, AssignableValue> points): points(std::move(points)){
        markPoints();
        initColor();
    };
    FigureValue(std::map<std::wstring, AssignableValue> points, AssignableValue color): points(std::move(points)), color(std::move(color)) {
        markPoints();
        markColor();
    };
    FigureValue(AssignableValue centre, double radius) : radius(AssignableValue(radius, RADIUS_VALUE)) {
        centre.type = FIGURE_POINT_VALUE;
        points[L"c"] = centre;
        initColor();
    };
    FigureValue(AssignableValue centre, double radius, AssignableValue color)
        : radius(AssignableValue(radius)), color(std::move(color)){
        centre.type = FIGURE_POINT_VALUE;
        points[L"c"] = centre;
        markColor();
    };
    void initColor() {
        color = AssignableValue(std::make_shared<ListValue>(std::vector<AssignableValue>(
                {AssignableValue(0, COLOR_PARAM_VALUE),
                 AssignableValue(0, COLOR_PARAM_VALUE),
                 AssignableValue(0, COLOR_PARAM_VALUE)
                })), COLOR_VALUE);
    }
    std::map<std::wstring, AssignableValue> & getPoints() {return points;};
    void markPoints() {
        for(auto & point : points) {
            point.second.type = FIGURE_POINT_VALUE;
        }
    }
    void markColor() {
        color.type = COLOR_VALUE;
        for (auto el: std::get<std::shared_ptr<ListValue>>(*(color.value))->getValues()) {
            el.type = COLOR_PARAM_VALUE;
        }
    }
    AssignableValue & getColor() {return color;};
    void setColor(std::shared_ptr<ListValue> newColor) { this->color = AssignableValue(newColor, COLOR_VALUE);};
    AssignableValue & getRadius() {return this->radius;};
    void setRadius(double r) {this->radius = AssignableValue(r, RADIUS_VALUE);};
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
        std::wstring result = L"(" + std::to_wstring(std::get<double>(*(visited->getX().value)));
        result += L", " + std::to_wstring(std::get<double>(*(visited->getY().value))) + L")";
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
            auto point = std::get<std::shared_ptr<PointValue>>(*(element.second.value));
            result += L"\t" + element.first + L": " + (*this)(point) + L", ";
        }
        result += L"}";
        return result;
    }
};

// static void do_drawing(cairo_t *);



class VisitorInterpreter : public Visitor {
private:
    const std::unordered_map<std::wstring, std::function<void()>> internalFunctions;

    const std::unordered_map<std::wstring, std::function<void(ListValue *)>> internalListFunctions;

    const std::unordered_map<std::wstring, std::function<void(FigureValue *)>> internalFigureFunctions;
    const std::unordered_map<variable_type, std::function<void(const Position &, const interpreter_value &, const std::wstring &)>> requiredTypeErrorMap;
    Position funcCallPosition;
    std::unordered_map<std::wstring, FuncDeclaration *> functionDeclarations;
    std::vector<FigureValue *> figuresToDraw;
    std::pair<double, double> lbPaneCorner;
    std::pair<double, double> ruPaneCorner;
    std::pair<int, int> actualPaneResolution;
    int maxResolutionW = 1920;
    int maxResolutionH = 1080;
    double scalingFactor = 1.0;


    std::queue<interpreter_value> functionCallParams;
    ErrorHandler * errorHandler;
    Scope figureScope = Scope();
    std::stack<FunctionCallContext> functionContexts;
    std::optional<interpreter_value> returnValue = std::nullopt;
    std::optional<AssignableValue> accessedObject = std::nullopt;
    std::optional<std::wstring> currentlyAnalyzedFigure = std::nullopt;
    std::optional<interpreter_value> lastResult = std::nullopt;
    bool lastConditionTrue = false;


    static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr, gpointer user_data);
    static void do_drawing(cairo_t *cr, gpointer user_data);

    std::pair<int, int> mapCoords(std::pair<double, double> coords);
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
    void requireArgNum(const std::wstring & name, int argNum, const std::wstring & argList);
    void requireArgType(const std::wstring & name, variable_type vt);
    void requireExpressionType(const Position &position, const interpreter_value &expressionValue, variable_type vt,
                               const std::wstring &errorMessage);
    void requireArgNumBetween(const std::wstring & name, int argNumLower, int argNumUpper, const std::wstring & argList);
    void createNewFigure(const std::wstring & name);
    std::shared_ptr<ListValue> consumeColorParam();
public:
    explicit VisitorInterpreter(ErrorHandler * eh);
    void visit(ExpressionOr * e) override;
    void visit(ExpressionAnd * e) override;
    void visit(ExpressionCompEq * e) override;
    void visit(ExpressionCompNeq * e) override;
    void visit(ExpressionCompLeq * e) override;
    void visit(ExpressionCompGeq * e) override;
    void visit(ExpressionCompGreater * e) override;
    void visit(ExpressionCompLess * e) override;
    void visit(ExpressionAdd * e) override;
    void visit(ExpressionSub * e) override;
    void visit(ExpressionMul * e) override;
    void visit(ExpressionDiv * e) override;
    void visit(ExpressionIs * e) override;
    void visit(ExpressionTo * e) override;
    void visit(ExpressionNeg * e) override;
    void visit(ExpressionNegMinus * e) override;
    void visit(ExpressionValueList * e) override;
    void visit(ExpressionValuePoint * e) override;
    void visit(ExpressionValueLiteral * e) override;
    void visit(ExpressionValueBrackets * e) override;

    void visit(WhileStatement * s) override;
    void visit(IfStatement * s) override;
    void visit(ForStatement * s) override;
    void visit(ForRangeStatement * s) override;
    void visit(DeclarationStatement * s) override;
    void visit(DeclarationAssignStatement * s) override;
    void visit(ReturnStatement * s) override;

    void visit(ConditionAndBlock * cb) override;

    void visit(ObjectAccessExpression * s) override;
    void visit(IdentifierExpressionStatement * s) override;
    void visit(IdentifierStatementAssign * s) override;
    void visit(IdentifierListIndexExpression * s) override;
    void visit(IdentifierFunctionCallExpression * e) override;
    void visit(IdentifierExpression * s) override;

    void visit(CodeBlock * cb) override;
    void visit(Parameter * p) override;
    void visit(FigureParameter * p) override;
    void visit(FigureDeclaration * fd) override;
    void visit(FuncDeclaration * fd) override;
    void visit(Program * p) override;
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

//struct Operatacje {
//    interpreter_value operator()(int & visited, int & rightVisited) {return true;}
//    bool operator()(double & visited) {return true;}
//    bool operator()(std::wstring & visited) {return true;}
//    bool operator()(bool & visited) {return true;}
//    bool operator()(std::monostate & visited) {return true;}
//    bool operator()(std::shared_ptr<PointValue> & visited) {return true;}
//    bool operator()(std::shared_ptr<ListValue> & visited) {return false;}
//    bool operator()(std::shared_ptr<FigureValue> & visited) {return false;}
//    //template auto typy
//};

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
    explicit TypeMatchVisitor(variable_type type) : type(type) {};
    bool operator()(int &) const {return type == INT_VARIABLE;}
    bool operator()(double & visited) const {return type == DOUBLE_VARIABLE;}
    bool operator()(std::wstring & visited) const {return type == STRING_VARIABLE;}
    bool operator()(bool & visited) const {return type == BOOL_VARIABLE;}
    bool operator()(std::monostate & visited) const {return type == NONE_VARIABLE;}
    bool operator()(std::shared_ptr<PointValue> & visited) const {return type == POINT_VARIABLE;}
    bool operator()(std::shared_ptr<ListValue> & visited) const {return type == LIST_VARIABLE;}
    bool operator()(std::shared_ptr<FigureValue> & visited) const {return type == FIGURE_VARIABLE;}
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
    explicit ConversionVisitor(variable_type & type) : type(type) {};
    interpreter_value operator()(int & visited) const {return int_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(double & visited) const {return double_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::wstring & visited) const {return string_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(bool & visited) const {return bool_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::monostate & visited) const {return none_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<PointValue> & visited) const {return point_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<ListValue> & visited) const {return list_conversion_map.at(this->type)(visited);};
    interpreter_value operator()(std::shared_ptr<FigureValue> & visited) const {return figure_conversion_map.at(this->type)(visited);};
};

#endif //LEXER_VISITORINTERPTER_H
