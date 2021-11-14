#include<iostream>
#include<fstream>
#include<unistd.h>

using namespace std;

int main(){
    int p1[2], p2[2];
    if (pipe (p1) == -1){
        perror("pipe error");
        return -1;
    }
//    if (pipe (p2) == -1){
//        perror("pipe error");
//        return -1;
//    }
    string t;
    const char * s;
    getline(cin, t);
    s = t.c_str();
    
    int a;
    cin >> a;
    
    int id = fork();
    switch (id){
        case -1: {
            perror("fork error");
            return -1;
        }
        case 0: {
            close(p1[0]);
            if (dup2(p1[1], 1) == -1){
                perror("dup2 error");
                return -1;
            }
            close(p1[1]);
            cout << a << endl;
 
//            if (dup2(p2[0], 0) == -1){
//                perror("dup2 error");
//                return -1;
//            }
//            close(p2[1]);
//            close(p2[0]);
            break;
            
        }
            
        default: {
//            if (dup2(p2[1], 1) == -1){
//                perror("dup2 error");
//                return -1;
//            }
//            close(p2[1]);
//            close(p2[0]);
            
            close(p1[1]);
//            cout << dup2(p1[0], 0) << endl;
            if (dup2(p1[0], 0) == -1){
                perror("dup2 error");
                return -1;
            }
//            return -1;
            close(p1[0]);
            if (execl("b.out", s, NULL) < 0){
                perror("execl error");
                return -1;
            }
        }
    }
    return 0;
}
