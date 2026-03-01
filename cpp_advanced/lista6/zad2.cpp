#include <bits/stdc++.h>
#include <cstdint>
#include <cstdio>
#include <ranges>
using namespace std;

struct Point {
    double x, y;
    uint8_t r, g, b;
    string name;


    uint8_t quadrant() const  {
        if(x > 0 and y > 0) return 1;
        if(x <= 0 and y > 0) return 2;
        if(x <= 0 and y <= 0) return 3;
        return 4;
    }

    double brightness() const {
        return 0.3 * this -> r + 0.59 * this -> g + 0.11 * this -> b;
    }

    friend ostream& operator << (ostream& out, const Point &p) {
        out << "{ ";
        out << "name: " << p.name << ", "
            << "x: "    << p.x << ", "
            << "y: "    << p.y << ", "
            << "r: "    << static_cast<int>(p.r) << ", "
            << "g: "    << static_cast<int>(p.g) << ", "
            << "b: "    << static_cast<int>(p.b);

        out << " }";
        return out;
    }
};

list<Point> points = {
    {.x = 13.4, .y = 4.3,  .r = 255, .g = 0,   .b = 0,   .name = "red"},
    {.x = -5.2, .y = 8.1,  .r = 0,   .g = 255, .b = 0,   .name = "green"},
    {.x = 1.0,  .y = -3.7, .r = 0,   .g = 0,   .b = 255, .name = "blue"},
    {.x = 0.0,  .y = 0.0,  .r = 255, .g = 255, .b = 255, .name = "white"},
    {.x = -9.5, .y = -2.4, .r = 0,   .g = 0,   .b = 0,   .name = "black"},
    {.x =  3.2, .y = -1.1, .r = 123, .g =  45, .b = 210, .name = "a"},
    {.x = -7.8, .y =  9.4, .r =  12, .g = 200, .b =  33, .name = "b"},
    {.x =  5.5, .y =  6.6, .r =  90, .g =  90, .b =  90, .name = "c"},
    {.x = -4.1, .y = -8.9, .r = 250, .g = 100, .b =  50, .name = "d"},
    {.x = 11.0, .y =  2.2, .r =  10, .g =  10, .b = 220, .name = "e"},
    {.x = -3.3, .y =  4.4, .r =  99, .g = 199, .b =  88, .name = "f"},
    {.x =  7.1, .y = -2.6, .r = 255, .g = 140, .b =   0, .name = "g"},
    {.x = -1.7, .y = -5.5, .r =  20, .g =  20, .b =  20, .name = "h"},
    {.x =  6.6, .y =  8.8, .r = 100, .g = 255, .b = 100, .name = "i"},
    {.x =  2.0, .y = -7.7, .r = 180, .g =  60, .b =  60, .name = "j"},
    {.x = -8.4, .y =  1.1, .r = 110, .g =  30, .b = 200, .name = "k"},
    {.x =  9.5, .y =  3.3, .r = 220, .g = 220, .b =  50, .name = "l"},
    {.x =  4.8, .y = -9.9, .r =  80, .g = 160, .b = 240, .name = "m"},
    {.x = -6.0, .y =  7.2, .r = 255, .g =  50, .b = 150, .name = "n"},
    {.x =  0.9, .y = -3.3, .r =  15, .g = 150, .b = 255, .name = "o"},
    {.x = 12.2, .y =  4.4, .r = 200, .g = 200, .b =   5, .name = "p"},
    {.x = -2.5, .y =  5.5, .r =  70, .g =  30, .b = 100, .name = "q"},
    {.x =  3.7, .y =  1.8, .r = 147, .g =   3, .b =  83, .name = "rrrrrrrrrr"},
};

void execute_a() {
    auto filtered = points
        | views::filter([](const Point &p){
            return p.name.size() <= 5;     
        });

    list<Point> new_points(filtered.begin(), filtered.end());
    points = move(new_points);

    for(auto &p: points)
        cout << p << endl;
}

void execute_b() {
    auto count_point_in_quadrant = [](uint8_t q) {
        auto rng = points 
            | views::filter([q](const Point &p) { return p.quadrant() == q; });
    
        return ranges::distance(rng);
    };

    for(uint8_t i: {0, 1, 2, 3})
    cout << static_cast<int>(i) << ' ' << count_point_in_quadrant(i) << endl;
}

void execute_c() {
    auto comp = [](const Point &a, const Point &b) {
        return a.brightness() < b.brightness();
    };
    
    points.sort(comp); // listy amja własny algorytm sortowania

    for(auto &p: points)
        cout << p << endl;
}

void execute_d() {
    auto filtered = points
        | views::filter([](const Point &p){ return p.brightness() < 64.; });
    
    list<Point> dimmed(filtered.begin(), filtered.end());

    cout << "size: " << dimmed.size() << endl;
    for(auto &p: dimmed)
        cout << p << endl;
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
