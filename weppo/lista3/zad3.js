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

/*
    opcja 1: zastąpienie var w 3 linijce let
    dlaczego działa:
        * var jest zakresu funkcyjnego nie blokowego 
        * każda funkcja zamyka się na to samo i
        * ostateczna wartosć i to 10 więc w wyniku dostajemy same 10
        
    opcja 2: użycie iife (natychmiastowego wywołania funcji)
    działa bo:
        * od razu inicjalizuje funkcje z danym i 
        * iife pozwala na wprowadzenie nowego zakresu i symulacje zakresu blokowego 

*/

function createFs2(n) { // tworzy tablicę n funkcji
    var fs = []; // i-ta funkcja z tablicy ma zwrócić i
    for ( var i=0; i<n; i++ ) {
        (function(j){
            fs[j] =
                function() {
                    return j;
                };
            }
        )(i);
    };
    return fs;
}

console.log()
var myfs = createFs2(10);
console.log( myfs[0]() ); // zerowa funkcja miała zwrócić 0
console.log( myfs[2]() ); // druga miała zwrócić 2
console.log( myfs[7]() );