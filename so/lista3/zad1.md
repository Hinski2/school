# zad1 

---

* `zadanie drugoplanowe` - background job, proces który działa w tle
* `lider sesji` - proces, który utworzył nowe sesje i zarząda grupami procesóœ w tej sesji
* `sesja` - pewne liczba grup procesóœ podłączonych do tego samego terminala sterującego 
* `terminal sterujący` - terminal przypisany do sesji.

--- 

    Zaprezentuj sytuację, w której proces zostanie osierocony. Uruchom powłokę w nowej instancji
    emulatora terminala przy pomocy polecenia «xterm -e ’bash -i’». W nowej powłoce wystartuj «sleep
    1000» jako zadanie drugoplanowe i sprawdź, kto jest jego rodzicem

1. foot -e bash -i
2. sleep 1000 &
3. jobs -l
4. ps -o pid,ppid,tty,cmd -p [pid]
5. kill -9 [ppid]
4. ps -o pid,ppid,tty,cmd -p [pid]

ppid = 1

    Poleceniem «kill» wyślij sygnał
    «SIGKILL» do uruchomionej wcześniej powłoki i sprawdź, kto stał się nowym rodzicem procesu «sleep».
    Zauważ, że powłoka jest liderem sesji. 

echo $$ zwraca pid powłoi
kill %1

    Co się dzieje z sesją, która utraci terminal sterujący? Przeprowadź
    eksperyment wysyłając «SIGKILL» do emulatora terminala zamiast do powłoki.

zadziała tak samo ppid = 1

echo $$ 
sudo strace -e trace=signal -p [terminalpid]

