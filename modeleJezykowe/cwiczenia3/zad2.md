# zad2 

--- 

TF: term frequency - liczy ile razy dane słowo występuje w dokumence
$$
    TF(t, d) = \frac{liczba \ wystąpień \ słowa \ t \ w \ doumencie \ d}{liczba \ wszystkich \ słów \ w dokumencie \ d}
$$

IDF:  inverse document frequency - sprawdza jak powszechne jest słowo we wszytkich dokumentach (korpusie)
'i', 'w', 'że'... mają wysokie tf, idf karze słowa które występuje w wielu dokumentach a nagradza unikalne

$$
    IDF(t) = log(\frac{liczba \ wszystkich \ dokumentów }{liczba \ dokumentów \ zawierająca \ słowo \ t})
$$

TF-IDF: Term frequency - inverse document frequency. embeding który mówi ja ważne jest dane słowo w kokretnym teksci na tle innych słów. 

$$
    TF\_IDF = TF * IDF 
$$

wysokie tf-idf: słowo występuje często w tym dokumencie, ale rzadko w innych ( jest to słowo kluczowe)

--- 

rzadkie reprezentacje wektorewe słów - typ embedingóœ w kßórym zamieniamy teks na vektór który skłąda się głównie z zer 
np: 
* bag of words // nah
* index-based-encoding
* tf-idf 

tf-idf to bag of words z wagami 

### dlaczego to nie jest idealne rozwiązanie 
jeśli mamy dwa zdania "piękna żagówka" i "śliczby żaglowiec" to te zdania znaczą to samo ale zostana zakodowane w zupełnie inny sposób 

---

0. zaczynamy z ogromna macierzą o wymiarach D (liczba dokumentów), V (wielkość słownika)
1. redukcja wymiarów z użyciem algorytmu pca
    teraz mamy macież D' na V (gdzie d to np 100)
2. klastrowanie słów. 
    możemy do tego użyć Gaussian Mixture Models, który jest miękkim algorytmem klasteryzującym
    więc teraz dla każdego słowa mamy prawdopodobieństo jak bardzo należyc do danego klastra

teraz możemy wrócić do naszego zdania
* wystarczy że dla dokumentu który chcemy zakodować obliczymy średnia wartości słów które obliczyliśmy przy pomocy naszego algorytmu 
* np jak mamy słowo w_0 to ma ono wartość v = [v_0, v_1, ... v_100]
* i liczymy dla tego średnią w dokumencie

--- 

jaka klastryzacja:
są dwa typy klastryzacji: miękka i twarda

przykłąd trawdej to k-means clustering: który konkretnie klasyfikuje punkty 
przykład miękkiej to gmm: który mówi dla danego punktu jakie jest prawdopodobieństo, ze punkt należy do danego klastra

--- 
pca (Principal component analysis)