// funkcja z wykładu zwracający ostatni prototyp obiektu o
function getLastProto(o){ 
    var p = o;
    do{
        o = p;
        p = Object.getPrototypeOf(o);
    } while(p);

    return o;
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

console.log(getLastProto(person) == Object.prototype)
console.log(getLastProto(car) == Object.prototype)
console.log(getLastProto(arr) == Object.prototype)
console.log(getLastProto(set) == Object.prototype)
console.log(getLastProto(map) == Object.prototype)
console.log(getLastProto({}) == Object.prototype)
        

