#include<math.h>

extern "C" float formula(int x);
extern "C" float row (int x);

float formula(int x){
    float x1 = x;
    float res = pow(1 + 1 / x1, x1);
    return res;
}

float f(float x){
    float res = 1;
    for (int i = 1; i <= x; i++) res *= i;
    return res;
}

float row (int x){
    float res = 0;
    for (float i = 0; i <= x; i++) res += 1 / f(i);
    return res;
}
