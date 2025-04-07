#include "node.h"
#include "clan.h"
#include "simplelist/list.h"
#include "cola.h"
#include <string>
#include <iostream>

using namespace std;

template<class T>
class Tree{
  private:
  Node<Clan<T>, List<Contribuyentes<T>>>* founder = nullptr;
  Node<Clan<T>, List<Contribuyentes<T>>>* lider = nullptr;
  

  public: 
  Tree();
  ~Tree();
  Node<Clan<T>, List<Contribuyentes<T>>>* getFounder();
  Node<Clan<T>, List<Contribuyentes<T>>>* findNode(Node<Clan<T>, List<Contribuyentes<T>>>* root, T id);
  void insertNode(Node<Clan<T>, List<Contribuyentes<T>>>* parent, Clan<T> miembro);
  void buildTree(Cola<Clan<T>>& cola);
  void Tree<T>::preOrder(Node<Clan<T>,List<Contribuyentes<T>>>*root);
};

template<class T>
Tree<T>::Tree():founder(nullptr), lider(nullptr){

}

template<class T>
Tree<T>::~Tree(){

}

template<class T>
Node<Clan<T>,List<Contribuyentes<T>>>* Tree<T>::getFounder(){
  return founder;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::findNode(Node<Clan<T>, List<Contribuyentes<T>>>* root, T id) {
    if (root == nullptr){
      return nullptr;
    } 
    if (root->getData().getID() == id){
      return root;
    } 
    Node<Clan<T>, List<Contribuyentes<T>>>* found = findNode(root->getLeft(), id);
    if (found == nullptr){
      found = findNode(root->getRight(), id);
      return found;
    }
}

template<class T>
void Tree<T>::insertNode(Node<Clan<T>, List<Contribuyentes<T>>>* parent, Clan<T> miembro) {
    List<Contribuyentes<T>> emptyList;
    if (parent->getLeft() == nullptr){
        Node<Clan<T>, List<Contribuyentes<T>>>* newNode = new Node<Clan<T>, List<Contribuyentes<T>>>(miembro, emptyList, nullptr, nullptr);
        parent->setLeft(newNode);
    } else if (parent->getRight() == nullptr) {
        Node<Clan<T>, List<Contribuyentes<T>>>* newNode = new Node<Clan<T>, List<Contribuyentes<T>>>(miembro, emptyList, nullptr, nullptr);
        parent->setRight(newNode);
    } else {
        insertNode(parent->getLeft(), miembro);
    }
}

template<class T>
void Tree<T>::buildTree(Cola<Clan<T>>&cola){
  Cola<Clan<T>> aux;

  while(!cola.vacio()){
    Clan<T> miembro = cola.front();
    cola.pop();
    if(miembro.getId_Father() == "null"){
      List<Contribuyentes<T>> listavacia;
      founder = new Node<Clan<T>, List<Contribuyentes<T>>>(miembro, listavacia, nullptr, nullptr);
    }else{
      aux.push(miembro);
    }
  }
  bool insertar = true;
  while(!aux.vacio() && insertar){
    insertar = false;
    int size = 0;
    Cola<Clan<T>> temp;
    while(!aux.vacio()){
      size ++;
      Clan<T> m = aux.front();
      aux.pop();
      temp.push(m);
    }

    for(int i = 0; i<size; i++){
      Clan<T> miembro = temp.front();
      temp.pop();
      Node<Clan<T>, List<Contribuyentes<T>>>* parent = findNode(founder, miembro.getId_Father());
      if(parent!= nullptr){
        agregar(parent, miembro);
        insertar = true;
      }else{
        aux.push(miembro);
      }
    }
  }
  
}
template<class T>
void Tree<T>::preOrder(Node<Clan<T>, List<Contribuyentes<T>>>* root){
    if(root == nullptr) return;
    root->getData().print();
    preOrder(root->getLeft());
    preOrder(root->getRight());
}