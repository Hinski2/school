type 'v formula =
    | Var of 'v
    | Neg of 'v formula
    | Conj of 'v formula * 'v formula
    | Disj of 'v formula * 'v formula
;;

let zaneguj = function
    | Var v -> Neg (Var v)  (*tego przypadku nie dostane*)
    | Neg f -> f
    | Conj (a, b) -> Disj (Neg a, Neg b)
    | Disj (a, b) -> Conj (Neg a, Neg b)


let rec to_nnf = function
    | Var v -> Var v
    | Neg (Var v) -> Neg (Var v)

    | Neg f -> to_nnf (zaneguj f)
    | Conj (a, b) -> Conj(to_nnf a, to_nnf b)
    | Disj (a, b) -> Disj(to_nnf a, to_nnf b)