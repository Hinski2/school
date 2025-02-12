function createGenerator(maxLen=12) {
    var _state = 0;
    return () => ({
        next: function() {
            return {
                value: _state,
                done: _state++ > maxLen
            }
        }
    })
}

var foo = {
    [Symbol.iterator]: createGenerator()
};

function *fib_gen(maxLen = 10){
    var memory = {0: 1, 1: 1};
    for(let i = 0; i <= maxLen; i++){
        if(i in memory) yield memory[i];
        else yield memory[i] = memory[i - 1] + memory[i - 2];
    }
}

var foo = {
    [Symbol.iterator]: () => fib_gen(5)
}

// for(let f of foo)
//     console.log(f)

// function getLastProto(o){ 
//     var p = o;
//     do{
//         o = p;
//         p = Object.getPrototypeOf(o);
//     } while(p);

//     return o;
// }

var getLastProto = (o) => {
    var p = Object.getPrototypeOf(o)
    while(p){
        o = p; 
        p = Object.getPrototypeOf(o)
    }

    return o
}

let person = {
    age: 6,
    foo: function(){
        console.log(this.age);
    }
};

let car = {
    color: 'black',
    foo: function(x){
        return x;
    }
};

const arr = [1, 2, 3]
const set = new Set()
const map = new Map()

// console.log(getLastProto(person) == Object.prototype)
// console.log(getLastProto(car) == Object.prototype)
// console.log(getLastProto(arr) == Object.prototype)
// console.log(getLastProto(set) == Object.prototype)
// console.log(getLastProto(map) == Object.prototype)
// console.log(getLastProto({}) == Object.prototype)

// tworzenie własnych prototypwó
function Person (name, age) {
    this.name = name;
    this.age = age;
}

// dodanie metody do prototypu
Person.prototype.sayHello = function() {
    console.log(`Hi ${this.name}`);
};

// tworzenie instancji o protytypie person
const kuba = new Person('kuba', 25);
// kuba.sayHello(); // Hi kuba

// console.log(Object.getPrototypeOf(kuba) === Person.prototype) // true
