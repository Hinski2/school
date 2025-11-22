#include <bits/stdc++.h> 
using namespace std;

struct Histogram {
    vector<pair<char, double>> data;

    friend ostream& operator << (ostream& out, const Histogram &h) {
        vector<string> plot(21, string(h.data.size(), ' '));

        // fill bars
        for(int j = 0; j < h.data.size(); j++) {
            double treshold = 0.05;
            for(auto i = 19; treshold <= h.data[j].second; i--, treshold += 0.05)
                plot[i][j] = '*';
        }

        // fill names 
        for(int j = 0; j < h.data.size(); j++)
            plot[20][j] = h.data[j].first;


        for(int i = 0; i < 21; i++) 
            out << plot[i] << endl;
        
        return out;
    }
};

int main(int argc, char *argv[]) {
    istream* in;
    ifstream f;

    if(argc > 1) {  
        f.open(argv[1]);
        if(!f) {
            throw invalid_argument("couldnt open argv[1] = " + string(argv[1]));
        }

        in = &f;
    } else {
        in = &cin;
    }

    istream_iterator<char> it_in(*in), end_in;
    
    int total = 0;
    unordered_map<char, int> occ;

    for(; it_in != end_in; ++it_in) {
        char c = *it_in;
        if('a' <= c and c <= 'z') occ[c]++, total++;
        else if('A' <= c and c <= 'Z') occ[c + 32]++, total++;
    }
    
    vector<pair<char, double>> data(occ.begin(), occ.end());
    for(auto &[c, occ]: data)
            occ /= total;

    sort(data.begin(), data.end());

    Histogram histogram(data);
    cout << histogram << endl;
}
