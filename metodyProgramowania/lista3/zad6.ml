type 'a tree = 
    | Leaf
    | Node of 'a tree * 'a * 'a tree;;
let t =
    Node (Node (Leaf, 2, Leaf),
    5,
    Node (Node (Leaf, 6, Leaf),
    8,
    Node (Leaf, 9, Leaf)));;

let rec fold_tree f a t =
    match t with
    | Leaf -> a
    | Node (l, v, r) -> f (fold_tree f a l) v (fold_tree f a r);;

let tree_product t = fold_tree (fun l v r -> v * l * r) 1 t;;
let tree_flip t = fold_tree (fun l v r -> Node (r, v, l)) Leaf t;;
let tree_height t = fold_tree (fun l v r -> 1 + max l r) 0 t;;
let tree_span t = fold_tree (fun (lmin, lmax) v (rmin, rmax) ->
    (min (min lmin v) rmin, max (max lmax v) rmax)) (max_int, min_int) t;;
let preorder t = fold_tree (fun l v r -> [v] @ l @ r) [] t



