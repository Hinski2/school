# zad 4

rozważmy indukcje na drzewie po odległości werzchołka docelowego od wierzchołka startowego, nazwijmy tą odległość n
### krok bazowy
dla n = 0 v = vend więc h(v) = cost(v) = 0 z rozsądności heurystyki. Od razu znajdujemy optymalną drogę 

### krok indukcyjny
zał:
* h jest optymistyczna więc h(v) <= cost(v)
* h znajduje optymalną drogę dla vend w odleglości n od vstart

weźmy wierzchołek uend który jest następnikiem vend więc odległość od początku to n + cost(v, u)
**cel:** pokazać że h jest optymalna dla uend

```
z zał umiemy znaleźć optymistyczną drogę z v do vend
h(vend) jest optymistyczna,więc
    h(vend) = h*(vend)

rozważmy dowolny następnik vend, nazwijmy go u
wiemy że jeden z wierzchołków u = uend, wtedy
    h(u) = h(v) + cost(u, v) = h(v) + cost(uend, v) i jest to najmiejszy koszt pomiędzy następnikami
więc A* wybierze te u, kótre u = uend 
więc A* znajdzie optymalną ścieżke z vstart do uend

QED
```

h(v) <= h*(v) z założenia o optymiźmie heurystyki

poniewarz przestrzeń stanów jest drzewem to istnieje jedna ścieżka pomiędzy dwoma różnymi wierzchołkami

A* przeszukuje przestrzeń zgodnie ze wzorem f(v) = h(v) + c(v), gdzie c(u) to koszt dotarcia do wierzchołka v, a prawdziwy koszt dotarcia do v i z v do końca to h*(v) + c(v)

więc z optymizmu:
    h(v) <= h*(v)
dodajemy opustronnie c(v)
    h(v) + c(v) <= h*(v) + c(v)
wiemy że rzeczwisty koszt 
