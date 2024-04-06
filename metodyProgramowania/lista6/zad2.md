# zad 2

Palindromy to wyrazy czytane od przodu i od tyłu w taki sam sposób. Wystarczy tworzyć je od środka. zasada produkcji P:
* P -> ϵ
* P -> a
* P -> b
* P -> a P a
* P -> b P b

G = { V, sigma, S, P}
V := V (zbiór zmiennych lub symboli nieterminalnych): Jest to zbiór wszystkich symboli, które mogą być zastępowane za pomocą reguł produkcji

sigma := (zbiór symboli terminalnych): Są to symbole, które pojawiają się w wyrazach języka i nie są dalej rozwijane w procesie wyprowadzania

S :=  (symbol startowy): To symbol, od którego rozpoczynamy proces generowania wyrazów w języku.

P:= (reguły produkcji): Zestaw reguł określających, jak symbole nieterminalne mogą być przekształcane w symbole terminalne (lub inne symbole nieterminalne).

w naszym przypadku:
V := {P}
sigma := {a, b}
S := P