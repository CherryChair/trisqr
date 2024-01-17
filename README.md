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
  - [Budowanie projektu](#budowanie-projektu)
    - [Budowanie z testami.](#budowanie-z-testami)
    - [Budowanie tylko pliku wykonywalnego interpretera](#budowanie-tylko-pliku-wykonywalnego-interpretera)
  - [Uruchamianie programu](#uruchamianie-programu)
  - [Obsługiwane typy zmiennych](#obsługiwane-typy-zmiennych)
  - [Komentarze](#komentarze)
  - [Tworzenie zmiennych](#tworzenie-zmiennych)
  - [Instrukcja warunkowa](#instrukcja-warunkowa)
  - [Pętle](#pętle)
  - [Funkcje](#funkcje)
  - [Punkty](#punkty)
  - [Tworzenie figur](#tworzenie-figur)
  - [Wartości z ustalonym typem](#wartości-z-ustalonym-typem)
  - [Metody i atrybuty figur](#metody-i-atrybuty-figur)
    - [Współdzielone](#współdzielone)
    - [Charakterystyczne](#charakterystyczne)
  - [Opis błędów](#opis-błędów)
    - [Błędy leksykalne](#błędy-leksykalne)
    - [Błędy składniowe](#błędy-składniowe)
    - [Błędy semantyczne](#błędy-semantyczne)
    - [Błędy semantyczne](#błędy-semantyczne-1)
    - [Błędy wykryte podczas wykonania](#błędy-wykryte-podczas-wykonania)
    - [Błędy interpretera](#błędy-interpretera)
  - [Operatory](#operatory)
  - [Gramatyka](#gramatyka)
  - [Testowanie](#testowanie)
  - [Znane błędy implementacji](#znane-błędy-implementacji)

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

Instrukcje na dystrybucje na podstawie Debiana (testowane na WSL2 z Ubuntu 22.04.1 LTS).
Wymagane narzędzia do budowania to cmake i make.
Figury są rysowane w okienkach gtk przez cairo.
- instalujemy gtk3 i cairomm-1.0
```bash
sudo apt install libcairomm-1.0-dev
sudo apt install libgtk-3-dev
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
pkg_check_modules(CAIROMM REQUIRED IMPORTED_TARGET cairomm-1.0)
pkg_check_modules(GTK3 REQUIRED IMPORTED_TARGET gtk+-3.0)

# 'Google_Tests_run' is the target name
# 'test1.cpp tests2.cpp' are source files with tests
add_executable(Google_Tests_run ../Tests/interpreter_tests.cpp ../Tests/parser_tests.cpp ../Tests/lexer_tests.cpp ../Lexer/lexer.cpp ../Lexer/lexer.h ../Lexer/Token.cpp ../Lexer/Token.h ../ErrorHandler/ErrorHandler.cpp ../ErrorHandler/ErrorHandler.h ../Parser/Parser.cpp ../Parser/Parser.h ../Program/Program.cpp ../Program/Program.h ../Visitors/Visitor.cpp ../Visitors/Visitor.h ../Lexer/position.h ../Lexer/lexer_error_types.h ../Visitors/VisitorTree.cpp ../Visitors/VisitorTree.h ../Visitors/VisitorInterpreter.cpp ../Visitors/VisitorInterpreter.h)
target_link_libraries(Google_Tests_run gtest gtest_main PkgConfig::CAIROMM PkgConfig::GTK3)
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
- `example_program.trsqr` - program obrazujący kolejne wartości ciągów 1/n i 1/n^2 
- `triangles.trsqr` - program rysujący coraz mniejsze trójkąty w różnych kolorach
- `parser_basic.trisqr` - zawiera testy podstawowych funkcjonalności języka
- `test.trqisqr` - zawiera testy dostępów do list i usuwania ich elementów, kończy się błędem
- `fibonacci.trisqr` - zawiera implementację rekurencyjną i z użyciem pętli for funkcji wyliczającej wartości ciągu Fibonacciego

W `Tests` znajdują się:
- `semantic_hell.trisqr` - plik zawierający dużo błędów semantycznych, testuje działanie analizatora semantycznego 
- `parser_condition_tests.trisqr` - plik testujący ewaluację wyrażeń z `||` i `&&`, jest on wykorzystywany w interpreter_tests.cpp

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
- `draw(list, p1, p2)` - otwiera okienko z narysowanymi figurami geometrycznymi zawartymi w liście, ignoruje elementy listy niebędące figurami, rysowana scena jest rozpięta w prostokącie, którego przeciwległe wierzchołki to p1 i p2, p1 lew dolny róg, p2 prawy górny.

## Punkty

Istnieje zmienna typu ```point```, punkt zawiera współrzędną ```x``` i ```y``` o wartościach double. Tworzymy ją tak ```(x, y)```. Do jego wartości moża się dostać za pomocą ```.x``` i ```.y```. Punkty można dodawać i odejmować.

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
Tak zadeklarowaną figurę tworzymy za pomocą ```vv triangle1 = Triangle((x1,y1), (x2,y2), (x3,y3), [r,g,b])```, możemy pominąć kolor w parametrach albo wszystkie parametry ```vv triangle2 = Triangle()```, wtedy jest tworzona z domyślnymi wartościami punktów z deklaracji. Potem możemy dostawać się do punktów za pomocą nazw nadanych w deklaracji. Np. ```triangle1.a```. 

Figury będą rysowane przez tworzenie linii między kolejno zadeklarowanymi punktami, np. w przykładowym ```Triangle```, rysujemy linie a->b, b->c, c->b.

Dodatkowo wprowadzona jest figura ```Circle```. Nowe koło jest tworzone przez: ```Circle(<middle_point>, <radius>)``` lub ```Circle()```, które tworzy koło jednostkowe o środku w punkcie ```(0,0)```. Można też podać kolor.

## Wartości z ustalonym typem

Istnieje 5 rodzajów wartości, które powodują wystąpienie wyjątku przy próbie zapisu do nich innej wartości nieodpowiedniego typu.
- punkt - przechowuje tylko wartości double
- punkt figury - przy próbie zapisu innej wartości niż punkt mamy wyjątek
- promień - szczególny parametr Circle(), tylko wartość double
- kolor figury - lista 3 int od 0 do 255
- parametr koloru figury - int od 0 do 255

## Metody i atrybuty figur

### Współdzielone

Metody:
- .<nazwa_punktu_z_deklaracji> - punkt 
- .circ() - zwraca obwód
- .area() - zwraca pole liczone metodą trapezów, dla figur samoprzecinających się wyniki będą niepoprawne
- .scale(double scale) - skaluje figurę w stosunku do początku układu współrzędnych o skalę scale
- .rotate((double x1, double y1), double angle) - obraca figurę wokół początku układu współrzędnych o kąt angle podawany w radianach, ##nie zachachowuje kształtu figury
- .transport(double x, double y) - przesuwa figurę o wektor (x, y)
- .copy() - zwraca kopię danej figury

Parametry:
- color - [int r, int g, int b] kolor linii figury w RGB, domyślnie ustawiane na [0,0,0]

### Charakterystyczne

- koło:
  - .r - parametr oznaczający promień
  - .c - parametr oznaczający środek 

## Opis błędów

### Błędy leksykalne
Analiza leksykalna sprawdza, czy udało się poprawnie stworzyć token, w przypadku wystąpienia zbyt długiego napisu, komentarza lub liczby tworzy token z maksymalną dozwoloną liczbą analizowanych znaków, ostrzega o tworzeniu zbyt dużych liczb całkowitych lub zmiennoprzecinkowych.

### Błędy składniowe

Po wykryciu błędu parser rzuca wyjątek.

### Błędy semantyczne

Sprawdzane są ponowne deklaracje identyfikatorów, braki deklaracji identyfikatorów i ustawianie nazwy identyfikatorów na nazwy funkcji i metod wewnętrznych. Analizator semantyczny rzuca wyjątek po przeanalizowaniu całego programu i wypisaniu wykrytych błędów.

### Błędy semantyczne

Sprawdzane są ponowne deklaracje identyfikatorów, braki deklaracji identyfikatorów i ustawianie nazwy identyfikatorów na nazwy funkcji i metod wewnętrznych. Analizator semantyczny rzuca wyjątek po przeanalizowaniu całego programu i wypisaniu wykrytych błędów.

### Błędy wykryte podczas wykonania

Błędy wykonania są zgłaszane, jeśli się odwołamy do nieistniejących elementów listy, porównamy, dodamy lub pomnożymy nieprawidłowe wartości. Pojawiają się też jeśli przypiszemy wartości niedozwolone odpowiednim zmiennym oraz w przypadku, gdy użyjemy nieodpowiednich argumentów we wbudowanych metodach i funkcjach. 


### Błędy interpretera

W przypadku braku wartości wyrażenia pomimo oczekiwania jej przez interpreter, jest sygnalizowany błąd interpretera, oznacza on bład w implementacji.

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

## Znane błędy implementacji

- w przypadku wystąpienia nierozpoznanego zanku, parser wykrywa koniec funkcji i kończy analize ogłaszając błąd składniowy
- w przypadku tworzenia figury i natychmiastowego jej skalowania figura z przypisaną wartością `vv a = Trianlge().scale(2.0)` pojawia się błąd złego dostępu do wariantu, wartości przechowywane w punktach są niezaincjalizowane