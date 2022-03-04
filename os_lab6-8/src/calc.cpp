#include"mylib.h"

using namespace std;



int main (int a, char * tr[]){
    string qw (* tr);
//    cout << "GOT_STRING: " << qw << endl;
    string up_port = get_word(qw);
    string req_port = get_word(qw);
    string rep_port = get_word(qw);
    string my_id = get_word(qw);
    Request * p = new Request(req_port), * l = NULL, * r = NULL;
    Reply * prep = new Reply(rep_port), * rep = NULL;
    int pr_id = fork();
    if (pr_id == -1){
        perror ("Fork error.");
        exit(-1);
    }
    else if (pr_id == 0){
        Request * p_sec = new Request(req_port);
        rep = new Reply(up_port);
        while(1){
            string m = rep->recieve();
            rep->reply("OK");
            p_sec->send(m);
//            cout << my_id << ": up " << m << endl;
        }
    }
//    cout << my_id << ": started" << endl;
    p->send("OK: " + to_string(getpid()) + " " + to_string(pr_id));
    while (1){
        string s = prep->recieve();
        if (first_word(s) == "ping"){
            string t1 = "-1";
            string t2 = "-1";
            if (l != NULL) t1 = l->send(s);
            if (r != NULL) t2 = r->send(s);
            if (t1 != "-1") t1 += " " + my_id;
            else t1 = my_id;
            if (t2 != "-1") t1 += " " + t2;
            prep->reply(t1);
        }
        prep->reply("OK");
        if (first_word(s) == "stop"){
            if (l != NULL) l->send(s);
            if (r != NULL) r->send(s);
            break;
        }
        else if (first_word(s) != my_id){
            if (l != NULL) l->send(s);
            if (r != NULL) r->send(s);
        }
        else{
            get_word(s);
            string t = get_word(s);
            if (t == "c"){
                int new_id = stoi(get_word(s));
                string up = get_word(s);
                string rep = get_word(s);
                create_node(new_id, up + " " + up_port + " " + rep);
                if (l == NULL) l = new Request(rep);
                else r = new Request(rep);
//                cout << my_id << ": new node id = " << new_id << endl;
            }
            else if (t == "s"){
                long long n, a, res = 0;
                n = stoi(get_word(s));
                for (int i = 0; i < n; i++){
                    a = stoi(get_word(s));
                    res += a;
                }
//                cout << my_id << ": SOLVED" << endl;
                string result = "OK:" + my_id + ": " + to_string(res);
                p->send(result);
                
                //cout << my_id << ": " << res << endl;
            }
            else if (t == "k"){
                if (l != NULL) l->send("stop");
                if (r != NULL) r->send("stop");
                break;
            }
        }
    }
    if (kill(pr_id, SIGKILL) == -1) perror ("Can't kill"); 
    if (p != NULL) delete p;
    delete prep;
    if (l != NULL) delete l;
    if (rep != NULL) delete rep;
    if (r != NULL) delete r;
    cout << my_id << ": STOPPED" << endl;
    return 0;
}
