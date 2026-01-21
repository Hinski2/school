# zad 2

--- 

* `sekcja krytyczna` - fragment kodu operujacy na wspólnych danych 
* `blokowanie drobnoziarnieste` - zakładania osobnhych blokad na poszczególne elementy zamiast jednej użej blokady

--- 

### prblem sekcji krytycznej 
mamy system w którym mamy n procesów P_0 ... P_{n - 1}. każdy z nich ma fragment kodu, w którym modyfikure współdzeilone dane. ten fragment kodu nazywamy sekcją krytyczną 

### założenia jakie musi psełniać rozwiązanie problemu sekcji krytycznej
* `wzajemne wykluczenie` - jeśli proces P_i jest w sekcje krytcznej to nik inny nie może tam być
* `postęp` - jesli nikt nie jest w sekcji krytycznej a jakieś procesy chcą tam wejść to decycja o tym kto ma wejść nie może byc odkładana w nieskończoność 
* `ograniczone oczekiwanie` - musi istnieć limit ile razy inne procesy mogą wepchnąć się w kolejke przed procesem, który zgłosił chec wejścia. zapobiega to głodzeniu

### czemu w programach prestrzeni uzytkownika do jej implementacji nie możemy używać wyłączenia przrwań
* gdyby użytkownik mógł wysłączać przerwania mógłby zmonopolizować procesor. jeśli taki program wszedłby w nieskończona pętle przy wyłączonych wszystkich przerwaniach to system operacyjny nie mógłby odzyska kontorlli
* nie powstrzymuje to innych wątków przed wejściem do sekcji krytycznej 

### odwołując sie do prawa Amdahla powiedz czemu programistom powinno zależeć na tym, by sekcje krytyczne były możliwie jak najkrótsze (blokowanie drobronizarniste)
Prawo Amdahla - maksymalne przyśpieszenie programu przy użyciu wielu procesorów jest limitowane przes tą część programu, która musi byćw ykonywana sekwencyjnie 

* skekcja krytyczna jest częścia sekwencyjmą bo w sekcji krytcznej może by tylko jeden wątek naraz
* blokowanie drobnoziarniste polega na dążeniu do teby by sekcje krytczne były nak najkrótsze co zmniejsza udział części sekwencyjnej w całym programie