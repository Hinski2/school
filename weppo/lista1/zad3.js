function sieve(n){
    let used = Array(n + 1).fill(false);
    let prime = [];

    for(let i = 2; i <= n; i++){
        if(used[i]) continue;
        prime.push(i);
        for(let j = i * i; j <= n; j += i)
            used[j] = true;
    }

    return prime
}

mak = 1e5;
console.log(sieve(mak))