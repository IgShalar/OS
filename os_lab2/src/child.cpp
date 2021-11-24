#include<fstream>
#include<iostream>

using namespace std;

int main(int a, char * s[]){
    ofstream f;
    f.open(* s);
    if (!f){
        perror("Can`t create file");
        return -1;
    }
    int b, c = 2;
    cin >> b;
    while (c * c <= b){
        if (b % c == 0){
            f << b;
            f.close();
            return 0;
        }
        c++;
    }
    f.close();
    return 0;
}
