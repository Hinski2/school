#include <bits/stdc++.h>
using namespace std;
typedef long long ll;
#define UwU cin.tie(0); cout.tie(0); ios::sync_with_stdio(0);

struct Point {
    ll x, y;
    friend Point operator-(const Point& a, const Point& b) {
        return Point{a.x - b.x, a.y - b.y};
    }

    friend ostream& operator<<(ostream& out, const Point& a) {
        out << a.x << ' ' << a.y;
        return out;
    }

    friend bool operator<(const Point& a, const Point& b) {
        return a.x < b.x || (a.x == b.x && a.y < b.y);
    }

    friend bool operator,(const Point& a, const Point& b) {
        return a.y < b.y;
    }
};

typedef pair<Point, Point> two;

ll norm(const Point& a) {
    return a.x * a.x + a.y * a.y;
}

ll dist2(const Point& a, const Point& b) {
    return norm(a - b);
}

two brute(vector<Point>& px, int l, int r, ll& best) {
    best = LLONG_MAX;
    two res;
    for (int i = l; i <= r; ++i) {
        for (int j = i + 1; j <= r; ++j) {
            ll d = dist2(px[i], px[j]);
            if (d < best) {
                best = d;
                res = {px[i], px[j]};
            }
        }
    }
    return res;
}

two get(vector<Point>& px, vector<Point>& py, int l, int r, ll& best) {
    if (r - l <= 3) return brute(px, l, r, best);

    int mid = (l + r) / 2;
    Point m = px[mid];

    vector<Point> pl, pr;
    for (auto point : py) {
        if (point < m) pl.push_back(point);
        else pr.push_back(point);
    }

    ll dl, dr;
    two left = get(px, pl, l, mid, dl);
    two right = get(px, pr, mid + 1, r, dr);

    best = dl;
    two res = left;
    if (dr < dl) {
        best = dr;
        res = right;
    }

    vector<Point> strip;
    for (auto point : py) {
        if ((point.x - m.x) * (point.x - m.x) < best)
            strip.push_back(point);
    }

    for (int i = 0; i < (int)strip.size(); ++i) {
        for (int j = i + 1; j < (int)strip.size() && (strip[j].y - strip[i].y) * (strip[j].y - strip[i].y) < best; ++j) {
            ll d = dist2(strip[i], strip[j]);
            if (d < best) {
                best = d;
                res = {strip[i], strip[j]};
            }
        }
    }
    return res;
}

int main() {
    UwU;
    int n; cin >> n;
    vector<Point> points(n);
    for (int i = 0; i < n; i++) {
        cin >> points[i].x >> points[i].y;
    }

    vector<Point> px = points, py = points;
    sort(px.begin(), px.end());
    sort(py.begin(), py.end(), [](const Point& a, const Point& b) {
        return a.y < b.y;
    });

    ll best;
    auto [a, b] = get(px, py, 0, n - 1, best);
    cout << a << "\n" << b;

    return 0;
}