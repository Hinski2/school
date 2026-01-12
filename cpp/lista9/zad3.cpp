#include <bits/stdc++.h>
using namespace std;
namespace fs = std::filesystem;

void foo(fs::path p) {
    if(!fs::exists(p)) {
        cout << "[???] " << endl;
        return;
    }

    if(fs::is_directory(p)) {
        cout << "[Dir] ";
    } else if(fs::is_regular_file(p)) {
        cout << "[File] ";
        cout << "Size: " << fs::file_size(p) << ' ';
    } else {
        cout << "[Other] ";
    }

    cout << "CanonicalPath: " << fs::canonical(p) << ' ';
    cout << "LastModification: " << fs::last_write_time(p) << endl;
}

int main(int argc, char** argv) {
    for(int i = 1; i < argc; i++) {
        foo(filesystem::path(argv[i]));
    }
}
