#include <vector>
#include <algorithm>
#include <limits>

// Proste insertion sort, bo czasem trzeba umieć
// wziąć chaos w swoje ręce.
void insertionSort(std::vector<int>& A) {
    int n = A.size();
    for (int i = 1; i < n; ++i) {
        int key = A[i];
        int j = i - 1;
        while (j >= 0 && A[j] > key) {
            A[j + 1] = A[j];
            --j;
        }
        A[j + 1] = key;
    }
}

// O(1)-pamięciowy QuickSort z małym progiem m,
// który zostawiamy niesortowany do insertion sortu.
// Żebyś mógł poczuć, jak granica równa się nic.
void IQS(std::vector<int>& A) {
    int n = A.size();
    const int m = 9;           // threshold dla insertion sort
    int l = 0, r = n;          // [l…r) – prawa granica wyłączona

    // sentinel na końcu, żeby nie martwić się o out-of-bounds
    A.push_back(std::numeric_limits<int>::max());
    r = n + 1;

    // główna pętla – trwa, dopóki nie ogarniesz całej tablicy
    while (l < n) {
        // jeśli segment jest „za duży”, rozłóż go szybkim sortem
        while (r - l > m) {
            int p = A[l];      // pivot = lewy element
            int i = l + 1;
            int j = r - 1;

            // klasyczne partition, ale z while zamiast do…while
            while (true) {
                while (A[i] < p) ++i;
                while (A[j] > p) --j;
                if (i < j) {
                    std::swap(A[i++], A[j--]);
                } else {
                    break;
                }
            }
            std::swap(A[l], A[j]);  // pivot na swoje miejsce
            r = j;                  // sortuj dalej lewą część
        }

        // przejdź do kolejnego nieuporządkowanego „zakamarka”
        l = r;
        if (l >= n) break;
        ++l;
        while (l < n && A[l] == A[l - 1]) ++l;

        // wyznacz prawą granicę dla następnego segmentu
        if (l < n) {
            int p = A[l];
            r = l + 1;
            while (r < n && A[r] <= p) ++r;
            --r;
            std::swap(A[l], A[r]);
        }
    }

    // usuń sentinel i dokończ małe fragmenty insertion sortem
    A.pop_back();
    insertionSort(A);
}