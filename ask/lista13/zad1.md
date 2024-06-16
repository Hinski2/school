# zad1

---

Pojęcia do wytłumaczenia:
* profilowanie programu
* profil płaski
* profil grafu wywołań
* zliczanie interwałowe

Pytania w zadaniu:
* W jakim celu profiluje się programy
* Jakie informacje niesie ze sobą profil płaski i profil grafu wywołań
* Czemu profilowanie programu wymaga zbudowania go ze specjalną opcją kompilatora -pg
* Na czym polega zliczanie interwałowe (ang. interval counting)

---
* **profilowanie programu** - Profilowanie programu analizuje wydajność kodu, zbierając dane o czasie wykonania i liczbie wywołań funkcji.
* **profil płaski** - Profil płaski to lista funkcji wywoływanych podczas działania programu, z informacjami o liczbie wywołań i czasie wykonania, posortowana według czasu.
* **Profil grafu wywołań** - Profil grafu wywołań pokazuje funkcje programu z ich rodzicami (wywołującymi funkcjami) i dziećmi (wywoływanymi funkcjami), wraz z czasem spędzonym na każdej funkcji i czasem dziedziczonym od potomków.
* **Zliczanie interwałowe** - Zliczanie interwałowe to metoda pomiaru czasu wykonania funkcji poprzez okresowe przerywanie programu (co pewien stały interwał czasu) i sprawdzanie, która funkcja jest aktualnie wykonywana. Licznik dla tej funkcji jest wtedy zwiększany o wartość interwału, co pozwala oszacować względny czas spędzony na poszczególnych funkcjach.

---

* **W jakim celu profiluje się programy** - Profilowanie programów ma na celu zidentyfikowanie wąskich gardeł wydajności, aby zoptymalizować kod i poprawić jego efektywność.
* **Jakie informacje niesie ze sobą profil płaski i profil grafu wywołań** - 
    * Profil płaski: Liczba wywołań i czas wykonania każdej funkcji, posortowane według czasu.
    * Profil grafu wywołań: Informacje o rodzicach i dzieciach funkcji, czas spędzony na funkcji oraz czas dziedziczony od potomków.
* **Czemu profilowanie programu wymaga zbudowania go ze specjalną opcją kompilatora -pg** - Flaga -pg w kompilatorze GCC generuje dodatkowy kod, który zapisuje informacje profilowe odpowiednie dla programu analitycznego gprof.
* **Na czym polega zliczanie interwałowe (ang. interval counting)** - Zliczanie interwałowe mierzy czas funkcji przez okresowe przerywanie programu i zwiększanie licznika funkcji wykonywanej w momencie przerwania, co pozwala oszacować względny czas spędzony na poszczególnych funkcjach.