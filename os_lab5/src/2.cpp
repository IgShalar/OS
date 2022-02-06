#include<iostream>
#include<stdlib.h>
#include <dlfcn.h>

using namespace std;

int main(){
    void * lib_handle1 = dlopen("libd1.so", RTLD_LAZY);
    if (!lib_handle1){
        perror("dlopen lib1 error.");
        return -1;
    }
    void * lib_handle2 = dlopen("libd2.so", RTLD_LAZY);
    if (!lib_handle1){
        perror("dlopen lib1 error.");
        return -1;
    }
    float (* fn1)(int);
    float (* fn2)(int);
    fn1 = (float (*)(int)) dlsym(lib_handle1, "Leibniz");
    if (fn1 == NULL){
        perror("dlsym error.");
        return -1;
    }
    fn2 = (float (*)(int)) dlsym(lib_handle2, "formula");
    if (fn2 == NULL){
        perror("dlsym error.");
        return -1;
    }
    
    cout << endl << "USAGE:" << endl;
    cout << "calculate pi: 1 [x]" << endl;
    cout << "example: 1 10000" << endl;
    cout << "calculate e: 2 [x]" << endl;
    cout << "change pi realisation: 0 1" << endl;
    cout << "change e realisation: 0 2" << endl;
    cout << "exit: q" << endl;
    cout << "__________________________________________________" << endl << endl;
    bool m1 = 0, m2 = 0;
    int a;
    char ch;
    while (1){
        cin >> ch;
        switch (ch){
            case '1':{
                cin >> a;
                cout << fn1(a) << endl;
                break;
            }
            case '2': {
                cin >> a;
                cout << fn2(a) << endl;
                break;
            }
            case '0': {
                cin >> a;
                if (a == 1){
                    if (m1){
                        fn1 = (float (*)(int)) dlsym(lib_handle1, "Leibniz");
                        if (fn1 == NULL){
                            perror("dlsym error.");
                            return -1;
                        }
                    }
                    else{
                        fn1 = (float (*)(int)) dlsym(lib_handle1, "Wallis");
                        if (fn1 == NULL){
                            perror("dlsym error.");
                            return -1;
                        }
                    }
                    m1 = !(m1);
                }
                else if (a == 2){
                    if (m2){
                        fn2 = (float (*)(int)) dlsym(lib_handle2, "formula");
                        if (fn2 == NULL){
                            perror("dlsym error.");
                            return -1;
                        }
                    }
                    else{
                        fn2 = (float (*)(int)) dlsym(lib_handle2, "row");
                        if (fn2 == NULL){
                            perror("dlsym error.");
                            return -1;
                        }
                    }
                    m2 = !(m2);
                }
                break;
            }
            case 'q': {
                return 0;
            }
        }
    }
    dlclose (lib_handle1);
    dlclose (lib_handle2);
    return 0;
}
