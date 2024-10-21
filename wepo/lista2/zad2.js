/*
    operator . vs [] w obiektach
        ? różnice:
            . nazwy nie mogą mieć w sobie spacji i zaczynać się od cyfr
            [] nazwy moga mieć spacje i zaczyać się od cyfr 
*/

let person = {
    name: "Kuba",
    age: 19,
    1: 10,
    '[object Object]': 'XD'
}

console.log(person['name'], person['age'], person['1'])
console.log(person.name, person.age) // nie da się pesron.1

/*
    użycie nie stringa jako argumentu w [] w obiektach 
        ? argument: liczba
            nie ma znaczenie kod jest konwertowany na string
        ? argument: inny obkiet 
            zmnienia nazwe obiektu na object Object niezależnie od nazwy
        ? jaki wpływ na klucz ma programista
            sami sobie go usatawiamy
*/

let obiekt = {
    name: 'Json'
}

console.log()
console.log(person[1], person['1'])
console.log(person[obiekt], person['obiekt'])

/*
    użycie argumnetu !: number dla [] w tablicy
        ? co jeśli argumentem jest napis
            arr[x] działa jak arr['x'] jeśli x jest liczbą
        ? co jeśli argumentem jest inny obiekt
            tak samo jak w przypadku obiektu 
        ? Czy i jak zmienia się zawartość tablicy jeśli zostanie do niej dopisana właściwość pod kluczem, który nie jest liczbą
            dopisuje jako osobne pole tablicy na skońcu obiektu 
        ? czy można zmienić lenght tablicy na mniejszy/większy i co wtedy się dzieje z tablicą 
            tak: zmniejszamy lub zwiększamy tablice 
*/


var arr = [5, 4, 3, 2, 1, 0]

console.log()
console.log(arr['0'], arr['5'], arr['a'])
console.log(arr[obiekt], obiekt.toString()) // zaminenia na object object 

arr['a'] = 5;
console.log(arr) //zmiana pod kluczemk który nie jest liczba
console.log(arr['a'])

arr.length = 3
console.log(arr)
arr.length = 4
console.log(arr)
