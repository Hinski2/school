# zad7

---

#### pojęcia do wytłumaczenia:
* **rejestr sterujący** - Specjalny rejestr w procesorze, który przechowuje ustawienia konfiguracyjne wpływające na działanie procesora, takie jak zarządzanie pamięcią, ochrona pamięci i inne tryby pracy.
* **tryb uprzewilejowany  (ang. supervisor mode)** - Tryb pracy procesora, w którym ma on dostęp do wszystkich instrukcji i zasobów systemowych, używany przez system operacyjny do zarządzania sprzętem i zadaniami krytycznymi.
* **tryb urzytkownika** - Tryb pracy procesora, w którym dostęp do krytycznych zasobów i instrukcji jest ograniczony, zapewniając bezpieczeństwo i stabilność systemu, używany przez aplikacje użytkownika.
* **izolacja** -  Mechanizm w systemach komputerowych, który zapewnia, że procesy i aplikacje działają w oddzielnych przestrzeniach pamięci, chroniąc je przed wzajemnym wpływem i potencjalnymi błędami.

---

Górne 20 bitów: Adres fizyczny katalogu stron.
Dolne 12 bitów: Process-Context Identifier (PCID) (jeśli włączone)

Jeśli PCID działa to dzieki temu każdy proces ma osobny TLB (Translation Lookaside Buffer)

TLB pamięć, Zawiera ona najczęściej używane mapowania adresów, co pozwala na szybki dostęp bez konieczności odwoływania się do głównej tabeli stron

#### Co przechowuje rejestr CR3:
Rejestr CR3 przechowuje fizyczny adres pierwszego katalogu stron, co umożliwia procesorowi translację adresów wirtualnych na fizyczne. Jeśli bit PCIDE w rejestre CR4 jest zapalony, to najniższe 12 bitów jest używane przez PCID (process-context identifier)

#### Czemu jest on dostępny wyłącznie dla programów działających w trybie uprzywilejowanym:
CR3 jest dostępny tylko w trybie uprzywilejowanym, aby zapewnić bezpieczeństwo i stabilność systemu. Zapobiega to przypadkowemu lub złośliwemu modyfikowaniu struktury pamięci, co mogłoby prowadzić do poważnych błędów systemowych lub naruszeń bezpieczeństwa.

#### Czy moglibyśmy zagwarantować izolację, jeśli pamięć przechowująca tablicę stron była dostępna w trybie użytkownika
Nie, nie moglibyśmy zagwarantować izolacji, jeśli pamięć przechowująca tablicę stron była dostępna w trybie użytkownika. Użytkownicy mogliby modyfikować tablice stron, co mogłoby prowadzić do naruszenia izolacji procesów i potencjalnych ataków na system.