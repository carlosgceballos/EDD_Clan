#include "nodecola.h"
template<class T>
class Cola{
  protected:
  NodeCola<T>* head = nullptr;
  NodeCola<T>* tail = nullptr;

  public:
  Cola() : head(nullptr), tail(nullptr) {}
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
  return head == nullptr; 
}

template<class T>
void Cola<T>::push(T data){
  if(vacio()){
    this->head = new NodeCola<T>(data, nullptr);
    this->tail = head;
    return;
  }
  NodeCola<T> *newNode = new NodeCola<T>(data, nullptr);
  tail->setNext(newNode);
  this->tail=newNode;
  newNode = nullptr;

}

template<class T>
void Cola<T>::pop(){
  if(vacio()){
    return;
  }
  NodeCola<T>* temp = head;
  head = head->getNext();
  if(head == nullptr){
      tail = nullptr;
  }
  delete temp;
}

template<class T>
T Cola<T>::front(){
  if(vacio()){
    cout<<"La cola está vacía";
  }
  return head->getData();
}

template<class T>
void Cola<T>::print(){
    NodeCola<T>* current = head;
    while(current != nullptr){
        cout << current->getData() << " ";
        current = current->getNext();
    }
    cout << endl;
}
