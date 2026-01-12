#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

bool contains_cbp(fs::path p) {
    for(auto entry: fs::directory_iterator(p)) {
        if(entry.is_regular_file() and entry.path().extension() == ".cbp")
            return 1;
    }

    return 0;
}

void remove_bin(fs::path p) {
    for(auto entry: fs::directory_iterator(p))  {
        if(entry.is_directory() and entry.path().filename() == "bin") { 
            cerr << "Remove " << entry.path() << endl;
            fs::remove_all(entry);
        }
    }
}

void foo(fs::path p) {
    if(!fs::exists(p) or !fs::is_directory(p)) {
        cerr << "[??????]" << endl;
        return;
    }
    
    // dodatkowo obecny katalog
    if(contains_cbp(p))
        remove_bin(p);
    
    for(auto entry: fs::recursive_directory_iterator(p)) {
        if(entry.is_directory() and contains_cbp(entry)) {
            remove_bin(entry);
        }
    }
}

int main() {
    string s;
    while((cin >> s)) {
        foo(fs::path(s));
    }
}
