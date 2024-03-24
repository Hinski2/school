type 'v nnf =
    | NNFLit of bool * 'v
    | NNFConj of 'v nnf * 'v nnf
    | NNFDisj of 'v nnf * 'v nnf
;;

let rec neg_nnf = function
    | NNFLit (b, v) -> NNFLit (not b, v)
    | NNFConj (a, b) -> NNFDisj (neg_nnf a, neg_nnf b)
    | NNFDisj (a, b) -> NNFConj (neg_nnf a, neg_nnf b)
;;

(* wytłumaczenie zmiany NNFConj -> NNFDisj *)
(* ~(a and b) -> ~a or ~b *)
(* ~(a or b) -> ~a and ~b *)

(* dowód poprawności*)
(* 
    Podstawa indukcji:
        Cel: pokazać, że neg_nnf (neg_nnf φ) ≡ φ
        dla: φ będącego literałem

        L = 
        = neg_nnf ( neg_nnf φ ) = { z def neg_nnf } =
        = neg_nnf (not φ) = { z def neg_nnf } =
        = not (not φ) = { z logiki } =
        = φ = R

    Krok indukcyjny:
        zał: zachodzi neg_nnf (neg_nnf f1) = f1
        zał: zachodzi neg_nnf (neg_nnf f2) = f2
        cel1: pokazać że neg_nnf (neg_nnf (f1 and f2)) = f1 and f2
        cel2: pokazać że neg_nnf (neg_nnf (f1 or f2)) = f1 or f2

        cel1:
            L =
            = neg_nnf (neg_nnf (f1 and f2)) = { z def } = 
            = neg_nnf (!f1 or !f2) = {z def} =
            = f1 and f2 = R
        
        cel2:
            L =
            = neg_nnf (neg_nnf (f1 or f2)) = { z def } = 
            = neg_nnf (!f1 and !f2) = {z def} =
            = f1 or f2 = R
    
    Wniosek:
        neg_nnf (neg_nnf φ) ≡ φ dla dowolnej formuły φ
*)