#include<fstream>
#include<iostream>
#include<sys/mman.h>
#include<sys/stat.h>
#include<fcntl.h>
#include<unistd.h>

using namespace std;

const int wait_time = 100000;

int main(int a, char * s[]){
    int fd = shm_open("file1", O_RDONLY, S_IRUSR);
    if (fd == -1){
        perror("shm_open error");
        return -1;
    }
    int * ptr = (int *) mmap(NULL, 2 * sizeof (int), PROT_READ, MAP_SHARED, fd, 0);
    if (ptr == MAP_FAILED){
        perror("mmap error");
        return -1;
    }
    ofstream f;
    f.open(* s);
    if (!f){
        perror("Can`t create file");
        return -1;
    }
    int b, c = 2;
    while (* (ptr + 1) != 1) usleep(wait_time);
    b = * ptr;
    while (c * c <= b){
        if (b % c == 0){
            f << b;
            f.close();
            break;
        }
        c++;
    }
    if (munmap(ptr, 2 * sizeof (int)) == -1){
        perror("munmap error");
        return -1;
    }
    if (shm_unlink("file1") == -1){
        perror("shm_unlink error");
        return -1;
    }
    f.close();
    return 0;
}
