# zad 1

---

* `warstwa łącza` - warstwa która odpowiada za przenoszenie datagramów z jednego węzła do następnego na trasie
* `warstwa sieciowa` - warstwa odpowiedzlana za przenoszenie datagramów z hosta źródłowego do hosta docelowego
* `warstwa transportowa` - warstwa zajmująca sie transportem wiadomości pomiędzy punktami końcowymi aplikacji
* `pakiet` -  porcja danych przesyłana w sieci która na różnych warstwach jest `wiadomością`, `segmentem`, `datagamem`, `ramką`
* `kapsułkowanie` - zamykanie pakietu z niższej warstwy z dodatkiem nowego naagłówka wyższej warstwy. tak powstaje pakiet tej wyższej warstwy - jak matrioszki
* `ramka` - pakiet na warstwie łącza
* `datagram` - pakiet na warstwie siecowej
* `segment` -  pakiet na wartwie transportowej

---

#### warstwy: 

| warstwa | jednostka danych | przykład | zadanie |
| --- | --- | --- | --- | 
| aplikacji | message | HTTP, SMTP | usługi siecowe użytkownika
| transportowa | segment | TCP, UPD | komunikacja proces-proces
| siecowa | datagram | ip | routing, komunikacja host - host
| łącza | ramka | ethernet, wifi | komunikacją węzeł - węzeł
| fizyczna | bit | światłowód, kabel | fizyczna transmisja sygnałów

---

#### wireshark

* przechwyć kilka pakietów protokołów UDP i TCP 
* wyśtietl nagłówki ramki, datagramu i segmentu
* zidentyfikuj adres źródłowy i docelowy pakietu 

---

### czemu protokoły warstwy łącza i siecowej nie są używane do komunikacji między procesami użytkonika
ponieważ protokoły te działają na poziomie całego urządzenia (host - host lub węzłów) a nie konkretnych aplikacji, nie posiadaja mechanizmów które pozwalaja rozróżnić do którego z wielu procesów na komputerze dane maja trafić (nie znają numerów partów)