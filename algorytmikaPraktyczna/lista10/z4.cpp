#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'

template<typename T> 
istream& operator >> (istream& in, vector<T> &v) {
    for(auto &u: v)
        in >> u;
    return in;
} 

struct Point {
    static Point start_p;

    int x, y;
    Point(int x = 0, int y = 0) : x(x), y(y) {}

    friend istream& operator >> (istream& in, Point& p) {
        in >> p.x >> p.y;
        return in;
    }

    Point operator - (const Point& other) const {
        return Point(x - other.x, y - other.y);
    }

    static int cross_product(const Point a, const Point b) {
        return a.x * b.y - b.x * a.y;
    }

    int int_dist(const Point &other) const {
        int xx = x - other.x;
        int yy = y - other.y;
        return xx * xx + yy * yy;
    }

    bool operator < (const Point &other) const {
        int cross = cross_product(*this - start_p, other - start_p); 

        if(cross < 0) return 0;
        else if(cross > 0) return 1;
        else return int_dist(start_p) < other.int_dist(start_p);
    }
};

Point Point::start_p;

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> Point::start_p.x;

    int n; cin >> n;
    vector<Point> points(n); cin >> points;
    sort(points.begin(), points.end());

    int ans = 1;
    Point last = points[0];
    for(int i = 1; i < n; i++) {
        if(Point::cross_product(last - Point::start_p, points[i] - Point::start_p))
            ans++;
        last = points[i];
    }

    cout << ans << endl;
}