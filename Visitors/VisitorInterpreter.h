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
    std::map<std::wstring, std::shared_ptr<PointValue>> points;
    std::shared_ptr<ListValue> color;
    std::shared_ptr<double> radius = nullptr;
public:
    FigureValue() {color = std::make_shared<ListValue>(std::vector<AssignableValue>({AssignableValue(0), AssignableValue(0), AssignableValue(0)}));};
    FigureValue(std::map<std::wstring, std::shared_ptr<PointValue>> points): points(std::move(points)){
        color = std::make_shared<ListValue>(std::vector<AssignableValue>({AssignableValue(0), AssignableValue(0), AssignableValue(0)}));
    };
    FigureValue(std::map<std::wstring, std::shared_ptr<PointValue>> points, std::shared_ptr<ListValue> color)
        : points(std::move(points)), color(std::move(color)){};
    FigureValue(std::shared_ptr<PointValue> centre, double radius) : radius(std::make_shared<double>(radius)) {
        points[L"c"] = centre;
        color = std::make_shared<ListValue>(std::vector<AssignableValue>({AssignableValue(0), AssignableValue(0), AssignableValue(0)}));
    };
    FigureValue(std::shared_ptr<PointValue> centre, double radius, std::shared_ptr<ListValue> color)
        : radius(std::make_shared<double>(radius)), color(std::move(color)){
        points[L"c"] = centre;
    };
    std::map<std::wstring, std::shared_ptr<PointValue>> & getPoints() {return points;};
    std::shared_ptr<ListValue> & getColor() {return color;};
    void setColor(std::shared_ptr<ListValue> color) { this->color = std::move(color);};
    std::shared_ptr<double> & getRadius() {return this->radius;};
    void setRadius(double r) {this->radius = std::make_shared<double>(r);};
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

// static void do_drawing(cairo_t *);



class VisitorInterpreter : public Visitor {
private:
    Position funcCallPosition;
    std::unordered_map<std::wstring, FuncDeclaration *> functionDeclarations;
    std::vector<FigureValue *> figuresToDraw;
//    std::vector<PointValue *> pointsToDraw;
    std::pair<double, double> lbPaneCorner;
    std::pair<double, double> ruPaneCorner;
    std::pair<int, int> actualPaneResolution;
    int maxResolutionW = 1920;
    int maxResolutionH = 1080;
    double scalingFactor = 1.0;

    static gboolean on_draw_event(GtkWidget *widget, cairo_t *cr,
        gpointer user_data)
    {      
        do_drawing(cr, user_data);

        return FALSE;
    }

    static void do_drawing(cairo_t *cr, gpointer user_data)
    {
        cairo_set_line_width(cr, 4.0);
        VisitorInterpreter * visitor = (VisitorInterpreter *) user_data;
        for (auto figure : visitor->figuresToDraw) {
            auto & points = figure->getPoints();
            auto &rgb = figure->getColor();
            double r = (double)std::get<int>(*(rgb->getValues()[0].value));
            double g = (double)std::get<int>(*(rgb->getValues()[1].value));
            double b = (double)std::get<int>(*(rgb->getValues()[2].value));
            cairo_set_source_rgb(cr, r/255.0, g/255.0, b/255.0);
            PointValue * previousPoint = points.rbegin()->second.get();
            double p_x;
            double p_y;
            if (auto radius = figure->getRadius()) {
                p_x = std::get<double>(*(previousPoint->getX().value));
                p_y = std::get<double>(*(previousPoint->getY().value));
                auto centre = visitor->mapCoords(std::pair<double, double>(p_x, p_y));
                cairo_arc(cr, centre.first, centre.second, *radius * visitor->scalingFactor, 0, 2 * M_PI);
            } else {
                PointValue * currentPoint;
                double c_x;
                double c_y;
                for(auto point: points) {
                    currentPoint = point.second.get();
                    p_x = std::get<double>(*(previousPoint->getX().value));
                    p_y = std::get<double>(*(previousPoint->getY().value));
                    c_x = std::get<double>(*(currentPoint->getX().value));
                    c_y = std::get<double>(*(currentPoint->getY().value));
                    previousPoint = currentPoint;
                    auto pointA = visitor->mapCoords(std::pair<double, double>(p_x, p_y));
                    auto pointB = visitor->mapCoords(std::pair<double, double>(c_x, c_y));
                    cairo_move_to(cr, pointA.first, pointA.second);
                    cairo_line_to(cr, pointB.first, pointB.second);

                }
            }
            cairo_stroke(cr);
        }

        cairo_set_source_rgb(cr, 0, 0, 0);
//        cairo_select_font_face(cr, "Sans", CAIRO_FONT_SLANT_NORMAL,
//            CAIRO_FONT_WEIGHT_NORMAL);
//        cairo_set_font_size(cr, 40.0);

//        cairo_show_text(cr, "Disziplin ist Macht.");
    }

