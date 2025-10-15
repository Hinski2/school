# zad 2

---

* `proces zombie` - to proces ktory już zakończył dzialanie ale jego pcb (proces control block) nadal istnieje w tablicy procesów. dzieje sietak gdy rodzic nieodebrał kodu zakończenia dziecka (wywołując wait() lub waitpid())
* `proces sierota` - proces którego rodzic już nie istnieje, wtedy os "adoptuje" go podpinając ten proces pod proces init (pid=1)
* `stan` - stan w ktorym znajduje sie proces:
    * running - wykonywany aktualnie przez cpu
    * ready - gotwy do wykonywania
    * sleeping - czeka na zdarzenie lub I/O
    * stopped -  zatrzymany np przez SIGSTOP
    * terminated - usunięty 
---

### jak jądro systemu reaguje na sytuacje gdy proces staje sie sierotą
jądro automatycznie przypisuje go procesowi init (pid=1), który staje sie jego nowym rodzicem który potem będzie odpowiedzialny za posprzątanie zombie

### w jaki sposób pogrzebać proces który wszedł w stan zobmie
opcja a) proces rodzica wywoluje wait() -> wtedy proces zostaje usunięty i nie staje sie zombie
opcja b) proces rodzica nie wywoluje wait() i sie kończy -> wtedy zombie staje sie sierotą, a init staje sie jego rodzicem który czeka aż sierota wywoła exit() żeby móc po nim automatycznie posprzątać 

### czemu proces nie może sam siebie pogrzebać
bo exit() musiałby zwolnic stos jądra, exit() to wywołuje syscall _exit(2) i wywołuje sie na stosie jądra, a skoro się na nim wywołuje to nie może go zwolnić,

### proces moze czekać tylko na zmiane stanu swoch dzieci, co złego mogło by  sie stać gdyby znieść to ograniczenie
##### (a) dziecko może czekać na zmianę stanu swojego rodzica
 mogło by dojść do sytuacji gdzie dziecko czeka na zmiane stanu rodzica, a rodzic czeka na zmiane stanu dziecka (deadlock) 
##### (b) wieel procesóœ oczekuje na zmiane tanu jednego procesu 
po zakończeniu procesu trzeba by było obudzieć wiele innych, co mogło by prowadzic do race conditions (bo jakoś trzeba zarządzic tym w jakiej kolejności budzić procesy)

#### Proces wykonujący w jądrze implementację wywołania systemowego _exit(2) nie może zwolnić stosu jądra,
na którym się wykonuje. Kto zatem musi to zrobić?

1. proces woła exit() w przestrzenie użytkownika -> wchodzimy do jądrz przez syscall _exit(2)
2. w jądrze proces:
    * ustawia stan na zombie
    * zwalnai zasoby uzytkoniak
    * nie zwalnia włąsnego stosu jadra - bo aktualnie sie na nim znajduje

(scheduler nie tylko decyduje który proces na działać, ale też jest odpowiedzalny za usuwanie procesóœ w kolejki)
3. scheduler usuwa proces z listy aktywnych procesóœ 
4. gdy rodzic wykona wait()
    * jądro odpiera status zakończonego dziecka
    * wtedy zwalniany jest stos jadra 

