#include <iostream>

template <class T>
class NodeList{
  private:
  T data;
  NodeList<T>* next = nullptr;
  public:
  NodeList(T, NodeList<T>*);
  NodeList(T);
  ~NodeList();
  T getData();
  void setData(T);
  NodeList<T>* getNext();
  void setNext(NodeList<T>*);
  void print();
};

using namespace std;


template<class T>
NodeList<T>::NodeList(T data, NodeList<T>* next){
    this->data = data;
    this->next = next;
}

template<class T>
NodeList<T>::NodeList(T data){
  this->data=data;
}

template<class T>
NodeList<T>::~NodeList(){
    this->next = nullptr;
}
template<class T>
T NodeList<T>::getData(){
    return this->data;
}
template<class T>
void NodeList<T>::setData(T data){
    this->data = data;
}

template<class T>
NodeList<T>* NodeList<T>::getNext(){
    return this->next;
}

template<class T>
void NodeList<T>::setNext(NodeList<T>* next){
    this->next = next;
}

template<class T>
void NodeList<T>::print(){
   cout<<this->data<<endl;
   cout<<this->next<<endl;
}