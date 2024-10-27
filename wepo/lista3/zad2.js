function forEach( a, f ) {
    for(let u of a)
        f(u)
}

function map( a, f ) {
    let res = [];
    for(let [idx, val] of a.entries())
        res[idx] = f(val);
    return res;
}

function filter( a, f ) {
    let res = [];
    for(let [idx, val] of a.entries())
        if(f(val)) res[idx] = val;
    return res;
}

var a = [1,2,3,4];
forEach( a, b => { console.log( b ); } );
forEach( a, function(b){ console.log( b ) } );
console.log();
// [1,2,3,4]

console.log(filter( a, b => b < 3 ));
console.log(filter( a, function(b){ return b < 3}));
console.log();
// [1,2]

console.log(map( a, b => b * 2 ));
console.log(map( a, function(b){return b * 2} ));
console.log();
// [2,4,6,8]
    