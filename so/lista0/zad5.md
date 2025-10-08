# zad 5

--- 

volatile - volatile mówi kompilatorowi, że zmienna może zmienić zwoją wartość, nawet jeśli kod programu na to nie wskazuje. Gdybyśmy nie dali volatile do zmiennej jest szansa że kompilator uznałby że to stała, bo nic nie wskazuje że zmienna ma zmienić swoja wartość. gdy mamy zmięnna z volatile kompilator:
* nie może zapamiętywać wartości w rejestrze
* każdorazowe odwołanie sie do zmiennej musi czytać / zaisywać ja 
* kompilator nie może zakładać, że wartość zmiennej pomiędzy dwoma odczytami sie nie zmienila 

kiedy używamy: 
* gdy zmienne są modyfikowane w obsłudze przerwań
* w embeded gdy używamy rejestrów urządzenia (rejestry kontrolera maja swoje adresy które można czytać/pisać jak zmienne )