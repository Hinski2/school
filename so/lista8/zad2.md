# zad2

## różnica między fragmentacją wew. i zewn.
- Fragmentacja wewnętrzna: Występuje, gdy alokator przydziela procesowi blok pamięci większy niż ten, o który proces prosił. Różnica między rozmiarem przydzielonym a rzeczywiście używanym marnuje się wewnątrz zaalokowanego bloku. Wynika to często z wyrównywania rozmiarów bloków (np. do potęgi dwójki) lub minimalnego rozmiaru jednostki alokacji.
- Fragmentacja zewnętrzna: Występuje, gdy całkowita ilość wolnej pamięci w systemie jest wystarczająca do spełnienia żądania alokacji, ale pamięć ta nie jest ciągła (jest podzielona na wiele małych "dziur" między zajętymi blokami). W rezultacie alokator nie może znaleźć jednego spójnego fragmentu o wymaganym rozmiarze.

## dlaczego malloc nie może stosować kompaktowania?
- Kompaktowanie (czyli przesuwanie zajętych bloków pamięci tak, aby wszystkie wolne fragmenty utworzyły jeden duży obszar) jest niemożliwe w standardowych implementacjach malloc w językach takich jak C czy C++, ponieważ:
  - Bezpośrednie wskaźniki: Programy w C/C++ operują na bezpośrednich adresach pamięci (wskaźnikach). Biblioteka malloc zwraca wskaźnik do konkretnego adresu w pamięci wirtualnej.
  - Brak wiedzy o wskaźnikach: Alokator pamięci nie wie, w ilu miejscach programu i w jakich strukturach danych użytkownik przechowywał kopię tego wskaźnika.
  - Unieważnienie danych: Gdyby alokator przesunął dane w inne miejsce (skompaktował pamięć), wszystkie wskaźniki posiadane przez program nadal wskazywałyby na stary adres (teraz zawierający inne dane lub będący częścią innego bloku), co doprowadziłoby do błędów.

## dwie główne przyczyny występowania fragmentacji zew.
- Izolowane zwolnienia (Isolated Deaths)
  - Definicja: Fragmentacja powstaje, gdy tworzone są wolne obszary, których sąsiedzi są nadal zajęci.
  - Wyjaśnienie: Jest to funkcja tego, które obiekty zostały umieszczone obok siebie i kiedy "umierają" (są zwalniane). Jeśli obiekty sąsiadujące w pamięci nie są zwalniane w tym samym czasie, powstają luki (dziury), których nie da się scalić w większy blok. Gdyby alokator umieścił obok siebie obiekty, które giną w tym samym czasie, po ich zwolnieniu powstałby jeden duży, ciągły obszar wolnej pamięci.
- Zmienność zachowania w czasie (Time-varying behavior)
  - Definicja: Fragmentacja wynika ze zmian w sposobie, w jaki program korzysta z pamięci w trakcie swojego działania.
  - Wyjaśnienie: Typowym przykładem jest sytuacja, w której program zwalnia małe bloki pamięci, a następnie żąda przydziału dużych bloków. Dotyczy to również fazowości działania programu – różne fazy mogą wymagać innej liczby obiektów o drastycznie różnych rozmiarach (np. "bursty patterns" – wzorce impulsowe). Jeśli alokator nie potrafi wykorzystać tych wzorców, dziury po małych obiektach będą bezużyteczne dla nowych, dużych żądań.
