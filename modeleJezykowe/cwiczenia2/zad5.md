# zad 5

--- 

zasada kerchkhoffsa:


    system  szyfrowania musi być bezpieczny nawet wtedy, gdy przecienik zna cały algorytm. a jedyną tajemniacą jest plucz

czli sam algorytm może być znany i opisany w papierze/ artykule np RSA

to czego przeciwnik nie wie to hasło / kombinacja. odpowwiednio losowy, tak by atakujacy nei potrawił odszyfrować wiadomości, nawet znając algorytm 

co to daje:
* bezpieczeństwo przez ukrywanie algorytmu jest złudne, bo prędzej, czy puźniek któraś z osób znająca algorytm może się wygadać na jego temat, lub ktoś zreverse-engineruej kod algorytmui 

* algodytmy takie jak RSA są otwarte, każdy może zobaczyć na jakiej zasadzie działają. ich bezpieczeństwo opiera się o matematyke a nie o sekret 

---

zał: za klucz uznajemy model językowy, czyli wszystko oprócz samego modelu może być znane naczelnikowi 


#### pomysł 1 

jeśli algorytm bedzie znany, to ten pomsył nieSpełnia zasady kerckhoffsa

#### pomysł 2 

Spełnia, bo naczelnik nie może użyć brute force i przejżeć wszystkich dostępnych modeli, a jeśli nawet może to mozemy sami wytrenować model 

#### pomysł 3 

emmmm, zał z zadania tutaj nie pasuje, bo w tym pomyśle kluczem jest randomowa funkcja + seed

wiec ogólnei tak jeśli naczelnik nie zna seed'a

#### pomysł 4 

i to jeszcze jak!!!! 
