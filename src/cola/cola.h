#include "nodecola.h"
template<class T>
class Cola{
  protected:
  NodeCola<T>* head = nullptr;
  NodeCola<T>* tail = nullptr;

  public:
  Cola(NodeCola<T>*);
  T front();
  void push(T);
  void pop();
  bool vacio();
  void print();
};

template <class T>
Cola<T>::Cola(NodeCola<T>* node){
  this->tail=node;
}

template<class T>
bool Cola<T>::vacio(){
  return this ->tail == nullptr;
}

template<class T>
void Cola<T>::push(T data){
  if(vacio()){
    this->head = new Node<T>(data, nullptr);
    this->tail = head;
    return;
  }
  NodeCola<T> *newNode = new Node<T> (data, nullptr);
  tail->setNext(newNode);
  this->tail=newNode;
  newNode = nullptr;

}

template<class T>
void Cola<T>::pop(){
  int t;
  if(vacio()){
    cout<<t<<endl;
  }
  NodeCola<T>* temp = head;
  t = temp->getData();
  head= head->getNext();
  delete temp;
  cout<<t<<endl;
};

template<class T>
T Cola<T>::front(){
  if(vacio()){
    cout<<"La cola está vacía";
  }
  return head->getData();
}
