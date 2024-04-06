# zad 3

typ opisujący zmienne w NNF

``` ocaml
type 'v nnf =
    | NNFLit of bool * 'v
    | NNFConj of 'v nnf * 'v nnf
    | NNFDisj of 'v nnf * 'v nnf
```

#### zasada indukcji dla typu nnf
 cel: chcemy pokazać że własność p zachodzi dla każdego 'v nnf

##### podstawa indukcji:
musimy pokazać że P zachodzi dla każdego literału czyli formuły typu NNFLit (b, v), gdzie b jest flagą boolowską, a v zmienną. Czyli musimy pokazać że P zachodzi dla każdego literau

##### krok indukcyjny:
1. Dla koniunkcji
**zakł:** że P zachodzi dla formul f1, f2 typu 'v nnf
**cel:** pokazać że P zachodzi też dla formuły NNFConj f1 f2

2. Dla alternatywy
**zkał:** że P zachodzi dla formul f1, f2 typu 'v nnf
**cel:** pokazać ze P zachodzi też dla formuły NNFDisj f1 f2

#### wniosek
Jeśli P zachodzi dla podstawy indukcji oraz dla kroku indukcyjnego, to wnioskujemy że P zachodzi dla wszystkich formuł typu 'v nnf