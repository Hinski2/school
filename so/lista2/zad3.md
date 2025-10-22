# zad 3 

---

* `zainstalowane procedury obsługi sygnałów` - funkcje ustawione przez proces (np sigaction) określające co ma sie stać przy nadejściu danego sygnału:
    * zognoraowanie
    * domyślne działanie
    * wowałanie customowego (naszego) handlera

---

### zasoby procesu które są dziedziczone przez proces potomy
* otwarte deskryptory plików
* Real/effective UID/GID
* PGID (proces group id), SID (session ID)
* bieżący katalog roboczy i główny
* mask sygnałów
* environment
* mapowanie pamieci 

### zasoby procesu które są przekazywane do nowego progamu załadowanego do rpzestrzeni adresowej
* PID, PPID
* Real UID/GID
* PGID
* bierzący katalog roboczy i główny
* maska sygnałów i pending signals
* blokady plików 

trzeba przekazać jawnie argv, envp

### czemu przed wywolaniem fork należy opróżnić bufory bibliotek stdio
bo bufory stdio są w pamieci użtykownika i kopiują się przy fork(). jesli przed fork() w buforze jest jakis tekst: 
* rodzic i dziecko dostana kopię tego samego bufora
* potem oba procesy go opróżnią, czyli zaipiszą lub przemieszcządwa razy

dla tego przed fork() dobrze robić 
```c
    fflush();
```

### co jądro robi w trakcie wywołąnia execve z konfigurając zainstalowanych procedu obsługi sygnału 

jądro podmienia program i resetuje sygnały, czyli zainstalowane włsne handlery są wyrzucane. Maska sygnałów i sygnałów oczekujacych (pending) sa dziedziczone