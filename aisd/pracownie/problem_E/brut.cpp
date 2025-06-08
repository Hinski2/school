#include <bits/stdc++.h>
using namespace std;

#define endl '\n'

class Turbo_smart_struct {
private:
    vector<int> vals;

    void shift_left(int pos){
        for(int i = pos; i + 1 < vals.size(); i++)
            vals[i] = vals[i + 1];
        vals.pop_back();
    }

    void shift_right(int pos){
        vals.push_back(0);
        for(int i = vals.size() - 1; i > pos; i--)
            vals[i] = vals[i - 1];
    }

public:
    void insert(int pos, int val){
        if(pos == vals.size()) vals.push_back(val);
        else {
            shift_right(pos);
            vals[pos] = val;
        }
    }

    void del(int pos){
        vals[pos] = 0;
        shift_left(pos);
    }

    int64_t sum(int p1, int p2){
        int64_t suma = 0;
        for(int i = p1; i <= p2; i++)
            suma += vals[i];
        return suma;
    }
};

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int q; cin >> q;
    Turbo_smart_struct tss;

    while(q--){
        char c; cin >> c;
        if(c == 'I'){
            int pos, x; cin >> pos >> x;
            tss.insert(pos, x);
        } else if(c == 'S') {
            int p1, p2; cin >> p1 >> p2;
            cout << tss.sum(--p1, --p2) << endl;
        } else {
            int pos; cin >> pos;
            tss.del(--pos);
        }
    }
}
