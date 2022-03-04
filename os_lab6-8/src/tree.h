#include<set>
#include<iostream>

using namespace std;

struct node{
    node * l, * r;
    int v;
    int s;
    
    node(int a){
        l = NULL;
        r = NULL;
        v = a;
        s = 1;
    }
};

struct Tree{
    node * root;
    
    Tree(){
        root = new node(-2);
    }
    
    
    
    void print(node * now){
        if (now == NULL) return;
        cout << now->v << ": " << now->s << endl;
        print(now->l);
        print(now->r);
    }
    
    int cnt_dfs(node * now){
        if (now == NULL) return 0;
        int l = cnt_dfs(now->l);
        int r = cnt_dfs(now->r);
        now->s = l + r + 1;
        return now->s;
    }
    
    void cnt(){
        cnt_dfs(root);
    }
    
    
    void del_dfs(node * now){
        if (now == NULL) return;
        del_dfs(now->l);
        del_dfs(now->r);
        delete now;
    }
    
    void add_dfs(node * now, int p, int val){
        if (now == NULL) return;
        if (now->v == p){
            if (now->l == NULL) now->l = new node(val);
            else if (now->r == NULL) now->r = new node (val);
            return;
        }
        add_dfs(now->l, p, val);
        add_dfs(now->r, p, val);
    }
    
    void add(int p, int val){
        add_dfs(root, p, val);
        cnt();
    }
    
    void find_dfs(node * now, int &res, set <int> &s){
        if (now == NULL) return;
        if (now->l == NULL){
            if (s.find(now->v) == s.end()) res = now->v;
            return;
        }
        if (now->r == NULL){
             if (s.find(now->v) == s.end()) res = now->v;
            return;
        }
        if (now->l->s <= now->r->s) find_dfs(now->l, res, s);
        if (now->l->s >= now->r->s) find_dfs(now->r, res, s);
    }
    
    int find(set <int> &s){
        int res = -1;
        find_dfs(root, res, s);
        return res;
    }
    
    ~Tree(){
        del_dfs(root);
    }
};
