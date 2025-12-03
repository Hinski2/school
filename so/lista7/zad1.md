# zad 1 

---

* `odwzorowanie pliku w pamięci` - mechanizm który pozwala traktować plik z dysku tak jak kawałek pamięci ram. dzięki niemu zamiast używać read / write działąmy na bajtach w pamięci 
* `odwzorowanie pamięcie anonimowej` - rezerwacja czytego obszaru pamięci ram, który nie ma żadnego odpowiednika w pliku na dysku
* `odwzorowanie prywatne` - własna kopia. zmiany są widoczne tylko dla nas i nie są zapisywane do oryginalnego pliku ani widoczne przez innych
* `odwzorowanie dzielone` - wspóldzielone odwrozorwanie, każda zmiana jest natychmiast widoczna dla innych procesóœ. w przypadku mapowania pliku zmiany są autoamtycznie zapisywane na dysk

--- 

### odworowanie pliku w pamięci vs odzworowanie pamięci anonimowej

| | odwzorowanie pliku w pamięci | odwzorowanie pamięci anonimowej | 
| --- | --- | --- 
| co jest źródłem | fizyczny plik na dysku | brak pliku, to czysty obszar w pamięci ram |
| czym jest wypełniona na starcie | zawartościa pliku | zerami | 
| zastosowanie | szybkie operacje na plikach, zamiast read / write | przydzielanie pamięci dla programu (np używane przez malloc) | 

### jaka zawartościa wypełniana jest pamięć wirtualna nalężąca do tych odwzorowań

# ↑

### odwzrorowanie prywatne vs dzilone 
| | prywatne | dizelone | 
| --- | --- | --- |
| widoczność zmian | zmiany widzi tylko proces, inne procesy korzytające z tego samego obszaru nie widzą tych zmian | zmiany są widoczne natychmiast dla wszystkich innych procesów, które mapują ten obszar
| wpływ na plik oryginalny | znie zmianie arytinału, zmiany nie są zapisywane na dysk | nadpisuje, zmiany trafiają na dysk | 
| mechanizmy działąnia | wykorzystuje copy on write | wszystkie procesy operują na tych samych stonach pamięci ram |

### czy pamięć obiektów odwzorowanych prywatnie moze być współdzielona 

tak, ale dopuki nikt ich nie modyfikuje. gdy jakiś proces będzie chciał zmodyfikować odwzorowanie prywatne pojawi się mechanizm copy on write, więc so stworzy kopię tylko tej konkretnej storny, która jest modyfikowana i proces dostanie prywatną kopię na własnosć, reszta nadal może być współdzielona 

### czemu można tworzyć odwzorowania plików urządzeń blokowych w pamięć, a znakowych nie

urządzenia blokowe:
* przechowuja dane w blokach o stałym rozmiarze
* mają skończoną wielkość 
* występuje w nich adresowanie, wiec możemy poprosić np o blok 42

urzaądzenai znakowe:
* strumienie danych, w których znaki płyną jeden po drugim i cząsto nie są nigdzie przechowywane
* mie posiadaja adresowanai

te różnice w specyfikacji urządzeń blokowych i znakowych sprawiają, że możemy tylko mapować urządzenia blokowe, bo mmap wymaga obiektu, który ma określoną długości i pozwala na swobodny dostęp do adresóœ  