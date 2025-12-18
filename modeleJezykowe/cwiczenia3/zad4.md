# zad 4

--- 

#### problem: musimy zmienić graf w zdania
musimy z użyciem word2Vec udawawać że:
* węzły w grafie to słowa
* ścieżki w grafie to zdania

#### potrzebujemy 
1. wygenerować korpus 
2. nauczyć word2Vec 
3. interpretować embeddingi 

### 1. generacja korpusu
mamy sieć społe z węzłami (jako osoby ) i ścieżkami ( relacjami znajomości )

* bardzo dużo razy: 
    * wybieramy wierzchołek startowy x i dodajemy 
    wielokrotnie (np 7 razy): patrzymy na ostatni wiechołek w zdaniu nazwijmy go n
        * patrzymy na wszystkich sąsiadów n (czyli węzły w relacji znajomości) i wybieramy losowego sąsiana m 
        * dodajemy m na koniec listy 
    * zmieniamy liste w stringa 
    wiec mamy np " ".join(["kuba iliński", "dawid pawliczek"... "jan mączyński"])

### 2. uczenie word2Vec
trenujemy word2 vec na naszym korpusie
po treningu jeśli w naszym korpusie dawid i kuba będą często blisko siebie, to powinni po treningu być blisko siebie w przestrzeni

### 3. interpretacja embeddingów 
word2Vec zwrócił nam gęsty wektor 
* jeśli np janek i kuab będą mieli wspólnych znająmych lub jak będą znajomymi to powibbo byv blisko siebie w przestrezmi 
czyli bęą mieli wysokie cosi similarity 

---- 

dla netfix mamy graf dwudizelny `osoba` -[:lubi / :nie_lubi]-> `film`
tworzymy korpus jako: 

    osoba film osoba film ... 
    dawid matrix kuba minecraft movie