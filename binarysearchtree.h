#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H


#include <iostream>
#include <string>
#include "node.h"
using namespace std;

class BST {
private:
    node* root;
    bool insert(node*&,string&, string&, int&, string&, string&, string&);
    bool isEmpty(node*)const{return root;}
    bool retrieve(node*&, const string&, const string&, int&, string&, string&, string&)const;
    node* remove(node*&, string& key);
    node* getParent(node*&, string);
    node* search(node*&, string&)const;
public:
    BST();
    bool insert(string&, string&, int&, string&, string&, string&);
    bool isEmpty()const{return isEmpty(root);}
    bool search(string& key){ return search(root,key) ? true:false;}
    bool retrieve(const string&, const string&, int&, string&, string&)const;
    void remove(string& key);
    node* getRoot(){return root;}
    node* searchInOrder(node*, string);
};

#endif // BINARYSEARCHTREE_H
