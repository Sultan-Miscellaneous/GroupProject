#ifndef NODE_H
#define NODE_H

using namespace std;
class node{
public:
    node(){
        left = right = NULL;
    }
    node(const string k, string p, int r, string m, string ph, string i){
        key = k;
        position = p;
        room = r;
        mobile = m;
        phone = ph;
        info = i;
        left = right = NULL;
    }
    string key;
    string position;
    int room;
    string mobile;
    string phone;
    string info;
    node* left;
    node* right;
};


#endif // NODE_H
