#include <bits/stdc++.h>
using namespace std;

constexpr int inf = 1e9 + 7;

class Heap { // min heap
private: 
    vector<int> arr;

    void build_fast(const vector<int>& vals) { // O(n)
        arr = vals;
        for(int i = vals.size() - 1; i; i--)
            shift_down(i);
    } 

    void build_slow(const vector<int>& vals) { // O(n log(n))
        for(auto u: vals) { 
            insert(u);
        }
    }

    void shift_up(int idx) {
        while(idx and arr[idx] < arr[idx / 2]) {
            swap(arr[idx], arr[idx / 2]);
            idx /= 2;
        }
    }

    void shift_down(int idx) {
        // swap with smaller
        int l_val = (*this)[idx * 2];
        int r_val = (*this)[idx * 2 + 1];

        while(arr[idx] > l_val or arr[idx] > r_val) {
            if(l_val < r_val) {
                swap(arr[idx], arr[idx * 2]);
                idx = idx * 2;
            } else {
                swap(arr[idx], arr[idx * 2 + 1]);
                idx = idx * 2 + 1;
            }

            l_val = (*this)[idx * 2];
            r_val = (*this)[idx * 2 + 1];
        }
    }

    int operator[] (int idx) {
        if(!valid_idx(idx)) return inf;
        return arr[idx];
    }

    bool valid_idx(int idx) {
        if(idx >= arr.size() or idx < 0) return false;
        return true; 
    }

    int find_idx_with_val(int val) {
        int pos = inf;

        function<void(int)> dfs = [&](int idx) -> void {
            if(!valid_idx(idx)) return;

            if(arr[idx] == val) {
                pos = idx;
            } else {
                if((*this)[idx * 2] <= val) dfs(idx * 2);
                if((*this)[idx * 2 + 1] <= val) dfs(idx * 2 + 1);
            }
        };
        
        return pos;
    }

public:
    Heap(const vector<int>& vals = {}) {
        if(!vals.empty()) {
            build_fast(vals);
        }
    }

    int pop_top() {
        int top = get_top();

        swap(arr[0], arr[arr.size() - 1]); // swap top and last elemetn
        arr.pop_back(); // remove top

        if(arr.size())
            shift_down(0);  // we need to shift down the first (former last) elemtne

        return top;
    }

    int get_top() {
        return arr[0];
    }

    void insert(int val) {
        arr.push_back(val);
        shift_up(arr.size() - 1);
    }

    void update_by_idx(int idx, int new_val) {
        if(!valid_idx(idx)) return;

        int old_val = arr[idx];
        arr[idx] = new_val;

        if(new_val < old_val) {
            shift_up(idx);
        } else {
            shift_down(idx);
        }
    }


    void update_by_val(int old_val, int new_val) {
        int pos = find_idx_with_val(old_val);
        if(pos == inf) return;

        update_by_idx(pos, new_val);
    }
};

void heap_sort(vector<int> &vals) {
    Heap heap(vals);
    for(int i = 0; i < vals.size(); i++) {
        vals[i] = heap.pop_top();
    }
}

int main() {
    vector<int> vals = {1, 4, 3, 2, 5, 1};
    heap_sort(vals);

    for(auto u: vals)
        cout << u << ' ';
    cout << endl;
}