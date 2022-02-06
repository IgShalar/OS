#include<iostream>

extern "C" float Leibniz(int a);
extern "C" float Wallis(int a);
extern "C" float formula(int x);
extern "C" float row (int x);

using namespace std;

int main(){
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
                if (m1) cout << Wallis(a) << endl;
                else cout << Leibniz(a) << endl;
                break;
            }
            case '2': {
                cin >> a;
                if (m2) cout << row(a) << endl;
                else cout << formula(a) << endl;
                break;
            }
            case '0': {
                cin >> a;
                if (a == 1) m1 = !(m1);
                else if (a == 2) m2 = !(m2);
                break;
            }
            case 'q': {
                return 0;
            }
        }
    }
    return 0;
}
