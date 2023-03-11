#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>
#include <stdexcept>

#include "map.h"

template<typename K, typename V>
class BstMap : public Map<K,V>{
  public:
    class Node{
      public:
        K key;
        V value;
        Node * left;
        Node * right;
        Node(): key(0), value(0), left(NULL), right(NULL){};
        Node(const K k,const V v): key(k), value(v), left(NULL), right(NULL){};
    };
  Node * root;
  
  public:
    BstMap() : root(NULL){}
    
    BstMap(const BstMap & rhs) : root(NULL) { root = copy(rhs.root); }

    Node * copy(Node * current) {
      if (current == NULL) {
        return NULL;
      }
      Node * root = new Node(current->key, current->value);
      root->left = copy(current->left);
      root->right = copy(current->right);
      return root;
    }
  
    BstMap & operator=(const BstMap & rhs) {
      if (this != &rhs) {
        destroyNodes(root);
        root = copy(rhs.root);
      }
      return *this;
    }
    
    virtual void add(const K & key, const V & value){
      if(root==NULL){
        root = new Node(key,value);
        return;
      }
      Node ** cur = &root;
      while((*cur)!=NULL){
        if((*cur)->key<key){
          cur = &(*cur)->right;
        }else if((*cur)->key>key){
          cur = &(*cur)->left;
        }else{
          (*cur)->value = value;
          break;
        }
      }
      if((*cur)==NULL){
        (*cur) = new Node(key,value);
      }
      return;
    }
    virtual const V & lookup(const K& key) const throw (std::invalid_argument){
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
        throw std::invalid_argument("cannot find key\n");
      }
      return n->value;
    }
    virtual void remove(const K& key){
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
        K tK = c->key;
        V tV = c->value;
        remove(c->key);
        (*n)->key = tK;
        (*n)->value = tV;
      }
    }
    virtual ~BstMap<K,V>(){
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


