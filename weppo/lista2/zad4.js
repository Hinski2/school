/*
    typeof vs instanceof
    
    typeof:
        * zwraca typ podstawowy zmiennej 
        * typy podstawowo: string, number, boolean, undefind, object, funciton
    
    instanceof:
        * sprawdza czy obiekt jest instacją określonej klasy
        * zwraca true albo false
*/

console.log(typeof 'hello')  // string
console.log(typeof 42)       // number
console.log(typeof {})       // object

const arr = new Array()
console.log(arr instanceof Array)   // true
console.log(arr instanceof Map)     // false
console.log(arr instanceof Object)  // false