#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H
#include <iostream>
using namespace std;
template <class keyType,class dataType>
class node{
public:
    node(){
        left = right = NULL;
    }
    node(keyType key,dataType data){
        this->key = key;
        this->data = data;
        left = right = NULL;
    }
    keyType key;
    dataType data;
    node* left;
    node* right;
};

template <class keyType,class dataType>
class BinarySearchTree
{
private:
    int sz, idx;
    node<keyType,dataType>* root;
    node<keyType,dataType>** arr;
    bool insertt(node<keyType,dataType>*& ptr,keyType key,dataType data){
        if(ptr==NULL){
            ptr = new node<keyType,dataType>(key,data);
            return true;
        }else if (ptr->key == key)
            return false;
        else if(key<ptr->key)
            return insertt(ptr->left,key,data);
        else
            return insertt(ptr->right,key,data);
    };
    bool isEmpty(node<keyType,dataType>*)const{return root;}
    node<keyType,dataType>* remove(node<keyType,dataType>*& ptr, keyType key){
        node<keyType,dataType>* save;
        if(ptr == NULL)
            return NULL;
        if(ptr->key == key){
            if(ptr->right == NULL && ptr->left == NULL){
                free(ptr);
                return NULL;
            }
        }else if(ptr->right == NULL || ptr->left == NULL){
            if(ptr->right == NULL){
                save = ptr->left;
                free(ptr);
                return save;
            }else{
                save = ptr->right;
                free(ptr);
                return save;
            }
        }else{
            save = getParent(ptr->left, key);
            ptr->key = save->key;
            ptr->left = remove(ptr->left, key);
            return ptr;
        }

        if(ptr->key < key){
            ptr->right = remove(ptr->right, key);
        }else if(ptr->key > key){
            ptr->left = remove(ptr->left, key);
        }
        return ptr;
    };
    void clear(node<keyType,dataType>*& ptr){
        if(ptr!=NULL){
           clear(ptr->left);
           clear(ptr->right);
           delete ptr;
        }
    }
    node<keyType,dataType>* getParent(node<keyType,dataType>*& ptr, keyType key){
        node<keyType,dataType>* p = NULL, *x = root;
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
    };
    node<keyType,dataType>* searchAndReturnPointer(node<keyType,dataType>*& ptr, keyType key)const{
        if(!ptr){
            return NULL;
        }else if (ptr->key == key)
            return ptr;
        else if(key<ptr->key)
            return searchAndReturnPointer(ptr->left, key);
        else
            return searchAndReturnPointer(ptr->right, key);
    };
    void inOrder(node<keyType,dataType>*& t){
        if (t){
            if(t->left) inOrder(t->left);
            *(arr+idx) = t;
            idx++;
            if(t->right)inOrder(t->right);
        }
    };
public:
    BinarySearchTree(){
        sz = 0;
        root = NULL;
        arr = NULL;
    };

    ~BinarySearchTree(){
        clear();
    };
    void clear(){
        if(root!=NULL)
            clear(root);
        sz = 0;
        root=NULL;
        idx=0;
        if(arr!=NULL){
            delete arr;
            arr=NULL;
        }
    }
    bool insert(keyType key,dataType data){
        if(insertt(root,key,data)==true){
            sz++;
            return true;
        }else{
            return false;
        }
    };

    bool isEmpty()const{
        return isEmpty(root);
    };

    bool search(keyType key){
        return searchAndReturnPointer(root,key) ? true:false;
    };

    bool retrieve(const keyType key,dataType& data){
        node<keyType,dataType>* recievedData = searchAndReturnPointer(root,key);
        if(recievedData!=NULL){
            data=recievedData->data;
            return true;
        }else{
            return false;
        }
    };

    void remove(keyType key){
        remove(root, key);
    };

    int size(){return sz;}
    node<keyType,dataType>* getRoot(){
        return root;
    };

    void inOrder(){
        idx = 0;
        if(arr!=NULL){
            delete arr;
            arr=NULL;
        }
        arr = new node<keyType,dataType>*[sz];
        inOrder(root);
    };

    node<keyType,dataType>* operator[](int i){
        return *(arr+i);
    };
};

#endif // BINARYSEARCHTREE_H
