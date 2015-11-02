#include "binarysearchtree.h"

BST::BST(){
    sz = 0;
    root = NULL;
}

BST::~BST(){
    delete root;
}

bool BST::insert(string key, string position, int room, string mobile, string phone, string info){
    return (sz++,insertt(root, key, position, room, mobile, phone, info));
}

bool BST::insertt(node* &ptr, string key, string position, int room, string mobile, string phone, string info){
    if(!ptr){
        ptr = new node(key,position,room,mobile,phone,info);
        return true;
    }else if (ptr->key == key)
        return false;
    else if(key<ptr->key)
        return insertt(ptr->left,key,position,room,mobile,phone,info);
    else
        return insertt(ptr->right,key,position,room,mobile,phone,info);
}

node* BST::search(node*& ptr, string key)const{
    if(!ptr){
        return NULL;
    }else if (ptr->key == key)
        return ptr;
    else if(key<ptr->key)
        return search(ptr->left, key);
    else
        return search(ptr->right, key);
}



void BST::remove(string key){
    remove(root, key);
}

node* BST::remove(node*& root, string key){
    node* save;
    if(root == NULL)
        return NULL;
    if(root->key == key){
        if(root->right == NULL && root->left == NULL){
            free(root);
            return NULL;
        }
    }else if(root->right == NULL || root->left == NULL){
        if(root->right == NULL){
            save = root->left;
            free(root);
            return save;
        }else{
            save = root->right;
            free(root);
            return save;
        }
    }else{
        save = getParent(root->left, key);
        root->key = save->key;
        root->left = remove(root->left, key);
        return root;
    }

    if(root->key < key){
        root->right = remove(root->right, key);
    }else if(root->key > key){
        root->left = remove(root->left, key);
    }
    return root;
}

void BST::inOrder(node* t){
    if (t){
        if(t->left) inOrder(t->left);
        *(arr+idx) = t;
        idx++;
        if(t->right)inOrder(t->right);
    }
}

node* BST::getParent(node*& ptr, string key){
    node* p = NULL, *x = root;
    bool found = false;
    while (!found && x) {
        if(key<ptr->key){
            p = x;
            x = x->left;
        }else if(key>ptr->key){
            p = x;
            x = x->right;
        }else{
            found = true;
        }
    }
    return p;
}

//string BST::operator[][](int i, int j){

//}


