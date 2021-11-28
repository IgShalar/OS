#include<iostream>
#include<fstream>
#include<unistd.h>
#include<sys/mman.h>
#include <sys/stat.h>
#include <fcntl.h>
#include<unistd.h>

using namespace std;

const int wait_time = 100000;

int main(){
    string t;
    const char * s;
    getline(cin, t);
    s = t.c_str();
    int a;
    cin >> a;
    int fd = shm_open("file1", O_CREAT | O_RDWR, S_IRUSR | S_IWUSR);
    if (fd == -1){
        perror("shm_open error");
        return -1;
    }
    if (ftruncate(fd, 2 * sizeof (int)) == -1){
        perror("ftruncate error");
        return -1;
    }
    int * ptr = (int *) mmap(NULL, 2 * sizeof (int), PROT_READ|PROT_WRITE, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap error");
        return -1;
    }
    int id = fork();
    switch (id){
        case -1: {
            perror("fork error");
            return -1;
        }
        case 0: {
            if (execl("b.out", s, NULL) < 0){
                perror("execl error");
                return -1;
            }
            break;
            
        }
            
        default: {
            * ptr = a;
            * (ptr + 1) = 1;
            if (munmap(ptr, 2 * sizeof (int)) == -1){
                perror("munmap error");
                return -1;
            }
            
        }
    }
    return 0;
}
