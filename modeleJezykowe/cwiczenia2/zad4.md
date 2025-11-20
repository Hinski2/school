# zad 4

---

#### pomysł 1

słowa które chcemy przekazać to pierwsze słowo co 5 zdań w liście

plusy:
* proste w zakodowaniu (w pythonie)

minusy: 
* może rzucać się w oczy że co 5 zdanie dzieniw się zaczyna 

#### pomysł 2 
mamy przeciez dostęp do tego samego modelu, mozna to wykożystać 

mamy dostęp do rozkładu prawdopodobieństwa. jeśli chcemy zakodować:
0 -> wybieramy token z parzystym idx
1 -> wybieramy token z nieparzystym idx

plusy:
* proste w zakodowaniu
* możemy tak przekazać dużo informacji 
* ciężkie do wykrycia

minusy: 
* ...

#### pomysł 3 

umawiamy się z towarzyszami na określoną funkcje generowania liczb losowych z określonym ziarnem. na jej podstawie generujemy co ile słów w liście będzie słowo które chcemy przekazać 

plusy: 
* nawet jeśli naczelnik zaóważy coś podejrzanego nie bedzie wiedział które słowa w liście to te które chcemy przekazać towarzyszą 

minusy: 
* trochę cieższe w zakodowaniu 

#### pomysł 4 

fuzja pomysłu 2 i 3