#include <bits/stdc++.h>
#include <fstream>
#include <random>
using namespace std;

int main() {
    random_device rd;
    mt19937 gen(rd());
    
    uniform_real_distribution<> unf_real_d(0.0, 1.0);
    binomial_distribution<> bin_d(10, 0.5);
    normal_distribution<> norm_d(5., 2.); 

    ofstream file("nums.csv");
    for(int i = 0; i < 1000; i++) {
        file << unf_real_d(gen) << ';' << bin_d(gen) << ';' << norm_d(gen) << endl;
    }
}
