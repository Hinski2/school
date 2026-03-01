#include <bits/stdc++.h>

template<typename T>
using fun = T(*)(T); // wskaźnik na funkcje która przyjmuje t i zwraca t

template<typename T> 
void transform(T tab[], int n, fun<T> f) {
    for(int i = 0; i < n; i++)
        tab[i] = f(tab[i]);
}

int main() {
    fun<int> square = [](int x) {
        return x * x;
    };

    fun<int> negate = [](int x) {
        return -x;
    };

    int tab[] = {1, 2, 3, 4, 5};
    int n = sizeof(tab) / sizeof(tab[0]);

    transform(tab, n, negate);
    for(int i = 0; i < n; i++)
        std::cout << tab[i] << ' ';
    std::cout << std::endl;

    transform(tab, n, square);
    for(int i = 0; i < n; i++)
        std::cout << tab[i] << ' ';
    std::cout << std::endl;
}
