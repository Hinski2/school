# zad 5

#### preprocesing dla wariantu z paliwem
* obliczamy odległości pomiędzy wszystkimi miastami n^3
* dla każdego wierzchołka sprawdzamy jaką stacje paliwową najlepiej wybrać (do której możemy dojechać) tak by jak najmniej zboczyć ze ścieżki optymalniej z v do vend w n^2 (czyli minimalizuje odl(v, k) + odl(k, vend) )

#### preprocesing dla wariantu z paczkami
* obliczamy odległości pomiędzy wszystimi miastami w n^3
* tworzymy nowy graf do którego nie dodajemy wierzchołków do których nie mamy rozwieźć paczek zostawiając tylko niezbędne krawędzie między wierzchołkami (krawędzie to nowe drogi które powstają zazwyczaj z połączenia wielu krawędzi z poprzedniego grafu)


#### heurystyka dla wariantu z paliwem

sprawdzamy czy wystarczy nam paliwa na dotarcie z wierzchołka v do vend
* tak: wtedy kierujemy się do vend
* nie: wtedy kierujemy się w kierunku wierzchołka k, do którego jesteśmy w stanie dojechać, który zawiera stacje i minimalizuje odl(v, k) + odl(k, vend)

czyli tak naprawde używamy 2 heuryk w zależności od sytuacji
* odl(v, end)
* odl(v, k) + odl(k, vend)