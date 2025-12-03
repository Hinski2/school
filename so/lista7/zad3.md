# zad 3

--- 

* `zbiór roborzy` - zbiór stron pamięci wirtualnej, do których proces odwoływał sie w ostatnim czasie
* `zbiór rezydentny` - zbiór fizycznych storn ram, ktore są obecnie załadowane do pamięci ram

---

    cat /proc/1465/status | egrep 'Vm|Rss'

``` bash
    VmPeak:	  432680 kB         # Virtual memory peak - maksymalna wielkośc pamięci writalnej, jaka proces kiedykolwiek osiagnoł
    VmSize:	  432552 kB         # Virtula Memory Size -  aktualna wielkosc pamięci wirtalnej 
    VmLck:	       0 kB         # Locked Virtual Memory - pamięć wirtualna zablokowana, która nie podlega wymianie (swap)
    VmPin:	       0 kB         # Pinned Virtual Memory -  pamięć wirtualna zablokowana, która jest używana przez jądro
    VmHWM:	  113548 kB         # Peak Resident Set Size - maksymalna ilość pamięci ram, jaką proces kiedykolwiek osiągnoł
    VmRSS:	  105544 kB         # Virtual Memory Resident Set Size - aktualna wielkość pamięci ram
    RssAnon:	   27308 kB     # Anonymous Resident Set Size - ilośc pamięci anonimowej 
    RssFile:	   78168 kB     # File Resident Set Size - ilość pamięci która ma odwzorowanie w pliku
    RssShmem:	      68 kB     # Shared Memory Residet Set Size - ilość pamięci współdzielonej
    VmData:	   25112 kB         # Data Setment Size -ilość pamięci zajmowana przez segment danych i setere
    VmStk:	     132 kB         # Stack size - ilość pamięci zajmowana przez stos
    VmExe:	    1736 kB         # Executable Size - ilość pamięci jaką zajmuje kod wykonywalny
    VmLib:	  230732 kB         # Library Size - pamięć zajmowana przez biblioteki współdzielone
    VmPTE:	     568 kB         # Page Table Entries Size - rozmiar pamięci zajmowane przez tablice stron
    VmSwap:	       0 kB         # Swapped Memory - pamięć wirtualna, która obecnie znajduje się na dysku w swap
``` 

pamięć zablokowana - pamięć ram która ma zablokowaną opcje bycia wymienioną (swap)

### zbiór roboczy vs zbior rezydentny

| | zbiór roboczy | zbiór rezydentny | 
| --- | --- | --- | 
| co opisuje | storony pamięci wirtualnej ostatniu używanych | strony pamięci ram, które proces aktualnie zajmuje
| lokalizacja | pamięć wirutlana | pamięć fizyczna ram


### skrtyp do wyznaczania sumy VMSIze i VmRSS wszystkich procesów

### czemu ta druga wartosć nie pokrywa się z rozmiarem używanej pamięci raportowanym przez polecenei vmstat -s