#include <algorithm>
#include <bits/stdc++.h>
#include <print>
using namespace std;

// wypisz wszystkie wartości z zadanego zakresu [a, b]
template<class It, typename T>
struct Task1 {
    T a, b;

    void operator() (It begin, It end) const {
        for(; begin != end; begin++) {
            if(a <= *begin and *begin <= b) print("{} ", *begin);
        }
        println();
    }  
};

// wypisz co k-ta wartośc zaczynając od pozycji p-tej
template<class It>
struct Task2 {
    int p, k;

    void operator() (It begin, It end) const {
        for(try_advance(begin, end, p - 1); begin != end; try_advance(begin, end, k))
            print("{} ", *begin);

        println();
    }

    void try_advance(It& begin, It& end, int k) const {
        for(int i = 0; i < k and begin != end; begin++, i++);
    }
};

// wypisz element minimalny i maksymalny
template<class It, typename T>
struct Task3 {
    pair<T, T> operator() (It begin, It end) const {
        T mini = *begin, maxi = *begin;

        for(; begin != end; begin++) {
            mini = min(mini, *begin);
            maxi = max(maxi, *begin);
        }

        return pair{mini, maxi};
    }
};

// wyznacz sume
template<class It, typename T> 
struct Task4 {
    T operator() (It begin, It end) const {
        T sum = T{};
        for(; begin != end; begin++) 
            sum += *begin;
        
        return sum;
    }
};

int main() {
    vector<double> a = {1., 2.5, 4.7, 1.8, 1.8, 9.5, 10.2, -.3};
    list<int> b = {10, 2, 4, 3, 2, 5, 7, 9};
    set<string> c = {"ala", "b", "ccccc", "XD", "dkfjdkfjdk", "kuba"};
        
    // taks1 
    println("\ntaks1:");
    Task1<vector<double>::iterator, double>{2.0, 5.2}(a.begin(), a.end());
    Task1<list<int>::iterator, int>{2, 5}(b.begin(), b.end());
    Task1<set<string>::iterator, string>{"aa", "ccc"}(c.begin(), c.end());

    // task2
    println("\ntaks2:");
    Task2<vector<double>::iterator>{2, 2}(a.begin(), a.end());
    Task2<list<int>::iterator>{2, 2}(b.begin(), b.end());
    Task2<set<string>::iterator>{2, 2}(c.begin(), c.end());

    // task3
    println("\ntaks3:");
    auto [a1, a2] = Task3<vector<double>::iterator, double>{}(a.begin(), a.end());
    println("{} {}", a1, a2);
    auto [b1, b2] = Task3<list<int>::iterator, int>{}(b.begin(), b.end());
    println("{} {}", b1, b2);
    auto [c1, c2] = Task3<set<string>::iterator, string>{}(c.begin(), c.end());
    println("{} {}", c1, c2);
    
    // task4
    println("\ntaks4:");
    println("{}", Task4<vector<double>::iterator, double>{}(a.begin(), a.end()));
    println("{}", Task4<list<int>::iterator, int>{}(b.begin(), b.end()));
    println("{}", Task4<set<string>::iterator, string>{}(c.begin(), c.end()));

}
