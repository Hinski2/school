#include <bits/stdc++.h>
#include <fstream>
#include <ios>
#include <locale>
#include <string>
using namespace std;

void generate() {
    ofstream file("file.txt");
    file << "żółtość jaźń ąę" << endl;
    file.close();
}

void convert(const char* inputFile, const char* output_utf32_name, const char* output_iso_name) {
    // czytanie plikuk
    wifstream in(inputFile);
    in.imbue(locale("pl_PL.UTF-8"));
    wstring ws{istreambuf_iterator<wchar_t>(in), istreambuf_iterator<wchar_t>()};

    // konwersja na iso
    wofstream output_iso(output_iso_name);
    output_iso.imbue(locale("pl_PL.ISO-8859-2"));
    output_iso << ws;
    output_iso.close();

    // konwersja na utf32
    ofstream output_utf32(output_utf32_name, ios::binary);
    u32string in32(ws.begin(), ws.end());
    output_utf32.write(
        reinterpret_cast<const char*>(in32.data()),
        in32.size() * sizeof(char32_t)
    );
    output_utf32.close();
}

int main(int argc, char* argv[]) {
    ios_base::sync_with_stdio(0);

    if(argc == 4) {
        convert(argv[1], argv[2], argv[3]);
    } else {
        generate();
    }
}

// hexdump -C file
// file -i file
// print(b'\xbf.decode('iso-8859-2'))
// print(b'\x7c\x01\x00\x00'.decode('utf-32-le'))
