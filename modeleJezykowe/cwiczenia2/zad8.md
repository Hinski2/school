# zad 8 

--- 

#### zabiegi językowe:
* rymowanie: np jak na schemacie AA BB 
* podobna długość wersów i zbliżnali liczba sylab
* zakończenie czasownikiem / rzeczownikiem 

--- 

1. z góry ustalamy:
    * liczbę wersów
    * schemat rymowania
    * przedział liczby sylab na wers np [8 - 12]

2. tworzymy listę słów które bedziemy stawiali na końcu wersów 

3. dla każdej pary np (AA lub BB) wybieramy ostatnie słowo dla pierwszego i ostatniego wersu, tak by sie rymowały  

4. załużmy ze chemy wygenerować tekst który będzie miał x tokenów i kończy się danym wyrazem
    1. generujemy wiele sensownye prefxy t0, t1.... t_{x - 1}
    2. liczymy p(w_x | w_1..w_{x - 1})
    3. wybieramy prefix który maksymalizuje p
5. wybieramy że x jest z przedziału [5 - 10], wykonujemy krok 4 dla każdego x z przedziału, sprawdzamy które odfiltrowujemy te które nei spełniaja reguły sylab, wybieramy wers z największym p
