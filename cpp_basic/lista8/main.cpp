#include "num.hpp"

int main() {
    std::cout << "liczby" << std::endl;
    std::array<int, 10> arr = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10};
    arr_permute(arr);
    arr_print(arr);

    std::cout << "sortowanie bombelkowe" << std::endl;
    arr_buble_sort(arr);
    arr_print(arr);

    std::cout << "sortowanie przez scalanie" << std::endl;
    arr_permute(arr);
    arr_print(arr);
    arr_merge_sort(arr);
    arr_print(arr);
}
