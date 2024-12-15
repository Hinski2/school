//! poprawnie
// dzieki temu podejściu:
//      * unikamy wywołania konstruktora
//      * jesteśmy dodawać metody do Worker.prototype bez wpływania na Person.prototype
//      * 
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

//! niepoprawnie
// złe bo Worker.prototype i Person.prototype wskazują na ten sam obiekt, więc wszystkie zmiany w Worker prototype wpływają
// na Person.proototype
var Person = function(name, surname) {
    this.name = name;
    this.surname = surname;
}
 
var Worker = function(name, surname, age) {
    Person.call( this, name, surname );
    this.age = age;
}

Worker.prototype = Person.prototype;

var worker = new Worker('kuba', 'iliński', 19);
Worker.prototype.sayHello = function() {
    console.log('hello worker');
}

var person = new Person('jakub', 'ilin');
person.sayHello()
console.log()

//! niepoprawnie
// niepoprawne, bo wywołujemy konstruktor więc:
//      * tworzenie instancji może być czasochłonne
//      * jeśli konstruktor Person() robi jakieś dodatwowe operacje np logowanie to użycie new Pesron() spowoduje ich wywołanie
//      * Worker.propttype będzie zawierał własności zainicjalizowane przez konstruktor Person

var Person = function(name, surname) {
    this.name = name;
    this.surname = surname;
}
 
var Worker = function(name, surname, age) {
    Person.call( this, name, surname );
    this.age = age;
}

Worker.prototype = new Person();
console.log(Worker.prototype.name) // undefined bo wywołujemy konstruktor Person() bez argumentów 
console.log(Worker.prototype.surname)




