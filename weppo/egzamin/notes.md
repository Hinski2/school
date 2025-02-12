# Notatki pod egzamin

--- 

# Moduły

### komendy do npm:
* `npm init -y` - tworzy package.json
* `npm install express` - instaluje expres
* `npm -g nodemon` - instaluje globalnie nodemon
* `npm install` - instaluje zależności z package.json
* `npm update` - aktualizuje zależności 
* `npm run x` - włącza skrypt x 

### inne komendy
* `node app.js` - uruchamia program
* `node --watch app.js` - monitoruje zmiany w pliku i automatycznie restartuje skrypt po ich wykryciu
* `tsc --init` - tworzy plik niezbędny do uruchamainia tsc (jak skompikujemy ts -> js to nie jest wymagany)
* `tsc app.ts` - kompiluje app.ts do app.js (tworzy plik)
* `ts-node app.ts` - niejawnie kompiluje i uruchamia app.ts (nie tworzy pliku app.js)

### package.json:
``` js
{
  "name": "test0",
  "version": "1.0.0",
  "main": "index.js",                                           
  "scripts": {                                                  // tu dodajemy własne skrypty
    "test": "echo \"Error: no test specified\" && exit 1"
  },
  "keywords": [],
  "author": "",
  "license": "ISC",
  "description": ""
}
```

---

# ES modules vs commonJS
| es | commonJS |
| --- | --- | 
| fajniejszy| mniej fajny |
| używaliśmy w projekcie | nie używaliśmy |
| używa import | używa require |
| używa export {} | używa module.exports = {}

importy
``` js
// commonJS
const fs = require('fs')
const myModule = require('./myModule')

// ES
import fs from 'fs';
import myModule from './myModule.js'; 
```

eksporty
``` js
// commonJS
module.exports = {add, multiply}

//ES
export {add, multiply}
```

---

# Podstawowe struktury i działania na nich

### tworzenie tablic
``` js
var a = Array(10).map((val, idx) => idx) // nie zadziałą poprawnie bo elementy nie za zainicjowane
var b = [...Array(10)].map((val, idx) => idx + 1)   // zadziała, jeśli mamy empty value i rozpakujemy wartość to dostaniemu undefined
var c = Array(10).fill(0).map((val, idx) => idx + 1) // zadziała
```

### działania na tablicach 
``` js 
// .map((val, idx) => new_val)
var c = Array(10).fill(0).map((val, idx) => idx + 1)
var a = Array(100).fill(0).map((val, idx) => foo(idx + 1));

// .filter((val, idx) => jeśli true wartość zachowywana, jeśli false nie)
var a = Array(100).fill(0).map((val, idx) => idx + 1).filter((val, idx) => val % 2 == 0 ? true : false)

// .forEach((val) => coś)
var a = Array(10).fill(0).map((val, idx) => idx + 1).forEach((val) => console.log(val))

// .reduceRight((acc, cur) => acc2)
var a = Array(10).fill(0).map((val, idx) => idx + 1).reduceRight((acc, cur) => acc + cur);

//array.splice
array.splice(start, deleteNo, item1, item2, .. itemn)
    start := indeks początkowy
    deleteNo (opcjonalny) :=
        * 0 - nic nie zostanie usunięte
        * n - n elementów zostanie usuniętych
        * pominiętny paramter - zostaną usunięte wszystkie elementy od start do końca
    itemx (opcjonalny) := elementy do dodania 
```

### funkcje
``` js
var foo = (x) => {
    let sum = 0;
    for(; x; x = Math.floor(x / 10)){
        sum += x % 10;
    }
}

function sum(x){
    let sum = 0;
    for(; x; x = Math.floor(x / 10)){
        sum += x % 10;
    }

    return sum;
}

var f = (x) => {
    if(x == 0) return 0;
    else if(x == 1) return 1;
    return f(x - 1) + f(x - 2);
}
```
``` js
// funkcje ze zmienną ilością argumentów 
var sum = (...args) => {
    let sum = 0
    for(let u of args)
        sum += u;
    return sum;
}
// poprawne wywołanie
var x= [1,2,3,4,5]
sum(...x)

```

