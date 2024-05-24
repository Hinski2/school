# zad1

---

#### parametry dysku:
* jeden plater
* jedna głowica
* 576 tysięcy ścieżek na powierzchnię
* 32000 sektorów na ścieżkę
* 7200 obrotów na minutę
* czas wyszukiwania: 1ms na przeskoczenie o 24 tysięcy ścieżek

#### pojęcia do wyjaśienia
* **Plater** - okrągła płyta znajdująca się wewnątrz dysku twardego, pokryta magnetycznym materiałem, na której zapisywane są dane.
* **Głowica** - element urządzenia, który czyta i zapisuje dane na magnetycznej powierzchni platera, przemieszczając się nad jego powierzchnią.
* **Ścieżka** - koncentryczny krąg na powierzchni platera, na którym zapisywane są dane. Wszystkie ścieżki mają jednakową szerokość.
* **Sektor** - najmniejsza jednostka zapisu danych na ścieżce, zazwyczaj zawierająca 512 bajtów danych.
* **Czas wyszukiwania** - czas potrzebny głowicy dysku na przemieszczenie się do określonej ścieżki, na której znajdują się żądane dane.
* **Czas opóźnienia obrotowego** - czas oczekiwania na to, aż żądany sektor znajdzie się pod głowicą po dotarciu głowicy na odpowiednią ścieżkę. Zależy od prędkości obrotowej dysku.
* **Czas transferu** - czas potrzebny na faktyczne odczytanie lub zapisanie danych na dysku, po umiejscowieniu głowicy nad odpowiednim sektorem.

#### 1. średni czas wyszukiwania
Średni czas wyszukiwania jest połową czasu potrzebnego do przeskoczenia maksymalnej liczby ścieżek.

```python
# Obliczenie maksymalnego czasu wyszukiwania
T_max_seek = (576000ścieżki / 24000ścieżki/ms) * 1ms  -> 24ms

# Obliczenie średniego czasu wyszukiwania
T_avg_seek = T_max_seek / 2  -> 12ms
```

#### 2. Średni czas opóźnienia obrotowego
Średni czas opóźnienia obrotowego to połowa czasu potrzebnego na jedno pełne obroty dysku.

```python
# Obliczenie czasu jednego pełnego obrotu
T_one_rotation = (60s / 7200RPM) * 1000  -> 8.33ms
# Obliczenie średniego czasu opóźnienia obrotowego
T_avg_rotation = T_one_rotation / 2 -> 4.17ms
```
#### 3. Czas transferu sektora
Czas transferu jednego sektora jest czasem, w którym jeden sektor przechodzi pod głowicą.

```python
T_avg_transfer = T_one_rotation / sector_per_track = 8.33ms / 32000 -> 0.00026ms
```

#### 4. Całkowity średni czas obsługi żądania
Całkowity średni czas obsługi żądania to suma średniego czasu wyszukiwania, średniego czasu opóźnienia obrotowego i czasu transferu sektora.
```python
# Obliczenie całkowitego średniego czasu obsługi żądania
T_access = T_avg_seek + T_avg_rotation + T_avg_transfer = 
= 12ms + 4.17ms + 0.00026ms -> 16.17ms
```


