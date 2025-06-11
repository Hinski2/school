#include<bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
typedef int64_t i64;

class Hsh {
private:
    string s;
    vector<pair<i64, i64>> hsh_inc, hsh_dec;
    vector<pair<i64, i64>> pow;

    static constexpr i64 p = 31;
    static constexpr i64 mod[2] = {1'000'000'007, 1'000'000'123};

    void hsh_string() {
        hsh_inc.resize(s.size());
        hsh_dec.resize(s.size());
        pow.resize(s.size());
        pow[0] = {1, 1};
        
        for(i64 i = 1; i < s.size(); i++) {
            pow[i].fi = (pow[i - 1].fi * p) % mod[0];
            pow[i].se = (pow[i - 1].se * p) % mod[1];

            hsh_dec[i].fi = (hsh_dec[i - 1].fi * p + (s[i] - 'a')) % mod[0];
            hsh_dec[i].se = (hsh_dec[i - 1].se * p + (s[i] - 'a')) % mod[1];

            hsh_inc[i].fi = (hsh_inc[i - 1].fi + pow[i - 1].fi * (s[i] - 'a')) % mod[0];
            hsh_inc[i].se = (hsh_inc[i - 1].se + pow[i - 1].se * (s[i] - 'a')) % mod[1];
        }
    }

    pair<i64, i64> get_hsh_dec(i64 l, i64 r) {
        if(l > r) return {0, 0};
        
        pair<i64, i64> ans = {0, 0};
        ans.fi = (hsh_dec[r].fi - (hsh_dec[l - 1].fi * pow[r - (l - 1)].fi) % mod[0] + mod[0]) % mod[0];
        ans.se = (hsh_dec[r].se - (hsh_dec[l - 1].se * pow[r - (l - 1)].se) % mod[1] + mod[1]) % mod[1];

        return ans;
    }

    pair<i64, i64> get_hsh_inc(i64 l, i64 r) {
        if(l > r) return {0, 0};

        pair<i64, i64> ans;
        ans.fi = ((hsh_inc[r].fi - hsh_inc[l - 1].fi) % mod[0] + mod[0]) % mod[0];
        ans.se = ((hsh_inc[r].se - hsh_inc[l - 1].se) % mod[1] + mod[1]) % mod[1];

        return ans;
    }

public:
    bool is_palindrom(int l, int r) {
        auto hsh_d = get_hsh_dec(l, r);
        auto hsh_i = get_hsh_inc(l, r);

        hsh_d = {(hsh_d.fi * pow[l - 1].fi) % mod[0], (hsh_d.se * pow[l - 1].se) % mod[1]};
        return hsh_i == hsh_d;
    }

    bool contains_palindrom_with_len(int len) {
        for(int i = len; i < size(); i++)
            if(is_palindrom(i - len + 1, i)) return 1;
        
        return 0;
    }

    void print_palindrom_with_len(int len) {
        int l, r;
        for(int i = len; i < size(); i++) {
            if(is_palindrom(i - len + 1, i)) {
                l = i - len + 1;
                r = i;
                break;
            }
        }

        for(; l <= r; l++)
            cout << s[l];
        cout << endl;
    }

    inline i64 size() {
        return s.size();
    }

    friend istream& operator>>(istream& in, Hsh& hsh) {
        in >> hsh.s;
        hsh.s = " " + hsh.s; 
        hsh.hsh_string();

        return in;
    }
};

int main() {
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Hsh a; cin >> a;

    // even
    int l = 0, r = a.size();
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if(a.contains_palindrom_with_len(mid * 2)) l = mid;
        else r = mid - 1;
    }

    int even_ans = a.contains_palindrom_with_len(l * 2) * (l * 2);

    // odd
    l = 0, r = a.size();
    while(l < r) {
        int mid = (l + r + 1) / 2;
        if(a.contains_palindrom_with_len(mid * 2 + 1)) l = mid;
        else r = mid - 1;
    }

    int odd_ans = a.contains_palindrom_with_len(l * 2 + 1) * (l * 2 + 1);
    a.print_palindrom_with_len(max(even_ans, odd_ans));
}