#include <bits/stdc++.h>
using namespace std;


struct Segment{
    int u, d, idx;

    bool operator < (const Segment &other) const { 
        if(d != other.d) return d < other.d;
        return u < other.u;
    }
};

istream& operator >> (istream &in, vector<Segment> &v){
    for(int i = 0; i < v.size(); i++){
        auto &u = v[i];
        cin >> u.u >> u.d;
        u.idx = i;
    }

    return in;
}

int main(){
    // get input 
    int n; cin >> n;
    vector<Segment> segments(n); cin >> segments;

    // process data
    sort(segments.begin(), segments.end());

    // make dp
    vector<int> p(n, -1);       // parrent's idx
    vector<pair<int, int>> dp;  // (val, idx)

    for(auto [u, d, idx]: segments){
        if(dp.empty() or dp.back().first < u){
            if(!dp.empty()){
                p[idx] = dp.back().second;
            }
            dp.push_back({u, idx});
        } else {
            auto pos = upper_bound(dp.begin(), dp.end(), u, [](const int &b, const pair<int, int> &a){
                return b < a.first;
            });

            p[idx] = p[pos -> second];
            *pos = {u, idx};
        }

    }

    // retrive path
    int idx = dp.back().second;
    while(idx != -1){
        cout << idx << endl;
        idx = p[idx]; 
    }
}