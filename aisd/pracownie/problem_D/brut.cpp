#include<bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MAX_PT_NO = 1e6 + 5;
int n;

struct struct_point{
    int x, y;

    friend istream& operator>> (istream &in, struct_point &pt){
        cin >> pt.x >> pt.y;
        return in;
    }

    friend ostream& operator << (ostream &out, struct_point &pt){
        cout << pt.x << ' ' << pt.y;
        return out;
    }

    int dist(const struct_point &other){
        return (x - other.x) * (x - other.x) + 
                (y - other.y) * (y - other.y); 
    }

    // <dist, arg_min>
    pair<double, int> closest(struct_point *points){
        int min_dist = INT64_MAX, arg_min_dist = 0;

        for(int i = 0; i < n; i++){
            if(&points[i] == this) continue;

            int dist = this -> dist(points[i]);
            if(dist < min_dist){
                min_dist = dist;
                arg_min_dist = i;
            }
        } 

        return {min_dist, arg_min_dist};
    }

} points[MAX_PT_NO];

signed main(){
    // get input 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    for(int i = 0; i < n; i++){
        cin >> points[i];
    }

    // get ans
    struct_point p1, p2;
    int min_dist = INT64_MAX;
    for(int i = 0; i < n; i++){
        auto [dist, idx] = points[i].closest(points);

        if(dist < min_dist){
            min_dist = dist;
            p1 = points[i];
            p2 = points[idx];
        }
    }

    // print ans 
    cout << p1 << endl << p2 << endl;

}