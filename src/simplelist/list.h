#ifndef LIST_H
#define LIST_H

#include "nodelist.h"
#include "contribuyentes.h"

template<class T>
class List {
    private:
      NodeList<T>* head = nullptr;
    public:
      List();
      List(NodeList<T>*);
      void insert(T data);
      void insertFirst(T data);
      bool remove(T data);
      bool isEmpty();
      void print();
};

template<class T>
List<T>::List() : head(nullptr) {}

template<class T>
List<T>::List(NodeList<T>* node) {
    this->head = node;
}

template<class T>
bool List<T>::isEmpty() {
    return this->head == nullptr;
}

template<class T>
void List<T>::insertFirst(T data) {
    if(isEmpty()){
        this->head = new NodeList<T>(data, nullptr);
        return;
    }
    NodeList<T>* temp = this->head;
    this->head = new NodeList<T>(data, temp);
}

template<class T>
void List<T>::insert(T data) {
    if(isEmpty() || data.getGrado() > head->getData().getGrado() ||
       (data.getGrado() == head->getData().getGrado() && data.getEdad() > head->getData().getEdad())){
       insertFirst(data);
       return;
    }

    NodeList<T>* newNode = new NodeList<T>(data, nullptr);
    NodeList<T>* actual = head;
    NodeList<T>* prev = nullptr;

    while(actual != nullptr && 
         (actual->getData().getGrado() > data.getGrado() ||
         (actual->getData().getGrado() == data.getGrado() && actual->getData().getEdad() > data.getEdad()))){
         prev = actual;
         actual = actual->getNext();
    }
      
    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
}

template<class T>
bool List<T>::remove(T data) {
   if(isEmpty()){
      return false;
   }

   NodeList<T>* nodeToDelete = head;
   NodeList<T>* prev = nullptr;
   
   while (nodeToDelete != nullptr && nodeToDelete->getData().getId() != data.getId()){
      prev = nodeToDelete;
      nodeToDelete = nodeToDelete->getNext();
   }

   if(nodeToDelete != nullptr){
      if(prev == nullptr){
         head = nodeToDelete->getNext();
      } else {
         prev->setNext(nodeToDelete->getNext());
      }
      delete nodeToDelete;
      return true;
   }
   
   return false;
}

template<class T>
void List<T>::print() {
    NodeList<T>* current = head;
    while(current != nullptr){
        current->getData().print();
        std::cout << std::endl;
        current = current->getNext();
    }
}

#endif // LIST_H
