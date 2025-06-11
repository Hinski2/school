#include<bits/stdc++.h>
using namespace std;

#define int long long
#define endl '\n'
constexpr int inf = 1e9 + 7;

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

    static int cross_product(const Point a, const Point b, const Point c){
	    int _x = (b.x - a.x) * (c.y - a.y);
	    int _y = (c.x - a.x) * (b.y - a.y);

	    return _x - _y;
    }

    int int_dist(const Point &other) const {
        int xx = x - other.x;
        int yy = y - other.y;
        return xx * xx + yy * yy;
    }

    bool operator < (const Point &other) const {
        int cross = cross_product(start_p, *this, other); 

        if(cross > 0) return true;
        else if(cross < 0) return false;
        else return int_dist(start_p) < other.int_dist(start_p);
    }

    bool lex_cmp(const Point &other) const {
        if(x != other.x) return x < other.x;
        return y < other.y;
    }
};

Point min(vector<Point> &v) {
    Point ans = v[0];
    for(auto &p: v) {
        if(p.y < ans.y or (p.y == ans.y and p.x < ans.x))
            ans = p;
    }

    return ans;
}

Point Point::start_p;

void make_and_print_convex_hull(vector<Point> &points) {
    vector<Point> lower, upper;
    lower.reserve(points.size() + 10);
    upper.reserve(points.size() + 10);

    for(auto p: points) {
        while(lower.size() >= 2 and Point::cross_product(lower[lower.size() - 2], lower[lower.size() - 1], p) < 0)
            lower.pop_back();

        lower.push_back(p);
    }

    for(int i = points.size() - 1; i >= 0; i--) {
        auto &p = points[i];

        while(upper.size() >= 2 and Point::cross_product(upper[upper.size() - 2], upper[upper.size() - 1], p) < 0)
            upper.pop_back();

        upper.push_back(p);
    }

    lower.pop_back();
    upper.pop_back();

    for(auto u: upper)
        lower.push_back(u);

    sort(lower.begin(), lower.end(), [](const Point &a, const Point &b){
        return a.lex_cmp(b);
    });

    cout << lower.size() << endl;
    for(auto p: lower) 
        cout << p.x << ' ' << p.y << endl;
}

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);

    int n; cin >> n;
    vector<Point> points(n); cin >> points;
    Point::start_p = min(points);

    sort(points.begin(), points.end(), [](const Point &a, const Point &b){
        return a.lex_cmp(b);
    });

    make_and_print_convex_hull(points);
}