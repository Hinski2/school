#include<bits/stdc++.h>
using namespace std;

typedef int64_t i64;

class Hsh {
private:
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
    int n;
    string s;

    Hsh() {
        cin >> s;
        n = s.size();
        s = ' ' + s + s;

        hsh_string();
    }

    inline i64 size() const {
        return s.size();
    }

    int lcp(int start_a, int start_b) const {
        int l = 0, r = n;
        while(l < r) {
            int mid = (l + r + 1) / 2;
            if((*this)(start_a, start_a + mid - 1) == (*this)(start_b, start_b + mid - 1)) l = mid;
            else r = mid - 1;
        }

        return l;
    }

    pair<i64, i64> operator ()(i64 l, i64 r) const {
        if(l > r) return {0, 0};
        
        pair<i64, i64> ans = {0, 0};
        ans.first = (pref[r].first - (pref[l - 1].first * pow[r - (l - 1)].first) % mod[0] + mod[0]) % mod[0];
        ans.second = (pref[r].second - (pref[l - 1].second * pow[r - (l - 1)].second) % mod[1] + mod[1]) % mod[1];

        return ans;
    }
};

int main() {
    // get input 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Hsh hsh;

    // find ans
    int best_start = 1;
    for(int i = 2; i <= hsh.n; i++) {
        int lcp = hsh.lcp(best_start, i);
        if(hsh.s[best_start + lcp] > hsh.s[i + lcp]) {
            best_start = i;
        }
    }

    // print ans
    for(int i = 0; i < hsh.n; i++)
        cout << hsh.s[best_start + i];
    cout << endl;
}