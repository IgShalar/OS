#include<vector>

using namespace std;

int size(pair <int, int> * a){
    return a->second - a->first + 1;
}

int find_minrun(int n){
    int minrun, r = 0;;
    if (n < 64) minrun = max(n / 4, 1); /*
    чтобы продемонстрировать парралельную обработку при небольших n
    */
    else{
        while (n >= 64) {
            r |= n & 1;
            n >>= 1;
        }
        minrun = n + r;
    }
    return minrun;
}

vector <pair <int, int> > * divide(int minrun, vector <int> * t){
    vector <pair <int, int> > * q = new vector <pair <int, int> >;
    vector <int> &v = *t;
    int n = v.size();
    pair <int, int> p = {0, -1};
    int now = 1;
    while (now < n){
        while (v[now] < v[now - 1] && now < n) now++;
        if (now > p.first + 1){
            reverse(v.begin() + p.first, v.begin() + now);
            if (now - p.first < minrun) now = min(p.first + minrun, n);
            p.second = now - 1;
            q->push_back(p);
            p = {-1, -1};
            p.first = now;
            now++;
        }
        if (now == n) break;
        while (v[now] >= v[now - 1] && now < n) now++;
        if (now > p.first + 1){
            if (now - p.first < minrun) now = min(p.first + minrun, n);
            p.second = now - 1;
            q->push_back(p);
            p = {-1, -1};
            p.first = now;
            now++;
        }
    }
    if (p.first == n - 1 && p.second == -1) q->push_back({n - 1, n - 1});
    return q;
}

pair <int, int> pair_merge (pair <int, int> a, pair <int, int> b){
    a.first = min(a.first, b.first);
    a.second += b.second;
    return a;
}
