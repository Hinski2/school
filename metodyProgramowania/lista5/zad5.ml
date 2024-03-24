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

let rec eval_nnf sigma = function
    | NNFLit (b, v) -> if b then not (sigma v) else sigma v
    | NNFConj (a, b) -> eval_nnf sigma a && eval_nnf sigma b
    | NNFDisj (a, b) -> eval_nnf sigma a || eval_nnf sigma b
;;

(* dowód: dla dowolnej formuły φ i wartościowania σ zachodzi eval_nnf σ (neg_nnf φ) ≡ not (eval_nnf σ φ) *)
(* 
    Podstawa indukcji:
        dla: fi będącego literałem postaci NNFLit (b, v)
        cel: pokazać że eval_nnf sig (neg_nnf fi) ≡ not (eval_nnf sig fi)

        L =
        = eval_nnf sig (neg_nnf NNFlit(b, v)) = { z def neg_nnf } =
        = eval_nnf sig NNFlit(not b, v) = { z def eval_nnf } = 
        = if (not b) then not (sigma v) else sigma v = {logika} =
        = if b then sigma v else (not sigma v) = 

        R = 
        = not (eval_nnf sigma fi) = { z def eval_nnf }
        = not (if b then not (sigma v) else sigma v) = { logika } = 
        = if b then sigma v else (not sigma v)

        L = R

    Krok indukcyjny:
        zakł: eval_nnf sig (neg_nnf f1) ≡ not (eval_nnf sig f1)
        zakł: eval_nnf sig (neg_nnf f2) ≡ not (eval_nnf sig f2)
        cel1: eval_nnf sig (neg_nnf NNFConj(f1, f2) = not (eval_nnf sig NNFConj(f1, f2))
        cel1: eval_nnf sig (neg_nnf NNFDisj(f1, f2) = not (eval_nnf sig NNFDisj(f1, f2))

        cel1:
            L = 
            = eval_nnf sig (neg_nnf NNFConj(f1, f2)) = { z def NNFConj } =
            = eval_nnf sig (neg_nnf (eval_nnf sig f1 && eval_nnf sig f2)) = { z def neg_nnf } =
            = eval_nnf sig (NNFDisj (neg_nnf f1, neg_nnf f2)) = { z def eval_nnf } =
            = eval_nnf sig !f1 || eval_nnf sig !f2

            R = 
            = not (eval_nnf sig NNFConj(f1, f2) = { z def eval_nnf } = 
            = not (eval_nnf sig f1 && eval_nnf sig f2) = { logika } = 
            = eval_nnf sig !f1 || eval_nnf sig !f2

            L = R
        
        cel2:
            tak samo jak poprzedio
*)
