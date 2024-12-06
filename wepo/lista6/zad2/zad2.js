"use strict";
function fibo_iter(n) {
    let a = 0, b = 1, c = 0;
    if (n == 1)
        return a;
    else if (n == 2)
        return b;
    for (let i = 2; i < n; i++) {
        c = a + b;
        a = b;
        b = c;
    }
    return c;
}
function fibo_rec(n) {
    if (n == 1)
        return 0;
    else if (n == 2)
        return 1;
    return fibo_rec(n - 1) + fibo_rec(n - 2);
}
function fibo(n) {
    if (n == 1)
        return 0;
    else if (n == 2)
        return 1;
    return fibo_mem(n - 1) + fibo_mem(n - 2);
}
function memorize(fn) {
    const cache = {};
    return function (n) {
        if (n in cache)
            return cache[n];
        else
            return cache[n] = fn(n);
    };
}
var fibo_mem = memorize(fibo); // przypisanie funkcji do zmiennej 
for (let i = 1; i <= 43; i++) {
    console.time(`fibo_iter(${i}), time`);
    let x = fibo_iter(i);
    console.timeEnd(`fibo_iter(${i}), time`);
    console.time(`fibo_rec(${i}), time`);
    let y = fibo_rec(i);
    console.timeEnd(`fibo_rec(${i}), time`);
    console.time(`fibo_mem(${i}), time`);
    let z = fibo_mem(i);
    console.timeEnd(`fibo_mem(${i}), time`);
    console.log(`fibo_iter: ${x}, fibo_rec: ${y}, fibo_mem: ${z}`);
    console.log();
}
