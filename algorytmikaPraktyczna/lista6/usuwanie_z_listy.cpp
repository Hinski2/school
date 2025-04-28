#include <bits/stdc++.h>
using namespace std;

constexpr int BASE = 1 << 18;
int n;

struct Node{
    int sum;
};

struct Tree{
    Node node[BASE * 2];
    int arr[BASE];

    void update_node(int v){
        node[v].sum = node[v * 2].sum + node[v * 2 + 1].sum;
    }

    void update_tree(int idx){
        while(idx){
            update_node(idx);
            idx /= 2;
        }
    }

    void build(){
        for(int i = 1; i <= n; i++){
            cin >> arr[i];
            node[i + BASE].sum = 1;
        }

        for(int i = BASE - 1; i; i--)
            update_node(i);
    }

    int find_and_remove(int k){
        int idx = 1;
        while(idx < BASE){
            if(node[idx * 2].sum >= k) idx *= 2;
            else{
                k -= node[idx * 2].sum;
                idx = idx * 2 + 1;
            }
        }

        node[idx].sum = 0;
        update_tree(idx / 2);

        return arr[idx - BASE];
    }
} tree;

int main(){
    // get input
    ios_base::sync_with_stdio(0); cin.tie(0); cout.tie(0);
    cin >> n;
    tree.build();

    // answear querries
    while(n--){
        int x; cin >> x;
        cout << tree.find_and_remove(x) << ' ';
    }

}