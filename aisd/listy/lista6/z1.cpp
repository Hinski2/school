#include <bits/stdc++.h>
using namespace std;

template<typename T> ostream& operator<<(ostream& os, const vector<T>& v){
    for(const auto &u: v){
        os << u << ' ';
    }
    return os;
}

template<typename T> istream& operator>>(istream& is, vector<T>& v){
    for(auto& u : v){
        is >> u;
    }
    return is;
}

template<typename T> long long sum(const vector<T> &v){
    long long s = 0;
    for(auto u: v) s += u;
    return s;
}

template<typename T> T max(const vector<T> &v){
    T maxi = v[0];
    for(auto u: v) maxi = max(maxi, u);
    return maxi;
}

template<typename T> T min(const vector<T> &v){
    T mini = v[0];
    for(auto u: v) mini = min(mini, u);
    return mini;
}

template<typename T> unsigned arg_max(const vector<T> &v){
    T maxi = v[0];
    unsigned pos = 0;
    for(unsigned i = 1; i <= v.size(); i++)
        if(v[i] > maxi){
            maxi = v[i];
            pos = i;
        }
    return pos;
}

template<typename T> unsigned arg_min(const vector<T> &v){
    T mini = v[0];
    unsigned pos = 0;
    for(unsigned i = 1; i <= v.size(); i++)
        if(v[i] < mini){
            mini = v[i];
            pos = i;
        }
    return pos;
}

#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()
#define endl '\n'
#define alf 'z' + 1
#define yn (solve() ? "YES" : "NO")

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;

const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
const int mak = 2e5 + 7;

// 10 operacji max
void sort_5(vector<int> &v, int start, int size) {
    for(int i = 1; i < size; i++) {
        int j = i;
        while(j > 0 and v[j - 1 + start] > v[j + start]) {
            swap(v[j - 1 + start], v[j + start]);
            j--;
        }
    }
}

int partition(vector<int> &v, int l, int r, int pivot_idx) {
    int pivot = v[pivot_idx];
    swap(v[pivot_idx], v[r]);

    int j = l; // wskazuje mniejsce gdzie powinien trafić następny element mniejszy od pivot
    // niezmiennik {wszystkie lementy < j są mniejsze od pivot} (więc j wspazuje nam na miejsce gdzie MOŻE znajdować się element > pivot)

    for(int i = l; i < r; i++) {
        if(v[i] < pivot)
            swap(v[j++], v[i]);
    }

    swap(v[j], v[r]);
    return j;
}

pair<int, int> get_pseudo_mean(vector<int> &v, int l, int r) { // <pos, val>
    while(r - l + 1 > 5) {
        int pos = l + 1;
        for(int i = l; i <= r; i += 5) {
            int len = min(5, r - i + 1);
            sort_5(v, i, len);
            swap(v[pos++], v[i + len / 2]);
        }
        r = pos - 1;
    } 

    sort_5(v, l, r - l + 1);
    return {l + (r - l) / 2, v[l + (r - l) / 2]};
}

int get_mean(vector<int> &v, int l, int r) {
    int target_pos = (l + r) / 2;

    while(true) {
        auto [pos_pseude_mean, pseudo_mean] = get_pseudo_mean(v, l, r);
        int pos_pivot = partition(v, l, r, pos_pseude_mean);

        if(pos_pivot == target_pos) return pseudo_mean;
        else if(pos_pivot > target_pos) r = pos_pivot - 1;
        else l = pos_pivot + 1;
    }
}

int get_pos(vector<int> &v, int l, int r, int val) {
    for(int i = l; i <= r; i++)
        if(v[i] == val) return i;

    return -1;
}


void quick_sort(vector<int> &v) {
    int mean = get_mean(v, 0, v.size() - 1);
    partition(v, 0, v.size() - 1, get_pos(v, 0, v.size() - 1, mean));

    int LEN = 1;
    while(LEN * 2 < v.size())
        LEN *= 2;

    for(int len = LEN; len > 1; len /= 2) {
        for(unsigned long i = 0; i < v.size(); i += len) {
            int r = min(i + len - 1, v.size() - 1);

            // find pivot in v[i: i + len)
            int mean = get_mean(v, i, r - 1);
            

            // split into three cathegories
            partition(v, i, r, get_pos(v, i, r, mean));
        }
    }

    for(int len = LEN; len > 1; len /= 2) {
        for(unsigned long i = v.size() - LEN; i < v.size(); i += len) {
            int r = min(i + len - 1, v.size() - 1);

            // find pivot in v[i: i + len)
            int mean = get_mean(v, i, r);

            // split into three cathegories
            partition(v, i, r, get_pos(v, i, r, mean));
        }
    }
}

int main(){
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    int n; cin >> n;
    vector<int> v(n); cin >> v;
    quick_sort(v);
    cout << v << endl;
}


