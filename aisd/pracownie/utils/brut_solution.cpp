#include<bits/stdc++.h>
using namespace std;

#define int long long
constexpr int MAX_BAN = 105;

int n, p, m;
struct struct_pattern{
    bool arr[3][3];

    friend istream& operator>>(istream& in, struct_pattern &p){
        char c;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                in >> c;
                p.arr[i][j] = c == '.' ? 0 : 1;
            }
        }

        return in;
    }
} pattern[MAX_BAN];

struct struct_board{
    bool arr[5][5];

    void update(int mask){
        for(int i = 0; i < 5; i++){
            for(int j = 0; j < n; j++){
                arr[i][j] = mask % 2;
                mask /= 2;
            }
        }
    }

    bool overlap(int x, int y, const struct_pattern &pat){
        x -= 2, y -= 2;
        for(int i = 0; i < 3; i++){
            for(int j = 0; j < 3; j++){
                if(arr[i + x][j + y] != pat.arr[i][j]) return 0;
            }
        }

        return 1;
    }

    bool contains_pattern(const struct_pattern &pat){
        for(int i = 2; i < 5; i++){
            for(int j = 2; j < n; j++){
                if(overlap(i, j, pat)) return 1;
            }
        }

        return 0;
    }
} board;


signed main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> p >> m;
    for(int i = 0; i < p; i++)
        cin >> pattern[i];

    // computer ans
    int ans = 0;
    for(int mask = 0; mask < (1 << (n * 5)); mask++){
        board.update(mask);
        bool ok = true;
        for(int i = 0; i < p and ok; i++)
            if(board.contains_pattern(pattern[i])) ok = false;

        if(ok) ans = (ans + 1) % m;
    }

    // print ans
    cout << ans << endl;
}