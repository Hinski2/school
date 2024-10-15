mamy szereg naprzemienny:
$$
        S = \pi = 4 * \sum_k^\infty \frac{(-1)^k}{2k + 1} \\
        a_k = 4 / (2k + 1)
$$

wiemy że jak przybliżamy szereg to:
    $|S - S_n| \leq a_{n+1}$
    
zależy nam na przybliżeniu 1e-6
    więc szukamy n dla którego: $a_{n+1} \leq 1e-6$
    $$
        4 / (2n + 3) <= 1e-6 \\
        n >= 1999998.5\\
        więc \ n = 1999999
    $$
