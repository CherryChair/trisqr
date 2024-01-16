# Projekt TKOM

## Informacje wstępne
Autor: **Michał Kowalczyk**

Nazwa języka: **TriSqr**

Język realizacji: **c++**

## Spis treści

- [Projekt TKOM](#projekt-tkom)
  - [Informacje wstępne](#informacje-wstępne)
  - [Spis treści](#spis-treści)
  - [Treść zadania](#treść-zadania)
  - [Wymagania funkcjonalne](#wymagania-funkcjonalne)
  - [Wymagania niefunkcjonalne](#wymagania-niefunkcjonalne)
  - [Konfiguracja](#konfiguracja)
  - [Obsługiwane typy zmiennych](#obsługiwane-typy-zmiennych)
  - [Komentarze](#komentarze)
  - [Tworzenie zmiennych](#tworzenie-zmiennych)
  - [Instrukcja warunkowa](#instrukcja-warunkowa)
  - [Pętle](#pętle)
  - [Funkcje](#funkcje)
  - [Punkty](#punkty)
  - [Tworzenie figur](#tworzenie-figur)
  - [Metody i atrybuty figur](#metody-i-atrybuty-figur)
    - [Współdzielone](#współdzielone)
    - [Charakterystyczne](#charakterystyczne)
  - [Złożone przykłady wykorzystania języka](#złożone-przykłady-wykorzystania-języka)
    - [Przykład nr 1](#przykład-nr-1)
    - [Przykład nr 2](#przykład-nr-2)
  - [Przykłady błędów](#przykłady-błędów)
    - [Błędy leksykalne](#błędy-leksykalne)
    - [Błędy składniowe](#błędy-składniowe)
    - [Błędy semantyczne](#błędy-semantyczne)
  - [Operatory](#operatory)
  - [Gramatyka](#gramatyka)
  - [Testowanie](#testowanie)

## Treść zadania

Język do opisu figur geometrycznych i ich właściwości. Podstawowe typy figur geometrycznych (trójkąt, prostokąt, romb, trapez, koło itd.) są wbudowanymi typami języka. Każdy typ posiada wbudowane metody służące do wyznaczania charakterystycznych dla niego wielkości, np. obwód, pole powierzchni, wysokość, średnica itp. Kolekcja figur tworzy scenę wyświetlaną na ekranie.

## Wymagania funkcjonalne

- możliwość rysowania wielu scen
- możliwość rysowania figur w różnych kolorach 
- możliwość wykonania kodu z pliku
- komunikaty o błędach wyświetlają numer linii i znaku miejsca wystąpienia błędu

## Wymagania niefunkcjonalne
- leniwe odczytywanie strumienia danych
- testowanie błędów
- testowanie poprawności realizowania przykładów kodu

## Budowanie projektu

Środowisko Linux.
Wymagane narzędzia do budowania to cmake i make.
GLFW
- instalujemy glfw
```bash
sudo apt install libglfw3-dev
```
### Budowanie z testami.
- w folderze głównym repozytorium tworzymy folder googletest i przechodzimy do niego
```bash
mkdir googletest
cd googletest
```
- pobieramy repozytorium googletest
```bash
git clone https://github.com/google/googletest.git
```
- zmieniamy nazwę foleru zawierającego repozytorium
```bash
mv googletest lib
```
- tworzymy plik `CMakeLists.txt`
```bash
touch CMakeLists.txt
```
- wypełniamy go treścią
```cmake
# 'Google_test' is the subproject name
project(Google_tests)

# 'lib' is the folder with Google Test sources
add_subdirectory(lib)
include_directories(lib/googletest/include lib/googletest)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run ../Tests/interpreter_tests.cpp ../Tests/parser_tests.cpp ../Tests/lexer_tests.cpp ../Lexer/lexer.cpp ../Lexer/lexer.h ../Lexer/Token.cpp ../Lexer/Token.h ../ErrorHandler/ErrorHandler.cpp ../ErrorHandler/ErrorHandler.h ../Parser/Parser.cpp ../Parser/Parser.h ../Program/Program.cpp ../Program/Program.h ../Visitors/Visitor.cpp ../Visitors/Visitor.h ../Lexer/position.h ../Lexer/lexer_error_types.h ../Visitors/VisitorTree.cpp ../Visitors/VisitorTree.h ../Visitors/VisitorInterpreter.cpp ../Visitors/VisitorInterpreter.h)
target_link_libraries(Google_Tests_run gtest gtest_main)
```
- wracamy do głównego folderu projektu, tworzymy katalog, gdzie projekt się zbuduje i go budujemy
```bash
cd ..
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```
### Budowanie tylko pliku wykonywalnego interpretera
- w pliku `CMakeLists.txt` zakomenujemy linijkę dotyczącą testów
```cmake
# add_subdirectory(googletest)
```
- tworzymy katalog, gdzie projekt się zbuduje i go budujemy
```bash
mkdir cmake-build-debug
cd cmake-build-debug
cmake ..
make
```
## Uruchamianie programu

Plik wykonywalny interpretera `trisqr` buduje się w foldere `cmake-build-debug`. Przyjmuje 1 arguemnt, który jest ścieżką do pliku tekstowego zawierającego kod źródłowy w języku **trisqr**. Niestety na niektórych środowiskach polskie znaki przeszkadzają lexerowi w budowaniu tokenów, więc zaleca się używanie 

Plik wykonywalny testów to `cmake-build-debug/googletest/Google_Tests_run`.

Przykładowe programy z kodem źródłowym **trisqr** w znajdują się w folderze `Examples` i `Tests`.

W `Examples` znajdują się:
- `parser_basic.trisqr` - zawiera testy podstawowych funkcjonalności języka
- `test.trqisqr` - zawiera testy dostępów do list i usuwania ich elementów, kończy się błędem
- `fibonacci.trisqr` - zawiera implementację rekurencyjną i z użyciem pętli for funkcji wyliczającej wartości ciągu Fibonacciego

W `Tests` znajdują się:
- `semantic_hell.trisqr` - plik zawierający dużo błędów semantycznych, testuje działanie analizatora semantycznego 
- `parser_condition_tests.trisqr` - plik testujący ewaluację wyrażeń z `||` i `&&`, jest on wykorzystywany w interpreter_tests.cpp

## Konfiguracja

W plikach konfiguracyjnych zdefiniujemy m.in. wartość PI, maksymalną długość wartości napisów w kodzie. 

## Obsługiwane typy zmiennych

Wariant typowania: dynamiczne, silne.

Typy:
- liczbowe:
  - całkowita
  - zmiennoprzecinkowa
- boolowska
- napis
- lista
- figura
- punkt 
- pusta wartość none
  
Lista przyjmuje dowolne typy. Dwie listy można łączyć za pomocą "+", ta operacja zwraca nową listę będącą złączeniem 2 list. Poszeczególne elementy indeksowane sa od 0 i dostajemy się do nich za pomocą nawiasów kwadratowych ```list[i]```.
Metody listy:
- ```.append(el)``` - dodaje element na koniec listy
- ```.delete(index)``` - usuwa element o indeksie ```index```
- ```.len()``` - zwraca ilość elementów listy

Zmienne typu str można konkatenować za pomocą "+".

Zmienne typu:
- `point`
- `list`
- `figure`

są mutowalne.

Przez silne typowanie wymagane jest wprowadzenie możliwości konwersji typów. Będziemy to robić za pomocą operatora ```to```, przy zmianie zmiennej *variable* na typ *type*: ```*variable* to *type*```.

Możliwe konwersje typów:
- ```int to double```
- ```int to bool```
- ```double to int```
- ```double to bool```
- ```bool to int```
- ```bool to double```
- ```str to int```
- ```str to double```
- wszystkie typy mają reprezentację w postać `str`

Wprowadzimy też wygodne sprawdzanie typów zmiennych: ``` *variable* is *type*```.

## Komentarze

Komentarz od "#" do końca linii.

## Tworzenie zmiennych

Deklaracja zmiennej:
```
vv nazwa_zmiennej
```
Wartości zmiennych są przechowywane przez referencje.
Nie ma możliwości tworzenia zmiennych globalnych.
## Instrukcja warunkowa

Instrukcja warunkowa ma postać:
```
if (wyrażenie bool) { 
  *kod*
} elif (wyrażenie bool) {
  *kod*
} else{
  *kod*
}
```

## Pętle
Pętla while:
```
while (wyrażenie bool) {
    *kod*
}
```
Będą 2 pętle for:
```
for el in list {
  *kod*
}
```
iteracja po elementach "el" listy "list".
```
for i in range(s,k){
  *kod*
}
```
"i" przyjmuje kolejne wartości od "s" do "k" z wyłączeniem k.

## Funkcje

Funkcje będą definiowane za pomocą:
```
func NazwaFunkcji(a, b, c){
    *kod*
}
```
Może istniejć tylko jedna funkcja o danej nazwie, a program wykonuje się od funkcji `main`.

Jest możliwość rekursji. Nie trzeba podawać return na końcu funkcji, wtedy automatycznie zwraca wartość `none`, tak samo jak przy napisaniu `return;`. W przypadku odwołania się do funkcji można podać mniej argumentów niż jest w deklaracje, wtedy parametry bez podanych wartości przyjmują wartości `none`.

Istnieją wbudowane funkcje:
- `print(variable)` - przyjmuje 1 argument dowolnego typu, wysyła na standardowe wyjście reprezentacje `variable`
- `printn(variable)` - print + `'\n'`
- `input()` - przyjmuje podane przez użytkownika napisy ze standardowego wejścia, pobiera napis do najbliższego białego znaku
- `draw(list, p1, p2)` - otwiera okienko z narysowanymi figurami geometrycznymi zawartymi w liście, ignoruje elementy listy niebędące figurami, rysowana scena jest rozpięta w prostokącie, którego przeciwległe wierzchołki to p1 i p2. Można pominąć p1 i p2 przy wywoływaniu metody wtedy zostanie narysowana scena, która będzie zawierać wszystkie podane figury (poprzez analizę najmniejszych i największych wartości x i y punktów należacych do sceny)

## Punkty

Istnieje zmienna typu ```point```, punkt zawiera współrzędną ```x``` i ```y``` o wartościach double. Tworzymy go tak ```(x, y)```. Do jego wartości moża się dostać za pomocą ```.x``` i ```.y```. Punkty można dodawać i odejmować.

## Tworzenie figur

Typy figur są tworzone za pomocą deklaracji 
```figure <Identifier> {<point_name>:<default_point_value>, <point_name>:<default_point_value>, ..., <point_name>:<default_point_value>, color:<defalut_color_value>}```

Np.
```
figure Triangle{
  a: (0.0,0.0),
  b: (0.0,1.0),
  c: (1.0,0.0),
  color: [255,0,0]
}
```
Deklaracje podajemy poza funkcjami, punkty mogą zawierać w sobie wyrażenia, które są ewaluowane na początku działania programu przed funkcją main.
Tak zadeklarowaną figurę tworzymy za pomocą ```vv triangle1 = Triangle((x1,y1), (x2,y2), (x3,y3), [r,g,b])``` lub za pomocą ```vv triangle2 = Triangle()```, wtedy jest tworzona z domylnymi wartościami punktów z deklaracji. Potem możemy dostawać się do punktów za pomocą nazw nadanych w deklaracji. Np. ```triangle1.a```. 

Figury będą rysowane przez tworzenie linii między kolejno zadeklarowanymi punktami, np. w przykładowym ```Triangle```, rysujemy linie a->b, b->c, c->b.

Dodatkowo wprowadzona jest figura ```Circle```. Nowe koło jest tworzone przez: ```Circle(<middle_point>, <radius>)``` lub ```Circle()```, które tworzy koło jednostkowe o środku w punkcie ```(0,0)```.

## Metody i atrybuty figur

### Współdzielone

Metody:
- .<nazwa_punktu_z_deklaracji> - punkt 
- .circ() - zwraca obwód
- .area() - zwraca pole, w przypadku figur, których boki się przecinają zwracane jest ```-1```.
- .scale(double scale) - skaluje figurę w stosunku do początku układu współrzędnych o skalę scale
- .scale(double scale, (double x1, double y1)) - skaluje figurę o skalę scale w stosunku do wybranego punktu
- .rotate(double angle) - obraca figurę wokół początku układu współrzędnych o kąt angle podawany w radianach
- .transport(double x, double y) - przesuwa figurę o wektor (x, y)
- .copy() - zwraca kopię danej figury

Parametry:
- color - [int r, int g, int b] kolor linii figury w RGB, domyślnie ustawiane na [0,0,0]
- border - (double) grubość linii

### Charakterystyczne

- koło:
  - .r - parametr oznaczający promień
  - .cent - parametr oznaczający środek 

## Złożone przykłady wykorzystania języka

### Przykład nr 1
Coś à la trójkąt Sierpińskiego:

```
figure Triangle {
  a: (0.0, 0.0),
  b: (1.0, 0.0),
  c: (0.0, 1.0),
}

func sierpinsky(a, b, c, n, list){
  if (n <= 0) {
    return;
  }
  vv n_n = n-1;
  vv newTriangle = Traingle(a, b, c);
  x_off = (b.x-a.x)/2.0;
  y_off = (c.y-a.y)/2.0;
  newTriangle.color = [255, 255, 255];
  newTriangle.color = 0;
  list.append(newTriangle);
  sierpinsky((a.x-x_off, a.y-y_off), (b.x, b.y-y_off), (c.x-x_off, c.y), n_n, list);
  sierpinsky((a.x+x_off, a.y-y_off), (b.x, b.y-y_off), (c.x+x_off, c.y), n_n, list);
  sierpinsky((a.x-x_off, a.y+y_off), (b.x, b.y+y_off), (c.x-x_off, c.y), n_n, list);
}

func main() {
  vv sierpinskyList = [];
  vv newTriangle = Triangle();
  newTriangle.rotate(pi)
  newTriangle.scale(16.0)
  newTriangle.color = [0, 0, 0];
  newTriangle.color = 0;
  sierpinsky((8.0, 8.0), (0.0, 8.0), (8.0, 0.0), 6, sierpinskyList)
  draw(sierpinskyList, (-1.0, -1.0), (17.0, 17.0));
}

```

### Przykład nr 2
Tworzymy coraz minejsze kwadraty obrazujące kolejne elementy ciągów 1/n^2 i 1/2^(2*n):
```
figure Square {
  a: (0.0,0.0),
  b: (0.0,1.0),
  c: (1.0,0.0),
  d: (1.0,1.0)
}

func power(base, n) {
  if(n>0){
    return base*power(base, n-1);
  } elif (n < 0) {
    return -1;
  }
  return 1;
}

func sumAreas(list) {
  vv sum = 0;
  for el in list{
    if(el is Figure){
      sum = sum + el.area();
    }
  }
  return sum;
}

func main() {
  vv list1 = [];
  vv list2 = [];
  vv n = 10;
  vv sum_of_scale1 = 0.0;
  vv sum_of_scale2 = 0.0;
  vv base_sqr = Square();
  fori i in (0, n){
    vv scale1 = power(0.5, i);
    vv scale2 = 1.0/(i to double);
    vv sqr1 = base_sqr.copy().scale(scale1);
    vv sqr2 = base_sqr.copy().scale(scale2);
    sqr1.transport(sum_of_scale1 + scale1/2.0, scale1/2.0);
    sqr2.transport(-sum_of_scale2 + -scale2/2.0, scale2/2.0);
    sum_of_scale1 = sum_of_scale1 + scale1;
    sum_of_scale2 = sum_of_scale2 + scale2;
    list1.append(sqr1);
    list2.append(sqr2);
  }
  vv sum1 = sumAreas(list1);
  vv sum2 = sumAreas(list2);
  vv max_sum = 0.0;
  if (sum1 > sum2) {
    max_sum = sum1;
  } else {
    max_sum = sum2;
  }
  print("Suma 1: " + sum1 to str);
  print("Suma 2: " + sum2 to str);
  list_to_draw = list1 + list2;
  draw(list_to_draw, (list2[list2.len-1].a.x - 1.0, -1.0), (list1[list1.len-1].a.x + 1.0, max_sum + 1.0));
}
```

## Przykłady błędów

### Błędy leksykalne
Dla kodu w rodzaju:
```
1.2 to str + '3 to int; \n\r\n \r vv a;  \r\n
```
Pojawi się błąd:
```
LEX_ERR: String is not closed.
Line 1, character 14: '3 to int; \n\r\n \r vv a;  \r\n << error
```
Dla kodu w rodzaju:
```
1.2'3 to int; \n\r\n \r vv a;  \r\n
```
Pojawi się błąd:
```
LEX_ERR: String is not closed.
Line 1, character 4: '3 to int; \n\r\n \r vv a;  \r\n << error
```
Dla kodu w rodzaju:
```
2.2147483648 2147483648.2147483648
```
Pojawi się błąd:
```
LEX_ERR: Number after . is too big.
Line 1, character 1: 2.2147483648 << error
LEX_ERR: Number is too big.
Line 1, character 14: 2147483648 << error
LEX_ERR: Number is too big.
Line 1, character 25: 2147483648 << error
```
Dla kodu w rodzaju:
```
if (1.33 to int == 1 & true) {
  a = a+1;
}
```
Pojawi się błąd
```
LEX_ERR: Missing second & in && operator.
Line 1, character 22: &  << error
```
### Błędy składniowe
Dla kodu w rodzaju:
```
if 1.33 to int == 1 && true) {
  a = a+1;
}
```
Przerwie się dalsze sprawdzanie i pojawi się błąd
```
PARSE_ERR: Missing left bracket.
Line 1, character 4: if 1.33  << error
```
Dla kodu w rodzaju:
```
if (1.33 to int == 1 && {}) {
  a = a+1;
}
```
Przerwie się dalsze sprawdzanie i pojawi się błąd
```
PARSE_ERR: Wrong character after and operator.
Line 1, character 22: && {}  << error
```
### Błędy semantyczne
Dla kodu w rodzaju:
```
vv a = 0;
vv b = 0;
if (1.33 to int == 1 & true) {
  a = b();
}
```
Pojawi się błąd
```
ERR: b is not a function or method.
Line 4, character 7: b()  << error
```
Dla kodu w rodzaju:
```
figure Triangle {a:(0.0, 0.0), b:(0.0, 1.0), c:(1.0, 0.0)}

func main() {
  vv tr1 = Triangle();
  vv d = tr1.d;
}
```
Pojawi się błąd
```
ERR: Triangle does not have attribute d.
Line 4, character 7: tr1.d  << error
```
## Operatory

Im większa liczba, tym wyższy priorytet.

|Operator|Priorytet|
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

## Gramatyka
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
## Testowanie

Biblioteka użyta do testowania to w googletest. 

Testy jednostkowe zostały zaimplementowane w dużym stopniu dla analizatora leksykalnego w `Tests/lexer_tests.cpp`. Sprawdzane są wartości tokenów, ich pozycje i komunikaty o błędach.

W przypadku analizatora składniowego zaimplementowane są odpowiednie funkcje do porównywania drzew rozbioru składniowego i jest zrobiony przykładowy test w `Tests/parser_tests.cpp`.

W przypadku analizatora semantycznego testy były przeprowadzane przez analizę komunikatów o błedach w pliku `Tests/semantic_hell.trisqr`.

Istnieje możliwość tworzenia testów akceptacyjnych dla interpretera, w `interpreter_tests.cpp` jest jeden przykładowy test sprawdzający kolejność i wczesne akceptowanie wyniku podczas ewaluacji wyrażeń logicznych. Wykonuje on program, którego kod źródłowy jest w `Tests/parser_condition_tests.cpp`, testowane jest, czy program przekazuje na standadowe wyjście napisy PASS oddzielone nowymi linijkami.
