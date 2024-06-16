***DEFINICJE***
### Adres wirtualny
Adres wirtualny to adres używany przez proces do odwoływania się do pamięci. Jest to logiczny adres, który różni się od fizycznego adresu pamięci RAM. Procesor i system operacyjny używają mechanizmu zarządzania pamięcią wirtualną, aby tłumaczyć adresy wirtualne na adresy fizyczne. Dzięki temu każdy proces może mieć swoją własną, niezależną przestrzeń adresową, co zwiększa bezpieczeństwo i stabilność systemu.

### Strona
Strona to podstawowa jednostka pamięci w systemie zarządzania pamięcią wirtualną. Typowy rozmiar strony to 4 KiB, chociaż mogą być używane również inne rozmiary. Pamięć wirtualna jest podzielona na strony, a każda strona może być mapowana do dowolnej ramki w pamięci fizycznej. System operacyjny zarządza tym mapowaniem, co pozwala na bardziej efektywne wykorzystanie pamięci oraz izolację procesów.

### Wpis tablicy stron
Wpis tablicy stron to pojedynczy rekord w tablicy stron, który zawiera informacje niezbędne do przetłumaczenia adresu wirtualnego na fizyczny. Typowe informacje zawarte we wpisie tablicy stron to:
- Adres ramki w pamięci fizycznej, do której mapowana jest dana strona wirtualna
- Bity statusowe, takie jak bit obecności (czy strona jest w pamięci), bity uprawnień (czy strona może być odczytywana, zapisywana itp.), oraz inne bity kontrolne

### Wirtualna przestrzeń adresowa
Wirtualna przestrzeń adresowa to zakres adresów wirtualnych, które może używać proces. W systemach 32-bitowych przestrzeń ta wynosi do 4 GiB (od 0x00000000 do 0xFFFFFFFF), a w systemach 64-bitowych może być znacznie większa. Przestrzeń adresowa każdego procesu jest izolowana od przestrzeni adresowych innych procesów, co zapobiega ich wzajemnemu zakłócaniu i zwiększa bezpieczeństwo.

### Tablica dwupoziomowa
Tablica dwupoziomowa to struktura danych używana w zarządzaniu pamięcią wirtualną, która składa się z dwóch poziomów tablic stron. Pierwszy poziom to katalog tablic stron, który wskazuje na tablice stron drugiego poziomu. Drugi poziom to właściwe tablice stron, które zawierają wpisy mapujące adresy wirtualne na adresy fizyczne. Dwupoziomowy schemat tablic stron pozwala na bardziej efektywne zarządzanie pamięcią, szczególnie w dużych przestrzeniach adresowych, ponieważ katalog tablic stron może mapować tylko używane obszary pamięci, zamiast rezerwować miejsce na całą przestrzeń adresową z góry.

#### Przykład dwupoziomowej tablicy stron:
- **Katalog tablic stron**: Zawiera wskaźniki do tablic stron. Każdy wpis w katalogu odpowiada dużemu blokowi przestrzeni adresowej wirtualnej.
- **Tablice stron**: Każda tablica stron mapuje mniejsze bloki przestrzeni adresowej (np. 4 MiB w przypadku 32-bitowych adresów i stron 4 KiB).

Dwupoziomowa tablica stron jest bardziej elastyczna i skalowalna niż jednopoziomowa, ponieważ nie wymaga przechowywania wszystkich wpisów tablicy stron w jednym dużym bloku pamięci.

### (a) Jednopoziomowa tablica stron

#### Maksymalny rozmiar tablicy stron

Jednopoziomowa tablica stron mapuje wszystkie strony procesu bezpośrednio do ramki w pamięci fizycznej. Aby obliczyć maksymalny rozmiar tablicy stron dla procesu używającego 1 GiB przestrzeni wirtualnej, postępujemy następująco:

1. **Rozmiar strony**: 4 KiB = 2^12 bajtów
2. **Liczba stron**: Proces używa 1 GiB = 2^30 bajtów, więc liczba stron to:
   Liczba stron = 2^30 bajtów / 2^12 bajtów na stronę = 2^18 stron
3. **Rozmiar wpisu w tablicy stron**: 4 bajty

Maksymalny rozmiar tablicy stron = 2^18 stron * 4 bajty na wpis = 2^20 bajtów = 1 MiB

#### Minimalny rozmiar tablicy stron

W przypadku jednopoziomowej tablicy stron każda używana strona procesu musi być odwzorowana w tablicy stron, więc minimalny rozmiar tablicy stron jest taki sam jak maksymalny rozmiar, ponieważ każda z 2^18 stron musi być odwzorowana.

Minimalny rozmiar tablicy stron:
1 MiB

### (b) Dwupoziomowa tablica stron

W dwupoziomowej tablicy stron mamy katalog tablic stron i tablice stron. Przeanalizujmy obie struktury:

1. **Liczba wpisów w katalogu tablic stron**: 1024 (każdy wpis wskazuje na tablicę stron)
2. **Rozmiar strony**: 4 KiB
3. **Liczba stron**: Proces używa 1 GiB = 2^30 bajtów, więc liczba stron to:
 Liczba stron = 2^30 bajtów / 2^12 bajtów na stronę = 2^18 stron
4. **Rozmiar wpisu w tablicy stron**: 4 bajty

#### Maksymalny rozmiar tablicy stron

Aby obliczyć maksymalny rozmiar dwupoziomowej tablicy stron, musimy uwzględnić wszystkie wpisy w katalogu i w tablicach stron:

- Katalog tablic stron ma 1024 wpisów.
- Każda tablica stron ma 1024 wpisów.

Liczba tablic stron potrzebnych do odwzorowania 1 GiB pamięci wirtualnej:
Liczba stron wirtualnych = 2^18 

Liczba tablic stron = 2^18 stron / 1024 wpisów na tablicę = 2^8 = 256 tablic stron

Każda tablica stron ma 1024 wpisów po 4 bajty każdy:

256 tablic * 1024 wpisów * 4 bajty = 2^8 * 2^10 * 4 = 2^20 bajtów = 1 MiB

Katalog tablic stron ma 1024 wpisów po 4 bajty każdy:

1024 wpisów * times 4 bajty = 4096 bajtów = 4 KiB

Łączny maksymalny rozmiar tablicy stron:
1 MiB + 4 KiB

#### Minimalny rozmiar tablicy stron

Minimalny rozmiar dwupoziomowej tablicy stron to sytuacja, w której proces wykorzystuje jedną stronę pamięci wirtualnej:

- Katalog tablic stron: 4 KiB
- Jedna tablica stron: 4 KiB (bo każda tablica stron zajmuje jedną stronę)

Łączny minimalny rozmiar tablicy stron:
4 KiB (katalog) + 4 KiB (jedna tablica stron) = 8 KiB

Podsumowanie:
- Jednopoziomowa tablica stron: maksymalny i minimalny rozmiar: 1 MiB
- Dwupoziomowa tablica stron: maksymalny rozmiar: 1 MiB + 4 KiB, minimalny rozmiar: 8 KiB