``` js
/*
    Foo(): funkcja 
    Bar(): publiczna metoda prototypu Foo
    Qux(): funkcja prywatna którą możemy zawołać tylko z wewnątrz Bar 

    chcemy używać 
*/

const Foo = (() => {
    function Qux(){
        console.log("wywołanie Qux")
    }

    function Foo(){ // konstruktor Foo
    }
    
    Foo.prototype.Bar = function() {
        Qux();
    }

    return Foo // zwracam konstruktor Foo
})();

const foo = new Foo();
foo.Bar() // działa 
foo.Qux() // błąd 
```

### memoryzacja
```js
function fibo(n){
    if(n == 1) return 0;
    else if(n == 2) return 1;
    return fibo_mem(n - 1) + fibo_mem(n - 2); // ważne by tutaj nie użyć fibo, tylko fibo_mem
}

function memorize(fn){
    var cache = {};
    return function(n){
        if(n in cache) return cache[n];
        else return cache[n] = fn(n);
    }
}

var fibo_mem = memorize(fibo);
console.log(fibo_mem(50))
```

### `==` vs `===`
Operator `==` sprawdza tylko wartość, ale jeśli typy są różne, JavaScript próbuje je przekonwertować
Operator `===` sprawdza zarówno wartość, jak i typ.

### stringi
``` js
    var s = '11' + 21; // 1121
    var s = 21 + '11'; // 2111
    s.length // 4
```

### obiekty i prototypy
``` js
var person = {
    name: "kuba", 
    age: 19,
    1: 10
}

console.log(person['name'], person['age'], person['1'])
console.log(person.name, person.age) // nie da się pesron.1

// dodanie nowej wartości
person.surname = 'Iliński'; // { '1': 10, name: 'kuba', age: 19, surname: 'Iliński' }
```

Pola i medoty można dodać przez przypisanie i przy użyciu defineProperty
Własnosci można dodać tylko przez defineProperty

``` js
let person = {
    name: "Kuba",   // pole 
    _age: 19,       // własność

    // metoda
    display_name: function(){
        console.log(this.name)
    },

    // akcesory
    get age(){
        return this._age;
    },

    set age(new_age){
        this._age = new_age;
    }
}

person._height = 178;               // dodanie nowej właności
person.display_age = function(){    // dodanie noew moteody
    console.log(this._age)
};

Object.defineProperty(person, 'height', { // dodanie akcesorów
    get: function() {
        return this._height;
    }, 
    set: function(new_height) {
        this._height = new_height
    }
})

person.display_age()
person.age = 20
person.display_age()
```

każdy obiekt dziedziczy z Object.prototype. czyli na samym końcu łańcuch prototypów jest Object.prototype
``` js
var getLastProto = (o) => {
    var p = Object.getPrototypeOf(o)
    while(p){
        o = p; 
        p = Object.getPrototypeOf(o)
    }

    return o
}

const set = new Set()
console.log(getLastProto(set) == Object.prototype) // true
```

przydatne metody dla obiektów:
``` js
Object.keys(o) // zwraca klucze obiektu o

Object.getPrototypeOf(o) // zwraca prototyp obiektu o

function belongs_to_object(o, f){ // sprawdzanie czy obiekt zawiera klucz f 
    return Object.keys(o).includes(f)
}

// ustawianie prototypu programera na person 
let person = {
    age: 6,
    foo: function(){
        console.log(this.age);
    }
};

let programmer = {
    name: 'kuba',
    lvl: 'tech-lead'
}

Object.setPrototypeOf(programmer, person)
```
W js każdy obiekt ma prototyp czyli 'rodzica' od którego może dziedziczyć własności i metody
`setPrototypeOf(a, b)` - dynamicznie zmienia prototyp już istniejącego obiektu a na b

``` js
// tworzenie własnych prototypów
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
kuba.sayHello(); // Hi kuba

console.log(Object.getPrototypeOf(kuba) === Person.prototype) // true

// ustawianie prototypu dla prototypu
var Person = function(name, surname) {
    this.name = name;
    this.surname = surname;
}
 
var Worker = function(name, surname, age) {
    Person.call( this, name, surname );
    this.age = age;
}

Worker.prototype = Object.create(Person.prototype);

// obiekt
var worker = new Worker('kuba', 'iliński', 19);
console.log()
```

