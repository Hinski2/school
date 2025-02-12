// function memorize(fn: (n : number) => number): (n: number) => number{
//     const cache: Record<number, number> = {};
//     return function(n: number): number{
//         if(n in cache) return cache[n];
//         return cache[n] = fn(n);
//     }
// }

// function fibo_rec(n: number): number {
//     if(n == 1) return 1;
//     if(n == 2) return 1;
//     return fibo_mem(n - 1) + fibo_mem(n - 2);
// }

// let fibo_mem = memorize(fibo_rec);
// console.log(fibo_mem(5))

let fibo_mem = (() => {
    let mem: Record<number, number> = {1: 1, 2: 1};

    return (n: number): number => {
        if(n in mem) return mem[n];
        return mem[n] = fibo_mem(n - 1) + fibo_mem(n - 2);
    }
})();

console.log(fibo_mem(500))