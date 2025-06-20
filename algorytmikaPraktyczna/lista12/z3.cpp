#include<bits/stdc++.h>
using namespace std;

typedef int32_t i32;
typedef int64_t i64;

constexpr i64 mod = 1e9 + 7;
constexpr i64 m_input = 5005;

string text;
i64 dp[m_input];

struct Node {
    i64 end;
    Node* next[26];

    Node() {
        end = 0;
        for(int i = 0; i < 26; i++)
            next[i] = nullptr;
    }

    ~Node() {
        for(int i = 0; i < 26; i++) {
            delete next[i];
        }
    }
};

class Trie {
private:
    i32 n;
    Node* root;

    void add_string() {
        string s; cin >> s;
        Node* now = root;
        for(auto c: s) {
            if(now -> next[c - 'a'] == nullptr) {
                now -> next[c - 'a'] = new Node;
            } 

            now = now -> next[c - 'a'];
        }

        now -> end++;
    }

public:
    Trie() {
        root = new Node;
        cin >> n; 
        for(int i = 0; i < n; i++) {
            add_string();
        }
    }

    ~Trie() {
        delete root;
    }

    i64 count(i32 l, i32 r) {
        Node* now = root;
        for(int i = l; i < r; i++) {
            char& c = text[i];
            if(now -> next[c - 'a'] == nullptr) return 0;
            now = now -> next[c - 'a'];
        }

        return now -> end;
    }

    void compute_dp(i32 tail_len) {
        Node* now = root;
        for(int i = tail_len - 1, str_idx = text.size() - tail_len; i >= 0; i--, str_idx++) {
            if(now == nullptr) break;

            now = now -> next[text[str_idx] - 'a'];
            dp[tail_len] += dp[i] * (now != nullptr ? now -> end: 0);
            dp[tail_len] %= mod;
        }
    }
};


int main() { 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> text;
    Trie trie;

    dp[0] = 1;
    for(int tail_len = 1; tail_len <= text.size(); tail_len++) {
        trie.compute_dp(tail_len);
    }

    cout << dp[text.size()] << endl;
}