    std::pair<int, int> mapCoords(std::pair<double, double> coords){
        coords.first -= lbPaneCorner.first;
        coords.second -= lbPaneCorner.second;
        coords.first *= scalingFactor;
        coords.second *= scalingFactor;
        coords.second = (double)(actualPaneResolution.second) - coords.second;
        return std::pair<int, int>((int)coords.first, (int)coords.second);
    }

    const std::unordered_map<std::wstring, std::function<void()>> internalFunctions = {
            {L"print", [this](){
                this->requireArgNum(L"print()", 1, L"1 argument");
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                std::wcout << std::visit(PrintVisitor{}, value);
                this->lastResult = std::monostate();
            }},
            {L"printn", [this](){
                this->requireArgNum(L"printn()", 1, L"1 argument");
                this->internalFunctions.at(L"print")();
                std::wcout << std::endl;
            }},
            {L"draw", [this](){
                this->requireArgNum(L"draw()", 3, L"(list figureList, point lbCorner, point ruCorner) arguments");
                this->requireArgType(L"figure list", LIST_VARIABLE);
                interpreter_value figureListParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                ListValue * figureList = std::get<std::shared_ptr<ListValue>>(figureListParam).get();

                this->requireArgType(L"left bottom corner", POINT_VARIABLE);
                interpreter_value lbCornerParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * lbCorner = std::get<std::shared_ptr<PointValue>>(lbCornerParam).get();
                double lb_x = std::get<double>(*(lbCorner->getX().value));
                double lb_y = std::get<double>(*(lbCorner->getY().value));

                this->requireArgType(L"right upper corner", POINT_VARIABLE);
                interpreter_value ruCornerParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * ruCorner = std::get<std::shared_ptr<PointValue>>(ruCornerParam).get();
                double ru_x = std::get<double>(*(ruCorner->getX().value));
                double ru_y = std::get<double>(*(ruCorner->getY().value));

                this->lbPaneCorner = std::pair<double, double>(lb_x, lb_y);
                this->ruPaneCorner = std::pair<double, double>(ru_x, ru_y);
                //potencjalnie cairo_rotate i cairo_transforma zamist tych rzeczy

                if (lb_x >=  ru_x) {
                    this->handleRuntimeError(this->funcCallPosition, L"Wrong pane corner, left x must be less than right x");
                }

                if (lb_y >=  ru_y) {
                    this->handleRuntimeError(this->funcCallPosition, L"Wrong pane corner, left y must be less than right y");
                }

                double paneXSize = ruPaneCorner.first - lbPaneCorner.first;
                double paneYSize = ruPaneCorner.second - lbPaneCorner.second;


                if ((double)maxResolutionH/(double)maxResolutionW >= paneYSize/paneXSize) {
                    actualPaneResolution.first = maxResolutionW;
                    actualPaneResolution.second = (int)((double)maxResolutionW*((double)paneYSize/(double)paneXSize));
                    scalingFactor = (double) actualPaneResolution.first/paneXSize;
                } else {
                    actualPaneResolution.first = (int)((double)maxResolutionH*((double)paneXSize/(double)paneYSize));
                    actualPaneResolution.second = maxResolutionH;
                    scalingFactor = (double) actualPaneResolution.second/paneYSize;
                }


                auto & valueList = figureList->getValues();

                for (auto element : valueList) {
                    interpreter_value value = *(element.value);
                    if (std::holds_alternative<std::shared_ptr<PointValue>>(value)) {
//                        this->pointsToDraw.push_back(std::get<std::shared_ptr<PointValue>>(value).get());
                    } else if (std::holds_alternative<std::shared_ptr<FigureValue>>(value)) {
                        this->figuresToDraw.push_back(std::get<std::shared_ptr<FigureValue>>(value).get());
                    } else {
                        this->handleRuntimeError(this->funcCallPosition, L"List contains other elements than figures or points");
                    }
                }

                GtkWidget *window;
                GtkWidget *darea;


                gtk_init(NULL, NULL);

                window = gtk_window_new(GTK_WINDOW_TOPLEVEL);

                darea = gtk_drawing_area_new();
                gtk_container_add(GTK_CONTAINER(window), darea);

                g_signal_connect(G_OBJECT(darea), "draw",
                    G_CALLBACK(on_draw_event), this);
                g_signal_connect(window, "destroy",
                    G_CALLBACK(gtk_main_quit), NULL);

                gtk_window_set_position(GTK_WINDOW(window), GTK_WIN_POS_CENTER);
                gtk_window_set_default_size(GTK_WINDOW(window), this->actualPaneResolution.first, this->actualPaneResolution.second);
                gtk_window_set_title(GTK_WINDOW(window), "GTK window");

                gtk_widget_show_all(window);

                gtk_main();

                this->figuresToDraw.clear();
//                this->pointsToDraw.clear();

                this->lastResult = std::monostate();
            }},
            {L"input", [this](){
                this->requireArgNum(L"input()", 0, L"no arguments");
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                std::wstring result;
                std::wcin >> result;
                this->lastResult = result;
            }},
            {L"Circle", [this](){
                this->requireArgNumBetween(L"Circle()", 0, 3, L"(point centre, double radius, list color) arguments");
                std::shared_ptr<PointValue> centrePoint = std::make_shared<PointValue>(0, 0);
                double radius = 1.0;
                if (!this->functionCallParams.empty()) {
                    this->requireArgType(L"circle centre", POINT_VARIABLE);
                    interpreter_value passedCentrePoint = this->functionCallParams.front();
                    this->functionCallParams.pop();
                    auto passedCentrePointValue = std::get<std::shared_ptr<PointValue>>(passedCentrePoint);
                    double xCoord = std::get<double>(*(passedCentrePointValue->getX().value));
                    double yCoord = std::get<double>(*(passedCentrePointValue->getY().value));
                    centrePoint = std::make_shared<PointValue>(xCoord, yCoord);
                    if (!this->functionCallParams.empty()) {
                        this->requireArgType(L"radius", DOUBLE_VARIABLE);
                        interpreter_value passedRadius = this->functionCallParams.front();
                        this->functionCallParams.pop();
                        radius = std::get<double>(passedRadius);


                        std::shared_ptr<ListValue> colorParam = this->consumeColorParam();
                        if (colorParam) {
                            this->lastResult = std::make_shared<FigureValue>(centrePoint, radius, std::move(colorParam));
                        }

                    }
                }
                this->lastResult = std::make_shared<FigureValue>(centrePoint, radius);
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
                this->requireArgNum(L".delete()", 1, L"(int index) argument");
                this->requireArgType(L"removed index", INT_VARIABLE);
                std::queue<interpreter_value> & funcCallParams = this->getFunctionCallParams();
                interpreter_value value = funcCallParams.front();
                funcCallParams.pop();
                int removedIndex = std::get<int>(value);
                if (listValue->len() <= removedIndex) {
                    this->handleRuntimeError(this->funcCallPosition, L"Removed index out of range");
                }
                listValue->remove(removedIndex);
                this->lastResult = listValue->shared_from_this();
            }},
            {L"len", [this](ListValue * listValue){
                this->requireArgNum(L".len()", 0, L"no arguments");
                this->lastResult = (int) listValue->len();
            }},
    };

