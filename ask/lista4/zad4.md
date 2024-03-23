# zad 4

ogolnie o co chodzi
``` c
    decode(ll x, ll y):
        //swapuje x i y
        rax = x + y
        x ^= x + y
        y ^= x + y

        rax = x     // wartość: y
        rax &= y    // and'uje x i y
        rax >>= 63
        return rax
```

bardziej zwięzła wersja
``` c
    decode(ll x, ll y):
    return ((x ^ (x + y)) & (y ^ (x + y))) >> 63;
```

zwięzła wersja zoptymalizowana

```c
    return (x & y) >> 63; 
```

czyli sprawdzam czy x i y mają ten sam znak
jeśli nie to 0 jeśli tak to -1
