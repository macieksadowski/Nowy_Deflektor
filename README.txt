           Gra Nowy Deflektor - Maciej Sadowski, 2018
--------------------------------------------------------------------------------
Gra polega na kierowaniu promieniem lasera w celu zniszczenia wszystkich detonatorów znajdujących się na planszy. 
Laserem kierujemy zmieniając położenia luster znajdujących się na planszy, które odbijają laser (klikając na nie). 
Po zniszczeniu detonatorów należy nakierować laser na odbiornik, który odblokuje się tylko wtedy, 
gdy wszystkie detonatory na planszy będą zniszczone- liczbę punktów jest widoczna na wskaźniku w prawym, dolnym rogu planszy.
Laser ma ograniczony czas działania, co symbolizuje wskaźnik energii w prawym, dolnym rogu planszy.

Struktura pliku "konfiguracja.ini":	
------------------------------
LINIA 1 -tempo gry w procentach, gdzie 0 oznacza nieskończony czas na przejście poziomu, 100- najmniejszy czas
LINIA 2 I KOLEJNE -w tych linijkach znajdują się nazwy plików tekstowych z planszami, można dodać własne plansze, minimum 1 
DOMYŚLNA TREŚĆ PLIKU:

predkosc_gry=100
plansza_treningowa.txt
poziom1.txt

Struktura pliku planszy:
-----------------------------

Plik tekstowy 9 wierszy, 15 znaków każdy, reprezentujący położenie elementów na planszy.
Dozwolone znaki:
K - klocek absorbujący (ściana)
P - detonator (punkt do zniszczenia)
L - lustro
A - lustro obracające się automatycznie
E - emiter
O - odbiornik
SPACJA - puste pole!

Ilość znaków inna niż 15x9 powoduje błędy działania programu!
