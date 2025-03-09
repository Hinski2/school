# zad 4

---

definicja drzewa binarnego
``` c++
struct node{
    int val;
    node *l;
    node *r;
}
```

liczenie liczby wierzchołków drzewa
```c++
int no_node(node *v){
    if(v == nullptr){
        return 0;
    } 

    return no_node(v -> l) + no_node(v -> r) + 1;
}
```

liczenie maksynalnej odległości między wierzchołkami drzewa. najdłuższa ścieżka niekoniecznie musi przechodzic przez korzeń!

```c++
int maxi = 0;
int compute_longest_path(node *v){
    if(v == nullptr){
        return 1;
    }

    int l = compute_longest_path(v -> l);
    int r = compute_longest_path(v -> r);
    maxi = max(maxi, l + r);

    return max(l, r) + 1;
}
```

każda ścieżka ma swój najwyższy punkt w drzewie (czyli wierzchołek najbliżej korzania). my sprawdzamy najdłuzszą ścieżke dla każdego z wierzchołków wiec w szczególności sprawdzimy też dla najwyższego wierzchołka w najdłuzszej ścieżce, więc ją znajdziemy 