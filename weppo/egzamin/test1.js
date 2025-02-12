var person = {
    name: "kuba", 
    age: 19,
    1: 10
}

// console.log(person['name'], person['age'], person['1'])
// console.log(person.name, person.age) // nie da się pesron.1

person.surname = 'Iliński';

function fibo(n){
    if(n == 1) return 0;
    else if(n == 2) return 1;
    return fibo_mem(n - 1) + fibo_mem(n - 2);
}

function memorize(fn){
    var cache = {};
    return function(n){
        if(n in cache) return cache[n];
        else return cache[n] = fn(n);
    }
}

var fibo_mem = memorize(fibo);

function createFs(n) { 
    var fs = []; // 
    for ( var i=0; i<n; i++ ) {
        ((x) => {
            fs[x] =
                function() {
                    return x;
                };
        })(i);
    };
    return fs;
}

var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );