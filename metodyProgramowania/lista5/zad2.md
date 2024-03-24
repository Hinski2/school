# zad 2

**cel:** pokaż, że dla dowolnych list xs i ys istnieje lista zs taka, że append xs ys ≡ zs.

#### definicja append
``` ocaml
    let rec append xs ys = match xs with
    | [] -> ys
    | h :: t -> x :: append t ys
```

#### podstawa indukcji
**zakł:** że xs jest []
**cel:** $\exist$ zs = append xs ys
``` ocaml
    R =
    = append [] ys = { z def append } =
    = ys =
    = L
```

#### krok indukcyjny
**zakł:** że zachodzi $\exist$ zs = append xs ys
**cel:** chce pokazać że append (x::xs) ys = zs
``` ocaml
    L = 
    = append (x :: xs) ys = { z def } = 
    = x :: append xs ys = {z zał ind } =
    = x :: zs = R
```

##### QED