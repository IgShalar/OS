#include"mylib.h"
#include<queue>
#include<set>
#include"tree.h"

using namespace std;

Tree tree;
set <int> nodes;
Request * l = NULL, * r = NULL;

set <int> ping (){
//    this_thread::sleep_for(std::chrono::milliseconds(500 * WAIT));
    string m = "ping";
    string s = "";
    if (l != NULL) s += l->send(m);
    s += " ";
    if (r != NULL) s += r->send(m);
    set <int> res = nodes;
    remove_spaces(s);
    while (s != ""){
        string t = get_word(s);
        int a = stoi(t);
        if (a != -1) res.erase(a);
    }
    return res;
}


int main (){
    string up_port = get_port();
    string s = "";
    int pr_id = fork();
    if (pr_id == -1){
        perror ("Fork error.");
        exit(-1);
    }
    else if (pr_id == 0){
        Reply * rep = new Reply(up_port);
        while(1){
            string m = rep->recieve();
            cout << m << endl;
            rep->reply("GOT");
        }
    }
    while (1){
        cin >> s;
//        cout << "INPUT: " << s << endl;
        if (s == "exit"){
            if (l != NULL) l->send("stop");
            if (r != NULL) r->send("stop");
            break;
        }
        else if (s == "create"){
            int id;
            string t;
            cin >> id;
            if (nodes.find(id) != nodes.end()){
                cout << "Error: Already exists" << endl;
                continue;
            }
            set <int> busy = ping();
            int wh = tree.find(busy);
            if (wh == -1){
                cout << "Error: can't find avaliable parent" << endl;
                continue;
            }
            nodes.insert(id);
            tree.add(wh, id);
            cout << "WHERE: " << wh << endl; //root has id = -2
            if (wh == -2){
                string temp = get_port();
                create_node (id, get_port() + " " + up_port + " " + temp);
                if (l == NULL) l = new Request(temp);
                else r = new Request(temp);
            }
            else{
                string m = to_string(wh) + " c " + to_string(id) + " " + get_port() + " " + get_port();
//                cout << "TO SEND: " << m << endl;
                if (l != NULL) l->send(m);
                if (r != NULL) r->send(m);
            }
        }
        else if (s == "exec"){
            string t, res;
            int n;
            cin >> res;
            res += " s";
            cin >> n;
            res += " " + to_string(n);
            for (int i = 0; i < n; i++){
                cin >> t;
                res += " " + t;
            }
//            cout << "TO SEND: " << res << endl;
            string wh = first_word(res);
            int tr = stoi(wh);
            if (nodes.find(tr) == nodes.end()){
                cout << "Error:" << tr << ": Not found" << endl;
                continue;
            }
            set <int> qw = ping();
            if (qw.find(tr) != qw.end()){
                cout << "Error:" << tr << ": Node is unavailable" << endl;
                continue;
            }
            if (l != NULL) l->send(res);
            if (r != NULL) r->send(res);
        }
        else if (s == "pingall"){
            set<int> temp = ping();
            cout << "OK: ";
            if (temp.empty()) cout << "-1";
            else for (auto i : temp) cout << i << "; ";
            cout << endl;
        }
        else if (s == "kill"){
            int w;
            cin >> w;
            string m = to_string(w) + " k";
            if (l != NULL) l->send(m);
            if (r != NULL) r->send(m);
        }
    }
    if (kill(pr_id, SIGKILL) == -1) perror ("Can't kill");
    if (l != NULL) delete l;
    if (r != NULL) delete r;
    return 0;
}
