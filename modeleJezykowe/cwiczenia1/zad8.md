# zad 8 

---

#### opcja 1
* oba modele maja tą samą tekenizacje
* generujemy teskt płąz średnia prawdopodobieństwe 

$$
P(t) = \frac{P_1(t) + P_2(t)}{2} \\
P(t) = P_1(t) * \alpha + P_2(t) * (1 - \alpha)
$$

plusy: 
* prosta implementacja
* mozna rozmyć specjalizacje modeli

minusy: 
* wymaga identycznej tokenizacji 
* można rozmyć specjalizacje modeli

### opcja 2 
* modele mają różne tokenizacje
* część zdania jest generowana przez pierwszy model
* potem jego wyjście jest dekodowane do zwyklego tekstu. 
* tekst ten jest ponownie tokeniowowany przez drugi model, który generuje dalszą część

plusy: 
* działa nawet przy krótkich tekenizacjach 

minusy: 
* możliwa utrata spójności między fragmentami
* wolnijesze
* ryzyko różnic w stylu 

### opcja 3 
* rodzaj tokenizacji (czy taki sam czy inny ) nie istotny
* modele generują output na przemian
* najpierw pierwszy model 
* potem drugi 

plusy:
* prostota
* tokenizacja nie ma znaczenia 
* pozwala wykorzystać mocne strony obu modeli

minusy:
* tekst moze być niespójny stylistycznie 