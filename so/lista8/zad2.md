# zad 2 

--- 

`control flow` - 

---

### różnice miedzy protokołami warstwy transportowej: datagarmowy upd vs połączoniowy tcp 

| | udp | tcp |
| --- | --- | --- | 
| typ | bezpołączenowy | połączeniowy - zanim wyślemy dane musimy nawiązać połączenie | 
| niezawodność | brak | wysoka - potwierdzanie odbioru i retransmisje
| kolejnosć | niegwarantowana | gwarantowana
| duplikaty | możliwe | wykrywane i usuwane autoamtycznie 
| struktura | datagram który zachowuje gramice jeśli wyślemy 100 bajtów to przyjdzie 100 bajtów  | strumień bajtów bez granic
| kontorla przepływu | brak (można zalać dobiorce) | jest z uzyciem `advertise window`
| złożoność | prosty, lekki | skomplikowany 


### komunikacja półdupleksowa vs dupleksowa

`półdupleksowa` - komunikacja w odbydwu kierunkach, ale naprzemiennie - jedna strona w jednym momencie
`dupleksowa` - transmisja w obu kierunkach jednocześnie

### jak tcp radzi sobei z zagubieniem segmentu lub przyjściem w innej kolejności niż zostaały wysłane

zła kolejność: 
tcp wykorzytuje numery skewencyjne  by uporządkować dane
1. buforowanie: aplikacja nie przekazuje od razu pakietu nr2 jeśli ten z nr1 nie dotarł jeszcze
2. porządkowanie
3. dostarczanie

zgubienie pakietu: 
tcp ma mechanizm potwierdzania i retransmisji, jeśli nadawca po wysłąniu pakietu nie otrzyma potwierdzenia retransmiture pakiet

### skąd TCP wiek kiedy połączenie zostało zerwane
sposoby na zakończenie transmisji: 
* normalne / oficjalne zakończenie tramsmisji
* błąd lub restart drugiej strony.
jeśli przez awarie lub restart dtuga sttrona straciłą pamięc o połączeniu odeśli segment z flagą restart, która jest dla nas infromacją o tym żebyśmy zerwali połączenie bo wystąpoł błąd 
* awaria typu przecięcie kabla:
    * jeśli wywyłaby pakiety i odbiorca nie bedize nab odpowiedał to sami zakończymy połaczenie
    * jeśli nie wysyłamy rzeadnych pakietuw to sie nie dowiemy że połączenie zostało zerwane i możemy tak czekać w nieskończonosć 

### jaki problem rozwiązuje sterowanie przepływem implementowane przez tcp 
rozwiązuje problem przepełnienia bufora odbiorczego u odbiorcy
tcp zapobiega temu, wywyłając informacje o advertised window - czyli mówi nadawcy ile bitów może jeszcze wysłać 