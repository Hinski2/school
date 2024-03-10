let rec foldl f acc = function
| [] -> acc
| head::tail -> foldl f (f acc head) tail;;

let product xs = foldl (fun acc x -> acc * x) 1 xs;;

