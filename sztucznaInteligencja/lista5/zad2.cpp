#include <bits/stdc++.h>
#include <sys/resource.h>
using namespace std;

#define fi first 
#define se second

typedef pair<int, int> pii;
const int mak = 70;
const int target = 677;

pii setup[25];
int score;

void print_ans(){
    cout << score << endl;
    for(int i = 1; i < 25; i++)
        if(setup[i] != make_pair(-1, -1))
            cout << 1;
        else
            cout << 0;
    cout << endl;

    char board[mak][mak];
    for(int i = 0; i < mak; i++)
        for(int j = 0; j < mak; j++)
            board[i][j] = '.';

    for(int i = 1; i < 25; i++){
        if(setup[i] == make_pair(-1, -1)) continue;
        for(int x = setup[i].first; x < setup[i].first + i; x++)
            for(int y = setup[i].second; y < setup[i].second + i; y++)
                board[x][y] = 'A' -1 + i;
    }

    for(int i = 0; i < mak; i++){
        for(int j = 0; j < mak; j++)
            cout << board[i][j];
        cout << endl;
    }
    cout << endl;
    int cnt = 0;
    for(int i = 0; i < mak; i++)
        for(int j = 0; j < mak; j++)
            cnt += board[i][j] != '.';
    cout << 70 * 70 - cnt << endl;
}

void set_block(int x, int y, int sajz){
    setup[sajz] = {x, y};
    score -= sajz * sajz;

    if(score <= target){
        print_ans();
        exit(0);
    }
}

void unset_block(int x, int y, int sajz){
    setup[sajz] = {-1, -1};
    score += sajz * sajz;
}

inline bool square_intersect(pii a, int aLen, pii b, int bLen){
    pii l1 = a, r1 = {a.fi + aLen - 1, a.se + aLen - 1};
    pii l2 = b, r2 = {b.fi + bLen - 1, b.se + bLen - 1};

    if(l1.fi > r2.fi || l2.fi > r1.fi) return false;
    if(l1.se > r2.se || l2.se > r1.se) return false;
    return true;
}

bool free_point(int x, int y, int sajz){
    for(int i = 24; i > 0; i--){
        if(setup[i] == make_pair(-1, -1)) continue;
        if(square_intersect(make_pair(x, y), sajz, setup[i], i))
            return false;
    }
    return true;
}

pii get_first_bot(int x){
    for(int j = 0; j <= mak - x; j++)
        for(int i = 0; i <= mak - x; i++)
            if(free_point(i, j, x))
                return(make_pair(i, j));
    return make_pair(-1, -1);
}

pii get_first_left(int x){
    for(int i = 0; i <= mak - x; i++)
        for(int j = 0; j <= mak - x; j++)
            if(free_point(i, j, x))
                return(make_pair(i, j));
    return make_pair(-1, -1);
}

void backtrack(bool to_l){
    // print_ans();
    for(int x = 24; x > 0; x--){
        if(setup[x] != make_pair(-1, -1)) continue;
        pii poss;

        if(to_l){
            poss = get_first_left(x);
            if(poss != make_pair(-1, -1)){
                set_block(poss.fi, poss.se, x);
                backtrack(to_l^1);
                unset_block(poss.fi, poss.se, x);
            }
            poss = get_first_bot(x);
            if(poss != make_pair(-1, -1)){
                set_block(poss.fi, poss.se, x);
                backtrack(to_l^1);
                unset_block(poss.fi, poss.se, x);
            }
        }
        else{
            poss = get_first_bot(x);
            if(poss != make_pair(-1, -1)){
                set_block(poss.fi, poss.se, x);
                backtrack(to_l^1);
                unset_block(poss.fi, poss.se, x);
            }

            poss = get_first_left(x);
            if(poss != make_pair(-1, -1)){
                set_block(poss.fi, poss.se, x);
                backtrack(to_l^1);
                unset_block(poss.fi, poss.se, x);
            }
        }
    }
}

int main(){

    //początkowe ustawienie planszy
    score = 4900;

    for(int i = 1; i < 25; i++)
        setup[i] = setup[i] = {-1, -1};

    //ustawiam ciąg fibonacciego w lewym górym rogu
    set_block(0, 0, 21);
    set_block(21, 0, 5);
    set_block(26, 0, 8);
    set_block(21, 5, 1);
    set_block(21, 6, 2);
    set_block(21, 8, 13);
    set_block(23, 5, 3);

    backtrack(1);
}