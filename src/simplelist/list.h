#include "node.h"
#include "contribuyentes.h"

template<class T>
class List{
    private:
    NodeList<T>* head = nullptr;
    public:
        List(NodeList<T>*);
        void insert(T);
        void insertFirst(T);
        bool remove(T);
        bool isEmpty();
        void print();
};

template<class T>
List<T>::List(NodeList<T>* node){
    this->head=node;
}

template<class T>
bool List<T>::isEmpty(){
    return this->head == nullptr;
}

template<class T>
void List<T>::insertFirst(T data){
    if(isEmpty()){
        this->head = new NodeList<T>(data,nullptr);
        return;
    }
    NodeList<T>* temp = this->head;
    this->head = new NodeList<T>(data,temp);
    temp = nullptr;
}

template<class T>
void List<T>::insert(T data){
    if(isEmpty() || data.getGrado()<head->getData().getGrado()){
       insertFirst(data);
       return;
    }

    NodeList<T> *newNode =new NodeList<T>(data,nullptr);
    NodeList<T> *actual = head;
    NodeList<T> *prev = nullptr;
      
    while(actual!=nullptr && actual->getData().getGrado() < data.getGrado() || actual->getData().getGrado() == data.getGrado() && actual->getData().getEdad() < data.getEdad()) {
         prev = actual;
         actual = actual->getNext();
    }
      
    newNode->setNext(prev->getNext());
    prev->setNext(newNode);
}

template<class T>
bool List<T>::remove(T data){

   if(isEmpty()){
      return false;
   }

   NodeList<T>* NodeToDelete=head;

   NodeList<T>* prev=nullptr;

   
   while (NodeToDelete!=nullptr && NodeToDelete->getData().getId() !=data->getId())
   {
      prev=NodeToDelete;
      NodeToDelete=NodeToDelete->getNext();
   }

   if(NodeToDelete!=nullptr){
      if(prev==nullptr){
         head=NodeToDelete->getNext();
      }
      else{
         prev->setNext(NodeToDelete->getNext());
      }


      delete NodeToDelete;
      return true;
   }
   
   return false;
}

template<class T>
void List<T>::print(){
    NodeList<T>* actual = head;
    cout<<head<<endl;
    while (actual != nullptr)
    {
       actual->print();
       actual = actual->getNext();
    }
    
}