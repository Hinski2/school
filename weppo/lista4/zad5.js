/*
    Foo(): funkcja 
    Bar(): publiczna metoda prototypu Foo
    Qux(): funkcja prywatna którą możemy zawołać tylko z wewnątrz Bar 
*/

// korzystam z wskazówki i używam domknięcia
const Foo = (function(){
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
foo.Bar()
foo.Qux()
