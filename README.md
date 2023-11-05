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
- możliwość wykonania kodu z pliku lub interaktywnego wpisywania kodu w terminalu
- komunikaty o błędach wyświetlają numer linii i znaku miejsca wystąpienia błędu

## Wymagania niefunkcjonalne
- leniwe odczytywanie strumienia danych
- testowanie błędów
- testowanie poprawności realizowania przykładów kodu

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
- pusta wartośc none
  
Lista przyjmuje dowolne typy. Dwie listy można łączyć za pomocą "+", ta operacja zwraca nową listę będącą złączeniem 2 list. Poszeczególne elementy indeksowane sa od 0 i dostajemy się do nich za pomocą nawiasów kwadratowcyh ```list[i]```.
Metody listy:
- ```.append(el)``` - dodaje element na koniec listy
- ```.delete(index)``` - usuwa element o indeksie ```index```
- ```.len()``` - zwraca ilość elementów listy

Zmienne typu str można konkatenować za pomocą "+".

Przez silne typowanie wymagane jest wprowadzenie możliwości konwersji typów. Będziemy to robić za pomocą operatora ```to```, przy zmianie zmiennej *variable* na typ *type*: ```*variable* to *type*```.

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
Zmienne będą przechowywane przez referencje. Listy i figury będą mutowalne. Pozostałe zmienne nie będą.
Nie będzie zmiennych globalnych.
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
Będzie możliwośc rekursji. Można zwracać pustą wartość za pomocą "return;". Nie trzeba podawać return na końcu funkcji, wtedy automatycznie zwraca pustą wartość. Argumenty funkcji są przechowywane poprzez referencje dla zmiennych figurowych i list, pozostałe przekazywane są poprzez wartość.

Poza tym będą wbudowane funkcje:
- print(str) - wypisuje w konsoli tekst zawarty w str
- draw(list, p1, p2) - otwiera okienko z narysowanymi figurami geometrycznymi zawartymi w liście, ignoruje elementy listy niebędące figurami, rysowana scena jest rozpięta w prostokącie, którego przeciwległe wierzchołki to p1 i p2. Można pominąć p1 i p2 przy wywoływaniu metody wtedy zostanie narysowana scena, która będzie zawierać wszystkie podane figury (poprzez analizę najmniejszych i największych wartości x i y punktów należacych do sceny)

## Punkty

Istnieje zmienna typu ```point```, punkt zawiera współrzędną ```x``` i ```y``` o wartościach double. Tworzymy go tak ```(x, y)```. Do jego wartości moża się dostać za pomocą ```.x``` i ```.y```. Można zmienić ich wartości.

## Tworzenie figur

Typy figur będą tworzone za pomocą deklaracji 
```figure <Identifier> {<point_name>:<default_point_value>, <point_name>:<default_point_value>, ...}```

Np.
```
figure Triangle{
  a: (0.0,0.0),
  b: (0.0,1.0),
  c: (1.0,0.0),
}
```

Tak zadeklarowaną figurę tworzymy za pomocą ```vv triangle1 = Triangle((x1,y1), (x2,y2), (x3,y3))``` lub za pomocą ```vv triangle2 = Triangle()```, wtedy jest tworzona z domylnymi wartościami punktów podanymi w deklaracji. Potem możemy dostawać się do punktów za pomocą nazw nadanych w deklaracji. Np. ```triangle1.a```. 

Figury będą rysowane przez tworzenie linii między kolejno zadeklarowanymi punktami, np. w przykładowym ```Triangle```, rysujemy linie a->b, b->c, c->b.

Dodatkowo wprowadzona jest figura ```Circle```. Nowe koło jest tworzone przez: ```Circle(<middle_point>, <radius>)``` lub ```Circle()```, które tworzy koło jednostkowe o środku w punkcie ```(0,0)```.

## Metody i atrybuty figur

### Współdzielone

