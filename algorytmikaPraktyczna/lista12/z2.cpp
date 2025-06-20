#include<bits/stdc++.h>
using namespace std;

#define endl '\n'

class KMP {
private:
    string pattern;
    vector<int> lps;

    void make_lps() {
        lps.resize(pattern.size());

        for(int i = 1; i < pattern.size(); i++) {
            int len = lps[i - 1];
            while(len and pattern[i] != pattern[len])
                len = lps[len - 1];
            
            if(pattern[i] == pattern[len])
                len++;
            
            lps[i] = len;
        }
    }

public:
    KMP() {
        cin >> pattern;
        make_lps();
    }

    void solve() {
        int len = lps[pattern.size() - 1];
        stack<int> s;

        while(len) {
            s.push(len);
            len = lps[len - 1];
        }

        while(!s.empty()) {
            cout << s.top() << ' ';
            s.pop();
        }

        cout << endl;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    KMP kmp;
    kmp.solve();
}