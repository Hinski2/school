# zad4

--- 

### tworzenie programów uprzywilejowanych
Programy uprzywilejowane powinny działać z minimalną liczbą uprawnień bo:
* zwiększanie powierzchni ataku - jeśli w programie pojawi się bug, a program działą jako root atakujacy może przejąć nasz program
* błąd w jednej lini - jeśli zrobimy błąd nawet w jednej lini, to to może być wystarczające dla atakującego do przejęcia władzy nad programem
* minimalizacja szkód - w przypadku błędu jeśli większość pracy wykonujemy jako użytkownik to , potencjał na przejęcie naszego programu jest mniejszy
* unikanie niezamierzonych konsekwencji - jeśli program działa z uprawnienaimi root'a to możemy przez przypadek narobić dużo szkód np: modyfikować pliki systemowe 

jak projektować bezpiecznie programy uprzywilejowane:
* używać przylilejy tylko wtedy gdy są potrzebne 
* gdy przywileje nie będą potrzebne - można zrzec sie ich na stałe 
* nie wykonuj exec() z uprawnieniami
* nie uruchamiaj powłoki z uprawnieniami
* przed exec() zamnij wszystkie niepotrzebne deskryptory 


### czemu standardowy zestaw funkcji systemu uniksowego jest niewysarczajacy do impliementajci programów uprzywilejowanych 

ponieważ w unix są tylko dwi klasy procesów 
* z efektywnym uid = 0, omija wszystkie sprawdzenia uprawnień
* wszystkie pozostałe, mają normalne sprawdzenia uid/gid i bitów rwx

to bardzo zero jedynkowe. 
wiec jeśli chcemy mieć program ktory służy tylko i wyłącznie do ustawiania czasu systemowego (wyamga uprawnień roota). a nie potrzemujemy reszty czyli czytania dowolnych plików, omijania wszystkich rwx... to musimy takiemu programowi dać całem pakiet uprawnień roota a nie tylko możliwość ustaianai czasu

### jak staraja sie to naprawić zdolności (capablilities)
naprawia to powyżej
* zamiast jednego super uprawnienia mamy wiele małych przywilejów.
* np: punkt poniżej


### majac CAP_DAC_READ_SEARCH i CAP_KILL jądro pomija sprawdzanie upoważnień do wykonwania akcji: 
* CAP_DAC_READ_SEARCH - (DAC - Discreationary access control)pozwala omijać sprawdzenie uprawnień do odczytu i przechodznia po katalagu. bez prawa zapisu (write)
* CAP_KILL - daje prawo do wysyłania sygnałów kill. normalnie proces może wysłać sygnał do innego procesu tylko jeśli ma ten sam uid (lub jest root'em)

### kiedy proces użytkonika może wysłać sygnał do innego procesu
normalnie proces może wysłać sygnał do innego procesu tylko jeśli ma ten sam uid (lub jest root'em)