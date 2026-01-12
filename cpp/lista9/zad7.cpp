#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;

template<typename T> 
void serialize(T t, ofstream &out) {

}

template<typename T> 
T deserialize(istream &in) {
    
}

void serialize(string& s) {

}

void deserialize_str(istream &in) {

}

template<typename T>
pair<T*, size_t> deserialize_arr(istream &in) {

}

template<typename T>
void serialize(size_t size, T* t) {

}

void foo_serialize(ofstream &out) {

}

void foo_deserialize(ifstream &in) {

}

int main(int argc, char** argv) {
    if(argc == 3 and !strcmp(argv[1], "serialize")) {
        foo_serialize(ofstream(argv[2]));
    } else if(argc == 3 and !strcmp(argv[1], "deserialize")) {
        foo_deserialize(ifstream(argv[2]));
    }
}
