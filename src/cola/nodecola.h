#include <iostream>

template <class T>
class NodeCola{
  private:
  T data;
  NodeCola<T>* next = nullptr;
  public:
  NodeCola(T, NodeCola<T>*);
  NodeCola(T);
  ~NodeCola();
  T getData();
  void setData(T);
  NodeCola<T>* getNext();
  void setNext(NodeCola<T>*);
  void print();

};

using namespace std;

template<class T>
NodeCola<T>::NodeCola(T data, NodeCola<T>* next){
    this->data = data;
    this->next = next;
}

template<class T>
NodeCola<T>::NodeCola(T data){
  this->data=data;
}

template<class T>
NodeCola<T>::~NodeCola(){
    this->next = nullptr;
}
template<class T>
T NodeCola<T>::getData(){
    return this->data;
}
template<class T>
void NodeCola<T>::setData(T data){
    this->data = data;
}

template<class T>
NodeCola<T>* NodeCola<T>::getNext(){
    return this->next;
}

template<class T>
void NodeCola<T>::setNext(NodeCola<T>* next){
    this->next = next;
}

template<class T>
void NodeCola<T>::print(){
   cout<<this->data<<endl;
   cout<<this->next<<endl;
}