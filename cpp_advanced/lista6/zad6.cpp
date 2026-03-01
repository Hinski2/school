#include <bits/stdc++.h>
using namespace std;

struct Person {
    string first_name, last_name;
    uint32_t age, weight;
    double height;

    double bmi() {
        return weight / (height * height);
    }
    
    // inicjały, wiel, bmi
    tuple<string, uint32_t, double> foo1() {
        return {
            string{first_name[0]} + string{last_name[0]},
            age, 
            bmi(),
        };
    }

    // wiek, waga, wzrost
    tuple<uint32_t, uint32_t, double> foo2() {
        return {
            age, 
            weight, 
            height,
        };
    }

    // imie, nazwisko, wiek
    tuple<string, string, uint32_t> foo3() {
        return {
            first_name,
            last_name, 
            age,
        };
    }
};

template<typename T, size_t... IDXS, typename F> 
void tuple_for_each_impl(T &t, F f, index_sequence<IDXS...>) {
    (f(get<IDXS>(t)), ...);
}

template<typename T, typename F>
void tuple_for_each(T &t, F f) {
    tuple_for_each_impl(
        t, 
        f, 
        make_index_sequence<tuple_size_v<T>>{}
    );
}

int main() {
    Person p = {"kuba", "iliński", 20, 70, 1.80};

    auto [a, b, c] = p.foo1();
    cout << a << ' ' << b << ' ' << c << endl;

    auto t1 = p.foo2();
    tuple_for_each(t1, [](auto &x){
        cout << x << ' ';
    });
    cout << endl;

    auto t2 = p.foo3();
    tuple_for_each(t2, [](auto &x){
        cout << x << ' ';
    });
    cout << endl;

}
