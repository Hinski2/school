// funkcja sleep
function sleep(time){
    return new Promise((resolve) => setTimeout(resolve, time));
}

// iterator
function fib_itr1(){
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
function *fib_gen1(){
    var memory = {0: 1, 1: 1}
    for(var i = 0;; i++){
        if(i in memory) yield memory[i]
        else yield memory[i] = memory[i - 1] + memory[i - 2]
    }
}

// take 
function *take(it, top){
    for(var i = 0; _res = it.next(), !_res.done && i < top; i++){
        yield _res.value
    }
}


// iterator
function fib_itr2(top=10){
    var _state = 0
    var memory = {0: 1, 1: 1}

    return function(){
        return {
            next: function(){
                return {
                    value: (function(i){
                        if(i in memory) return memory[i]
                        return memory[i] = memory[i - 1] + memory[i - 2]
                    })(_state),
                    done: _state++ >= top
                }
            }
        }
    }
}

// generator
function fib_gen2(top = 10){
    var memory = {0: 1, 1: 1}
    return function*(){
        for(var i = 0; i <= top; i++){
            if(i in memory) yield memory[i]
            else yield memory[i] = memory[i - 1] + memory[i - 2]
        }
    }
}

async function main(){ // trzeba zrobićasynchronicznego maina by móc używać await 
    //* test iteratora 
    var foo1 = {
        [Symbol.iterator]: fib_itr2(7)
    }

    for(var f of foo1){
        console.log(f)
        await sleep(100)
    }
    console.log()

    //* test generatora
    var foo2 = {
        [Symbol.iterator]: fib_gen2(7)
    }

    for(var f of foo2){
        console.log(f)
        await sleep(100)
    }
    console.log()

    //* użycie take
    for(var f of take(fib_itr1(), 3))
        console.log(f)

}
main();
