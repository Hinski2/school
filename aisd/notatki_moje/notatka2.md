# notatka 2

---

## kopiec
**kopiec**: Drzewo T o wysokości d nazywamy kopcje meżli T spełnia następujące warunki:
1. struktura drzewa
    * wierzchołki są najpierw ułożone od góry potem od lewej do prawej
2. upocządkowanie
    * klucz w v nie jest większy niż klucz w synie v

#### implementacja
kopce opłąca się implementować w tablicy gdzie:
* root jest w K[1]
* lewy syn roota w K[2], prawy syn roota w K[3]
* wierzchołek v ma lewego syn w 2*v i prawego w 2*v + 1
* v ma ojca w v/2

``` c++
struct min_heap{
    vector<int> h = {-1}; // by root był pod 1

    //* przesówanie wierzchołków
    void shift_up(int idx);
    void shift_down(int idx);

    //* dodanie wierzchołka
    void insert(int val);

    //* znajdz inx wierzchołka z wartościa
    int find(int val);

    //* dostań najmniejszy element
    int top();
    int pop();

    //* zmiana elementu pod idx
    void update(int idx, int new_val);

    //* usunięcie wierzchołka z wartościa
    void remove(int val);

    //* budowanie kopca
    void slow_build(vector<int> &arr);
    void fast_build(vector<int> &arr);

    //* implementacje
    void shift_up(int idx){
        while(idx > 1 and h[idx] < h[idx / 2]){
            swap(h[idx], h[idx / 2]);
            idx /= 2;
        }
    }

    void shift_down(int idx){
        int left = idx * 2, right = idx * 2 + 1;
        while((left < h.size() and h[idx] > h[left]) or
            (right < h.size() and h[idx] > h[right])){

                int s;
                if(right >= h.size()) s = left;
                else s = h[left] < h[right] ? left : right; 

                swap(h[idx], h[s]);
                idx = s;
                left = s * 2;
                right = s * 2 + 1;
        }
    }

    void insert(int val){
        h.push_back(val);
        shift_up(h.size() - 1);
    }

    int top(){
        return h.size() > 1 ? h[1] : -1;
    }

    int pop(){
        if(h.size() <= 1) 
            return -1;

        int top = h[1];
        swap(h[1], h[h.size() - 1]);
        h.pop_back();
        shift_down(1);
        return top;
    }

    void update(int idx, int new_val){
        if(idx >= h.size())
            return;

        int old = h[idx];
        h[idx] = new_val;

        if(new_val > old) shift_down(idx);
        else shift_up(idx);
    }

    void slow_build(vector<int> &arr){
        h.resize(arr.size() + 1);
        for(int i = 0; i < arr.size(); i++)
            h[i + 1] = arr[i];
        
        for(int i = 2; i < h.size(); i++)
            shift_up(i);
    }

    void fast_build(vector<int> &arr){
        h.resize(arr.size() + 1);
        for(int i = 0; i < arr.size(); i++)
            h[i + 1] = arr[i];
        
        for(int i = h.size() - 1; i > 0; i--)
            shift_down(i);
    }

    int find(int val, int idx = 1){
        if(idx > h.size()){
            return -1;
        }

        // czy to ja
        if(h[idx] == val) return idx;

        // szukaj w lewym synie
        int l = find(val, idx * 2);
        if(l != -1) return l;

        // szukaj w prawym synie
        int r = find(val, idx * 2 + 1);
        if(r != -1) return r;

        // nie zlaleziono
        return -1;
    }

    void remove(int val){
        int idx = find(val);
        if(idx == -1) return;

        int new_val = h[h.size() - 1];
        h.pop_back();

        update(idx, new_val);
    }
};

void heap_sort(vector<int> &arr){
    min_heap heap;
    heap.fast_build(arr);

    for(int i = 0; i < arr.size(); i++){
        arr[i] = heap.pop();
    }
}

int main(){
    vector<int> v = {2, 4, 3, 1, 5, 6};
    heap_sort(v);
    for(auto u: v)
        cout << u << ' ';
    cout << endl;
}
```