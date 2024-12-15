function filter<T>(a: T[], f: (t: T) => boolean): T[] { // typy generyczne 
    let result = new Array<T>()
    for(let u of a){
        if(f(u)) result.push(u)
    }
    return result
}

function map<T, U>(a: T[], f: (t: T) => U): U[] {
    let result = new Array<U>() 
    for(let u of a){
        result.push(f(u))
    }
    return result
}

function for_each<T>(a: T[], f:(t: T) => void): void {
    for(let u of a)
        f(u)
}

let arr1: number[] = [1, 2, 2, 3, 4]
let arr2: string[] = ['a', 'b', 'c']

console.log(filter(arr1, (u: number) => u > 2))
console.log(filter(arr2, (u: string) => u > 'a'))

console.log(map(arr1, (u: number) => u * 2))

for_each(arr1, (u: number) => console.log(u))