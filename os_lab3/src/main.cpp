#include<iostream>
#include<unistd.h>
#include<thread>
#include<vector>
#include<chrono>
#include"mylib.h"

using namespace std;

const int wait_time = 100;

class thread_control{

private:
    mutex mtx;
    int num;
    
    
    void stop(){
        mtx.lock();
        num--;
        mtx.unlock();
    }
    
    void insertion_sort(vector <int> &v, int s, int l){ //Сортировка вставками подмассива
        
        for (int i = s + 1; i < s + l; i++){
            int j = i;
            while(j != s && v[j] < v[j - 1]){
                swap(v[j], v[j - 1]);
                j--;
            }
        }
        stop();
    }
    
    void my_merge(vector <int> &v, pair <int, int> a, pair<int,int> b){
        int s1 = a.first;
        int l1 = a.second;
        int s2 = b.first;
        int l2 = b.second;
        if (s1 > s2){
            swap (s1, s2);
            swap (l1, l2);
        }
        vector <int> t (l1);
        
        for (int i = 0; i < l1; i++) t[i] = v[s1 + i];
        int it1 = 0, it2 = s2, it3 = s1;
        while (it1 < l1 && it2 < s2 + l2){
            if (t[it1] < v[it2]){
                v[it3] = t[it1];
                it1++;
            }
            else{
                v[it3] = v[it2];
                it2++;
            }
            it3++;
        }
        while (it1 < l1){
            v[it3] = t[it1];
            it1++;
            it3++;
        }
        while (it2 < s2 + l2){
            v[it3] = v[it2];
            it2++;
            it3++;
        }
        
        stop();
    }

    
public:
    
    int max;
    
    thread_control(){
        num = 0;
        max = 5;
    }
    
    void start_sort(vector <int> &v, int s, int l){
        while (num == max) this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        mtx.lock();
        if (num == max){
            mtx.unlock();
            start_sort(ref(v), s, l);
            return;
        }
        thread thr(&thread_control::insertion_sort, this, ref(v), s, l);
        thr.detach();
        num++;
        mtx.unlock();
    }
    
    void start_merge(vector <int> &v, pair <int, int> a, pair<int,int> b){
        while (num == max) this_thread::sleep_for(std::chrono::milliseconds(wait_time));
        mtx.lock();
        if (num == max){
            mtx.unlock();
            start_merge(ref(v), a, b);
            return;
        }
        thread thr(&thread_control::my_merge, this, ref(v), a, b);
        thr.detach();
        num++;
        mtx.unlock();
    }
    
    void wait(){
        while (num != 0) this_thread::sleep_for(std::chrono::milliseconds(wait_time));
    }
    
};

thread_control now;

int main(int num, char * arg[]){
    string arg_get = arg[1];
    now.max = stoi(arg_get);
    int n, thr_cnt = 0, mx;
    cin >> n;
    vector <int> v(n);
    
    for (int i = 0; i < n; i++) cin >> v[i];
    if (n == 1){
        cout << v[0] << endl;
        return 0;
    }
    
    int minrun = find_minrun(n);
    vector <pair<int,int> > &q = * divide(minrun,  &v); //Входной массив разделяется на подмассивы
    
    for (int i = 0; i < q.size(); i++) q[i] = {q[i].first, size(&q[i])};
    
    for (int i = 0; i < q.size(); i++) now.start_sort(ref(v), q[i].first, q[i].second);
    
    now.wait();
    
    while (q.size() != 1){
        vector <pair <int, int> > temp;
        for (int i = 1; i < q.size(); i += 2){
            now.start_merge(ref(v), q[i], q[i - 1]);
            temp.push_back(pair_merge(q[i], q[i - 1]));
        }
        if (q.size() % 2 == 1) temp.push_back(q[q.size() - 1]);
        q = temp;
        
        now.wait();
    }
    cout << endl;
    for (int i = 0; i < v.size(); i++) cout << v[i] << " ";
    cout << endl;
    return 0;
}
