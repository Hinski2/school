# zad5 

---

#### czemu do wyboru set idx używamy bitów w środku adresu 
<!-- na wykładzie 56:21  https://youtu.be/wy-AdnZECuY?si=AgOcsrdyOIPONGgj&t=3381 -->

nasz adres: (jest poczielony tak)

| tag | set idx | offset
| --- | ------- | ---

założenia:
* używamy 16 bity direct-mapped cache
* adres jako 2 bity tag 2 bity set idx 2 bity offset
* block size = 4

nasz cache:
set0 (kolor a)
set1 (kolor b)
set2 (kolor c)
set3 (kolor d)

pamięć główna jeśli używamy set idx jako środkowe bity
0000XX -> kolor a
0001XX -> kolor b
0010XX -> kolor c
0011XX -> kolor d
0100XX -> kolor a
0101XX -> kolor b
0110XX -> kolor c
0111XX -> kolor d
1000XX -> kolor a
1001XX -> kolor b
1010XX -> kolor c
...
1111XX -> kolor d

pamięć główna jeśli używamy set idx jako środkowe bity
0000XX -> kolor a
0001XX -> kolor a
0010XX -> kolor a
0011XX -> kolor a
0100XX -> kolor b
0101XX -> kolor b
0110XX -> kolor b
0111XX -> kolor b
1000XX -> kolor c
1001XX -> kolor c
1010XX -> kolor c
...
1111XX -> kolor d

dzięki temu że używamy środkowych bitów możemy wziąć 4 elementy i całkowicie wypełnić nimi cache, a przez to jak czytamy tą tablice umieszczoną sekwencyjnie w pamięci to idelanie ona nam się mieści do pamięci cache, przec co będzie mniej konfliktów

gdybyśmy używali najbardziej znaczących bitów to do pamięci cache to nie moglibyśmy korzystać z tego że czytamy sekwencyjnie tablice, było by więcej konfliktów i źle wykorzystanego miejsca w pamięci cache

---

#### Co daje odrębna pamięć podręczną pierwszego poziomu dla danychi i dla instrukcji

* dzięki temu mamy jednoczesny dostęp do obu tych danych 
* instrukcje częsko są ładowane sekwencyjnie, a dane majbą często bardziej losowy dostęp do pamięci, więc użycie 2 poamięci l1 pozwala na lepsze dopasowanie charakterystyk cache do rodzaju danych
* zmniejszenie ilości missów bo dane i instrukcje są ładowane w inne miejsca 
* gdy dane i adresy są ładowane sekwencyjnie to dane i instrukcje nie konkurują o miejsce w pamięci cache 

---

#### Które fragmenty pamięci system operacyjny musi skonfigurować w trybie dostępu write-through

Write-through to metoda zarządzania pamięcią podręczną, w której każde zapisanie danych do pamięci podręcznej jest natychmiast równolegle zapisywane do pamięci głównej. 


* pamięć dla użądzeń I/0 - aby zapewnić, że każde zapisanie danych natychmiast trafi do urządzenia
* pamięć dla kart graficznych - aby zapewnić, że każda zmiana w obrazie jest natychmiast widoczna na ekranie
* Regiony pamięci współdzielonej między procesorami (jeśli używamy ich kilka)