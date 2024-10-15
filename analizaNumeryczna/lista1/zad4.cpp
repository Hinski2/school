#include <bits/stdc++.h>
using namespace std;


double f(int x){
    if(x == 0) return 1;
    else if(x == 1) return (double) -1/6;

    return (double) 35/6 * f(x - 1) + f(x - 2);
}

int main(){
    for(int i = 0; i <= 50; i++){
        cout << i << ' ' << f(i) << endl;
    }
}

/*
    0 -> 1
    1 -> - 1/6
    2 -> -35/36 + 1 = 1/36
    3 -> 35/6 * 1/36 - 1/6 = 35/216 - 36/216 = -1/216

    n -> (-1)^n * 1/(6^n) ???? 

    twierdzenie: f(x) = (-1)^n * 1/(6^n)
    baza indukcyjna
        dla n = 0:
        f(0)    = (-1)^0 * 1/(6^0)  
                = 1 * 1/1 = 1
        dla n = 1:
        f(1)    = (-1)^1 * 1/(6^1)
                = -1 * 1/6 = -1/6
    
    krok indukcyjny, weźmy dowolne x takie że f(x - 1) i f(x - 2) jest spełnione
    f(x)    = (def) = 35/6 f(x - 1) + f(x - 2)
            = (zał) = 35/6 * (-1)^(x-1) * 1/(6^(x-1) + (-1)^(x-2) * 1/(6^(x-2))
                    = 35/6 * ... działa reszte notetek w zeszycie 
        
*/