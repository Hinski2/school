function createGenerator(max=12) {
    return function(){ // jak mamy createGenerator(), a nie createGenerator to zwracamy obiekt iteratora a nie funkcje, a my chcemy tak jak wcześniej funkcje
        var _state = 0;
        return {
            next : function() {
                return {
                    value : _state,
                    done : _state++ >= max //dodanie limitu
                }
            }
        }
    }
}
// createGenerator() zwraca funkcje która po wywołaniu createGenerator()() dostarcza iterator 
var foo1 = {
    [Symbol.iterator]: createGenerator()
}
var foo2 = {
    [Symbol.iterator]: createGenerator()
}
var foo3 = {
    [Symbol.iterator]: createGenerator(5)
};

for ( var f of foo1 )
    console.log(f);
console.log()

for ( var f of foo2 )
    console.log(f);
console.log()

for ( var f of foo3 )
    console.log(f);
console.log()
    
console.log(createGenerator)                            // funkcja: createGenerator
console.log(createGenerator())                          // funkcja (anonimowa)
console.log(createGenerator()())                        // obiekt 
console.log(createGenerator()().next)                   // metoda next  
console.log(createGenerator()().next())                 // obiekt 
console.log(createGenerator()().next().value)           // wartość 0 