#### `Object.create(P.prototype)` vs `setPrototypeOf(a, b)`
``` js
    Worker.prototype = Object.create(Person.prototype); // tutaj zmieniamy prototyp dla prototypu
    Object.setPrototypeOf(programmer, person) // tutaj zmieniamy prototyp dla już istniejącego obiektu  (robimy to dynamicznie)
```

#### typy podstawowe a obiekty
typy podstawowe nie są obiektami, ale czasami na chwile mogą się zmieniać w obiekty 
``` js
var n = 1;
n.foo = 'foo'; // chwilowa zamiana w obiekt, ale w następnej linijce n nie jest obiektem więc traci pole foo
console.log(n.foo) // undefined
```
### IIFE
``` js
function createFs(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( let i=0; i<n; i++ ) {
        fs[i] =
            function() {
                return i;
            };
    };
    return fs;
}
var myfs = createFs(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );
// 10 10 10 // ale wszystkie zwracają 10!?

// możemy to naprawić przy użyciu iife
function createFs(n) { 
    var fs = []; // 
    for ( var i=0; i<n; i++ ) {
        ((x) => {
            fs[x] =
                function() {
                    return x;
                };
        })(i);
    };
    return fs;
}
```

---

# Iteratory i Generatory

### iterator
``` js
function createGenerator() {
    var _state = 0;
    return {
        next: function() {
            return {
                value: _state,
                done: _state++ >= 10
            }
        }
    }
}

var foo = {
    [Symbol.iterator]: createGenerator
};

for(let u of foo)
    console.log(u)
```

### iterator z ograniczeniem górnym
``` js

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

// lub też działa
function createGenerator(maxLen=12) {
    var _state = 0;
    return () => { return {
        next: function() {
            return {
                value: _state,
                done: _state++ > maxLen
            }
        }
    }}
}

var foo = {
    [Symbol.iterator]: createGenerator()
};

for(let u of foo)
    console.log(u)
```

### generator
``` js
function *fib_gen(){
    var memory = {0: 1, 1: 1};
    for(let i = 0;; i++){
        if(i in memory) yield memory[i];
        else yield memory[i] = memory[i - 1] + memory[i - 2];
    }
}

var foo = {
    [Symbol.iterator]: fib_gen
}

for(let f of foo)
    console.log(f)
```

### generator z ograniczeniem górnym
``` js
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

for(let f of foo)
    console.log(f)
```
---

# TSC
memoryzacja fibo w tsc
``` js
function memorize(fn: (n : number) => number): (n: number) => number{
    const cache: Record<number, number> = {};
    return function(n: number): number{
        if(n in cache) return cache[n];
        return cache[n] = fn(n);
    }
}

function fibo_rec(n: number): number {
    if(n == 1) return 1;
    if(n == 2) return 1;
    return fibo_mem(n - 1) + fibo_mem(n - 2);
}

let fibo_mem = memorize(fibo_rec);
console.log(fibo_mem(5))


// inne podejście
let fibo_mem = (() => {
    let mem: Record<number, number> = {1: 1, 2: 1};

    return (n: number): number => {
        if(n in mem) return mem[n];
        return mem[n] = fibo_mem(n - 1) + fibo_mem(n - 2);
    }
})();

console.log(fibo_mem(500))
```

typy genetyczne
``` js
function filter<T>(arr: T[], f: (n: T) => boolean): T[] {
    let ans: T[] = [];
    for(let u of arr)
        if(f(u)) ans.push(u);

    return ans;
}

function map<T, K>(arr: T[], f: (n: T) => K): K[] {
    let ans = new Array<K>();
    for(let i in arr)
        ans[i] = f(arr[i]);

    return ans;
}

function for_each<T>(a: T[], f:(t: T) => void): void {
    for(let u of a)
        f(u)
}

let x = filter([1, 3, 4, 5, 2], (n: number): boolean => (n % 2 == 0));
let y = map([1, 3, 4, 5, 2], (n: number): boolean => n % 2 == 0);
console.log(y)
```

zawężanie typów
``` js
type User = {
    name: string;
    age: number;
    occupation: string;
}

type Admin = {
    name: string;
    age: number;
    role: string;
}

export type Person = User | Admin;

export const persons: Person[] = [
    {
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];

function logPerson(person: Person){
    let additionalInformation: string;

    if('role' in person){   // w tym meijscu sprawdzamy czy person ma klucz 'role' jeśli tak to musi to by Admin
        additionalInformation = person.role;
    } 
    else { // jeśli nie ma to musi to być User
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

logPerson(persons[0]);
logPerson(persons[1]);
```

