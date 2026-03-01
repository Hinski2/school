#include <bits/stdc++.h>
#include <ios>
#include <iterator>
using namespace std;

void create() {
    ofstream file("liczby.txt");
    vector<int> v(10);
    for(int i = 0; i < 10; i++) v[i] = i;

    copy(v.begin(), v.end(), ostream_iterator<int>(file, " "));
    cout << endl;
}

double mean(vector<int> &v) {
    double sum = 0.;
    for(auto &u: v)
        sum += u;
    return sum / v.size();
}

double std_deviation(vector<int> &v) {
    double m = mean(v), sum = 0.;
    for(auto &u: v)
        sum += (u - m) * (u - m);

    return sqrt(sum / v.size());
}

void handle() {
    ifstream file("liczby.txt");
    vector<int> v{istream_iterator<int>(file), istream_iterator<int>()};

    cout << setprecision(3) << fixed;
    cout << "mean: " << mean(v) << endl;
    cout << "std_deviation: " << std_deviation(v) << endl;
}

int main(int argc, char* argv[]) {
    if(argc == 2 and !strcmp(argv[1], "0")) {
        create();
    } else if(argc == 2 and !strcmp(argv[1], "1")) {
        handle(); 
    }
}
