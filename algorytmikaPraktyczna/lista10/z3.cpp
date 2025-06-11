#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

struct Point {
    double x, y;

    Point(double x = 0, double y = 0) : x(x), y(y) {}

    friend istream& operator >> (istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

    Point operator - (const Point& other) {
        return Point(x - other.x, y - other.y);
    }

    double distance(const Point &other) {
        double xx = x - other.x;
        double yy = y - other.y;
        return sqrt(xx * xx + yy * yy);
    }

    static int cross_product(const Point a, const Point b) {
        return a.x * b.y - b.x * a.y;
    }
};

struct Line {
    Point p1, p2;

    friend istream& operator >> (istream& in, Line& p) {
        in >> p.p1 >> p.p2;
        return in;
    }

    double distance(Point p) {
        if(p1.x == p2.x) {
            return llabs(p.x - p1.x);
        } else {
            double a = (p1.y - p2.y) / (p1.x - p2.x);
            double b = p1.y - a * p1.x;

            double d = fabs(a * p.x - p.y + b) / sqrt(1.0 + a * a); 
            return d;
        }
    }
};

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cout << fixed << setprecision(12);
    
    int t; cin >> t;
    while(t--) {
        Line l; cin >> l;
        Point p; cin >> p;

        cout << l.distance(p) << endl;
    }
}