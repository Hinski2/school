function sum1(...args){
    let sum = 0;
    for(let u of args)
        sum += u
    return sum;
}

function sum2(){
    let sum = 0;
    for(let u of arguments)
        sum += u;
    return sum;
}

x = [1, 2, 3, 4, 5, 6]
y = 1
z = [1, 2]

console.log(sum1(...x), sum2(...x))
console.log(sum1(y), sum2(y))
console.log(sum1(...z), sum2(...z))
console.log(sum1(), sum2())