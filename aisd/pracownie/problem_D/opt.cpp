#include<bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MAX_PT_NO = 1e6 + 5;
constexpr int INF = 1e16;

struct Point{
    int x, y;

    friend istream& operator>> (istream &in, Point &pt){
        cin >> pt.x >> pt.y;
        return in;
    }

    friend ostream& operator << (ostream &out, Point &pt){
        cout << pt.x << ' ' << pt.y;
        return out;
    }

    bool operator < (const Point &other) const {
        if(x != other.x) return x < other.x;
        return y < other.y;
    }

    static int dist(const Point a, const Point b){
        return (a.x - b.x) * (a.x - b.x) + (a.y - b.y) * (a.y - b.y);
    }
} points[MAX_PT_NO];

struct My_vec{
    int size = 0;
    Point *item[MAX_PT_NO];

    void clear(){
        size = 0;
    }

    void add(Point *p){
        item[size++] = p;
    }

    static bool cmp(const Point *a, const Point *b){
        if(a -> y != b -> y) return a -> y < b -> y;
        return a -> x < b -> x;
    }

    void sort_by_y(){
        sort(item, item + size, cmp);
    }
} vec;

struct Ans{
    Point *p1, *p2;
    int dist;

    bool operator < (const Ans &other) const {
        return dist < other.dist;
    }

    static Ans find_ans(int l, int r){
        if(r - l + 1 <= 2){
            if(r - l + 1 < 2) return {nullptr, nullptr, INF};
            return {&points[l], &points[r], Point::dist(points[l], points[r])};
        }

        // merge ans
        int mid = (l + r) / 2;
        Ans ans_l = find_ans(l, mid);
        Ans ans_r = find_ans(mid + 1, r);
        Ans ans = min(ans_l, ans_r);

        // check the middle
        vec.clear();
        for(int i = mid; i >= l; i--){
            int d = points[i].x - points[mid].x;
            if(d * d <= ans.dist) vec.add(&points[i]);
            else break;
        }
        for(int i = mid + 1; i <= r; i++){
            int d = points[i].x - points[mid].x;
            if(d * d <= ans.dist) vec.add(&points[i]);
            else break;
        }

        vec.sort_by_y();
        for(int i = 0; i < vec.size; i++){
            for(int j = i + 1; j < i + 8 and j < vec.size; j++){
                int d = Point::dist(*vec.item[i], *vec.item[j]);
                if(d < ans.dist){
                    ans = {vec.item[i], vec.item[j], d};
                }
            }
        }

        return ans;
    }
};

signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    for(int i = 0; i < n; i++){
        cin >> points[i];
    }

    // find ans
    sort(points, points + n);
    Ans ans = Ans::find_ans(0, n - 1);
    cout << *ans.p1 << endl;
    cout << *ans.p2 << endl;
}