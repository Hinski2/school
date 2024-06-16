### Algorytm zastępowania stron NRU (Not Recently Used)

Algorytm NRU to prosty sposób zarządzania pamięcią w systemach operacyjnych. Algorytm ten wykorzystuje dwa bity, R (Referenced) i M (Modified), aby klasyfikować strony pamięci i decydować, którą stronę zastąpić, gdy konieczne jest załadowanie nowej strony do pamięci. Oto kroki działania algorytmu NRU:

1. **Inicjalizacja bitów**:
   - Gdy proces jest uruchamiany, bity R i M wszystkich stron są ustawiane na 0.

2. **Okresowe czyszczenie bitów R**:
   - Co pewien czas (np. przy każdym przerwaniu zegarowym), bit R wszystkich stron jest resetowany do 0, aby odróżnić strony, które były ostatnio używane, od tych, które nie były.

3. **Obsługa błędów stron**:
   - Gdy wystąpi błąd strony, system operacyjny przegląda wszystkie strony i klasyfikuje je w cztery kategorie na podstawie aktualnych wartości bitów R i M:
     - **Klasa 0**: Strona nie była referencjonowana ani modyfikowana (R = 0, M = 0).
     - **Klasa 1**: Strona była modyfikowana, ale nie była referencjonowana (R = 0, M = 1).
     - **Klasa 2**: Strona była referencjonowana, ale nie była modyfikowana (R = 1, M = 0).
     - **Klasa 3**: Strona była referencjonowana i modyfikowana (R = 1, M = 1).

4. **Wybór strony do zastąpienia**:
   - Algorytm NRU usuwa stronę z najniższą numerowaną, niepustą klasą. Jeśli istnieje strona w klasie 0, zostanie ona zastąpiona. Jeśli nie ma żadnej strony w klasie 0, algorytm przechodzi do klasy 1, i tak dalej.

### Bity A (Accessed) i D (Dirty) w x86-64

W architekturze x86-64, bity A i D mają podobne funkcje do bitów R i M opisanych powyżej:
- **Bit A (Accessed)**: Odpowiada za wskazanie, że strona była referencjonowana (odczytana lub zapisana). Jest ustawiany przez procesor przy każdym dostępie do strony.
- **Bit D (Dirty)**: Odpowiada za wskazanie, że strona była modyfikowana (zapisywana). Jest ustawiany przez procesor przy każdym zapisie do strony.

### Symulacja bitów A i D

Niektóre architektury nie implementują bitów A i D sprzętowo. W takim przypadku system operacyjny musi symulować te bity:

1. **Symulacja bitu A**:
   - Wszystkie wpisy tablic stron są oznaczone jako nieobecne (not present).
   - Gdy wystąpi błąd strony, system operacyjny oznacza stronę jako obecna i ustawia bit A w swoich wewnętrznych strukturach.
   - Przy każdym przerwaniu zegarowym system operacyjny może resetować bit A wewnętrznie, aby śledzić, które strony były ostatnio używane.

2. **Symulacja bitu D**:
   - Początkowo wszystkie strony są oznaczone jako tylko do odczytu.
   - Gdy wystąpi błąd strony z powodu próby zapisu, system operacyjny ustawia bit D w swoich wewnętrznych strukturach i zmienia status strony na zapisany.

### Wykorzystanie bitów A i D w algorytmie NRU

Algorytm NRU korzysta z bitów A i D w następujący sposób:

1. **Inicjalizacja**:
   - Podczas uruchamiania procesu, bity A i D wszystkich stron są ustawiane na 0.

2. **Okresowe czyszczenie bitu A**:
   - Przy każdym przerwaniu zegarowym system operacyjny resetuje bit A, aby śledzić, które strony były ostatnio używane.

3. **Klasyfikacja stron**:
   - Gdy wystąpi błąd strony, system operacyjny klasyfikuje strony w cztery klasy na podstawie wartości bitów A i D:
     - **Klasa 0**: A = 0, D = 0
     - **Klasa 1**: A = 0, D = 1
     - **Klasa 2**: A = 1, D = 0
     - **Klasa 3**: A = 1, D = 1

4. **Zastępowanie stron**:
   - System operacyjny wybiera stronę do zastąpienia z najniższej numerowanej, niepustej klasy.

### Podsumowanie

Algorytm NRU wykorzystuje bity R i M (odpowiadające bitom A i D w architekturze x86-64) do klasyfikacji stron i podejmowania decyzji o ich zastępowaniu. W przypadku braku sprzętowej implementacji tych bitów, system operacyjny może symulować je przy użyciu mechanizmów obsługi błędów stron i przerwań zegarowych. To pozwala na skuteczne zarządzanie pamięcią nawet na architekturach, które nie wspierają tych bitów bezpośrednio.