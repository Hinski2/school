var n = 1;

console.log(Object.getPrototypeOf(n))
console.log(typeof Object.getPrototypeOf(n)) // Object

n.foo = 'foo'; // chwilowa zamiana w obiekt, ale w następnej linijce n nie jest obiektem więc traci pole foo
console.log(n.foo) // undefined

/*
    mimio że dostajemy Object w 4 linijce, to typy podsatwowe w js nie są obiektami. Dostaliśmy taką odpowiedz
    bo w js istnieje takie coś jak autoboxing, czyli opakowywanie typów podstawowych na moment w klase, dzięki temu
    dostajemy dostęp do dodtkowych metod.
    Dostajemy undefine, bo typy podtawowe to nei obiekty. 
*/

