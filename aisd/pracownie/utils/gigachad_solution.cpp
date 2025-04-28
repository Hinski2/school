/*
    autor: Jakub Iliński 
    stany:
        dp[{0, 1}][mask0][mask1] = ilość dobrych konfiguracji gdy przedostatnia kolumna jest reprezento
            wana jako mask0, a ostatnia kolumna jako mask1

    przejścia:
        jeśli w połączonych kolumnach mask0, mask1, mask2 nie powstaje zakazany wzorzec 
        dp[1][mask1][maks2] += dp[0][mask0][mask1] 
*/

#include <bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MAX_BAN = 105;
constexpr int MAX_N = 5005;
constexpr int UPPER_BLOCK = 7399, MIDDLE_BLOCK = 14798, BOTTOM_BLOCK = 29596;

int n, p, mod;
int dp[2][32][32];
bool is_ok_3column[32768];

struct struct_pattern{
    bool arr[3][3];
    int hash;

    friend istream& operator>>(istream& in, struct_pattern &p){
        char c;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                in >> c;
                p.arr[i][j] = c == '.' ? 0 : 1;
            }
        }
        
        p.hash = p.hash_pattern();

        return in;
    }

    inline int hash_pattern(){
        return  arr[0][0]     + arr[0][1] * 32  + arr[0][2] * 1024 +
                arr[1][0] * 2 + arr[1][1] * 64  + arr[1][2] * 2048 +
                arr[2][0] * 4 + arr[2][1] * 128 + arr[2][2] * 4096;
    }
} pattern[105];

void preprocess(){
    for(int mask = 0; mask < 32768; mask++){
        is_ok_3column[mask] = true;

        for(int i = 0; i < p; i++){
            if((mask & UPPER_BLOCK) == pattern[i].hash or 
               (mask & MIDDLE_BLOCK) / 2 == pattern[i].hash or 
               (mask & BOTTOM_BLOCK) / 4 == pattern[i].hash
            ){
                is_ok_3column[mask] = false;
                break;
            }
        }
    }
}

void compute_dp(){
    for(int i = 3; i <= n; i++){
        // compute next state
        for(int m0 = 0; m0 < 32; m0++){
            for(int m1 = 0; m1 < 32; m1++){
                if(!dp[0][m0][m1]) continue;

                for(int m2 = 0; m2 < 32; m2++){
                    int three_column = m0 | (m1 << 5) | (m2 << 10);
                    if(!is_ok_3column[three_column]) continue;

                    dp[1][m1][m2] += dp[0][m0][m1];
                    if(dp[1][m1][m2] >= mod) dp[1][m1][m2] %= mod;
                }
            }
        }

        // copy and clean
        for(int m0 = 0; m0 < 32; m0++){
            for(int m1 = 0; m1 < 32; m1++){
                dp[0][m0][m1] = dp[1][m0][m1];  
                dp[1][m0][m1] = 0;
            }
        }
    }
}

signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> p >> mod;
    for(int i = 0; i < p; i++)
        cin >> pattern[i];

    // precompute ok 3columns
    preprocess();

    // setup dp
    for(int m0 = 0; m0 < 32; m0++){
        for(int m1 = 0; m1 < 32; m1++){
            dp[0][m0][m1] = 1;
        }
    }

    // compute ans
    compute_dp();

    int ans = 0;
    for(int m0 = 0; m0 < 32; m0++){
        for(int m1 = 0; m1 < 32; m1++){
            ans = (ans + dp[0][m0][m1]) % mod;
        }
    }

    cout << ans << endl;
}