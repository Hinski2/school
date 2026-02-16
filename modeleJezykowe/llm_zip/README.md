# LLM_ZIP

---

idea projektu z zadania 6, cwiczenia 2

https://github.com/Hinski2/school/blob/main/modeleJezykowe/cwiczenia2/zad6.md

--- 

### Struktura

##### sktuktura całego pliku

``` 
    [model_name in alfa coding]
    [0 if we use gamma coding, 1 if we use huffman coding]
    [no of files in beta coding]
    (BitSet)
    (BitSet)
    ...
    (BitSet)
```

##### BitSet

```
    file:
        [0]
        [len of file name in gamma coding] 
        [len of data in beta coding]
        [file_name (encoded with model)]
        [data (encoded with model)]
        
    directory:
        [1]
        [len of file name in gamma coding] 
        [file_name (encoded with model)]
```

### kodowania

* alfa code:
    najpierw zapisujemy len z użyciem beta code
    kodujemy każdy znak jako jego numer w ascii i zapisujemy z gamma code

* beta code:
    wersja gamma code która nie robi -1 przy rozmiarze 

* gamma code:
    legitne kodowanie z wikipedii: https://en.wikipedia.org/wiki/Elias_gamma_coding
