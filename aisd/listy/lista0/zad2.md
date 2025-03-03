# zad 2

---

``` c
for i := 1 to n:
    j := i
    while j < n: 
        sum := P(i, j)
        j++
```

złożoność: 
$$
[1 + n(P(i, j) + 1)] + [1 + (n - 1)(P(i, j) + 1)] + ... [1 + 1(P(i, j) + 1)] = \\
[n] + [n + (n - 1) + ... + 1] + [P(i, j)(n + (n - 1) + .. + 1)] = \\
n + \frac{n(n + 1)}{2} + P(i, j)\frac{n(n + 1)}{2}
$$

``` c
for i := 1 to n:
    j := i
    while j < n:
        sum := P(i, j)
        j += j
```

* dla ustalonego i petal startuje od j = i i w każdej iteracji podwaja j
* warunek stopu to $j \geq n$
* więc każda pętla wykona się tyle razy ile potrzeba by dojść przez mnożenia przez 2 do conajmniej n
* czyli szukamy najmniejszego k, takiego że $i \cdot 2^k \geq n$
* czyli $2^k \geq \frac{n}{i}$
* czyli $k \geq  log_2(\frac{n}{i})$
* k ~ $\lfloor log_2(\frac{n}{i}) \rfloor + 1$

wiemy że: $log_2(\frac{n}{i})$ = $log_2(n) - log_2(i)$
wieć rozpisujemy sume: $\sum_{i = 1}^n log_2(\frac{n}{i}) = \sum_{i = 1}^n [log_2(n) - log_2(i)]$

$\sum_{i = 1}^n log_2(n) = n\cdot log_2(n)$
$\sum_{i = 1}^n log_2(i) = log_2(1) + log_2(2) ... + log_2(n) = log_2(n!)$

przybliżenie stirlinga
n! ~ $\sqrt{2 \pi n}(\frac{n}{e})^n$
$log_2(n!) \approx log_2(\sqrt{2 \pi n}) + log_2((\frac{n}{e})^n) = log_2(\sqrt{2 \pi n}) + nlog_2(\frac{n}{e}) = log_2(\sqrt{2 \pi n}) + nlog_2(n) - nlog_2(e)$

więc $\sum_{i = 1}^n log_2(\frac{n}{i}) \approx n\cdot log_2(n) - (log_2(\sqrt{2 \pi n}) + nlog_2(n) - nlog_2(e)) = nlog_2(e) - log_2(\sqrt{2 \pi n})$