    const std::unordered_map<std::wstring, std::function<void(FigureValue *)>> internalFigureFunctions= {
            {L"circ", [this](FigureValue * figureValue){
                this->requireArgNum(L".circ()", 0, L"no arguments");
                auto & points = figureValue->getPoints();
                if (auto radius = figureValue->getRadius()) {
                    double rVal = *radius;
                    this->lastResult = 2.0 * M_PI * rVal;
                    return;
                }
                if (points.size() == 1) {
                    this->lastResult = 0.0;
                    return;
                }
                std::vector<PointValue *> orderedPoints;
                for (auto & namedPoint : points) {
                    orderedPoints.push_back(namedPoint.second.get());
                }
                double circ = 0.0;
                PointValue * prevPoint;
                PointValue * currentPoint;
                double p1_x;
                double p1_y;
                double p2_x;
                double p2_y;
                for (int i = 1; i<orderedPoints.size(); i++) {
                    prevPoint = orderedPoints[i - 1];
                    currentPoint = orderedPoints[i];
                    p1_x = std::get<double>(*(currentPoint->getX().value));
                    p1_y = std::get<double>(*(currentPoint->getY().value));
                    p2_x = std::get<double>(*(prevPoint->getX().value));
                    p2_y = std::get<double>(*(prevPoint->getY().value));
                    circ += sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
                }
                p1_x = std::get<double>(*(orderedPoints[0]->getX().value));
                p1_y = std::get<double>(*(orderedPoints[0]->getY().value));
                p2_x = std::get<double>(*(orderedPoints.back()->getX().value));
                p2_y = std::get<double>(*(orderedPoints.back()->getY().value));
                circ += sqrt((p1_x - p2_x) * (p1_x - p2_x) + (p1_y - p2_y) * (p1_y - p2_y));
                this->lastResult = circ;
            }},
            {L"area", [this](FigureValue * figureValue){
                this->requireArgNum(L".area()", 0, L"no arguments");
                auto & points = figureValue->getPoints();
                if (auto radius = figureValue->getRadius()) {
                    double rVal = *radius;
                    this->lastResult = M_PI_2 * rVal * rVal;
                    return;
                }
                if (points.size() == 1) {
                    this->lastResult = 0.0;
                    return;
                }
                std::vector<PointValue *> orderedPoints;
                for (auto & namedPoint : points) {
                    orderedPoints.push_back(namedPoint.second.get());
                }
                double area = 0.0;
                PointValue * prevPoint;
                PointValue * currentPoint;
                double p1_x;
                double p1_y;
                double p2_x;
                double p2_y;
                for (int i = 1; i<orderedPoints.size(); i++) {
                    prevPoint = orderedPoints[i - 1];
                    currentPoint = orderedPoints[i];
                    p1_x = std::get<double>(*(currentPoint->getX().value));
                    p1_y = std::get<double>(*(currentPoint->getY().value));
                    p2_x = std::get<double>(*(prevPoint->getX().value));
                    p2_y = std::get<double>(*(prevPoint->getY().value));
                    area += p1_x*p2_y - p1_y*p2_x;
                }
                p1_x = std::get<double>(*(orderedPoints[0]->getX().value));
                p1_y = std::get<double>(*(orderedPoints[0]->getY().value));
                p2_x = std::get<double>(*(orderedPoints.back()->getX().value));
                p2_y = std::get<double>(*(orderedPoints.back()->getY().value));
                area += p1_x*p2_y - p1_y*p2_x;
                area /= 2.0;
                this->lastResult = area;
            }},
            {L"scale", [this](FigureValue * figureValue){
                this->requireArgNum(L".scale()", 1, L"(double scale) argument");
                this->requireArgType(L"scale", DOUBLE_VARIABLE);
                auto & points = figureValue->getPoints();
                interpreter_value scaleParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                double scale = std::get<double>(scaleParam);
                double p1_x;
                double p1_y;

                for (auto & namedPoint : points) {
                    p1_x = std::get<double>(*(namedPoint.second->getX().value));
                    p1_y = std::get<double>(*(namedPoint.second->getY().value));
                    p1_x *= scale;
                    p1_y *= scale;
                    *(namedPoint.second->getX().value) = p1_x;
                    *(namedPoint.second->getY().value) = p1_y;
                }
                if (auto radius = figureValue->getRadius()) {
                    figureValue->setRadius(*radius*scale);
                }
                this->lastResult = figureValue->shared_from_this();
            }},
            {L"rotate", [this](FigureValue * figureValue){
                this->requireArgNum(L".rotate()", 2, L"(point rotationPoint, double angle) arguments");
                this->requireArgType(L"rotation point", POINT_VARIABLE);
                auto & points = figureValue->getPoints();
                interpreter_value rotationPoint = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * rotationPointVal = std::get<std::shared_ptr<PointValue>>(rotationPoint).get();
                double rotation_point_x = std::get<double>(*(rotationPointVal->getX().value));
                double rotation_point_y = std::get<double>(*(rotationPointVal->getY().value));
                this->requireArgType(L"rotation angle", DOUBLE_VARIABLE);
                interpreter_value angleParam = this->functionCallParams.front();
                this->functionCallParams.pop();
                double angle = std::get<double>(angleParam);
                double p1_x;
                double p1_y;
                double rot_x = sin(angle);
                double rot_y = cos(angle);

                for (auto & namedPoint : points) {
                    p1_x = std::get<double>(*(namedPoint.second->getX().value));
                    p1_y = std::get<double>(*(namedPoint.second->getY().value));
                    p1_x -= rotation_point_x;
                    p1_y -= rotation_point_y;
                    p1_x = p1_x * rot_x - p1_y * rot_y;
                    p1_y = p1_x * rot_y + p1_y * rot_x;
                    p1_x += rotation_point_x;
                    p1_y += rotation_point_y;
                    *(namedPoint.second->getX().value) = p1_x;
                    *(namedPoint.second->getY().value) = p1_y;
                }
                this->lastResult = figureValue->shared_from_this();
            }},
            {L"transport", [this](FigureValue * figureValue){
                this->requireArgNum(L".transport()", 1, L"(point transportVector) argument");
                this->requireArgType(L"transport vector", POINT_VARIABLE);
                interpreter_value transportVector = this->functionCallParams.front();
                this->functionCallParams.pop();
                PointValue * transportVectorVal = std::get<std::shared_ptr<PointValue>>(transportVector).get();
                double transport_x = std::get<double>(*(transportVectorVal->getX().value));
                double transport_y = std::get<double>(*(transportVectorVal->getY().value));
                auto & points = figureValue->getPoints();
                double p1_x;
                double p1_y;

                for (auto & namedPoint : points) {
                    p1_x = std::get<double>(*(namedPoint.second->getX().value));
                    p1_y = std::get<double>(*(namedPoint.second->getY().value));
                    p1_x += transport_x;
                    p1_y += transport_y;
                    *(namedPoint.second->getX().value) = p1_x;
                    *(namedPoint.second->getY().value) = p1_y;
                }
                this->lastResult = figureValue->shared_from_this();
            }},
            {L"copy", [this](FigureValue * figureValue){
                this->requireArgNum(L".copy()", 0, L"no arguments");
                auto & points = figureValue->getPoints();
                std::map<std::wstring, std::shared_ptr<PointValue>> newFigurePoints;
                auto color = figureValue->getColor()->getValues();
                int r = std::get<int>(*(color[0].value));
                int g = std::get<int>(*(color[1].value));
                int b = std::get<int>(*(color[2].value));
                ListValue newColor = ListValue(std::vector<AssignableValue>({AssignableValue(r), AssignableValue(g), AssignableValue(b)}));

                for (auto & namedPoint : points) {
                    double p1_x = std::get<double>(*(namedPoint.second->getX().value));
                    double p1_y = std::get<double>(*(namedPoint.second->getY().value));
                    std::shared_ptr<PointValue> newPoint = std::make_shared<PointValue>(p1_x, p1_y);
                    newFigurePoints[namedPoint.first] = newPoint;
                }
                this->lastResult = std::make_shared<FigureValue>(newFigurePoints, std::make_shared<ListValue>(newColor));
            }},
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
    std::optional<interpreter_value> lastResult = std::nullopt;
    bool lastConditionTrue = false;


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
    void requireArgNumBetween(const std::wstring & name, int argNumLower, int argNumUpper, const std::wstring & argList);
    void createNewFigure(const std::wstring & name);
    std::shared_ptr<ListValue> consumeColorParam();
public:
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
