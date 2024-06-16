# zad6

---

#### do wytłumaczenia:
* **translacja**  - Translacja adresu to proces przekształcania adresu logicznego (wygenerowanego przez program) na adres fizyczny w pamięci RAM. Dokonuje się to za pomocą jednostki zarządzania pamięcią (MMU), która wykorzystuje tablice stron, aby zmapować adresy logiczne na fizyczne.
* **wyjątek procesora** - Wyjątek procesora to zdarzenie, które przerywa normalne wykonanie programu z powodu błędu lub specjalnej sytuacji (np. dzielenie przez zero, próba dostępu do nieistniejącej pamięci). Gdy wystąpi wyjątek, procesor zapisuje aktualny stan programu (np. adres instrukcji), a następnie przechodzi do wykonywania specjalnej procedury obsługi wyjątku (ang. exception handler), która podejmuje odpowiednie działania naprawcze lub diagnostyczne. Po obsłużeniu wyjątku, program może być wznowiony lub zakończony, w zależności od rodzaju i powagi wyjątku.
* **błąd strony (ang. page fault)** - Błąd strony to zdarzenie, które występuje, gdy program próbuje uzyskać dostęp do strony pamięci, która nie jest obecnie w pamięci RAM, co powoduje konieczność załadowania tej strony z pamięci masowej.

---

#### cztery przypadki wykonania instrukcji «mov», dla których procesor zgłosi wyjątek błędu dostępu do pamięci.

1. **Dostęp do nieistniejącej strony pamięci** : Próbujemy uzyskać dostęp do strony, która nie jest załadowana do pamięci RAM. System operacyjny musi wtedy załadować brakującą stronę z dysku.
2. **Dostęp do strony bez uprawnień (protection fault)**: Próbujemy zapisać dane do strony pamięci, która jest oznaczona jako tylko do odczytu lub próbujemy odczytać/zapisać dane ze strony, do której nie mamy odpowiednich uprawnień.
3. **Dostęp do niezaadresowanej przestrzeni pamięci**: Próbujemy uzyskać dostęp do adresu, który nie jest zmapowany do żadnej fizycznej pamięci (np. odwołanie do pustego wskaźnika).
4. **Dostęp do nieprawidłowego adresu (segment fault)**: Próbujemy uzyskać dostęp do pamięci poza dozwolonym zakresem segmentu, co może się zdarzyć w systemach z segmentacją pamięci. Na przykład, odwołanie do adresu poza limitem segmentu danych.
5. **page fault** - w ramie nie znajduje się to co szukamy, pytamy SO czy jest to na dysku

wszystkie te przypadki poza ostatnim na pewno spowodują zakończenie programu z błędem 

---

Procedura obsługi błędu strony (page fault handler) odpowiada za załadowanie brakującej strony pamięci z dysku do RAM, aktualizację tablic stron oraz ponowne uruchomienie instrukcji, która spowodowała błąd strony.
#### Przed procedurą:
* Procesor generuje wyjątek błędu strony i przechodzi do trybu jądra.
* Zapisuje stan programu i adres błędu.
#### Po procedurze:
* Aktualizacja tablic stron.
* Przywrócenie stanu programu.
* Ponowne uruchomienie instrukcji, która spowodowała błąd strony.

