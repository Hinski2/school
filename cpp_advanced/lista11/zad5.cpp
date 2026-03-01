#include <bits/stdc++.h>
using namespace std;

template<typename T> 
struct OnStack {
private:
    T value; 

public:
    template<typename... Args>
    OnStack(Args&&... args) : value(forward<Args>(args)...) {
        cerr << "stack" << endl;
    }

    T& operator*() {
        return value;
    }

    T* operator->() {
        return &value;
    }
};

template<typename T> 
struct OnHeap {
private:
    T* ptr;

public:
    template<typename... Args>
    OnHeap(Args&&... args) : ptr(new T(forward<Args>(args)...)) {
        cerr << "heap" << endl;
    }
    
    ~OnHeap() {
        delete ptr; 
    }

    T& operator*() {
        return *ptr;
    }

    T* operator->() {
        return ptr;
    }
};

template<typename T> 
struct ObjHolder {
    using type = typename conditional<
        (sizeof(T) <= sizeof(string)) && !is_array<T>::value,
        OnStack<T>,
        OnHeap<T>
    >::type;
};

struct C {
    int x;
};

int main() {
    typename ObjHolder<int>::type a(100);
    cout << *a << endl;

    typename ObjHolder<array<int, 30>>::type b;
    cout << (*b)[0] << endl;

    typename ObjHolder<C>::type c;
    cout << c -> x << endl;
}
