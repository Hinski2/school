#include <bits/stdc++.h>
using namespace std;

vector<int> compute_phi(int k) {
    vector<int> phi(k + 1);
    for(int i = 0; i <= k; i++)
        phi[i] = i;

    for(int i = 2; i <= k; i++) {
        if(phi[i] == i) {
            for(int j = i; j <= k; j += i)
                phi[j] -= phi[j] / i;
        }
    }

    return phi;
}

int main(int argc, char** argv) {
    ofstream file("phi.txt");
    vector<int> phi = compute_phi(atoi(argv[1]));

    copy(phi.begin(), phi.end(), ostream_iterator<int>(file, "; "));
}
