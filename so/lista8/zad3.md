# zad 3

--- 

`gniazdo strumieniowe` - rodzaj gniazda siecowego które komunikuje się w formie ciągłego strumienia bajtów bez granic poszczególnych komunikatów
`port ulotny` - tymczasowy numer portu przygielany przez ao ablikacji tylko na czas trwanai konkretnego połączenia

--- 

![](/img/i1.png)

1. faza przygotowania serwera 
    * socket() - serwer tworzy gniazgo 
    * bind() - serwer przypisuje gniazdu konkretyny adres ip i port
    * listen() - serwer nasłuchuchuje przychodzących połączeń 
    * accept() - 

2. faza nawiazania połączenia i przygotowanie klienta 
    * socket() - klient tworzy swój socket 
    * connect() - klient wywołuje tą funkcje podając adres serwera 
    * funkcja accept() an serwerze budzi się i towrzy dedykowane gniazdo tyko dale tego klienta 

3. faza komunikacji
    * request od klenta -> replay od serwera 

4. faza zakończenia 
    * serwer albo klient wywołują close() 

---

### w którym momencie następuje zwiazanie gniazda z adresem lokalnym i zdalnym 
serwer:
* adres lokalny: w momencie wywołania bind() 
* adres zdalny: gdy funkcja accept() się obudzi i jest tworzone newe gniazdo 

klient: 
* adres lokalny: jest przydizelany port ulotny podczas wywołania connect()
* adres zdalny: po ustanowieniu połączenia

### która ze stron komunikacji używa portów ulotnych 
klient. gdy klient wywołuje connect() so przydziale mu losowy wolny port 

### co specyfikuje drugi argument wywołąnia systemowego listen(2)

    #include <sys/socket.h>
    int listen(int sockfd, int backlog);

`backlog` określa maksymlaną długość kolejki połączzeń oczekujacych na obsłużenie przez aplikacje

### z jakim numerem portu jest związane gniazdo przekazywane do i zwracane z accept(2)

* przekazywane - zwiazane z adresem lokalnym do którego zostało przypisane za pomocą funkcji bind(2) 
* zwracane - jest to nowo połączone gniazdo

### skąd serwer wie, że klient zakończył połączenie 

* gdy serwer wywołuj read() i zwraca ono 0 
* w przypadku błędu, próba operacji na błędzie zwróci -1 i ustawi errno 