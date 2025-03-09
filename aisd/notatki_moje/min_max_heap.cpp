#include <bits/stdc++.h>
using namespace std;

struct min_max_heap{
    int n = 0;
    vector<int> min_vec, max_vec;

    int insert(int val){

    }
};

class min_max_heap{
private:
    // data
    optional<int> buff;
    vector<int> min_vec, max_vec;

    void insert_min_heap(int val){
    }

    void insert_max_heap(int val){
    }

    optional<int> min_vec_get(){
        if(min_vec.size() > 0) return min_vec[1];
        return nullopt;
    }

    optional<int> max_vec_get(){
        if(max_vec.size() > 0) return max_vec[1];
        return nullopt;
    }

public:
    // constructor
    min_max_heap(){ 
        min_vec.resize(1); // start indexing from 1
        max_vec.resize(1);
    }

    void insert(int val){
        if(buff){ //albo buff.has_value
            int small = min(buff.value(), val); // albo po prostu *buff
            int large = max(buff.value(), val);
            buff.reset(); // lub buff = nullopt

            insert_min_heap(small);
            insert_max_heap(large);
        } else {
            buff = val;
        }
    }

    optional<int> get_min(){
        auto x = min_vec_get();
        if(x and buff){
            return min(x.value(), buff.value());
        } else if(x){
            return x;
        } else if(buff){
            return buff;
        }
        return nullopt;
    }
};

int main(){

}