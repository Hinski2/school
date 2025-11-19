# zad5

--- 

### jakei zadanie pełni exit(3)
1. uruchamia funkcje zarejestrowane przez on_exit() i atexit()
2. opróżnia buffory i zamyka strumienie 
3. pliki utworzone przez tempfile(3) są usunięte
4. na końcu wywołuje _exit(status)

### problem z bufforowaniem

#### fork
po fork(), fd są współdzielone. jeśli przed fork() było coś w buforze np stdout, ale jeśsze nie zostało wypisane do pliku/terminala to
* rodizc przy exit / fflush zapisze ten bufor
* dziecko przy exit/ fflush zapisze tą samą wartośc drugi raz 

aby teklmu zapobiec przed fork() zrób fflush(NULL); który wypisze wszystkie otwarte strumienie
#### execve 

execve()
* zastępuje cały obraz procesu nowym programem
* ale ie rusza fd, które są dziedziczone
* bufory starego programu znikną, bo to była pamięć user-space poprzedniego procesu

więc jeśli w buforze przed execve były jakies dane, to po execve te dane znikną (przepadną)

aby temu zapobiec zrob fflush(NULL) przed execve()

#### _exit 
_exit od razu końcy proces, nie flushuje fd.
jesli chemy używać _exit() zamiast exit() to musimy sami zadbać o wypisanie buffora

### domyśle strategie bufforowania strumieni
typy bufforowania:
* niebuforowany
* buforowanie liniowe
* buforowanie pełne

* plik terminala - buforowanie liniowe
* plik zwykly -  buforowanie blokowe
* stderr - niebuforowany