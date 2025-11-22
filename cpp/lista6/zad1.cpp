#include <algorithm>
#include <bits/stdc++.h>
#include <cstdint>
using namespace std;

struct Person {
    string first_name, last_name;
    uint32_t age, weight;
    double height;

    friend ostream& operator << (ostream& out, const Person &p) {
        out << '{';
        out << "first_name: " << p.first_name << ", "
            << "last_name: "  << p.last_name  << ", "
            << "age: "        << p.age        << ", "
            << "weight: "     << p.weight     << ", "
            << "height: "     << p.height;
        out << '}';

        return out;
    }
};

deque<Person> people = {
    {.first_name="kuba",    .last_name="ilinski",   .age=20, .weight=70,    .height=180.},
    {.first_name="jan",     .last_name="mączyński", .age=21, .weight=80,    .height=185.},
    {.first_name="łukasz",  .last_name="stodułka",  .age=20, .weight=75,    .height=180.},
    {.first_name="a",       .last_name="A",         .age=10, .weight=100,   .height=150.1},
    {.first_name="aa",      .last_name="AA",        .age=12, .weight=110,   .height=174.3},
    {.first_name="aaa",     .last_name="AAA",       .age=11, .weight=73,    .height=194.4},
    {.first_name="b",       .last_name="B",         .age=15, .weight=43,    .height=185.2},
    {.first_name="bb",      .last_name="BB",        .age=19, .weight=89,    .height=153.4},
    {.first_name="bbb",     .last_name="BBB",       .age=73, .weight=97,    .height=199.4},
    {.first_name="c",       .last_name="C",         .age=84, .weight=131,   .height=188.4},
    {.first_name="cc",      .last_name="CC",        .age=48, .weight=75,    .height=189.9},
    {.first_name="ccc",     .last_name="CCC",       .age=30, .weight=86,    .height=145.5},
};

void execute_a() {
    auto bmi = [](const Person &p) -> double {
        return  p.weight / (p.height * p.height);
    };

    auto comp = [&](const Person &a, const Person &b) -> bool {
        return bmi(a) < bmi(b);
    };

    sort(people.begin(), people.end(), comp);
    for(auto &p: people)
        cout << p << endl;
}

void execute_b() {
    auto weight_reduction = [](Person &p) -> void {
        p.weight *= 0.9;
    };

    for(auto &p: people) {
        weight_reduction(p);
        cout << p << endl;
    }
}

void execute_c() {
    auto light = people 
        | views::filter([](const Person &p){
            return p.weight <= 100;
        });

    
    cout << "light" << endl;
    for(auto &p: light)
        cout << p << endl;

    auto heavy = people 
        | views::filter([](const Person &p){
            return p.weight > 100;
        });

    cout << "heavy" << endl;
    for(auto &p: heavy)
        cout << p << endl;
}

void execute_d() {
    auto comp = [](const Person &a, const Person &b) -> uint32_t {
        return a.weight < b.weight;
    };

    cout << *min_element(people.cbegin(), people.cend(), comp) << endl;
    cout << *max_element(people.cbegin(), people.cend(), comp) << endl;
}

int main() {
    
    cout << "a" << endl;
    execute_a();

    cout << endl << endl << "b" << endl;
    execute_b();

    cout << endl << endl << "c" << endl;
    execute_c();

    cout << endl << endl << "d" << endl;
    execute_d();
}
