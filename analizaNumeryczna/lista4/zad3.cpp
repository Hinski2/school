    #include <bits/stdc++.h>
using namespace std;

inline double f(double x){
    return x - 0.49;
}

inline double diff(double a, double b){
    return abs(a - b);
}

int main(){
    double l = 0, r = 1, mid;
    for(int i = 1; i <= 5; i++){
        mid = (l + r) / 2;
        cout << "l: " << l << " | r: " << r << " | mid: " << mid << " | błąd prawdziwy: " << diff(mid, 0.49) << " | błąd oszacowany: " << 1. / (1 << i) << endl;
        
        if(f(mid) > 0) r = mid;
        else l = mid;
    }
}
