#pragma once
#include <array>
#include <iostream>
#include <ostream>

template<typename T, std::size_t N>
void arr_print(std::array<T, N> arr, std::ostream &out = std::cout) {
    for(const auto &elem : arr) {
        out << elem << ' ';
    }
}

template<typename T, std::size_t N>
void arr_copy(std::array<T, N> &from, std::array<T, N> &to) {
    for(std::size_t i = 0; i < N; i++) {
        to[i] = from[i];
    }
}

template<typename T, std::size_t N>
void arr_copy(std::span<T, N> &from, std::array<T, N> &to) {
    for(std::size_t i = 0; i < N; i++) {
        to[i] = from[i];
    }
}

template<typename T, std::size_t N>
void arr_copy(std::array<T, N> &from, std::span<T, N> &to) {
    for(std::size_t i = 0; i < N; i++) {
        to[i] = from[i];
    }
}

template<typename T, std::size_t N>
void arr_permute(std::array<T, N> &arr) {
    for(int i = 1; i < N; i++) {
        int j = rand() % (i + 1);
        std::swap(arr[i], arr[j]);
    }
}

template<typename T, std::size_t N>
void arr_buble_sort(std::array<T, N> &arr) {
    for(int i = 0; i < N - 1; i++) {
        for(int j = 0; j < N - i - 1; j++) {
            if(arr[j] > arr[j + 1]) {
                std::swap(arr[j], arr[j + 1]);
            }
        }
    }
}

namespace {
template<typename T>
void merge(std::span<T> &arr, std::span<T> &left, std::span<T> &right) {
    std::array<T, arr.size()> temp = arr_cpy(arr);
    std::size_t main_pos = 0, left_pos = 0, right_pos = 0;

    while(left_pos < left.size() and right_pos < right.size()) {
        if(left[left_pos] < right[right_pos]) {
            temp[main_pos++] = left[left_pos++];
        } else {
            temp[main_pos++] = right[right_pos++];
        }
    }

    while(left_pos < left.size()) {
        temp[main_pos++] = left[left_pos++];
    }

    while(right_pos < right.size()) {
        temp[main_pos++] = right[right_pos++];
    }

    arr_copy(temp, arr);
}

template<typename T> 
void merge_sort(std::span<T> &arr) {
    if(arr.size() == 2 and arr[0] > arr[1]) {
        swap(arr[0], arr[1]);
    } else if(arr.size() > 2) {
        std::size_t mid = arr.size() / 2;
        std::span<T> left(arr.data(), mid);
        std::span<T> right(arr.data() + mid, arr.size() - mid);

        merge_sort(left);
        merge_sort(right);
        merge(arr, left, right);
    }
}
} // namespace 

template<typename T, std::size_t N>
void arr_merge_sort(std::array<T, N> &arr) {
    std::span<T> arr_span(arr.data(), arr.size());
    merge_sort(arr_span);
}
