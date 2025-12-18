# zad6

--- 

* dostajemy jakieś pytanie q
* robimy zapytanie q do wikipedii 
* zwracamy tytuł pierwszego artykułu z zapiania które nie pokrywa sie z pytaniem

--- 

### czemu to może działać 

* pytania które dostajemy to często odwrócone definicje haseł encyklopedycznych 
* używamy wewnętrznej wyszukiwarki wikipedii, która powinna podsunąć nam artykuły związane z zapytaniem
* mamy mechanizm który sprawdza czy nasze zapytanie nakłada się w ponad 50% z tytułem 
    dzięki temu na pytanie kto napisał akademie pana kleksa nie zwracamy nazwe artykułu akademia pana kleksa
* większość pytań dotyczy faktów encyklopedycznych 

### propozycja ulepszenia

algorytm słabo sobie radzi z: 
* pytaniami tak / nie 
* w których odpowiedzią jest data / liczba

możemy to ulepszyć w taki sam sposób jak rozwiązywaliśmy pracownie 1, czyli użyć papugi 
* dla pytań tak nie sprawdzamy prawdopowobieństow "q tak" i "q nie"
* dla pytań o liczbe odfiltrowywujemy odpowiedzi papugi tak by dała nam tokeny tylko liczbowe
* pytania o data, tutaj wikipedia moze podać dobry akrtykuł w którym bedzie data, wystarczy że zescrapujemy artykuł i wygrzebiemy z niego date