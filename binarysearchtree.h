#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include <iostream>
#include <string>
#include "node.h"
using namespace std;

class BST {
private:
    int sz, idx;
    node* root;
    node** arr;
    bool insertt(node*&,string, string, int, string, string, string);
    bool isEmpty(node*)const{return root;}
    bool retrieve(node*&, const string, const string, int, string, string, string)const;
    node* remove(node*&, string key);
    node* getParent(node*&, string);
    node* search(node*&, string)const;
    void inOrder(node*);
public:
    BST();
    ~BST();
    bool insert(string, string, int, string, string, string);
    bool isEmpty()const{return isEmpty(root);}
    bool search(string key){ return search(root,key) ? true:false;}
    bool retrieve(const string, const string, int, string, string)const;
    void remove(string key);
    int size(){return sz;}
    node* getRoot(){return root;}
    void inOrder(){idx = 0; delete arr; arr = new node*[sz]; inOrder(root);}
    node* operator[](int i){return *(arr+i);}
};

#endif // BINARYSEARCHTREE_H
