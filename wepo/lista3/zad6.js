// funkcja sleep
function sleep(time){
    return new Promise((resolve) => setTimeout(resolve, time));
}

// iterator
function fib_itr(){
    var _state = 0
    var memory = {0: 1, 1: 1} 

    return {
        next: function(){
            return {
                value: (function(i){
                    if(i in memory) return memory[i]
                    return memory[i] = memory[i - 1] + memory[i - 2]
                })(_state++),
                done: false
            }
        }
    }
}

// generator
function *fib_gen(){
    var memory = {0: 1, 1: 1}
    for(var i = 0;; i++){
        if(i in memory) yield memory[i]
        else yield memory[i] = memory[i - 1] + memory[i - 2]
    }
}



async function main(){ // trzeba zrobićasynchronicznego maina by móc używać await 
    //* test iteratora 
    var foo1 = {
        [Symbol.iterator]: fib_itr
    }

    for(var f of foo1){
        console.log(f)
        await sleep(200)
    }

    //* test generatora
    var foo2 = {
        [Symbol.iterator]: fib_gen
    }

    for(var f of foo2){
        console.log(f)
        await sleep(200)
    }
}
main();
