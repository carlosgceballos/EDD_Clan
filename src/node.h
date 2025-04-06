#include <iostream>
#include <string>

template <class T, class U>
class Node{
  private:
  T data;
  U list;
  Node<T, U>* left = nullptr;
  Node<T, U>* right = nullptr;

  public:
  Node(T , U, Node<T, U>*, Node<T, U>*);
  ~Node();
  T getData();
  U getList();
  void setLeft(Node<T, U>*);
  void setRight(Node<T, U>*);
  void setData(T);
  void setList(U);
  Node<T, U>* getLeft();
  Node<T, U>* getRight(); 
};

using namespace std;

template<class T, class U> 
Node<T, U>::Node(T data, U list, Node<T, U>* left, Node<T, U>* right){
  this->data = data;
  this->list = list;
  this->left = left;
  this->right = right;
};

template<class T, class U>
Node<T, U>::~Node(){
  this-> left = nullptr;
  this->right = nullptr;
}

template <class T, class U>
void Node<T, U>::setData(T data){
    this->data=data;
}

template <class T, class U>
void Node<T, U>::setList(U list){
    this->list=list;
}

template <class T, class U>
void Node<T, U>::setLeft(Node<T, U>* left){
    this->left = left;
};

template <class T, class U>
void Node<T, U>::setRight(Node<T, U>* right){
    this->right = right;
};

template <class T, class U>
T Node<T, U>::getData(){
   return this->data;
}

template <class T, class U>
U Node<T, U>::getList(){
   return this->list;
}

template <class T, class U>
Node<T, U>* Node<T, U>::getLeft(){
   return this->left;
}

template <class T, class U>
Node<T, U>* Node<T, U>::getRight(){
   return this->right;
}