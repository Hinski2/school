# Zad 11
 
### a) Wykorzystanie czasu poświęconego na obliczenia najlepszego poprzedniego ruchu do obliczenia najlepszego bieżącego ruchu:
 
#### Alpha-Beta-Search
Alpha-Beta-Search może wykorzystać wyniki obliczeń z poprzednich ruchów poprzez technikę znaną jako **iterative deepening**. Metoda ta polega na przeszukiwaniu drzewa gry na coraz głębszych poziomach w wielu iteracjach, zaczynając od najmniejszych głębokości. Gdy gra przesuwa się do nowego ruchu, algorytm może wykorzystać drzewo przeszukiwań z poprzedniego ruchu jako bazę, pomijając te gałęzie, które już nie są relewantne (np. te, które dotyczą stanów nieosiągalnych z obecnej pozycji). Dzięki temu kolejne przeszukiwanie jest bardziej efektywne, bo można skupić się na bardziej obiecujących gałęziach, które nie zostały jeszcze w pełni zbadane.
 
#### MCTS (Monte Carlo Tree Search)
W przypadku MCTS, wykorzystanie pracy wykonanej w poprzednich ruchach nazywane jest **pruningiem drzewa**. Po wykonaniu ruchu, całe drzewo stanów, które zostało rozwinięte podczas poprzednich obliczeń, może zostać przycięte, pozostawiając tylko te gałęzie, które odpowiadają aktualnemu stanowi gry. W praktyce oznacza to, że zachowujemy tylko poddrzewo, którego korzeniem jest stan wynikający z ostatniego ruchu. Pozostałe części drzewa są usuwane, co pozwala zaoszczędzić pamięć i czas obliczeń w następnych krokach, gdyż MCTS skupia się na rozwijaniu nowych, bardziej perspektywicznych ścieżek od aktualnego stanu gry.
 
### b) Wykorzystanie możliwości równoległego wykonywania kodu w celu poprawy jakości gry:
 
#### Alpha-Beta-Search
Algorytm Alpha-Beta-Search może być równolegle realizowany na różnych poziomach drzewa gry. Paralelizacja może zostać zastosowana do niezależnego przeszukiwania różnych gałęzi drzewa, które nie zależą od siebie (tzw. **parallel depth-first search**). Każdy wątek lub proces może przeszukiwać oddzielną część drzewa, przyspieszając znalezienie minimalnych i maksymalnych wartości w danym poddrzewie. Wyniki z poszczególnych wątków są następnie agregowane, co pozwala na szybsze osiągnięcie optymalnego rozwiązania.
 
#### MCTS
Monte Carlo Tree Search idealnie nadaje się do równoległego przetwarzania, ponieważ poszczególne symulacje (tzw. **playouts**) w drzewie gry mogą być wykonywane niezależnie od siebie. Implementacja równoległa pozwala na jednoczesne przeprowadzenie wielu symulacji, co znacząco zwiększa szybkość budowania drzewa decyzyjnego i pozwala na głębsze i dokładniejsze eksplorowanie możliwych scenariuszy gry. W praktyce może to oznaczać, że podczas gdy jeden procesor pracuje nad rozwijaniem jednej gałęzi drzewa, inne procesory mogą pracować nad innymi gałęziami, zdecydowanie zwiększając efektywność algorytmu.