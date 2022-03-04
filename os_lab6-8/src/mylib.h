#include <zmq.h>
#include <unistd.h>
#include<iostream>
#include <sys/types.h>
#include <signal.h>
#include <chrono>
#include <thread>

using namespace std;

const int WAIT = 10;
const int LIM = 50;
int port = 48654;

class Request{
    
public:
    Request(string s){
        s = "tcp://localhost:" + s;
//        cout << "Connecting request to " << s << endl;
        ctx = zmq_ctx_new();
        if (ctx == NULL){
            perror("ctx");
        }
        req = zmq_socket(ctx, ZMQ_REQ);
        if (req == NULL){
            perror ("Can't create socket");
        }
        if (zmq_connect (req, s.c_str()) == -1) perror("Can't connect");
        if (zmq_setsockopt (req, ZMQ_RCVTIMEO, &WAIT, sizeof(int)) == -1){
            perror("Can't set wait");
        }
        if (zmq_setsockopt (req, ZMQ_LINGER, &WAIT, sizeof(int)) == -1){
            perror("Can't set linger");
        }
//        cout << "Request to " << s << " connected." << endl;
    }
    
    ~Request(){
        if (zmq_close(req) == -1) perror ("Can't close socket");
        if (zmq_ctx_destroy(ctx) == -1) perror("Can't destroy context.");
    }
    
    string send(const string &s){
        string res;
        char ch[size];
        zmq_send (req, s.c_str(), s.size() + 1, 0);
        if (zmq_recv (req, ch, size, 0) == -1) res = "-1";
        else{
            string temp(ch);
            res = temp;
        }
        return res;
    }
    
private:
    const int size = LIM;
    void * req, * ctx;
};


class Reply{
    
public:
    Reply(string s){
        s = "tcp://*:" + s;
//        cout << "Connecting reply to " << s << endl;
        ctx = zmq_ctx_new();
        if (ctx == NULL){
            perror("ctx");
        }
        rep = zmq_socket(ctx, ZMQ_REP);
        if (rep == NULL){
            perror ("Can't create socket");
        }
        int rc = 0;
        rc = zmq_bind (rep, s.c_str());
        if (rc == -1) perror ("Connection failed");
//        cout << "Reply to " << s << " connected." << endl;
    }
    
    ~Reply(){
        if (zmq_close(rep) == -1) perror ("Can't close socket");
        if (zmq_ctx_destroy(ctx) == -1) perror("Can't destroy context.");
    }
    
    string recieve(){
        char ch[size];
        zmq_recv (rep, ch, size, 0);
        string res(ch);
        return res;
    }
    
    void reply(const string &s){
        zmq_send (rep, s.c_str(), s.size() + 1, 0);
    }
    
private:
    const int size = LIM;
    void * rep, * ctx;
};

void remove_spaces (string &s){
    int now = 0;
    while (s[now] == ' ' && now < s.size()) now++;
    s.erase(0, now);
}

string get_word (string &s){
    int now = 0;
    while (s[now] == ' ' && now < s.size()) now++;
    s.erase(0, now);
    now = 0;
    while (s[now] != ' ' && now < s.size()) now++;
    string res = s.substr(0, now);
    s.erase(0, now);
    remove_spaces(s);
    return res;
}

string first_word (const string &s){
    int now = 0;
    string res = "";
    while (s[now] == ' ' && now < s.size()) now++;
    while (s[now] != ' ' && now < s.size()){
        res += s[now];
        now++;
    }
    return res;
}

void create_node(int my_id, const string &p){ // add request port
    string s = p;
    s += " " + to_string (my_id);
//    cout << "SEND_STRING: " << s << endl;
    int id = fork();
    if (id == -1){
        perror("Fork error");
    }
    else if (id == 0 && execl("calc", s.c_str(), NULL) < 0){
        perror("execl error");
    }
}

string get_port(){
    if (port == 49152){
        cout << "ERROR: Port limit exceeded." << endl;
        return "ERROR";
    }
    string res = to_string(port);
    port++;
    return res;
}





