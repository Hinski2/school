# zad 1

#### definicja funkcji map:
``` ocaml
    let rec map f xs = match xs with
    | [] -> []
    | x :: xs' -> f x :: map f xs'
```

**nasz cel to:** pokaż że `map f (map g xs) = map (fun x -> f (g x)) xs`

#### podstawa indukcji:
``` ocaml
    przypadek gdy xs jest listą pustą:
    L = 
    = map f ( map g [] ) = { z def map } =
    = map f [] = { z def map } =
    = []

    R = 
    = map (fun x -> f (g x)) [] = { z def map } =
    = []

    L = R
```

#### krok indukcyjny:
**zał:** `zachodzi map f(map g xs) = map (fun x -> f (g x)) xs`
**cel:** pokazać że zachodzi to też dla x :: xs

``` ocaml
L =
= map f (map g x :: xs) = { z def map } = 
= map f (g x :: map g xs) = { z def map } = 
= f g x :: map f ( map g xs ) = { z zał ind } = 
= f g x :: map (fun x -> f (g x)) xs

R = 
= map (fun x' -> f (g x')) x :: xs = { z def map } = 
= (fun x' -> f (g x')) x :: map (fun x' -> f (g x')) xs = { podstawiam x } = 
= (fun x -> f (g x)) :: map (fun x' -> f (g x')) xs = { zmiana na inny zapis } =
= f g x :: map (fun x' -> f (g x')) xs

L = R
```
#### QED