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
  - [Operatory](#operatory)
  - [Priorytety operatorów](#priorytety-operatorów)
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
    - [Przykład nr 3](#przykład-nr-3)
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
- kolekcja
- figury: 
  - trójkąt 
  - prostokąt
  - kwadrat
  - romb
  - trapez
  - koło
  - linia
- pusta wartośc none
  
Kolekcja przyjmuje dowolne typy. 

Przez silne typowanie wymagane jest wprowadzenie możliwości konwersji typów. Będziemy to robić za pomocą operatora "to", przy zmianie zmiennej *variable* na typ *type*: ```*variable* to *type*```.

Możliwe konwersje typów:
- ```int to double```
- ```int to str```
- ```str to double```
- ```str to int```
- ```double to int```

Wprowadzimy też wygodne sprawdzanie typów zmiennych: ``` *variable* is *type*```. Będzie można też sprawdzić, czy zmienna ma pustą wartość typu ```none```.

Jako, że w zastosowaniach języka mamy do czynienia z operacjami na figurach geometrycznych wprowadzimy stałą ```pi``` typu double. 

## Operatory

## Priorytety operatorów

## Komentarze

Komentarz od "#" do końca linii.

## Tworzenie zmiennych

Deklaracja zmiennej:
```
vv nazwa_zmiennej
```
Zmienne będą mutowalne.
TODO dalej przeanalizuj mutowalność
TODO zakresy widoczność
## Instrukcja warunkowa

Instrukcją warunkową będzie:
```
if (wyrażenie bool) { 
  *kod*
} elif {
  *kod*
} else{
  *kod*
}
```

## Pętle
Będzie pętla while:
```
while (wyrażenie bool){
    *kod*
}
```
Będą 2 pętle for:
```
for el in list{
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
fun NazwaFunkcji(a, b, c){
    *kod*
}
```
Będzie możliwośc rekursji. Można zwracać pustą wartość za pomocą "return;". Nie trzeba podawać return na końcu funkcji, wtedy automatycznie zwraca pustą wartość.

Poza tym będą wbudowane funkcje:
- print(str)
- draw(list) - otwiera okienko z narysowanymi figurami geometrycznymi
- draw(list)

## Błędy

Np. dla kodu w rodzaju:

```
func main(){
  vv a = 0;
  vv b = 0;
  vv c = a is b;
} 
```
Pojawi się błąd:
```
vv c = a is b;
4,15: "b" is not type
```

## Tworzenie figur

Wszystkie podane niżej wartości argumentów będą podawane jako double

- ```Triangle(x_1, y_1, x_2, y_2)``` - stwórz trójkąt o wierzchołku w środku układu współrzędnych i w punktach (x_1, y_1) i (x_2, y_2);
- ```Square(x)``` - stwórz kwadrat o długości boków x i środku masy w środku układu współrzędnych
Poniżej dla rombu i prostokątu przez linie określną x rozumiemy linię równoległą do osi OX, a przez y równoległą do osi OY:
- ```Rectangle(x, y)``` - stwórz prostokąt o długości boków x, y i środku masy w środku układu współrzędnych
- ```Rhombus(x, y)``` - stwórz romb o długości przekątnych x, y i środku masy w środku układu współrzędnych
- ```Trapezoid(a, b, h, x)``` - stwórz trapez równoramienny z podstawami a i b, b jest dolną podstawą i jej środek jest w środku układu współrzędnych, dodatkowo górna podstawa jest przesunięta o x w lewo lub w prawo w zależności od znaku 
- ```Circle(r)``` - tworzy koło o promieniu r i środku w śtodku układu współrzędnych

## Metody i atrybuty figur

### Współdzielone

Metody:
- .circ() - zwraca obwód
- .area() - zwraca pole
- .scale(double scale) - skaluje figurę w stosunku do początku układu współrzędnych o skalę scale
- .rotate(double angle) - obraca figurę wokół początku układu współrzędnych o kąt angle podawany w radianach
- .transport(double x, double y) - przesuwa figurę o wektor (x, y)
- .vertex() - zwraca listę wierzchołków (oprócz koła)

Parametry:
- color - (int r, int g, int b) kolor wypełnienia figury w RGB, jeśli ma wartość ```none```, oznacza, że figura nie ma koloru wypełnienia
- border - (double) grubość obwódki

### Charakterystyczne

- koło:
  - .r - parametr oznaczający promień
  - .cent - środek 

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

### Przykład nr 3


## Gramatyka

- program   :== {func_declaration}, main_declaration;
- main_declaration  :== "func main(){", code_block, "}";
- func_declaration  :== "func ", identifier, "(", [identifier, {", ", identifier}], "){", code_block, "}";
- code_block  :== {statement};
- statement :== while_stmnt
            | fori_stmnt
            | for_stmnt
            | if_stmnt
            | declaration
            | identifier_stmnt, ["=", expression], ";"
            | return;
- while_stmnt :== "while(",  bool_expression, "){", code_block, "}";
- if_stmnt  :== "if(",  bool_expression, "){", code_block, "}, {"elif(",  bool_expression, "){", code_block, "}"}, ["else {", code_block, "}"];
- fori_stmnt  :== "fori ", identifier, " in (", (identifier | int_val), (identifier | int_val), "){", code_block "}";
- for_stmnt :== "for ", identifier, " in ", identifier, "{", code_block "}";
- bool_expression :== bool_and, {"||",  bool_and};
- bool_and  :== bool_comp, {"&&",  bool_comp};
- bool_comp :== expression, [comp_operator, expression];
- declaration :== "vv ", identifier, ["=", expression], ";";
- identifier_stmnt  :== part, {".", part};
- part  :== identifier, ["(", expression, {", ", expression}, ")"];
- expression  :== expression_mul, {add_operator, expression_mul};
- expression_mul  :== part_mul, {mul_operator, part_mul};
- part_mul  :== value
            | list
            | identifier_stmnt
            | figure_declaration
            | "(", expression, ")";
- return    :== "return ", identifier, ";"
              | "return ", variable_val, ";"
- list      :== "[", (identifier_stmnt | expression), {", ", (identifier_stmnt | expression)} "]";
- value :== int_val
          | bool_val
          | double_val
          | string_val
          | "none";
- figure_declaration  :== "Triangle(",  expression, (", ", expression)*3, ")"
                        | "Square(", expression, ")"
                        | "Circle(", expression, ", ", expression, ")"
                        | "Rectangle(", expression, ", ", expression,")"
                        | "Rhombus(", expression, ", ", expression, ")"
                        | "Trapezoid(",  expression, (", ", expression)*3, ")";
- identifier :== (?!main)[a-zA-Z][0-9a-zA-Z_]*
- comp_operator :== "<"
                  | "=="
                  | ">"
                  | ">="
                  | "<="
                  | "==";
- mul_operator :== "*"
                  | "/";
- add_operator :== "+"
                  | "-";

## Sposób testowania

Oprócz podanych wyżej przykładów zastosowania języka, będziemy testować konwersje typów, sprawdzanie typów, błędy leksykalne i gramatyczne.