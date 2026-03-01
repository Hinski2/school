#include <bits/stdc++.h>
#include <filesystem>
using namespace std;
namespace fs = std::filesystem;

void foo(fs::path p) {
    if(!fs::exists(p) or !fs::is_directory(p)) {
        cerr << "[??????]" << endl;
        return;
    }
    
    size_t file = 0, dir = 0, size = 0;
    for(auto entry: fs::recursive_directory_iterator{p}) {
        if(entry.is_directory()) dir++;
        else if(entry.is_regular_file()) file++, size += entry.file_size();
    }

    cout << "files: " << file << endl; 
    cout << "dirs: " << dir << endl; 
    cout << "size: " << size << "   " << (double)size / 1024 / 1024 << "Mb" << endl;
}

int main() {
    string s;
    while((cin >> s)) {
        foo(fs::path(s));
    }
}
