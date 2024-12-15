const mak = 1e5

// return array of decimal digits of x without 0. eg (1012) => [1, 1, 2]
function representation(x){
    let arr = []
    while(x){
        if(x % 10) arr.push(x % 10)
        x = Math.floor(x / 10)
    }
    return arr
}

// return sum of array
function sum(x){
    let s = 0
    for(let u of x)
        s += u 
    return s
}


function f(x){
    let arr = representation(x)
    arr.push(sum(arr))
    for(let u of arr)
        if(x % u) return 0
    return 1
}


let arr = new Array(mak);
arr = [...arr.keys()].map((x) => x + 1)
// arr = arr.keys().map((x) => x + 1) //doesnt' work because .keys() return iterator 
console.log(arr.filter(f))


