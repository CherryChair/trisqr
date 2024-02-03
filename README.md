# TriSqr language

## Description

TriSqr is interpreted dynamically and strongly typed langnuage created during TKOM classes at WUT. In addition to offering standard types it offers point type and figure type. Figures can be drawn in GTK window.

## Table of contents

- [TriSqr language](#trisqr-language)
  - [Description](#description)
  - [Table of contents](#table-of-contents)
  - [Building project](#building-project)
    - [Building with tests](#building-with-tests)
    - [Building without tests](#building-without-tests)
  - [Running interpretes](#running-interpretes)
  - [Variable types](#variable-types)
  - [Comments](#comments)
  - [Declaring variables](#declaring-variables)
  - [Conditional statement](#conditional-statement)
  - [loops](#loops)
  - [Funkcje](#funkcje)
  - [Points](#points)
  - [Figures](#figures)
  - [Values with fixed type](#values-with-fixed-type)
  - [Figure attributes and methods](#figure-attributes-and-methods)
    - [Shared](#shared)
    - [Special](#special)
  - [Error types](#error-types)
    - [Lexical errors](#lexical-errors)
    - [Syntax errors](#syntax-errors)
    - [Semantic errors](#semantic-errors)
    - [Runtime errors](#runtime-errors)
    - [Intepreter errors](#intepreter-errors)
  - [Operators](#operators)
  - [Syntax EBNF](#syntax-ebnf)
  - [Tests](#tests)
  - [Known implementation errors](#known-implementation-errors)
  - [TODO](#todo)

## Building project

Project was built on WSL2 with Ubuntu 22.0.1 LTS and instructions below are considering using same environment.
Project is built using cmake.
Figures are drawn in gtk windows using cairo.
- install gtk3 and cairomm-1.0
```bash
sudo apt install libcairomm-1.0-dev
sudo apt install libgtk-3-dev
```
### Building with tests
- in main project direcotry create googletest directry and enter it
```bash
mkdir googletest
cd googletest
```
- clone googletest repository
```bash
git clone https://github.com/google/googletest.git
```
- change downloaded repository dir name to lib 
```bash
mv googletest lib
```
- create `CMakeLists.txt`
```bash
touch CMakeLists.txt
```
- copy text below to newly created `CMakeLists.txt`
```cmake
# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(lib/googletest/include lib/googletest)
pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.0)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run ../Tests/interpreter_tests.cpp ../Tests/parser_tests.cpp ../Tests/lexer_tests.cpp ../Lexer/lexer.cpp ../Lexer/lexer.h ../Lexer/Token.cpp ../Lexer/Token.h ../ErrorHandler/ErrorHandler.cpp ../ErrorHandler/ErrorHandler.h ../Parser/Parser.cpp ../Parser/Parser.h ../Program/Program.cpp ../Program/Program.h ../Visitors/Visitor.cpp ../Visitors/Visitor.h ../Lexer/position.h ../Lexer/lexer_error_types.h ../Visitors/VisitorTree.cpp ../Visitors/VisitorTree.h ../Visitors/VisitorInterpreter.cpp ../Visitors/VisitorInterpreter.h)
target_link_libraries(Google_Tests_run gtest gtest_main PkgConfig::CAIROMM PkgConfig::GTK3)
```
- return to main project direcotry, create build directory and build project
```bash
cd ..
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```
### Building without tests
- in file `CMakeLists.txt` comment out line adding test subdirectory
```cmake
# add_subdirectory(googletest)
```
- create build directory and build project
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```
## Running interpretes

Interpreter executable file `trisqr` is built inside directory `cmake-build-debug`. When executing it we pass 1 argument, which is path to text file containing source code in **TriSqr** language. On some environments there is a problem with recognition of UTF-8 signs, so it is recommended to use only ASCII signs.  

Test executable path is `cmake-build-debug/googletest/Google_Tests_run`.

Inside `Examples` and `Tests` subdirectories, there are examples of source code of **TriSqr**.

`Examples` contains:
- `example_program.trisqr` - program visualising values of 1/n and 1/n^2 
- `triangles.trisqr` - program drawing smaller and smaller triangles in different colors
- `parser_basic.trisqr` - testing basic functionality of language like assignements, mutability etc.
- `test.trisqr` - contatins test of access and manipulation of list elements
- `fibonacci.trisqr` - contains implementation of fibonacci sequence elements calculation using for loop and recursion

`Tests` contains:
- `semantic_hell.trisqr` - file containing multitude of semantic errors, temporarily used to test semantic analysis
- `parser_condition_tests.trisqr` - file testing evaluation of `||` and `&&` expression, used in interpreter_tests.cpp

## Variable types

**TriSqr** variables can change type during runtime, but comparisons, additions and simliar operations can only be performed between variables of same type.

Types:
- number types:
  - int
  - double
- bool
- string
- list
- figure
- point 
- none
  
Lists can store any type, even itself. Two lists can be concatenated with "+", which returns new list with elements of second list after elements of first. Elements are indexed from 0 and can be accessed using square brackets ```list[i]```.
List methods:
- ```.append(el1, el2, ...)``` - puts elements in function call at the end of the list 
- ```.delete(index)``` - deletes element on ```index``` position
- ```.len()``` - returns number of elements in list

Strings can be concatenated using "+".

Variables of type:
- `point`
- `list`
- `figure`

are mutable.

Type of varaible can be converted using ```to``` keyword: ```*variable* to *type*```.

Supported type converion:
- ```int to double```
- ```int to bool```
- ```double to int```
- ```double to bool```
- ```bool to int```
- ```bool to double```
- ```str to int```
- ```str to double```
- every type can be converted to `str`

Type of variable can be checked using: ``` *variable* is *type*```.

## Comments

Comments are from "#" to end of line.

## Declaring variables

Variable declaration:
```
vv variable_name
```
Variables are stored using pointers.

## Conditional statement

Conditional statement has form:
```
if (bool expression) { 
  *code*
} elif (bool expression) {
  *code*
} else{
  *code*
}
```

## loops
While loop:
```
while (bool expression) {
    *code*
}
```
There are 2 types of for loops:
```
for el in list {
  *code*
}
```
iterates through elements "el" of list "list".
```
for i in range(s,k){
  *code*
}
```
"i" takes subsequent values of integers from "s" to "k" excluding "k".

## Funkcje

Function definition:
```
func FunctioName(a, b, c){
    *code*
}
```
Function with same names are not allowed, program execution starts from `main`.

Functions can be recursive. If there is no return statement at the end of function, function returns `none`, `none` can also be returned using `return;`. When calling function with fewer params than in declaration, params not in function call are assigned `none` value.

Built-in functions:
- `print(variable)` - takes 1 pram of any type, sends to standard output string representation of `variable`
- `printn(variable)` - print + `'\n'`
- `input()` - takes user input from standard input, gets string to neares white sign and returns it
- `draw(list, p1, p2)` - opens gtk window with figures in list, drawn scene is in shape of rectangle with corners p1 and p2, p1 - left bottom corner, p2 - upper right corner.

## Points

Variable of type ```point``` contains coordinates ```x``` and ```y``` which are of type `double`. Points are created by ```(x, y)```. Coordinate values can be accessed by ```.x``` and ```.y```. Points can be subtracted and added using `+` and `-`.

## Figures

`Figures` are declated in this way:
```figure <Identifier> {<point_name>:<default_point_value>, <point_name>:<default_point_value>, ..., <point_name>:<default_point_value>, color:<defalut_color_value>}```

For example:
```
figure Triangle{
  a: (0.0,0.0),
  b: (0.0,1.0),
  c: (1.0,0.0),
  color: [255,0,0]
}
```
Declarations are placed outside of function definitions, figure points can include expressions, which are evaluated at the begging of execution before main.
Declated figure can be assigned using ```vv triangle1 = Triangle((x1,y1), (x2,y2), (x3,y3), [r,g,b])```, color can be skipped or all params can be skipped ```vv triangle2 = Triangle()```, whene params are skipped created figure params take values default values from declaration. Figure params can be accessed with `.`, for example ```triangle1.a```. 

FIgures are drawn by draing lines between vertices form declaration in order they are placed in declaration, for example in ```Triangle``` from before lines are drawn between: a->b, b->c, c->b.

There is additional ```Circle``` built-in figure. It's created with: ```Circle(<middle_point>, <radius>)``` or ```Circle()```, which creates unit circle in ```(0,0)```. Color value can also be passed to ```Circle``` constructor.

## Values with fixed type

There are 5 special values, that cause runtime error when program tries to change their value to type that is forbidden.
- point coordinates - only double
- figure point - only point value
- radius - only double
- figure color - list of 3 integers from 0 dto 255
- figure color param - integer from 0 to 255

## Figure attributes and methods 

### Shared

Methods:
- .circ() - returns circumference of figure
- .area() - returns area of figure calculated using trapezoid method, for figures that are irregular and their sides have common points calculated area won't be correct
- .scale(double scale) - scales figure `scale` times from `(0, 0)` point
- .rotate((double x1, double y1), double angle) - rotates figure vertices around `(x1, y1)` by `angle` in radians, **doesn't keep figure shape**
- .transport(double x, double y) - transports figure by vector `(x, y)`
- .copy() - returns copy of figure variable

Parametry:
- .<name_of_point_in_declaration> - vertex of figure
- color - [int r, int g, int b] colors of lines in RGB, default to black - [0,0,0]

### Special

- koło:
  - .r - radius of circle
  - .c - centre of circle

## Error types

### Lexical errors
Lexcial analysis check whether token was created correctly and in case of too long string, comment or number token is created with signs that are below size limit, if next limit is breached lexical analysis stops and error is thrown.

### Syntax errors

Error is thrown on first detected syntactic error. 

### Semantic errors

During semantic analysis we check undeclared identifiers, duplicate identifier declarations, identifiers with names of built-in functions, calls to methods that aren't built-in. Error is thrown after whole file is analyzed.

### Runtime errors

Errors are thrown when we try to access elements out of list range, compare, add, subtract, divide, multiply forbidden values. There are also errors which are thrown when we pass too many values to fucntion, values that are not allowed in built-in function or when we try to change value in points or figures to different type. 

### Intepreter errors

If there is expression value missing in place where it is expected to exist, interpreter error is thrown. Interpreter error is a signal of errors in language implmentation.

## Operators

Higher number means higher priority.

|Operators|Priority|
|---|---|
|  &#124;  &#124;  | 1  |
| &&  |  2  |
| <,>,<=,>=,==,!=  |  3 |
| is  |  4 |
| +,-  |  5 |
| *,/  |  6 |
| to  |  7 |
| !,-  |  8 |
| .  |  9 |
| [ ]  |  10 |
| ( )  |  11 |

## Syntax EBNF
```   
- Program                            :== {FuncDeclaration | FigureDeclaration};
- FuncDeclaration                    :== "func ", identifier, "(", decl_argument_list, ")", CodeBlock;          
- decl_argument_list                 :== [identifier, {", ", identifier}];
- FigureDeclaration                  :== "figure ", identifier, "{", point_list, "}";   
- point_list                         :== point_declaration, {",", point_declaration};   
- point_declaration                  :== identifier, ":", Expression;
- CodeBlock                          :== "{", {Statement}, "}";
- Statement                          :== WhileStatement
                                       | ForStatement
                                       | IfStatement
                                       | DeclarationStatement
                                       | IdentiferAssignOrExpressionStatement
                                       | IdentiferExpressionStatement
                                       | ReturnStatement;
- WhileStatement                     :== "while", ConditionAndBlock;
- IfStatement                        :== "if", ConditionAndBlock  {"elsif", ConditionAndBlock }, ["else", CodeBlock];
- ConditionAndBlock                  :== "(",  Expression, ")", CodeBlock;
- ForStatement                       :== "for", identifier, "in", Expression | range, CodeBlock;           
- range                              :== "range" "(", Expression, ",", Expression, ")";   
- DeclarationStatement               :== "vv ", identifier, ["=", Expression], ";";
- IdentiferAssignStatement           :== ObjectAccessExpression, "=", Expression, ";"
- IdentiferExpressionStatement       :== ObjectAccessExpression, ";"
- ReturnStatement                    :== "return ", [Expression], ";"
- ObjectAccessExpression             :== IdentifierListIndexExpression, {".", IdentifierListIndexExpression};   
- IdentifierListIndexExpression      :== IdentifierFunctionCallExpression, {"[", Expression, "]"};   
- IdentifierFunctionCallExpression   :== identifier, ["(", argument_list, ")"];
- argument_list                      :== [Expression, {",", Expression}];
- Expression                         :== ExpressionAnd, {"||",  ExpressionAnd};
- ExpressionAnd                      :== ExpressionComp , {"&&",  ExpressionComp};   
- ExpressionComp                     :== ExpressionIs, [comp_operator, ExpressionIs];   
- ExpressionIs                       :== ExpressionAdd, [" is ",  type];
- ExpressionAdd                      :== ExpressionMul, {add_operator, ExpressionMul};
- ExpressionMul                      :== ExpressionTo, {mul_operator, ExpressionTo};
- ExpressionTo                       :== ExpressionNeg, [" to ",  type];
- ExpressionNeg                      :== [negation_operator], ExpressionValue;
- ExpressionValue                    :== value
                                       | list
                                       | point
                                       | ObjectAccessExpression
                                       | "(", Expression, ")";
- list                               :== "[", Expression, {", ", Expression} "]";
- point                              :== "(", Expression, ",", Expression, ")";  
- value                              :== int_val
                                       | bool_val
                                       | double_val
                                       | string_val
                                       | "none";
- identifier                         :== [a-zA-Z][0-9a-zA-Z_]*
- type                               :== "none" 
                                       | "int" 
                                       | "bool" 
                                       | "str" 
                                       | "double" 
                                       | "figure" 
                                       | "point";
- comp_operator                      :== "<"
                                       | "=="
                                       | ">"
                                       | ">="
                                       | "<="
                                       | "!=";
- mul_operator                       :== "*"
                                       | "/";
- add_operator                       :== "+"
                                       | "-";
- bool_val                           :== "true"
                                       | "false"
- negation_operator                  :== "!"
                                       | "-";
- double_val                         :== int_val, ".", digit, {digit};
- string_val                         :== '"', {char | digit | special_char}, '"';
- char                               :== [a-zA-Z];
- special_char                       :== "\n" | "\\" | '\"' | "\r" |pozostałe normalnie;
- int_val                            :== digit_without_zero, {digit}
                                       | "0";
- digit                              :==  digit_without_zero | "0";
- digit_without_zero                 :== [1-9]
```           
## Tests

Tests are made using googletest library.

Unit tests for Lexical analyzer are almost finished. They're placed in `Tests/lexer_tests.cpp`. Lexer test check values of tokens, positions and errors.

In case of parser comparison of ASTs is implemented and there is an exapmle test in `Tests/parser_tests.cpp`.

Semantic analyzer is tested by reading errors in standard output which are generated when trying to run code in file `Tests/semantic_hell.trisqr`.

There is an exapmle acceptance test for interpreter in `interpreter_tests.cpp`. It check whether conditional expressions are evaluated in correct order and whether evaluation is stopped when result is known. It executes program in `Tests/parser_condition_tests.cpp`, which prints out `PASS` for each test.

## Known implementation errors

- In case of unknown sign in text file parser finishes analysis on it 
- In case when we call figure construtor and try to use scale on it at the same time `vv a = Trianlge().scale(2.0)` there is a bad variant access error values in points of figure are uninitialized
- When having duplicate function or figure decalrations there is semantic message but program just ignores on of declarations

## TODO

- make AST nodes params private and implement getters
- implment more tests
- change way of passing and storing values
- implement operation visitors for 2 interpreter_value 