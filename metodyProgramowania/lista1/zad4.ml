let max1 a b c = 
  if a >= b && a >= c then a
  else if b >= a && b >= c then b
  else c
let max2 a b c = 
  if b >= a && a >= c || c >= a && a >= b then a
  else if a >= b && b >= c || c >= b && b >= a then b
  else c

let suma_kwadratow a b c = let x = max1 a b c and 
  y = max2 a b c in let sk = fun i j -> i * i + j * j in sk x y;;

print_int (suma_kwadratow 1 2 3)