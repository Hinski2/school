function fibo_iter(n){
    let a = 0, b = 1, c;
    if(n == 1) return a;
    else if(n == 2) return b;

    for(let i = 2; i < n; i++){
        c = a + b;
        a = b;
        b = c;
    }

    return c;
}

function fibo_rec(n){
    if(n == 1) return 0;
    else if(n == 2) return 1;
    return fibo_rec(n - 1) + fibo_rec(n - 2);
}


for (let i = 10; i <= 44; i++) {
    console.time(`fibo_iter(${i}), time`);
    let x = fibo_iter(i);
    console.timeEnd(`fibo_iter(${i}), time`);

    console.time(`fibo_rec(${i}), time`);
    let y = fibo_rec(i);
    console.timeEnd(`fibo_rec(${i}), time`);

    console.log(`fibo_iter: ${x}, fibo_rec: ${y}`);
    console.log();
}