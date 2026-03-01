#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;

void foo(fs::path p) {
    if(!fs::exists(p) or !fs::is_directory(p)) {
        cerr << "[??????]" << endl;
        return;
    }
    
    vector<fs::directory_entry> entries{fs::directory_iterator(p), fs::directory_iterator()};
    sort(entries.begin(), entries.end(), [](const fs::directory_entry &a, const fs::directory_entry &b) {
        if(a.is_directory() != b.is_directory())
            return a.is_directory();
        return a.path().filename() < b.path().filename();
    });
    
    for(auto& entry: entries)
        cout << (entry.is_directory() ? "[Dir]" : "[Path]") << entry.path().filename() << endl;
}

int main() {
    string s;
    while((cin >> s)) {
        foo(fs::path(s));
    }
}
