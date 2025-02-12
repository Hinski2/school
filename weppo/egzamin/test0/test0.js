var a = Array(10).map((val, idx) => idx) // nie zadziałą poprawnie bo elementy nie za zainicjowane
var b = [...Array(10)].map((val, idx) => idx + 1)   // zadziała, jeśli mamy empty value i rozpakujemy wartość to dostaniemu undefined
var c = Array(10).fill(0).map((val, idx) => idx + 1) // zadziała


var a = Array(100).fill(0).map((val, idx) => idx + 1).filter((val, idx) => val % 2 == 0 ? true : false)

var foo = (x) => {
    let sum = 0;
    for(; x; x = Math.floor(x / 10)){
        sum += x % 10;
    }

    return sum;
}

function sum(x){
    let sum = 0;
    for(; x; x = Math.floor(x / 10)){
        sum += x % 10;
    }

    return sum;
}

var a = Array(10).fill(0).map((val, idx) => foo(idx + 1));
var a = Array(10).fill(0).map((val, idx) => idx + 1).reduceRight((acc, cur) => acc + cur);

// var a = Array(10).fill(0).map((val, idx) => idx + 1).forEach((val) => console.log(val))

var f = (x) => {
    if(x == 0) return 0;
    else if(x == 1) return 1;
    return f(x - 1) + f(x - 2);
}

var s = "11" + 21
// var s =  21 + '11'
console.log(s.length)