strażnicy typów 
``` js
type User = {
    type: 'User'; // dodajemy dodatkowe infor
    name: string;
    age: number;
    occupation: string;
}


type Admin = {
    type: 'Admin' // dodajemy dodtakowe info
    name: string;
    age: number;
    role: string;
}

export type Person = User | Admin;

function isUser(p: Person){ // strażnik typu - mówi nam czy dany obiekt ma taki typ
    return p.type === 'User';
}

function isAdmin(p: Person){
    return p.type === 'Admin';
}

export const persons: Person[] = [
    {
        type: 'User',
        name: 'Jan Kowalski',
        age: 17,
        occupation: 'Student'
    },
    {
        type: 'Admin',
        name: 'Tomasz Malinowski',
        age: 20,
        role: 'Administrator'
    }
];

function logPerson(person: Person){
    let additionalInformation: string;

    if(isAdmin(person)){ // sprawdzamy cze person jest adminem
        additionalInformation = person.role;
    } 
    else { 
        additionalInformation = person.occupation;
    }
    console.log(` - ${person.name}, ${person.age}, ${additionalInformation}`);
}

logPerson(persons[0]);
logPerson(persons[1]);
```

mechanizmy systemów typów
``` js 
// Extract vs Pick
// Extract 
    //  jest do uni typów
    // np type MyUnion = number | string 

// Pick 
    //jest do struktur obiektowych
    // np type Person = {...}

    /*
    Extract, Exclude:
        * Extract<Keys, Keys>: z zadanej uni typowej zwraca wskazane elementy
        * Exclude<Keys, Keys>: z zadanej uni typowej wyrzuca wskazane elementy

    */

type MyUnion = 'a' | 'b' | 'c' | 'd' | 'e';

type Extracted = Extract<MyUnion, 'a' | 'd'> // a, d
type Excluded = Exclude<MyUnion, 'a' | 'd'>  // b, c, e

    /*
    Record, Required, Readonly, Partial:
        * Partial<T>: konstruuje z zadanego typu typ, który ma wszystkie składowe opcjonalne
        * Required<T>: pokstruuje z zadanego typu typ, który ma wszystkieskładowe wymagane
        * Readonly<T>: Konstruuje z zadanego typu typ, który ma wszystkie składowe tylko do odczytu 
        * Record<Keys, T>: Konstuuje typ z zadanyhc kluczy i typu wartości
    */

type Person2 = {
    name: string; 
    age: number; 
    occupation: string;
}
type PartialPerson2 = Partial<Person2>;
//  {
//      name?: string;
//      age?: number;
//      occupation?: string;
//  }

type Person3 = {
  name?: string;
  age?: number;
  occupation?: string;
};
type RequiredPerson3 = Required<Person3>;
//  {
//      name: string;
//      age: number;
//      occupation: string;
//  }

type Person4 = {
  name: string;
  age: number;
  occupation: string;
};
type ReadonlyPerson4 = Readonly<Person4>;
// {
//   readonly name: string;
//   readonly age: number;
//   readonly occupation: string;
// }

type Role = 'admin' | 'user'
type Permission = Record<Role, boolean>
// {
//   admin: boolean;
//   user: boolean;
// }

    /*
    Pick, Omit
        * Pick<T, Keys>: Z zadanego typu struktury zwraca podtyp ze wskazanych kluczy 
        * Omit<T, Keys>: Z zadanego typu struktury zwraca podtyp z wyrzuconymi wskazanymi kluczami 
    */

type Person5 = {
    name: string;
    age: number;
    occupation: string;
};

type PickPerson5 = Pick<Person5, "name" | "age">;
//  {
//      name: string
//      age: number
//  }    

type OmitPerson5 = Omit<Person5, "occupation">;
//  {
//      name: string
//      age: number
//  } 

    /*
    Index Acess Types
        * pozwalają na dostęp do typu wartości, która jest przypisana do konkretnego klucza w danym typu obiketu
        * podobne do indeksowania w obiektach, ale zamiast wartości dostajemy typ
    */

type Person = {
    name: string; 
    age: number; 
    occupation: string;
}

let p: Person = {name: "kuba", age: 19, occupation: "programmer"};

type NameType = Person['name'];             // typ: string 
type AgeTyep = Person['age'];               // typ: number
type OccupationType = Person['occupation']  // typ: string


// bezpierczniejsza opcja
function readKey<K extends keyof Person>(person: Person, person_field: K): Person[K] {
    return person[person_field]
}

// podczas kompulacji dostaniemy string
// podczas wykonywania dostaniemy 'programmer'
console.log(readKey(p, 'occupation'))


```

