# Projekt TKOM

## Informacje wstępne
Autor: **Michał Kowalczyk**

Nazwa języka: **TriSqr**

## Spis treści
- [Projekt TKOM](#projekt-tkom)
  - [Informacje wstępne](#informacje-wstępne)
  - [Spis treści](#spis-treści)
  - [Treść zadania](#treść-zadania)
  - [Obsługiwane typy zmiennych](#obsługiwane-typy-zmiennych)
  - [Komentarze](#komentarze)
  - [Tworzenie zmiennych](#tworzenie-zmiennych)
  - [Instrukcja warunkowa](#instrukcja-warunkowa)
  - [Pętle](#pętle)
  - [Funkcje](#funkcje)
  - [Błędy](#błędy)
  - [Tworzenie figur](#tworzenie-figur)
  - [Metody i atrybuty figur](#metody-i-atrybuty-figur)
    - [Współdzielone](#współdzielone)
    - [Charakterystyczne](#charakterystyczne)
  - [Złożone przykłady wykorzystania języka](#złożone-przykłady-wykorzystania-języka)
    - [Przykład nr 1](#przykład-nr-1)
    - [Przykład nr 2](#przykład-nr-2)
  - [Gramatyka](#gramatyka)
  - [Sposób testowania](#sposób-testowania)

## Treść zadania

Język do opisu figur geometrycznych i ich właściwości. Podstawowe typy figur geometrycznych (trójkąt, prostokąt, romb, trapez, koło itd.) są wbudowanymi typami języka. Każdy typ posiada wbudowane metody służące do wyznaczania charakterystycznych dla niego wielkości, np. obwód, pole powierzchni, wysokość, średnica itp. Kolekcja figur tworzy scenę wyświetlaną na ekranie.

## Obsługiwane typy zmiennych

Wariant typowania: dynamiczne, silne.

Typy:
- liczbowe:
  - całkowita
  - zmiennoprzecinkowa
- boolowska
- napis
- lista
- figury: 
  - trójkąt 
  - prostokąt
  - kwadrat
  - romb
  - trapez
  - koło
  - linia
- pusta wartośc none
  
Lista przyjmuje dowolne typy. Ma metodę .append, która dodaje pojedynczy element na koniec listy, dwie listy można łączyć za pomocą "+", zwraca kopię złączonej listy.

Zmienne typi str można konkatenować za pomocą "+".

Przez silne typowanie wymagane jest wprowadzenie możliwości konwersji typów. Będziemy to robić za pomocą operatora "to", przy zmianie zmiennej *variable* na typ *type*: ```*variable* to *type*```.

Możliwe konwersje typów:
- ```int to double```
- ```int to str```
- ```str to double```
- ```str to int```
- ```double to int```
- ```double to str```

Wprowadzimy też wygodne sprawdzanie typów zmiennych: ``` *variable* is *type*```. Będzie można też sprawdzić, czy zmienna ma pustą wartość typu ```none```.


Jako, że w zastosowaniach języka mamy do czynienia z operacjami na figurach geometrycznych wprowadzimy stałą ```pi``` typu double. 

## Komentarze

Komentarz od "#" do końca linii.

## Tworzenie zmiennych

Deklaracja zmiennej:
```
vv nazwa_zmiennej
```
Zmienne będą mutowalne.
Nie będzie zmiennych globalnych, zmienne do funkcji będą przekazywane przez referencje.
## Instrukcja warunkowa

Instrukcją warunkową będzie:
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
Będzie pętla while:
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
fori i in (s,k){
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
Będzie możliwośc rekursji. Można zwracać pustą wartość za pomocą "return;". Nie trzeba podawać return na końcu funkcji, wtedy automatycznie zwraca pustą wartość.

Poza tym będą wbudowane funkcje:
- print(str) - wypisuje w konsoli tekst zawarty w str
- draw(list) - otwiera okienko z narysowanymi figurami geometrycznymi zawartymi w liście, ignoruje elementy listy niebędące figurami

## Błędy

Ta sekcja na razie zawiera tylko przykłady błędów leksykalnych, wraz z rozwojem języka dojdą kolejne przykłady.

Dla kodu w rodzaju:
```
1.2 to str + '3 to int; \n\r\n \r vv a;  \r\n
```
Pojawi się błąd:
```
ERR: String is not closed.
Line 1, character 14: '3 to int; \n\r\n \r vv a;  \r\n << error
```
Dla kodu w rodzaju:
```
1.2'3 to int; \n\r\n \r vv a;  \r\n
```
Pojawi się błąd:
```
ERR: String is not closed.
Line 1, character 4: '3 to int; \n\r\n \r vv a;  \r\n << error
```
Dla kodu w rodzaju:
```
2.2147483648 2147483648.2147483648
```
Pojawi się błąd:
```
ERR: Number after . is too big.
Line 1, character 1: 2.2147483648 << error
ERR: Number is too big.
Line 1, character 14: 2147483648 << error
ERR: Number is too big.
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
ERR: Unrecognized symbol.
Line 1, character 22: &  << error
```
## Tworzenie figur

Będą obsługiwane figury typu:
```Triangle, Square, Rectangle, Rhombus, Trapezoid, Circle```.

Dla wszystkich poza ```Circle``` tworzenie nowych figur będzie polegało na podawaniu punktów z wierzchołkami w listach typu:
```[x_1, y_1, x_2, y_2, x_3, y_3]```. dla koła deklaracja bedzie wyglądała tak: ```Circle(x_1, y_1, r)```, gdzie ```x_1, y_1``` jest jego środkiem, a ```r``` jest jego promieniem.



## Metody i atrybuty figur

### Współdzielone

Metody:
- .circ() - zwraca obwód
- .area() - zwraca pole
- .scale(double scale) - skaluje figurę w stosunku do początku układu współrzędnych o skalę scale
- .rotate(double angle) - obraca figurę wokół początku układu współrzędnych o kąt angle podawany w radianach
- .transport(double x, double y) - przesuwa figurę o wektor (x, y)
- .vertex() - zwraca listę wierzchołków (oprócz koła)
- .copy() - zwraca kopię danej figury

Parametry:
- color - (int r, int g, int b) kolor wypełnienia figury w RGB, jeśli ma wartość ```none```, oznacza, że figura nie ma koloru wypełnienia
- border - (double) grubość obwódki

### Charakterystyczne

- koło:
  - .r - parametr oznaczający promień
  - .cent - parametr oznaczający środek 

## Złożone przykłady wykorzystania języka

### Przykład nr 1
Coś à la trójkąt Sierpińskiego:

```
func sierpinsky(x_off, y_off, x, y, n, startingTriangle, list){
  if (n <= 0) {
    return;
  }
  vv n_n = n-1;
  vv newTriangle = Triangle(0.0, y, x, 0.0);
  newTriangle.rotate(pi);
  newTriangle.color = [255, 255, 255];
  newTriangle.border = 0;
  newTriangle.transport(x_off + x, y_off + y);
  list.append(newTriangle);
  sierpinsky(x/2.0 + x_off, y_off, x/2.0, y/2.0, n_n, list);
  sierpinsky(x_off, y/2.0 + y_off, x/2.0, y/2.0, n_n, list);
  sierpinsky(x_off, y_off, x/2.0, y/2.0, n_n, list);
}

func main() {
  vv sierpinskyList = [];
  vv newTriangle = Triangle(0.0, 16.0, 16.0, 0.0);
  newTriangle.rotate(pi)
  newTriangle.color = [0, 0, 0];
  newTriangle.border = 0;
  sierpinsky(0.0, 0.0, 16.0, 16.0, 6, sierpinskyList)
  draw(sierpinskyList);
}

```

### Przykład nr 2
Tworzymy coraz minejsze kwadraty obrazujące kolejne elementy ciągów 1/n^2 i 1/2^(2*n):
```
func power(base, n) {
  if(n>0){
    return base*power(base, n-1);
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
  fori i in (0, n){
    vv scale1 = power(0.5, i);
    vv scale2 = 1.0/(i to double);
    vv sqr1 = Square(scale1);
    vv sqr2 = Square(scale2);
    sqr1.transport(sum_of_scale1 + scale1/2.0, scale1/2.0);
    sqr2.transport(-sum_of_scale2 + -scale2/2.0, scale2/2.0);
    sum_of_scale1 = sum_of_scale1 + scale1;
    sum_of_scale2 = sum_of_scale2 + scale2;
    list1.append(sqr1);
    list2.append(sqr2);
  }
  vv sum1 = sumAreas(list1);
  vv sum2 = sumAreas(list2);
  print("Suma 1: " + sum1 to str);
  print("Suma 2: " + sum2 to str);
  list_to_draw = list1 + list2;
  draw(list_to_draw);
}
```

## Gramatyka
```
- program             :== {func_declaration};
- func_declaration    :== "func ", identifier, "(", [identifier, {", ", identifier}], "){", code_block, "}";
- code_block          :== {statement};
- statement           :== while_stmnt
                        | fori_stmnt
                        | for_stmnt
                        | if_stmnt
                        | declaration
                        | identifier_stmnt, ["=", expression], ";"
                        | return;
- while_stmnt         :== "while(",  bool_expression, "){", code_block, "}";
- if_stmnt            :== "if(",  bool_expression, "){", code_block, "}", {"elif(",  bool_expression, "){", code_block, "}"}, ["else {", code_block, "}"];
- fori_stmnt          :== "fori ", identifier, " in (", (identifier | int_val), (identifier | int_val), "){", code_block "}";
- for_stmnt           :== "for ", identifier, " in ", identifier, "{", code_block "}";
- bool_expression     :== bool_and, {"||",  bool_and};
- bool_and            :== expression_is , {"&&",  expression_is};
- expression_is       :== expression_to, [" is ",  type];
- expression_to       :== bool_comp, [" to ",  type];
- bool_comp           :== expression, [comp_operator, expression];
- declaration         :== "vv ", identifier, ["=", bool_expression], ";";
- identifier_stmnt    :== part, {".", part};
- part                :== identifier, ["(", bool_expression, {", ", bool_expression}, ")"];
- expression          :== expression_mul, {add_operator, expression_mul};
- expression_mul      :== part_mul, {mul_operator, part_mul};
- part_mul            :== [negation_operator], part_neg;
- part_neg            :== value
                        | list
                        | identifier_stmnt
                        | "(", bool_expression, ")";
- return              :== "return ", identifier, ";"
                        | "return ", variable_val, ";"
- list                :== "[", (identifier_stmnt | expression), {", ", (identifier_stmnt | expression)} "]";  
- value               :== int_val
                        | bool_val
                        | double_val
                        | string_val
                        | "none";
- identifier          :== [a-zA-Z][0-9a-zA-Z_]*
- type                :== "none" | "int" | "bool" | "str" | "double" | "Figure";
- comp_operator       :== "<"
                        | "=="
                        | ">"
                        | ">="
                        | "<="
                        | "!=";
- mul_operator        :== "*"
                        | "/";
- add_operator        :== "+"
                        | "-";
- bool_val            :== "true"
                        | "false"
- negation_operator   :== "!"
                        | "-";
- double_val          :== int_val, ".", digit, {digit};
- string_val          :== '"', {char | digit | special_char}, '"';
- char                :== [a-zA-Z];
- special_char        :== "\n" | "\\" | '\"' | "\r" |pozostałe normalnie;
- int_val             :== digit_without_zero, {digit}
                        | "0";
- digit               :==  digit_without_zero | "0";
- digit_without_zero  :== [1-9]
```
## Sposób testowania

Testy są zrealizowane za pomocą GTEST, do tej pory zaimplementowane zostały testy do leksera.
