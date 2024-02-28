let sum = fun x y -> x + y;;
let diff = fun x y -> x - y;;
let div = fun x y -> x / y;;
let mult = fun x y -> x * y;;

let calculator x y f = f x y;;
print_int (calculator 1 2 mult)