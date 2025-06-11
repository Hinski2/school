#include<bits/stdc++.h>
using namespace std;

#define fi first 
#define se second
#define endl '\n'

typedef int64_t i64;
typedef uint64_t u64;

class Randomozer {
private:
    unordered_map<i64, u64> us_fi, us_se;

    u64 create_rand() {
        static std::mt19937_64 rng(std::random_device{}());
        std::uniform_int_distribution<u64> dist;

        u64 rand = dist(rng);
        if(us_fi.count(rand) or us_se.count(rand)) {
            rand = dist(rng);
        }

        return rand;
    }

public:
    pair<u64, u64> operator[](i64 val) {
        if(us_fi.count(val)) {
            return {us_fi[val], us_se[val]};
        } else {
            us_fi[val] = create_rand();
            us_se[val] = create_rand();

            return{us_fi[val], us_se[val]};
        }
    }
} randomizer;

class Hsh {
private:
    vector<i64> vals;
    vector<pair<u64, u64>> pref; 

    void hsh_vector() {
        for(i64 i = 1; i < size(); i++) {
            auto [f, s] = randomizer[vals[i]];
            pref[i].fi = pref[i - 1].fi ^ f;
            pref[i].se = pref[i - 1].se ^ s;
        }
    }

public:
    Hsh(int n) {
        vals.resize(n + 1);
        for(int i = 1; i <= n; i++)
            cin >> vals[i];

        pref.resize(n + 1);
        hsh_vector();
    }

    inline i64 size() {
        return vals.size();
    }

    pair<u64, u64> operator ()(i64 l, i64 r) {
        if(l > r) return {0, 0};
        
        pair<i64, i64> ans = {0, 0};
        ans.fi = pref[r].fi ^ pref[l - 1].fi;
        ans.se = pref[r].se ^ pref[l - 1].se;

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n, q; cin >> n >> q;
    Hsh a(n), b(n);
    while(q--) {
        int la, ra; cin >> la >> ra;
        int lb, rb; cin >> lb >> rb;

        cout << (a(la, ra) == b(lb, rb) ? "TAK" : "NIE") << endl;
    }
}