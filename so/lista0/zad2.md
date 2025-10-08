# zad 2

---

* `obsługa przrwań` - mechanizm dzięki któremu CPU i SO reagują na zdarzenia np zakończenie opearcji dysku
* `wektor przerwań` - numer który cpu dostaje wraz z przerwaniem, jest to idx w tablicy wektorów przerwań w której są jest zapisany adres procedury obslugi przerwania
* `procedury obsługi przrwania` - kod w jadrze systemu operacyjneo, który odpowiada na na konkretne przerwanie
* `tryb jądra` - uprzywilejowany tryp bracy cpu w ktorym
    * można wykonywać wszystkie instrukcje
    * mozna odwoływaś cię do całej pamieci
    * mamy dostęp do wszystkich rejestrów 

---

### mechanizm obsługi przrwań bazujący na wektorze przerwań
1. zdarzenei sprzętkowe np naciśnięci klawisza -> urządzenie wysyła sygnał do CPU
2. CPU zatrzymuje wykonywany program i zapisuje jego stan (rejestry, program counter, stack pointer, rejestry flag, ...)
3. sprzęt dostarcza wektor przrwań
4. CPU sprawdza tablicę wektorów przrwań
5. CPU przełącza sie w tryb jądra i wykonuje proceduje pod adresem z tablicy wektorów przrwań
6. stan programu jest odtwarazny, CPU wraca do miejsca w którym przrwał działanie

---

### Co robi procesor przed pobraniem pierwszej instrukcji procedury obsługi przerwania i po natrafieniu na instrukcję powrotu z przerwania? 

cpu zatrzymuje wykonanie programu i zapisuje stan programu na stosie jądra i przełącza sie w tryb jądra

stan programu jest odtwarzany i cpu przełącza sie w tryb użytkownika

---

### czemu procedura obsługi przerwania powinna być wykonywana w trybie jądra i używać stosu odrębnego od stosu użytkownika?

* osobny stos jest potrzebny ponieważ podczas obsługi przerwania cpu wymaga dostępu do urządzeń, rejestrów i operacji uprzywilejowanych które są wymagane do obslugi przrwania
* stos uzytkownika moze być niepoprawny, złośliwy lub przepełniony
* zapewnia to separacje kontekstu, bo jadro ma swoje własne struktury i zmienne lokalne których nie mozna trzymać na stosie aplikacji 