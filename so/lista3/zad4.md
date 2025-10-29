# zad 4

---

* `urządzenie terminaal` - interaktywne urządzenie io które pozwala użytkownikowi na komunikcje z so
* `CSI` - control sequence introducer \e[

---


### pokaż dzialanie znaków sterujących  oraz sekwecji CSI 

znaki sterujące: 
* \a - sygnał dzwiękowy
* \b - kursor w lewo        echo -e "aa\bb"  
* \t - tab 
* \n - następna linia       echo -e "\ta\ta"
* \r - powrót karetki       echo -e "aaa\rbbb"
* \e - rozpoczyna sekwencje escape
* \e[ - rospoczyna sekwencje sterującą 

csi: 
* kursor:
    * csi n A - cursor up
    * csi n B - cursor down
    * csi n C - cursor forward
    * csi n D - cursor back
    * csi n ; m H - move cursor to row n column m

    * csi ? 25 l - hide cursor 
    * csi ? 25 h - show cursor
* scroll
    * csi n S - scroll up
    * csi n T - scroll down
* grafika \e[<parametry>m
    * 0 - reset parametróœ 
    * 1 - pogrubienie
    * 5 - miganie           echo -e "\e[5mmiganie"
    * 8 - ukrywa tekst      echo -e "\e[5mmiganie\e[8malal"
    * \e[<fg/gb>m  fg: [30, 37], bg: [40, 47]
        * \e[31m czerwony tekst
        * \e[44m niebieskie tlo
        * echo -e "\e[31;42mabc"

### sprawdzenie cat
```
(base) ➜  ~ cat  
^[[D^[[A^[[C^[[B

^C
(base) ➜  ~ cat -v 
^[[D^[[A^[[C^[[B
^[[D^[[A^[[C^[[B
```

zachowanie cat jest inne bo nie interpretuje klawyszy funkcyjnych tak jak powloka, tylko po prostu je wypisuje