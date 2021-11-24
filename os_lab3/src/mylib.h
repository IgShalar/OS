#ifndef MYLIB_H
#define MYLIB_H

#include<vector>

using namespace std;

int size (pair <int, int> *);

int find_minrun(int);

vector <pair <int, int> > * divide(int, vector <int> *);

pair <int, int> pair_merge (pair <int, int>, pair <int, int>);

#endif
