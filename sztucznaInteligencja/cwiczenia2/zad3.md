# zad 3

### czym jest spojna heurystyka
Spójna (consistent), s1, s2 to sąsiednie stany:
h(s1) <= cost(s1,s2) + h(s2) 

#### czym jest optymistyczna heurystyka
h(s) ≤ prawdziwy koszt dotarcia ze stanu s do stanu
końcowego

##### lepsze tłumaczenie
 **optymizm** An admissible heuristic is basically just "optimistic". It never overestimates a distance.

**spójność** A consistent heuristic is one where your prior beliefs about the distances between states are self-consistent. That is, you don't think that it costs 5 from B to the goal, 2 from A to B, and yet 20 from A to the goal. You are allowed to be overly optimistic though. So you could believe that it's 5 from B to the goal, 2 from A to B, and 4 from A to the goal.



### Dowód tego że spójna heurystyka jest optymistyczna

**podstawa indukcji:** rozważmy wierzchołek końcowy vend wtedy z rozsądności heurystyki mamy że h(vend) = 0, heurystyka w tym przypadku jest optyjistyczna (bo oczywiście cost(vend, vend) = 0)

**krok indukcyjny:** rozważmy wierzchołek v, zakł. że:
 * h(v) jest optymistyczna czyli h(v) <= cost(v, vend)
 * heurystyka jest spójna

**cel**: pokozać że dla każdego wierzchołka u prowadzącego do v, h(u) jest optymistyczna
czyli h(u) <= cost(u, vend)

``` 
ze spójności mamy:
    h(u) <= h(v) + cost(u, v)
ze spójności mamy:
    h(v) <= h(u) + cost(u, v)
z optimizmu h(v) mamy:
    h(v) <= cost(v, vend)

z zał, spójności
    h(u) <= h(v) + cost(u, v)
podstsawiamy optymizm h(v)
    h(u) <= cost(v, vend) + cost(u, v)
    
zastanówmy się czym jest cost(u, vend)
    cost(u, vend) <= cost(u, v) + cost(v, vend)
podstawiamy i otrzymujemy
    h(u) <= cost(u, vend)
qed
```



### Przykład heurystyki optymistycznej, ale nie spójnej

```
a b 0
b c 1

h(a) = 1 <= cost(a, c)
h(b) = 0 < 1 = cost(b, c)
h(c) = 0 
więc jest optymistyczna

h(a) > h(b) + cost(a, b)
1 > 0 + 0
więc nie jest spójna
```