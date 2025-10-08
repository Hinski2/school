# zad1

---

* `przerwanie sprzętowe` - zewnętrzny sygnał ze sprzętu do CPU informujacy, że zaszło zdarzenie które wymaga obsługi. Asynchroniczne.
    * przerwanie zegarowe
    * zakończenie operacji dyskowej
    * naciścięcie klawisza klawiatury

* `wyjatek procesora` - mechanizm do przrwania normalego przebiegu wykonywania progarmu, wtedy cpu wywołuje odpoweidni handler. ma podział na klasy: 
    - fault - błąd możliwy do naprawienia
    - trap - zgłaszany po poprawnym wykonaniu instrukcji
    - abort - błąd krtyczny niemozliwy do naprawy
    Synchroniczny.
    * dzielenie przez zero
    * page fault (pruba dostępu do nieobecnego / zabronionego pliku)
    * próba wykonania niepoprawnie zakodowanej instrkucji

* `pułapka` - celowe wywołanie jądra z poziomu programu, skutkujre kontrolowanym wejściem do jądra.
    * wywołanie systemowe
    * gdy ustawiamy breakpoint w debugerze
    * fork
---

### W jakim scenariuszu wyjątek procesora nie oznacza błędu czasu wykonania programu?

wyjątek procesora to nie zawsze błąd logiczny, może to też być mechanizm obsługi, OS spodziewa się wyjątku i wykorzystuje go jako częsc normalnej pracy 

przykład: Page Fault
    * proces wykonuje dostęp do strony której nie ma w RAM
    * CPU zgłasza page fault
    * SO ładuje strone z dysku i powtarza instrukcje
    * dla programu wygląda to jak normalny dostęp 

---

### Kiedy pułapka jest generowana w wyniku prawidłowej pracy programu?

Podczas systemcall'i (np. write, open, fok), w tle jest generowana pułapka