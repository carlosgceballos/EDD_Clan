#include <iostream>

template <class T>
class Node{
  private:
  T data;
  T list;
  Node<T>* left = nullptr;
  Node<T>* right = nullptr;

  public:
  Node(T , T, Node<T>*, Node<T>*);
  ~Node();
  T getData();
  T getList();
  void setLeft(Node<T>*);
  void setRight(Node<T>*);
  void setData(T);
  void setList(T);
};

using namespace std;

template<class T> 
Node<T>::Node(T data, T list, Node<T>* left, Node<T>* right){
  this->data = data;
  this->list = list;
  if(left != nullptr){
    this->left=left;
  }
  if(right != nullptr){
    this->right=right;
  }
};

template<class T>
Node<T>::~Node(){
  this-> left = nullptr;
  this->right = nullptr;
}

template <class T>
void Node<T>::setData(T data){
    this->data=data;
}

template <class T>
void Node<T>::setList(T list){
    this->list=list;
}

template <class T>
void Node<T>::setLeft(Node<T>* left){
    this->left = left;
};

template <class T>
void Node<T>::setRight(Node<T>* right){
    this->right = right;
};

template <class T>
T Node<T>::getData(){
   return this->data;
}

template <class T>
T Node<T>::getList(){
   return this->list;
}