Metody:
- .<nazwa_punktu_z_deklaracji> - punkt 
- .circ() - zwraca obwód
- .area() - zwraca pole, w przypadku figur, których boki się przecinają zwracane jest ```-1```.
- .scale(double scale) - skaluje figurę w stosunku do początku układu współrzędnych o skalę scale
- .rotate(double angle) - obraca figurę wokół początku układu współrzędnych o kąt angle podawany w radianach
- .transport(double x, double y) - przesuwa figurę o wektor (x, y)
- .vertex() - zwraca listę wierzchołków (oprócz koła)
- .copy() - zwraca kopię danej figury

Parametry:
- color - (int r, int g, int b) kolor wypełnienia figury w RGB, jeśli ma wartość ```none```, oznacza, że figura nie ma koloru wypełnienia
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
  newTriangle.border = 0;
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
  newTriangle.border = 0;
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
| to  |  5 |
| +,-  |  6 |
| *,/  |  7 |
| !,-  |  8 |
| .  |  9 |
| [ ]  |  10 |
| ( )  |  11 |

## Gramatyka
```
- program             :== {func_declaration | figure_declaration};
- func_declaration    :== "func ", identifier, decl_argument_list, code_block;
- decl_argument_list  :== "(", [identifier, {", ", identifier}], ")";
- figure_declaration  :== "figure ", identifier, point_list;
- point_list          :== "{", point_declaration, {",", point_declaration}, "}";
- point_declaration   :== identifier, ":", point_value;
- point_value         :== "(", double_val, ",", "double_val, ")";
- code_block          :== "{", {statement}, "}";
- statement           :== while_stmnt
                        | fori_stmnt
                        | for_stmnt
                        | if_stmnt
                        | declaration
                        | identifier_stmnt, ["=", bool_expression], ";"
                        | return;
- while_stmnt         :== "while(",  bool_expression, ")", code_block;
- if_stmnt            :== "if(",  bool_expression, ")", code_block, {"elif(",  bool_expression, ")", code_block }, ["else", code_block];
- fori_stmnt          :== "fori ", identifier, " in (", (identifier | int_val), (identifier | int_val), ")", code_block;
- for_stmnt           :== "for ", identifier, " in ", identifier, code_block;
- bool_expression     :== bool_and, {"||",  bool_and};
- bool_and            :== bool_comp , {"&&",  bool_comp};
- bool_comp           :== expression_is, [comp_operator, expression_is];
- expression_is       :== expression_to, [" is ",  type];
- expression_to       :== expression, [" to ",  type];
- declaration         :== "vv ", identifier, ["=", bool_expression], ";";
- identifier_stmnt    :== part_list, {".", part_list};
- part_list           :== part, "[", bool_expression, "]";
- part                :== identifier, [argument_list];
- argument_list       :== "(", [bool_expression, {", ", bool_expression}], ")";
- expression          :== expression_mul, {add_operator, expression_mul};
- expression_mul      :== part_mul, {mul_operator, part_mul};
- part_mul            :== [negation_operator], part_neg;
- part_neg            :== value
                        | list
                        | figure
                        | point
                        | identifier_stmnt
                        | "(", bool_expression, ")";
- return              :== "return ", [bool_expression], ";"
- list                :== "[", bool_expression, {", ", bool_expression} "]";
- figure              :== identifier, argument_list;  
- point               :== "(", bool_expression, ",", bool_expression, ")";  
- value               :== int_val
                        | bool_val
                        | double_val
                        | string_val
                        | "none";
- identifier          :== [a-zA-Z][0-9a-zA-Z_]*
- type                :== "none" 
                        | "int" 
                        | "bool" 
                        | "str" 
                        | "double" 
                        | "figure" 
                        | "point" 
                        | identifer;
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
## Testowanie

Testy jednostkowe zrealizowane będą w GTEST.

Analizator leksykalny będzie testowany poprzez sprawdzanie, czy dane tekstowe wyprodukują spodziewaną sekwencję tokenów.

W przypadku testowania analizatora składniowego będziemy sprawdzać, czy z przekazanych przez analizator leksykalny tokenów powstają odpowiednie drzewa składniowe, oczywiście testować też będziemy błędy.

Konieczne też będzie przetestowanie wykrywania błędów semantycznych i poprawne wykonywanie kodu, jak np. obroty i skalowanie figur.