---

# Express
server.js:
``` js
const express = require('express')
const path = require('path')
const app = express()

// set permissions
app.use(express.static(path.join(__dirname, 'public')))     // enables using static files 
app.use(express.urlencoded({extended: true}))               // enables to read from forms 

app.set('view engine', 'ejs') 

const userRouter = require('./routers/user')
app.use('/user', userRouter)

app.listen(3000)
```

routes/user.js
``` js
const express = require('express')
const router = express.Router()

router.get('/new', (req, res) =>{
    res.render('./../views/form/new.ejs');
})

router.post('/res', (req, res) => {
    const {firstName, lastName, subject, tasks} = req.body;
    let selectedTasks = [];
    if(tasks){
        if(Array.isArray(tasks)) selectedTasks = tasks
        else selectedTasks = [tasks]
    }

    res.render('./../views/form/print.ejs', {
        firstName, 
        lastName,
        subject,
        tasks: selectedTasks
    })
})

module.exports = router
```

---

# Inne 
### instanceof i typeof
`typeof`:
* zwraca typ podstawowy zmiennej 
* typy podstawowo: string, number, boolean, undefind, object, funciton
    
`instanceof`:
* sprawdza czy obiekt jest instacją określonej klasy
* zwraca true albo false

```js
console.log(typeof 'hello')  // string
console.log(typeof 42)       // number
console.log(typeof {})       // object

const arr = new Array()
console.log(arr instanceof Array)   // true
console.log(arr instanceof Map)     // false
console.log(arr instanceof Object)  // false
```

### input
``` js
async function getInput(){
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    return new Promise((resolve, reject) => {
        rl.question('input your name: ', (userInput) => {
            rl.close();
            resolve(userInput);
        });
    });
}

(async function main(){
    try{
        const user_input = await getInput();
        console.log(`witaj ${user_input}`);
    } catch (e) {
        console.log(e)
    };

})()
```
``` js
async function getInput(){
    const rl = readline.createInterface({
        input: process.stdin,
        output: process.stdout,
    });

    return new Promise((resolve, reject) => {
        rl.question('input your guess: ', (user_input) => {
            rl.close();
            try{
                if(isNaN(parseFloat(user_input)))
                    throw 'not valid number'

                let user_number = Number(user_input)
                resolve(user_number);
            }
            catch(error){
                console.log(error)
                return resolve((async() => await getInput())())
            }
        });
    });
}
```

### reading
``` js
// how to read file 
const fs = require('fs')

async function readfile(path){
    try{
        const file = await fs.promises.readFile(path, 'utf8');
        console.log(file);
    }
    catch(error){
        console.log('ERROR:', error);
    }
}

readfile('./file_to_read.txt');
```
``` js
// how to read big files line by line 
const fs = require('fs')
const rl = require('readline')

function parse_file(path){
    let data = new Map();
    return new Promise((resolve, reject) => {
        const fileStream = fs.createReadStream(path);
        const readline = rl.createInterface({
            input: fileStream 
        });

        readline.on('line', (line) => {
            let ip = line.split(' ')[1];
            if(data.has(ip))
                data.set(ip, data.get(ip) + 1);
            else 
                data.set(ip, 1);
        });

        readline.on('close', () => {
            resolve(data);   
        });

        readline.on('error', (err) => {
            reject(err);
        });
        
        fileStream.on('error', (err) => {
            reject(err);
        });
    });
}
```
``` js
// how to read site
function get_site_content(url){
    return new Promise((resolve, reject) => {
        https.get(url, (resp) => {
            let data = '';

            resp.on('data', (chunk) => { // zdarzenie data
                data += chunk;
            })

            resp.on('end', () => {
                resolve(data)
            })

            resp.on('error', (error) => {
                reject(error)
            })
        });
    });
}
```