#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "set.h"

template<typename T>
class BstSet : public Set<T>{
  public:
    class Node{
      public:
        T key;
        Node * left;
        Node * right;
        Node(): key(0), left(NULL), right(NULL){};
        Node(const T k): key(k), left(NULL), right(NULL){};
    };
  Node * root;
  
  public:
    BstSet() : root(NULL){}
    
    BstSet(const BstSet & rhs) : root(NULL) { root = copy(rhs.root); }

    Node * copy(Node * current) {
      if (current == NULL) {
        return NULL;
      }
      Node * root = new Node(current->key);
      root->left = copy(current->left);
      root->right = copy(current->right);
      return root;
    }
  
    BstSet & operator=(const BstSet & rhs) {
      if (this != &rhs) {
        destroyNodes(root);
        root = copy(rhs.root);
      }
      return *this;
    }
    
    virtual void add(const T & key){
      if(root==NULL){
        root = new Node(key);
        return;
      }
      Node ** cur = &root;
      while((*cur)!=NULL){
        if((*cur)->key<key){
          cur = &(*cur)->right;
        }else if((*cur)->key>key){
          cur = &(*cur)->left;
        }else{
          break;
        }
      }
      if((*cur)==NULL){
        (*cur) = new Node(key);
      }
      return;
    }
    virtual bool contains(const T & key) const{
      Node * n = root;
      while(n!=NULL){
        if(n->key == key){
          break;
        }else if(n->key > key){
          n = n->left;
        }else{
          n = n->right;
        }
      }
      if (n == NULL) {
        return false;
      }
      return true;
    }
    virtual void remove(const T & key){
      Node ** n = &root;
      while(*n!=NULL){
        if((*n)->key == key){
          break;
        }else if((*n)->key > key){
          n = &(*n)->left;
        }else{
          n = &(*n)->right;
        }
      }
      if (*n == NULL) {
        throw std::invalid_argument("cannot find key\n");
      }
      if((*n)->left == NULL){
        Node * tmp = (*n)->right;
        delete *n;
        *n = tmp;
      }else if((*n)->right == NULL){
        Node * tmp = (*n)->left;
        delete *n;
        *n = tmp;
      }else{
        Node * c = (*n)->left;
        while(c->right!=NULL){
          c = c->right;
        }
        T tK = c->key;
        remove(c->key);
        (*n)->key = tK;
      }
    }
    virtual ~BstSet<T>(){
      destroyNodes(root);
      root = NULL;
    };
    void destroyNodes(Node * n) {
      if (n == NULL) {
        return;
      }
      destroyNodes(n->left);
      destroyNodes(n->right);
      delete n;
    }
};

