#include <bits/stdc++.h>
#include <fstream>
#include <string>
using namespace std;

void generate() {
    ofstream file("file.txt");

    file << string(100, 'a') << endl;
    file << string(100, 'b') << endl;
    file << string(100, 'c') << endl;
    file << string(100, 'd') << endl;

    file.close();
}

void convert(const char* inputFile, const char* output_utf32_name, const char* output_iso_name) {
    wifstream in(inputFile);
    in.imbue(locale("pl_PL.UTF-8"));
    wstring ws{istreambuf_iterator<wchar_t>(in), istreambuf_iterator<wchar_t>()};

    wofstream output_iso(output_iso_name);
    output_iso.imbue(locale("pl_PL.ISO-8859-2"));
    output_iso << ws;
    output_iso.close();

    ofstream output_utf32(output_utf32_name, ios::binary);
    u32string in32(ws.begin(), ws.end());
    output_utf32.write(
        reinterpret_cast<const char*>(in32.data()),
        in32.size() * sizeof(char32_t)
    );
    output_utf32.close();
}

int main(int argc, char* argv[]) {
    if(argc == 4) {
        convert(argv[1], argv[2], argv[3]);
    } else {
        generate();
    }
}
