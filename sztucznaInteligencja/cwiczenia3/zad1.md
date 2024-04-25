# Zad1

---

1) **Local beam search dla k = 1**:
Local beam search to algorytm przeszukiwania lokalnego, który rozszerza ideę przeszukiwania zachłannego, przechowując k najlepszych stanów zamiast jednego. Gdy k = 1, algorytm staje się identyczny z przeszukiwaniem zachłannym, ponieważ w każdym kroku rozważany jest tylko jeden, najlepszy stan. Skupia się on na najbardziej obiecującym kierunku, co czyni go podatnym na utknięcie w lokalnych maksimach.
 
2) **Local beam search z jednym początkowym stanem i bez limitu na liczbę zachowanych stanów po generacji następnika**:
W tej wariacji, algorytm zaczyna od jednego stanu początkowego i w każdym kroku generuje wszystkie możliwe stany następcze, przechowując je wszystkie do dalszej analizy. Brak ograniczenia na liczbę zachowanych stanów sprawia, że staje się to równoważne z algorytmem przeszukiwania wszerz (breadth-first search), jeśli przyjmiemy, że każdy stan jest rozważany jako potencjalny kandydat.
 
3) **Symulowane wyżarzanie z T = 0 przez cały czas działania algorytmu**:
Symulowane wyżarzanie to technika, która naśladuje proces wyżarzania w metalurgii, gdzie temperatura kontroluje prawdopodobieństwo akceptacji gorszych rozwiązań w celu uniknięcia lokalnych minimum. Jeśli temperatura (T) jest stała i równa 0, algorytm nigdy nie zaakceptuje gorszego rozwiązania, zachowując się jak algorytm zachłanny. Nie będzie zdolny do wyjścia z lokalnego minimum, ograniczając jego zdolność do eksploracji przestrzeni stanów.
 
4) **Symulowane wyżarzanie z T = \(\infty \) przez cały czas działania algorytmu**:
Przy nieskończenie wysokiej temperaturze, każda zmiana jest akceptowana z takim samym prawdopodobieństwem, niezależnie od tego, czy jest lepsza, czy gorsza. To sprawia, że algorytm staje się losowym spacerem (random walk), ponieważ każdy generowany stan jest akceptowany.
 
5) **Algorytm genetyczny z populacją wielkości 1**:
Algorytmy genetyczne to metaheurystyki, które naśladują procesy ewolucji biologicznej, takie jak selekcja, krzyżowanie i mutacja, aby optymalizować rozwiązania. Populacja o wielkości 1 oznacza, że w każdej generacji jest tylko jeden osobnik, co eliminuje możliwość krzyżowania. Algorytm sprowadza się wtedy do przeszukiwania przez mutacje. Jednak bez różnorodności genetycznej, wprowadzanej przez krzyżowanie i większą populację, algorytm jest bardzo ograniczony w eksploracji przestrzeni rozwiązań i prawdopodobnie szybko zbiegnie do suboptymalnego rozwiązania.