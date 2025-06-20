#include<bits/stdc++.h>
using namespace std;

#define int long long

struct Node {
    Node* next[26];
    Node* fail;
    vector<int> output;
    int cnt;

    Node() : fail(nullptr), cnt(0) {
        for(int i = 0; i < 26; i++)
            next[i] = nullptr;
    }
};

class Authomata {
private:
    int k;
    Node* root;
    string text;
    vector<string> patterns;
    vector<int> occ;
    vector<Node*> order;

    void get_input() {
        cin >> text;
        cin >> k;

        patterns.resize(k + 1);
        for(int i = 1; i <= k; i++)
            cin >> patterns[i];
    }

    void make_trie() {
        for(int i = 1; i <= k; i++) {
            Node* now = root;
            for(auto c: patterns[i]) {
                if(now -> next[c - 'a'] == nullptr) 
                    now -> next[c - 'a'] = new Node;
                
                now = now -> next[c - 'a'];
            }

            now -> output.push_back(i);
        } 
    }

    void add_edges() {
        queue<Node*> q;
        root -> fail = root;

        for(int c = 0; c < 26; c++) {
            if(root -> next[c]) {
                root -> next[c] -> fail = root;
                q.push(root -> next[c]);
                order.push_back(root -> next[c]);
            } 
        }

        while(!q.empty()) { 
            Node* u = q.front(); q.pop();
            for(int c = 0; c < 26; c++) {
                Node* v = u -> next[c];
                if(v) {
                    Node* f = u -> fail;
                    while(f != root and !f -> next[c]) f = f -> fail;
                    if(f -> next[c]) f = f -> next[c];

                    v -> fail = f;
                    q.push(v);
                    order.push_back(v);
                } 
            }
        }
    }

public:
    Authomata() {
        root = new Node;

        get_input();
        make_trie();
        add_edges();
    }

    ~Authomata() {
        delete root;
    }

    void count_pattern_occurences() {
        occ.resize(k + 1);
        Node* v = root;

        for(auto c: text) {
            while(v != root and !v -> next[c - 'a']) v = v ->fail;
            if(v -> next[c - 'a']) v = v -> next[c - 'a'];
            v -> cnt++;
        }

        for(int i = order.size() - 1; i >= 0; i--) {
            auto u = order[i];
            if(u -> fail)
                u -> fail -> cnt += u -> cnt;
        }

        for(auto u: order)
            for(auto id: u -> output)
                occ[id] += u -> cnt;
    }

    void print_pattern_occurences() {
        for(int i = 1; i <= k; i++)
            cout << occ[i] << '\n';
    }
};

signed main() {
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    Authomata authomata;
    authomata.count_pattern_occurences();
    authomata.print_pattern_occurences();
}