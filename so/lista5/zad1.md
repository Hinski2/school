# zad 1

---

#### read() rura pusta
* jeśli są piszacy, blokujący fd: read() blokuje sie az pojawią sie dane 
* jesli są piszcy, fd nieblokujący (O_NOBLOCK): read() zwraca -1 i ustawia erno 
* nei ma piszących: read zwrac 0 (EOF)

#### read() rura pełna
* dane są dostępne, read zwraca tyle bajtów ile może 

#### write() rura pusta
* są czytający
    * n <= PIPE_BUF: zapis atomowy
    * n > PIPE_BUF, fd blokujący: piszemy tyle ile sie zmieści, potem bloujemy a ż swolni isę miejsce
    * n > PIPE_BUF, fd nieBlokujący: zwraca krótszy zapis
* brak czytających: dostaniemy SIGPIPE i -1

#### write() rura pełna 
* są czyatjących, blokujacy fd: blokuje aż zwolni się miejsce
* są czytających, O_NOBLOCK: -1 i erno
* brak czytających: dostaniemy SIGPIPE i -1


### pisanie tekstu.len() < PIPE_BUF
wtedy zapisy są atomowe

### ps -ef | grep sh | wc -l
Czemu wszystkie procesy należące do potoku zakończą się bez interwencji powloki, jeśli co najmniej jeden z nich umrze:
* umiera pierwszy proces -> następny dostaje EOF na wejściu
* umiera proces w środku -> następny dostaje EOF na wejściu, poprzedni gdy próbuje pisać dostaje SIGPIPE i umiera
* umiera ostatni: zamytak koniec 

### short count
short count - read() / write() zwraca liczbę przeczyatnych znaków mniejsza niż żądane. to nei bląd tylko informacja że udao się przetworzyć tylko część 

read: gdy w buforze jest mniej bajtów niż prosimy. gdy czytanie zostanie przerwane sygnałem
write: gdy n > PIPE_BUF i nieBlokujący FD. gyd pisanie zostanie przewane sygnałem

### łączenie dziecka i rodzica rurą utworzoną po fork
* ze zwykłą rurą nie wyjdzie, deskrytpory musza istnieć przed fork
* można użyć named pipe, z użyciem funkcji mkfifo

