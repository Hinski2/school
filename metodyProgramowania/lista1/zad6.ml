(*Przeanalizuj poniższe funkcje. W jaki sposób możesz użyć ich, aby sprawdzić,
czy interpreter wykonuje obliczenia używając gorliwej, czy leniwej kolejności
obliczania? Uzasadnij odpowiedź pokazując, jak interpreter wyliczyłby wartość
w zależności od kolejności obliczania. Załóż, że reguła obliczania wartości
wyrażenia if nie zależy od kolejności obliczania.*)

let rec f () = f ();; (* ta funkja się nie kończy *) 
let test x y =
  if x = 0 then 0 else y;;

test 0 (f ());;

(*jeśli gorliwa to najpierw oblicz f() czyli nigdy nie skoczy działania
  jeśli leniwa, to najpierw zacznie wyliczać test i nigdy nie obliczy f 
  więc program się skończy*)

(*program się nie kończy więc ocaml jest gorliwym językiem *)