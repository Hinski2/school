# zad1

## jakie są wady stosowania sbrk do zarządzania rozmiarem sterty przez malloc(3)?
- Głównym problemem z sbrk jest to, że zarządza ono pamięcią w sposób ciągły (liniowy). Wywołanie to przesuwa wskaźnik końca sterty (tzw. program break).
- Główna wada: Fragmentacja i niemożność oddania pamięci "ze środka"
  - Program alokuje pamięć dla obiektu A (na początku życia procesu).
  - Następnie alokuje pamięć dla obiektu B.
  - Sterta wygląda tak: [Początek] [ A ] [ B ] [Koniec/Break]
  - Teraz program zwalnia obiekt A (free(A)).
- Co się dzieje? Mimo że pamięć po A jest wolna, system operacyjny (jądro) widzi, że koniec sterty jest nadal za obiektem B. sbrk może jedynie przesuwać "suwak" w górę lub w dół. Dopóki obiekt B (który został zaalokowany później) istnieje, nie można obniżyć wskaźnika sterty poniżej B, aby oddać pamięć po A do systemu.
- Skutki:
  - Zwiększone zużycie pamięci: Proces "trzyma" pamięć, której już nie potrzebuje, ponieważ jest ona zablokowana przez nowsze alokacje znajdujące się wyżej na stercie.
  - Pamięć po A może być użyta ponownie tylko przez ten sam proces (jeśli malloc znajdzie tam miejsce na nowy obiekt), ale nie jest dostępna dla innych procesów w systemie.

## jak można to poprawić mmap i munmap?
- Niezależność: mmap pozwala zaalokować segment pamięci w dowolnym dostępnym miejscu przestrzeni adresowej, niezależnie od głównej sterty.
  - Mechanizm: Gdy malloc używa mmap (zazwyczaj dla dużych bloków pamięci), tworzy oddzielną "wyspę" pamięci.
  - Zwalnianie: Gdy wywołasz free na takim obszarze, biblioteka może natychmiast wywołać munmap. To wywołanie systemowe "wycina" dany fragment z przestrzeni adresowej i natychmiast zwraca go do jądra systemu.
- Zaleta: Zwolnienie pamięci zaalokowanej na początku działania programu (obiekt A) od razu zmniejsza zużycie pamięci procesu (RSS), niezależnie od tego, czy później zaalokowano inne obiekty (B, C, D).

## kiedy free może zwrócić pamięć do jądra?
- Dla pamięci przydzielonej przez sbrk (tradycyjna sterta): Procedura free może zwrócić pamięć do jądra (poprzez wywołanie sbrk z ujemną wartością) tylko wtedy, gdy zwalniany blok znajduje się na samym szczycie sterty.
  - Jeśli zwolnisz coś w środku sterty -> pamięć jest oznaczana jako "wolna" wewnątrz biblioteki malloc, ale fizycznie nadal należy do procesu.
  - Jeśli zwolnisz wszystko aż do szczytu -> malloc może (ale nie musi, zależy to od implementacji i tzw. trim threshold) obniżyć wskaźnik break, oddając pamięć.
- Dla pamięci przydzielonej przez mmap: Procedura free może zwrócić pamięć do jądra natychmiast, niezależnie od kolejności alokacji czy położenia innych bloków pamięci. Dzieje się tak zazwyczaj dla bardzo dużych alokacji (powyżej progu MMAP_THRESHOLD)
