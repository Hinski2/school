#include<bits/stdc++.h>
using namespace std;

typedef int32_t i32;
typedef int64_t i64;

i64 n, k;

struct Node {
    i64 end, sum;
    Node* next[2];

    Node() {
        end = sum = 0;
        next[0] = next[1] = nullptr;
    }

    ~Node() {
        delete next[0], next[1];
    }
};

class Trie {
private:
    i32 size;
    Node* root;

    vector<int> repr, k_repr;
    void get_binary_repr(int x) {
        repr.clear();

        for(int i = 0; i <= 20; i++) {
            repr.push_back(x % 2);
            x /= 2;
        }

        reverse(repr.begin(), repr.end());
    }

public:
    Trie() {
        root = new Node;
        size = 0;

        get_binary_repr(k);
        k_repr = repr;
    }

    ~Trie() {
        delete root;
    }

    void add_numb(int x) {
        get_binary_repr(x);
        Node* now = root;

        for(auto dig: repr) {
            if(now -> next[dig] == nullptr) {
                now -> next[dig] = new Node;
            } 

            now = now -> next[dig];
            now -> sum++;
        }

        now -> end++;
        size++;
    }

    i64 count(int x) {
        i64 ans = 0;
        Node* now = root;

        get_binary_repr(x);
        for(int i = 0; i <= 20 && now; i++) {
            const int& bit_x = repr[i];
            const int& bit_k = k_repr[i];

            if(bit_k) {
                if(now -> next[bit_x])      // 1path
                    ans += now -> next[bit_x] -> sum;
                now = now -> next[bit_x ^ 1];
            } else {                        // 0path
                now = now -> next[bit_x];
            }
        }

        return size - ans;
    }
};


int main() { 
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n >> k;

    Trie trie;
    i64 ans = 0;

    for(int i = 0; i < n; i++) {
        int x; cin >> x;
        ans += trie.count(x);
        trie.add_numb(x);
    }

    cout << ans << endl;
}