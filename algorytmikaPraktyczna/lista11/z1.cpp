#include<bits/stdc++.h>
using namespace std;

typedef int64_t i64;

class Hsh {
private:
    string s;
    vector<pair<i64, i64>> pref;
    vector<pair<i64, i64>> pow;

    static constexpr i64 p = 31;
    static constexpr i64 mod[2] = {1'000'000'007, 1'000'000'123};

    void hsh_string() {
        pref.resize(s.size());
        pow.resize(s.size());
        pow[0] = {1, 1};
        
        for(i64 i = 1; i < s.size(); i++) {
            pow[i].first = (pow[i - 1].first * p) % mod[0];
            pow[i].second = (pow[i - 1].second * p) % mod[1];

            pref[i].first = (pref[i - 1].first * p + (s[i] - 'a')) % mod[0];
            pref[i].second = (pref[i - 1].second * p + (s[i] - 'a')) % mod[1];
        }
    }

public:
    inline i64 size() {
        return s.size();
    }

    pair<i64, i64> operator ()(i64 l, i64 r) {
        if(l > r) return {0, 0};
        
        pair<i64, i64> ans = {0, 0};
        ans.first = (pref[r].first - (pref[l - 1].first * pow[r - (l - 1)].first) % mod[0] + mod[0]) % mod[0];
        ans.second = (pref[r].second - (pref[l - 1].second * pow[r - (l - 1)].second) % mod[1] + mod[1]) % mod[1];

        return ans;
    }

    pair<i64, i64> all() {
        return (*this)(1, size() - 1);
    }

    i64 count(Hsh& other) {
        int n = other.size(), cnt = 0;

        for(int i = n - 1; i < size(); i++) {
            cnt += other.all() == (*this)(i - n + 2, i);
        }

        return cnt;
    }

    friend istream& operator>>(istream& in, Hsh& hsh) {
        in >> hsh.s;
        hsh.s = " " + hsh.s; 
        hsh.hsh_string();

        return in;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Hsh a, b; cin >> a >> b;
    cout << a.count(b) << endl;
}