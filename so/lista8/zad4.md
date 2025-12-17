# zad4

## def
- gorliwie złącza - 

## algorytm przydziału pamięci
- «alloc: words -> id» i «free: id -> void» i ma do dyspozycji obszar 50 słów maszynowych
- Funkcja «alloc» zwraca bloki o identyfikatorach będącymi kolejnymi literami alfabetu
- Zwracane adresy są podzielne przez rozmiar słowa maszynowego. Implementacja używa dwukierunkowej listy wolnych bloków oraz boundary tags bez optymalizacji
- Wyszukiwanie wolnych bloków działa zgodnie z polityką best-fit
- Operacja zwalniania gorliwie złącza bloki i wstawia wolne bloki na koniec listy

- narzut pamięci każdy blok (zajęty i wolny) ma nagłówek i stopkę po 1 słowie (narzut 2)
- wolny blok przechowuje wskaźniki next,prev, czyli 2 na tagi + 2 na wsk. = 4
- jeśli po alok. reszta bloku ma < 4 sł nie można jej oddzielić - fr. wew.
- całkowita pamięć 50 słów

- na start:
  - wolny blok 50
  - lista wolnych bloków: [{a: 0, r: 50}]
