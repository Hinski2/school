(*Zauważ że w naszym modelu obliczania wartości dopuszczamy, aby operatorami były wyrażenia złożone. Korzystając z tej obserwacji, wyjaśnij działanie
następującej funkcji: *)

let a_plus_abs_b a b =
(if b > 0 then (+) else (-) ) a b

(* plus i minus to po prostu funkcje binarne i wybieramy którą funkcje mamy użyć
Wyrażenie warunkowe: (if b > 0 then (+) else (-))

Jeśli b jest większe od 0, to wyrażenie warunkowe zwraca operator dodawania (+).
Jeśli b jest mniejsze lub równe 0, to wyrażenie zwraca operator odejmowania (-).
Wywołanie operatora: Wybrany operator jest następnie wywoływany z a i b jako argumentami: (+) a b lub (-) a b.*)