#ifndef __LL_HPP__
#define __LL_HPP__

#include <assert.h>

#include <cstdio>
#include <cstdlib>
#include <exception>
#include <iostream>

class Error : public std::exception {
 public:
  virtual const char * what() const throw() {
    return "Cannot find the requested item!\n";
  }
};

template<typename T>
class LinkedList {
 private:
  class Node {
   public:
    T data;
    Node * next;
    Node * prev;
    Node() : data(0), next(NULL), prev(NULL){};
    Node(const T & d, Node * n, Node * p) : data(d), next(n), prev(p){};
  };
  Node * head;
  Node * tail;

 public:
  LinkedList() : head(NULL), tail(NULL) {};
  LinkedList (const LinkedList & rhs);
  LinkedList & operator=(const LinkedList & rhs);
  ~LinkedList();
  void addFront(const T & item);
  void addBack(const T & item);
  bool remove(const T & item);
  T & operator[](int index);
  const T & operator[](int index) const;
  int find(const T & item);
  int getSize() const;
};

template<typename T>
LinkedList<T>::LinkedList(const LinkedList & rhs) : head(NULL), tail(NULL) {
  Node * p = rhs.head;
  while (p != NULL) {
    addBack(p->data);
    p = p->next;
  }
}

template<typename T>
LinkedList<T> & LinkedList<T>::operator=(const LinkedList & rhs){
  if(this!=&rhs){
    LinkedList<T > tmp(rhs);
    std::swap(tmp.head, head);
    std::swap(tmp.tail, tail);
  }
  return *this;
}

template<typename T>
void LinkedList<T>::addFront(const T & item){
  head = new Node(item,head,NULL);
  if(tail==NULL){
    tail = head;
  }else{
    head->next->prev = head;
  }
}

template<typename T>
void LinkedList<T>::addBack(const T & item){
  tail = new Node(item,NULL,tail);
  if(head==NULL){
    head = tail;
  }else{
    tail->prev->next = tail;
  }
}

template<typename T>
bool LinkedList<T>::remove(const T & item) {
  Node * p = head;
  while (p != NULL) {
      if (p->data != item) {
        p = p->next;
      }
      else {
        if (head == tail && tail == p) {
          head = tail = NULL;
        }
        else if (tail == p) {
          tail = p->prev;
          tail->next = NULL;
        }
        else if (head == p) {
          head = p->next;
          head->prev = NULL;
        }
        else {
          p->prev->next = p->next;
          p->next->prev = p->prev;
        }
        delete p;
        return true;
      }
  }
  return false;
}

template<typename T>
T & LinkedList<T>::operator[](int index) {
  Node * p = head;
  while(index!=0){
    if(p == NULL){
      throw Error();
    }
    p = p->next;
    index--;
  }
  return p->data;
}

template<typename T>
const T & LinkedList<T>::operator[](int index) const {
  Node * p = head;
  while(index!=0){
    if(p == NULL){
      throw Error();
    }
    p = p->next;
    index--;
  }
  return p->data;
}

template<typename T>
int LinkedList<T>::find(const T & item) {
  Node * p = head;
  int idex = 0;
  while(p!=NULL){
    if(p->data==item){
      return idex;
    }
    p = p->next;
    idex++;
  }
  return -1;
}

template<typename T>
LinkedList<T>::~LinkedList() {
  while (head != NULL) {
    Node * p = head;
    head = head->next;
    delete p;
    p = head;
  }
  head = NULL;
  tail = NULL;
}

template<typename T>
int LinkedList<T>::getSize() const {
  int size = 0;
  for (Node * p = head; p != NULL; p = p->next) {
    size++;
  }
  return size;
}

#endif
