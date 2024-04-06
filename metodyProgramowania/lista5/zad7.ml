type 'v formula =
    | Var of 'v
    | Neg of 'v formula
    | Conj of 'v formula * 'v formula
    | Disj of 'v formula * 'v formula

type 'v nnf =
    | NNFLit of bool * 'v
    | NNFConj of 'v nnf * 'v nnf
    | NNFDisj of 'v nnf * 'v nnf
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

let rec eval_nnf sigma = function
    | NNFLit (b, v) -> if b then not (sigma v) else sigma v
    | NNFConj (a, b) -> eval_nnf sigma a && eval_nnf sigma b
    | NNFDisj (a, b) -> eval_nnf sigma a || eval_nnf sigma b
;;

let rec eval_formula sigma = function
    | Var v -> sigma v
    | Neg f -> not (eval_formula sigma f)
    | Conj (a, b) -> (eval_formula sigma a) && (eval_formula sigma b)
    | Disj (a, b) -> (eval_formula sigma a) || (eval_formula sigma b)

(* dowód dla eval_nnf σ (to_nnf φ) ≡ eval_formula σ φ *)
(* 
    krok indukcyjny:
        dla: fi będącego zmienną znadiową
        cel: pokazać eval_nnf σ (to_nnf φ) ≡ eval_formula σ φ

        L =
        = eval_nnf sigma (to_nnf fi) = { z def to nnf } =
        = eval_nnf sigma fi

*)


