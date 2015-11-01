#include "binarysearchtree.h"

BST::BST(){
    root = NULL;
}

bool BST::insert(string& key, string& position, int& room, string& mobile, string& phone, string& info){
    return insert(root, key, position, room, mobile, phone, info);
}

bool BST::insert(node* &ptr, string& key, string& position, int& room, string& mobile, string& phone, string& info){
    if(!ptr){
        ptr = new node(key,position,room,mobile,phone,info);
        return true;
    }else if (ptr->key == key)
        return false;
    else if(key<ptr->key)
        return insert(ptr->left,key,position,room,mobile,phone,info);
    else
        return insert(ptr->right,key,position,room,mobile,phone,info);

}


node* BST::search(node*& ptr, string& key)const{
    if(!ptr){
        return NULL;
    }else if (ptr->key == key)
        return ptr;
    else if(key<ptr->key)
        return search(ptr->left, key);
    else
        return search(ptr->right, key);
}



void BST::remove(string& key){
    remove(root, key);
}

node* BST::remove(node*& root, string& key){
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

node* BST::searchInOrder(node* t, string key){
    if (t){
        if(t->key == key) return t;
        if(t->left) searchInOrder(t->left, key);
        if(t->right) searchInOrder(t->right, key);
    }
    return t;
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
