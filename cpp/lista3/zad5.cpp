#include<bits/stdc++.h>
#include <chrono>
#include <iomanip>
using namespace std;

struct Matrix {
    size_t n, m;
    vector<vector<double>> data;

    inline static default_random_engine generator;
    inline static uniform_real_distribution<double> distribution{0.5, 2.0}; // [0,5, 2.0)

    Matrix(size_t n, size_t m) : n(n), m(m) {
        data.resize(n);
        for(auto &row: data) {
            row.resize(m);
            for(auto &e: row) {
                e = distribution(generator);
            }
        }
    }

    Matrix() = default;

    static Matrix zero (size_t n, size_t m) {
        Matrix res;
        res.n = n;
        res.m = m;
        res.data = vector<vector<double>>(n, vector<double>(m, 0.0));
        return res;
    }

    double& operator () (size_t i, size_t j) {
        return data[i][j];
    }

    double operator () (size_t i, size_t j) const {
        return data[i][j];
    }

    Matrix operator * (const Matrix &other) {
        Matrix res = Matrix::zero(n, m);

        for(size_t k = 0; k < m; k++) 
            for(size_t i = 0; i < m; i++)
                for(size_t j = 0; j < m; j++)
                    res(i, j) += data[i][k] * other(k, j);

        return res;
    }
};

int measure(Matrix m, size_t times) {
    auto start = chrono::high_resolution_clock::now();

    for(size_t i = 0; i < times; i++)
            m * m;

    auto end = chrono::high_resolution_clock::now();
    auto elapsed = duration_cast<chrono::milliseconds>(end - start);
    return elapsed.count() / times;
}

int main() {
    Matrix m0(50, 50);       
    Matrix m1(100, 100);       
    Matrix m2(200, 200);

    int t0 = measure(m0, 5);
    int t1 = measure(m1, 2);
    int t2 = measure(m2, 1);

    cout << fixed << setprecision(3);
    cout << "t0: " << t0 / 60000.0 << "min" << endl;
    cout << "t1: " << t1 / 60000.0 << "min" << endl;
    cout << "t2: " << t2 / 60000.0 << "min" << endl;
}
