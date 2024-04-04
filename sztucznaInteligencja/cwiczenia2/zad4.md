# zad 4

rozważmy indukcje na drzewie po odległości werzchołka docelowego od wierzchołka startowego, nazwijmy tą odległość n
### krok bazowy
dla n = 0 v = vend więc h(v) = cost(v) = 0 z rozsądności heurystyki. Od razu znajdujemy optymalną drogę 

### krok indukcyjny
zał:
* h jest optymistyczna więc h(v) <= cost(v)
* h znajduje optymalną drogę dla vend w odleglości n od vstart

weźmy wierzchołek uend który jest następnikiem vend więc odległość od początku to n + 1
**cel:** pokazać że h jest optymalna dla uend

```
z zał umiemy znaleźć optymistyczną drogę z v do vend
    h(vend) jest optymistyczna

rozważmy dowolny następnik vend, nazwijmy go u
wiemy że jeden z wierzchołków u = uend, wtedy
    h(u) = cost(u) = 0, bo h(u) jest optymistyczna
więc A* wybierze te u, kótre u = uend 
więc A* znajdzie optymalną ścieżke z vstart do uend

QED
```