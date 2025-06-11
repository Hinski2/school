#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Point {
    int x, y;

    Point(int x = 0, int y = 0) : x(x), y(y) {}

    friend istream& operator >> (istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

    Point operator - (const Point& other) {
        return Point(x - other.x, y - other.y);
    }

    static int cross_product(const Point a, const Point b) {
        return a.x * b.y - b.x * a.y;
    }
};

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int t; cin >> t;
    while(t--) {
        Point a, b, c; cin >> a >> b >> c;
        int cp = Point::cross_product(c - a, b - a);

        if(cp < 0) cout << "LEFT" << endl;
        else if(cp > 0) cout << "RIGHT" << endl;
        else cout << "TOUCH" << endl;
    }
}