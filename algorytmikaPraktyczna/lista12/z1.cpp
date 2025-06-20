#include<bits/stdc++.h>
using namespace std;

#define endl '\n'

class KMP {
private:
    string text;
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
        cin >> text >> pattern;
        make_lps();        
    }

    int count() {
        int ans = 0, len = 0;
        for(int i = 0; i < text.size(); i++) {
            while(len and text[i] != pattern[len])
                len = lps[len - 1];
            
            if(text[i] == pattern[len])
                len++;

            if(len == pattern.size()) {
                len = lps[len - 1];
                ans++;
            }
        }

        return ans;
    }
};

int main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    KMP kmp;
    cout << kmp.count() << endl;
}