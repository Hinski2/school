# zad4

---

`loop interchange` - technika optymalizacji, która polega na zamianie kolejności zagnieżdżonych pętli
`loop fusion` - optymalizacja, która polega na łączeniu dwóch lub więcej pętli, które mają tę samą strukturę iteracyjną
`usuwanie zmiennych indukcyjnych` - polega na usunięciu lub zastąpieniu zmiennych indukcyjnych w pętlach
`rematerialization` - optymalizaja polegająca na ponownym obliczeniu wartości zmiennej zamiast jej przechowywania w rejestrze lub pamięci

#### kod początkowy:
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k; // n = 2 ^ k

    /*
    x x x x x
    x x x x x
    x x x x x
    x x x x x
    x x x x x
    */


    for (long i = 0; i < n; i++)
        a[i * n] = a[i] = 0; // tutaj czyścimy pierwszy wiersz i pierwszą kolumne

    /*
    0 0 0 0 0
    0 x x x x
    0 x x x x
    0 x x x x
    0 x x x x
    */

    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            a[j * n + i] = i * j; // tutaj ustawiamy macierz z pominięciem pierwszej kolumny i wiersza

    /*
    0 0 0 0 0
    0 1 2 3 4
    0 2 4 6 8
    0 3 6 9 12
    0 4 8 12 16 
    */

    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];

    /*
    0 0 0 0 0               0 0 0 0 0
    0 1 2 3 4               0 0 0 0 0
    0 2 4 6 8          +    0 0 1 2 3
    0 3 6 9 12              0 0 2 4 6
    0 4 8 12 16             0 0 3 6 9
    */
}
```

#### usuwanie zmiennych indukcyjnych dla środkowej pętli 
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k; // n = 2 ^ k
    for (long i = 0; i < n; i++)
        a[i * n] = a[i] = 0;

    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            a[i * n + j] = i * j;

    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++)
            b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];
}
```

#### loop fusion dla drugiej i trzeciej pętli
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k; // n = 2 ^ k
    for (long i = 0; i < n; i++)
        a[i * n] = a[i] = 0;

    for (long i = 1; i < n; i++)
        for (long j = 1; j < n; j++){
            a[i * n + j] = i * j;
            b[i * n + j] = a[i * n + j] + a[(i - 1) * n + (j - 1)];
        }
}
```

#### dodanie dodatkowych zmiennych tak by nie liczyć tych samych żeczy
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k; 
    long itr1 = 0; // oddanie pierwszego iteratora

    for (long i = 0; i < n; i++){
        a[itr1] = a[i] = 0;
        itr1 += n;
    }

    itr1 = n + 1;   //ustawienie itr1 na odpowiednie miejsce
    long itr2 = 0;  // odanie drugiego iteratora  

    for (long i = 1; i < n; i++){
        for (long j = 1; j < n; j++){
            a[itr1] = i * j;
            b[itr1] = a[itr1] + a[itr2];
            itr1++;
            itr2++;
        }

        // przejście do następnej lini 
        itr1++;
        itr2++;
    }
}
```

#### strenght reduction dla i * j
```c
void compute2(long *a, long *b, long k) {
    long n = 1 << k; 
    long itr1 = 0; 

    for (long i = 0; i < n; i++){
        a[itr1] = a[i] = 0;
        itr1 += n;
    }

    itr1 = n + 1;   
    long itr2 = 0;  
    long val = 0;   //dodanie zmiennej pomocniczej

    for (long i = 1; i < n; i++){
        val = i;
        for (long j = 1; j < n; j++){
            a[itr1] = val;
            val += i;

            b[itr1] = a[itr1] + a[itr2];
            itr1++;
            itr2++;
        }

        itr1++;
        itr2++;
    }
}
``` 

