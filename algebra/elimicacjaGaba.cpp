#include <bits/stdc++.h>
#include <ext/pb_ds/assoc_container.hpp>
#include <ext/pb_ds/tree_policy.hpp>

using namespace std;
using namespace __gnu_pbds;

template<typename T>
std::ostream& operator<<(std::ostream& os, const std::vector<T>& v){
    for(const auto &u: v){
        os << u << ' ';
    }
    return os;
}
template<typename T>
std::istream& operator>>(std::istream& is, std::vector<T>& v){
    for(auto& u : v){
        is >> u;
    }
    return is;
}

#define fi first
#define se second
#define pb push_back
#define all(a) a.begin(), a.end()
#define endl '\n'
#define alf 'z' + 1
#define io ios_base::sync_with_stdio(0), cin.tie(0), cout.tie(0)
#define yn (solve() ? "YES" : "NO")

typedef long long ll;
typedef pair<int, int> pii;
typedef pair<ll, ll> pll;
typedef tree<int,null_type, less<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_set;
typedef tree<int, null_type, less_equal<int>, rb_tree_tag,
tree_order_statistics_node_update> ordered_multiset;
//erase: oms.erase(oms.upper_bound(value))

const int mod = 1e9 + 7;
const int inf = 1e9 + 7;
const int mak = 2e5 + 7;

int n, m;
vector<vector<ll>> matrix;
void wczytaj_dane(){
    cout << "Jaki jest twój rozmiar macierzy wojowniku?" << endl;
    cin >> n >> m;

    matrix.resize(n);
    for(int i = 0; i < n; i++) matrix[i].resize(m);

    cout << "podaj ją" << endl;
    for(int i = 0; i < n; i++) cin >> matrix[i];

    cout << "ok, teraz podaj co ma wyjść" << endl;
    m += 1;
    for(int i = 0, x; i < n; i++){
        cin >> x;
        matrix[i].pb(x);
    }
    cout << "git oto twoje rorzwiązanie" << endl; 
}

void wypisz_matrix(int krok){
    cout << "krok " << krok << ':' << endl;
    for(int i = 0; i < n; i++){
        for(int j = 0; j < m; j++)  cout << matrix[i][j] << ' ';
        cout << endl;
    }
}

int c;
bool cmp(const vector<ll> &a, const vector<ll> &b){
    return a[c] < b[c];
}

bool vector_zerowy(const vector<ll> &v){
    for(auto u: v)
        if(u) return false;
    return true;
}

void zmniejsz(vector<ll> &v){
    ll g = v[0];
    for(auto u: v) g = __gcd(u, g);

    if(g == 0) return;
    for(auto &u: v) u /= g;
}

void oblicz(){
    int END = n - 1;
    for(int i = 0; i <= END; i++, c++){
        //sortowanie
        sort(matrix.begin() + i, matrix.begin() + END + 1, cmp);

        //sprawdzenie czy pierwszy vector jest zerowy
        if(vector_zerowy(matrix[i])){
            swap(matrix[i], matrix[END]);
            END--;
        }

        //odejmowanie
        for(int j = i + 1; j <= END; j++){
            ll m1 = matrix[i][c], m2 = matrix[j][c];
            
            for(int k = 0; k < m; k++)
                matrix[j][k] = matrix[j][k] * m1 - matrix[i][k] * m2;
            
            zmniejsz(matrix[j]);
        }

        //wypisanie
        wypisz_matrix(i);
    }
}

int main(){
    wczytaj_dane();
    oblicz();
    cout << "EZZ" << endl;
}
