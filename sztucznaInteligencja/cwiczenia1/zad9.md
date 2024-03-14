# zadanie 9

---

### a) Koszt paliwa, ograniczona pojemność baku, stacje benzynowe w niektórych węzłach

**Przestrzeń stanów**:
Stan składa się z trzech elementów:
1. **Aktualne położenie** samochodu w sieci drogowej.
2. **Ilość paliwa w baku** w danym momencie.

**Model**:
- **Zbiór akcji** - przemieszczenia między węzłami z uwzględnieniem kosztu paliwa oraz tankowanie do pełna na stacjach benzynowych.
- **Model przejścia** - aktualizuje położenie i ilość paliwa po przemieszczeniu, resetuje ilość paliwa przy tankowaniu.
- **Test końcowy** - cel podróży został osiągnięty.
- **Funkcja kosztu** - suma zużytego paliwa.

### b) Kurier z K paczkami do rozwiezienia

**Przestrzeń stanów**:
Stan definiowany przez:
1. **Aktualne położenie kuriera** w sieci drogowej.
2. **Stan dostarczenia paczek** - maska bitowa ze stanem dostarczonych paczek 0: niedostarczona, 1: dostarczona

**Model**:
- **Zbiór akcji** - przemieszczenia między węzłami z uwzględnieniem dostarczenia paczek.
- **Model przejścia** - aktualizuje położenie kuriera i stan dostarczenia paczek.
- **Test końcowy** - wszystkie paczki zostały dostarczone.
- **Funkcja kosztu** - zdefiniowana jako liczba przemierzonych kilometrów
