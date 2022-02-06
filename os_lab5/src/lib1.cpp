#include<math.h>

extern "C" float Leibniz(int a);
extern "C" float Wallis(int a);

float Leibniz(int n){
    float res = 0;
    for (int i = 0; i < n; i++){
        res += pow(-1, i) / (2*i + 1);
    }
    return res * 4;
}

float Wallis(int n){
    float res = 1;
    for (int i = 1; i <= n; i++){
        res *= (4 * pow(i, 2)) / (4 * pow(i, 2) - 1);
    }
    return res * 2;
}
