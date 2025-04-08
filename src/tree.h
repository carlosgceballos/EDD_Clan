#include "node.h"
#include "clan.h"
#include "simplelist/list.h"
#include "cola/cola.h"
#include <string>
#include <iostream>
#include <fstream>
#include <sstream>

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
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarLider(Node<Clan<T>, List<Contribuyentes<T>>>* root);  
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarEnHijos(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarHermano(Node<Clan<T>, List<Contribuyentes<T>>>* nodo);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnHermano(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarTio(Node<Clan<T>, List<Contribuyentes<T>>>* nodo);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnTio(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnAncestro(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarPadre(Node<Clan<T>, List<Contribuyentes<T>>>* current, Node<Clan<T>, List<Contribuyentes<T>>>* target);
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarSucesor(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* buscarEnHijas(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnHermana(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnTia(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);
  Node<Clan<T>, List<Contribuyentes<T>>>* BuscarEnAncestra(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider);

  void insertNode(Node<Clan<T>, List<Contribuyentes<T>>>* parent, Clan<T> miembro);
  void buildTree(Cola<Clan<T>>& cola);
  void preOrder(Node<Clan<T>, List<Contribuyentes<T>>>* root);
  void buildTreeFromCSV(const string &filename);
  void readContribuyentesFromCSV(const string &filename);
  void modificarDatosNodo();
  void actualizarLider();
  void mostrarLineaSucesion();
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
    if (root == nullptr)
        return nullptr;
    if (root->getData().getID() == id)
        return root;
    Node<Clan<T>, List<Contribuyentes<T>>>* found = findNode(root->getLeft(), id);
    if (found != nullptr)
        return found;
    return findNode(root->getRight(), id);
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
void Tree<T>::buildTree(Cola<Clan<T>>& cola){
    Cola<Clan<T>> aux;
    while(!cola.vacio()){
        Clan<T> miembro = cola.front();
        cola.pop();
        if(miembro.getId_Father() == "null" || miembro.getId_Father() == ""){
            List<Contribuyentes<T>> listavacia;
            founder = new Node<Clan<T>, List<Contribuyentes<T>>>(miembro, listavacia, nullptr, nullptr);
        } else {
            aux.push(miembro);
        }
    }

    bool insertedSomething = false;
    do {
        insertedSomething = false;
        Cola<Clan<T>> aux2;
        while(!aux.vacio()){
            Clan<T> miembro = aux.front();
            aux.pop();
            Node<Clan<T>, List<Contribuyentes<T>>>* parent = findNode(founder, miembro.getId_Father());
            if(parent != nullptr){
                insertNode(parent, miembro);
                insertedSomething = true;
            } else {
                aux2.push(miembro);
            }
        }
        if(insertedSomething){
            aux = aux2;
        } else {
            break;
        }
    } while(!aux.vacio());
}


template<class T>
void Tree<T>::preOrder(Node<Clan<T>, List<Contribuyentes<T>>>* root){
    if(root == nullptr) return;
    root->getData().print();
    root->getList().print();
    preOrder(root->getLeft());
    preOrder(root->getRight());
}

template<class T>
void Tree<T>::buildTreeFromCSV(const string &filename) {
    Cola<Clan<T>> colaClan; 

    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }

    string line;
    getline(file, line);

    while(getline(file, line)){
        stringstream ss(line);
        string id, name, last_name, genderStr, ageStr, id_father, is_deadStr, was_chiefStr, is_chiefStr;

        getline(ss, id, ',');
        getline(ss, name, ',');
        getline(ss, last_name, ',');
        getline(ss, genderStr, ',');
        getline(ss, ageStr, ',');
        getline(ss, id_father, ',');
        getline(ss, is_deadStr, ',');
        getline(ss, was_chiefStr, ',');
        getline(ss, is_chiefStr, ',');

        char gender = genderStr.empty() ? '\0' : genderStr[0];
        int age = stoi(ageStr);
        bool is_dead = (is_deadStr == "1");
        bool was_chief = (was_chiefStr == "1");
        bool is_chief = (is_chiefStr == "1");

        Clan<T> miembro(id, name, last_name, gender, age, id_father, is_dead, was_chief, is_chief);

        colaClan.push(miembro);
    }
    file.close();

    buildTree(colaClan);
}

template<class T>
void Tree<T>::readContribuyentesFromCSV(const string &filename) {
    ifstream file(filename);
    if (!file.is_open()){
        cerr << "Error al abrir el archivo: " << filename << endl;
        return;
    }
    
    string line;
    getline(file, line); 

    while(getline(file, line)){
        stringstream ss(line);
        string id, idBenef, nombre, edadStr, contribucion, gradContStr;
        
        getline(ss, id, ',');
        getline(ss, idBenef, ',');
        getline(ss, nombre, ',');
        getline(ss, edadStr, ',');
        getline(ss, contribucion, ',');
        getline(ss, gradContStr, ',');
        
        int edad = stoi(edadStr);
        int gradCont = stoi(gradContStr);

        Contribuyentes<T> contribObj(id, idBenef, nombre, edad, contribucion, gradCont);
        Node<Clan<T>, List<Contribuyentes<T>>>* nodo = findNode(founder, idBenef);
        if(nodo != nullptr) {
            nodo->getList().insert(contribObj);
        } else {
            cerr << "No se encontró nodo con id: " << idBenef << endl;
        }
    }
    file.close();
}

//ya en proyecto
template<class T>
void Tree<T>::modificarDatosNodo() {
    T id;
    cout << "Ingrese el id del nodo a modificar: ";
    cin >> id;
    
    Node<Clan<T>, List<Contribuyentes<T>>>* nodo = findNode(founder, id);
    if(nodo == nullptr) {
         cout << "No se encontró un nodo con el id: " << id << endl;
         return;
    }
    
    Clan<T> clan = nodo->getData();
    bool continuar = true;
    
    while(continuar) {
         cout << "\nNodo encontrado:\n";
         clan.print();
         cout << "\nSeleccione el campo a modificar:" << endl;
         cout << "1. Nombre" << endl;
         cout << "2. Apellido" << endl;
         cout << "3. Género" << endl;
         cout << "4. Edad" << endl;
         cout << "5. Estado (0: vivo, 1: muerto)" << endl;
         cout << "6. Fue jefe (0 o 1)" << endl;
         cout << "7. Es jefe (0 o 1)" << endl;
         cout << "8. Salir" << endl;
         
         int opcion;
         cin >> opcion;
         cin.ignore();
         
         switch(opcion) {
             case 1: {
                     string nuevoNombre;
                     cout << "Ingrese el nuevo nombre: ";
                     getline(cin, nuevoNombre);
                     clan.setName(nuevoNombre);
                 }
                 break;
             case 2: {
                     string nuevoApellido;
                     cout << "Ingrese el nuevo apellido: ";
                     getline(cin, nuevoApellido);
                     clan.setLastName(nuevoApellido);
                 }
                 break;
             case 3: {
                     char nuevoGenero;
                     cout << "Ingrese el nuevo género (H/M): ";
                     cin >> nuevoGenero;
                     clan.setGender(nuevoGenero);
                     cin.ignore();
                 }
                 break;
             case 4: {
                     int nuevaEdad;
                     cout << "Ingrese la nueva edad: ";
                     cin >> nuevaEdad;
                     clan.setAge(nuevaEdad);
                     cin.ignore();
                 }
                 break;
             case 5: {
                     int estado;
                     cout << "Ingrese el estado (0 para vivo, 1 para muerto): ";
                     cin >> estado;
                     bool isDead = (estado == 1);
                     clan.setIsDead(isDead);
                     cin.ignore();
                 }
                 break;
             case 6: {
                     int fueJefe;
                     cout << "Ingrese 0 (false) o 1 (true) para 'fue jefe': ";
                     cin >> fueJefe;
                     clan.setWasChief(fueJefe);
                     cin.ignore();
                 }
                 break;
             case 7: {
                     int esJefe;
                     cout << "Ingrese 0 (false) o 1 (true) para 'es jefe': ";
                     cin >> esJefe;
                     clan.setIsChief(esJefe);
                     cin.ignore();
                 }
                 break;
             case 8:
                 continuar = false;
                 break;
             default:
                 cout << "Opción no válida." << endl;
         }
    }

    nodo->setData(clan);
    cout << "\nNodo modificado exitosamente:\n";
}

//

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarLider(Node<Clan<T>, List<Contribuyentes<T>>>* root) {
    if (root == nullptr)
        return nullptr;
    if (root->getData().getRol() == true)
        return root;
    Node<Clan<T>, List<Contribuyentes<T>>>* leftResult = buscarLider(root->getLeft());
    if (leftResult != nullptr)
        return leftResult;
    return buscarLider(root->getRight());
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarSucesor(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider) {
    if(nodoLider == nullptr)
    return nullptr;

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijos(nodoLider);
    if(candidato != nullptr)
        return candidato;
    
    candidato = BuscarEnHermano(nodoLider);
    if(candidato != nullptr)
        return candidato;
    
    candidato = BuscarEnTio(nodoLider);
    if(candidato != nullptr)
        return candidato;
    
    candidato = BuscarEnAncestro(nodoLider);
    if(candidato != nullptr)
    return candidato;

    candidato = buscarEnHijas(nodoLider);
    if(candidato!=nullptr)
    return candidato;

    candidato = BuscarEnHermana(nodoLider);
    if(candidato!=nullptr)
    return candidato;

    candidato = BuscarEnTia(nodoLider);
    if(candidato!=nullptr)
    return candidato;

    candidato= BuscarEnAncestra(nodoLider);
    if(candidato!=nullptr)
    return candidato;

}

template<class T>
void Tree<T>::actualizarLider(){
    Node<Clan<T>,List<Contribuyentes<T>>>* nodoLider = buscarLider(founder);
    if(nodoLider == nullptr){
        return;
    }

    if(nodoLider->getData().getAlive() == false && nodoLider->getData().getAge() < 70){
        return;
    }

    Clan<T> leaderData = nodoLider->getData();
    leaderData.setIsChief(false);
    leaderData.setWasChief(true);
    nodoLider->setData(leaderData);

    Node<Clan<T>,List<Contribuyentes<T>>>* sucesor = buscarSucesor(nodoLider);
    if(sucesor == nullptr){
        return;
    }
    Clan<T> sucesorData = sucesor->getData();
    sucesorData.setIsChief(true);
    sucesor->setData(sucesorData);
    cout<<"Actualizando lider...\n";
}


template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarHermano(Node<Clan<T>, List<Contribuyentes<T>>>* nodo) {
    if(nodo == nullptr)
        return nullptr;
    
    T idFather = nodo->getData().getId_Father();
    
    if(idFather == "null" || idFather == "")
        return nullptr;
    
    Node<Clan<T>, List<Contribuyentes<T>>>* padre = findNode(founder, idFather);
    if(padre == nullptr)
        return nullptr;
    
    if(padre->getLeft() != nullptr && padre->getLeft() != nodo)
        return padre->getLeft();

    if(padre->getRight() != nullptr && padre->getRight() != nodo)
        return padre->getRight();

    return nullptr;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarTio(Node<Clan<T>, List<Contribuyentes<T>>>* nodo) {
    if(nodo == nullptr)
        return nullptr;
    
    T idFather = nodo->getData().getId_Father();
    if(idFather == "null" || idFather == "")
        return nullptr;
    
    Node<Clan<T>, List<Contribuyentes<T>>>* padre = findNode(founder, idFather);
    Node<Clan<T>, List<Contribuyentes<T>>>* tio = buscarHermano(padre);

    if(tio == nullptr)
        return nullptr;
    
    return tio;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarEnHijos(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider) {
    if (nodoLider == nullptr)
        return nullptr;

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = nullptr;
    if (nodoLider->getLeft() != nullptr) {
        if (nodoLider->getLeft()->getData().getGender() == 'M' &&
            nodoLider->getLeft()->getData().getAlive() == false &&
            nodoLider->getLeft()->getData().getAge() < 70) {
            candidato = nodoLider->getLeft();
        }
    }
    if (nodoLider->getRight() != nullptr) {
        if (nodoLider->getRight()->getData().getGender() == 'M' &&
            nodoLider->getRight()->getData().getAlive() == false &&
            nodoLider->getRight()->getData().getAge() < 70) {
            if (candidato == nullptr)
                candidato = nodoLider->getRight();
            else if (nodoLider->getRight()->getData().getAge() > candidato->getData().getAge())
                candidato = nodoLider->getRight();
        }
    }
    if (candidato != nullptr)
        return candidato;
    
    if (nodoLider->getLeft() != nullptr && nodoLider->getRight() != nullptr) {
        if (nodoLider->getLeft()->getData().getAge() >= nodoLider->getRight()->getData().getAge()) {
            candidato = buscarEnHijos(nodoLider->getLeft());
            if (candidato != nullptr)
                return candidato;
            else
                return buscarEnHijos(nodoLider->getRight());
        } else {
            candidato = buscarEnHijos(nodoLider->getRight());
            if (candidato != nullptr)
                return candidato;
            else
                return buscarEnHijos(nodoLider->getLeft());
        }
    } else if (nodoLider->getLeft() != nullptr) {
        return buscarEnHijos(nodoLider->getLeft());
    } else if (nodoLider->getRight() != nullptr) {
        return buscarEnHijos(nodoLider->getRight());
    } else {
        return nullptr; 
    }
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnHermano(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider){
    Node<Clan<T>, List<Contribuyentes<T>>>* hermano = buscarHermano(nodoLider);
    if(hermano == nullptr){
        return nullptr;
    }

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijos(hermano);
    if(candidato != nullptr)
        return candidato;
    
    if(hermano->getData().getGender() == 'M' && hermano->getData().getAlive() == false && hermano->getData().getAge() < 70) {
        return hermano;
    }

    return nullptr;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnTio(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider){
    Node<Clan<T>, List<Contribuyentes<T>>>* tio = buscarTio(nodoLider);

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijos(tio);
    if(candidato != nullptr)
        return candidato;
    
    if(tio->getData().getGender() == 'M' && tio->getData().getAlive() == false && tio->getData().getAge() < 70) {
        return tio;
    }

    return nullptr;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarPadre(Node<Clan<T>, List<Contribuyentes<T>>>* current, Node<Clan<T>, List<Contribuyentes<T>>>* target) {
    if(current == nullptr)
        return nullptr;
    if(current->getLeft() == target || current->getRight() == target)
        return current;
    Node<Clan<T>, List<Contribuyentes<T>>>* res = buscarPadre(current->getLeft(), target);
    if(res != nullptr)
        return res;
    return buscarPadre(current->getRight(), target);
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnAncestro(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider) {
    if(nodoLider == founder)
        return nullptr;

    Node<Clan<T>, List<Contribuyentes<T>>>* padre = buscarPadre(founder, nodoLider);
    if(padre == nullptr)
        return nullptr;

    if(padre->getLeft() != nullptr && padre->getRight() != nullptr) {
        Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijos(padre);
        if(candidato != nullptr)
            return candidato;
    }

    return BuscarEnAncestro(padre);
}

// algoritmo para hijas
template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::buscarEnHijas(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider) {
    if (nodoLider == nullptr)
        return nullptr;

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = nullptr;
    if (nodoLider->getLeft() != nullptr) {
        if (nodoLider->getLeft()->getData().getGender() == 'W' && nodoLider->getLeft()->getData().getAlive() == false && nodoLider->getLeft()->getData().getAge() < 70) {
            candidato = nodoLider->getLeft();
        }
    }
    if (nodoLider->getRight() != nullptr) {
        if (nodoLider->getRight()->getData().getGender() == 'W' && nodoLider->getRight()->getData().getAlive() == false && nodoLider->getRight()->getData().getAge() < 70) {
            if (candidato == nullptr)
                candidato = nodoLider->getRight();
            else if (nodoLider->getRight()->getData().getAge() > candidato->getData().getAge())
                candidato = nodoLider->getRight();
        }
    }
    if (candidato != nullptr)
        return candidato;
    
    if (nodoLider->getLeft() != nullptr && nodoLider->getRight() != nullptr) {
        if (nodoLider->getLeft()->getData().getAge() >= nodoLider->getRight()->getData().getAge()) {
            candidato = buscarEnHijas(nodoLider->getLeft());
            if (candidato != nullptr)
                return candidato;
            else
                return buscarEnHijas(nodoLider->getRight());
        } else {
            candidato = buscarEnHijas(nodoLider->getRight());
            if (candidato != nullptr)
                return candidato;
            else
                return buscarEnHijas(nodoLider->getLeft());
        }
    } else if (nodoLider->getLeft() != nullptr) {
        return buscarEnHijas(nodoLider->getLeft());
    } else if (nodoLider->getRight() != nullptr) {
        return buscarEnHijas(nodoLider->getRight());
    } else {
        return nullptr; 
    }
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnHermana(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider){
    Node<Clan<T>, List<Contribuyentes<T>>>* hermano = buscarHermano(nodoLider);
    if(hermano == nullptr){
        return nullptr;
    }

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijas(hermano);
    if(candidato != nullptr)
        return candidato;
    
    if(hermano->getData().getGender() == 'W' && hermano->getData().getAlive() == false && hermano->getData().getAge() < 70) {
        return hermano;
    }

    return nullptr;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnTia(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider){
    Node<Clan<T>, List<Contribuyentes<T>>>* tio = buscarTio(nodoLider);

    Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijas(tio);
    if(candidato != nullptr)
        return candidato;
    
    if(tio->getData().getGender() == 'W' && tio->getData().getAlive() == false && tio->getData().getAge() < 70) {
        return tio;
    }

    return nullptr;
}

template<class T>
Node<Clan<T>, List<Contribuyentes<T>>>* Tree<T>::BuscarEnAncestra(Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider) {
    if(nodoLider == founder)
        return nullptr;

    Node<Clan<T>, List<Contribuyentes<T>>>* padre = buscarPadre(founder, nodoLider);
    if(padre == nullptr)
        return nullptr;

    if(padre->getLeft() != nullptr && padre->getRight() != nullptr) {
        Node<Clan<T>, List<Contribuyentes<T>>>* candidato = buscarEnHijas(padre);
        if(candidato != nullptr)
            return candidato;
    }

    return BuscarEnAncestra(padre);
}

template<class T>
void recorrerAux(Node<Clan<T>, List<Contribuyentes<T>>>* node, Cola<Clan<T>> &cola) {
    if (node == nullptr)
        return;
    cola.push(node->getData());
    preOrderToQueue(node->getLeft(), cola);
    preOrderToQueue(node->getRight(), cola);
}

template<class T>
void Tree<T>::mostrarLineaSucesion() {
    Cola<Clan<T>> colaNodos;
    recorrerAux(founder, colaNodos);

    Tree<T> auxTree;
    auxTree.buildTree(colaNodos);

    Node<Clan<T>, List<Contribuyentes<T>>>* nodoLider = auxTree.buscarLider(auxTree.getFounder());
    Node<Clan<T>, List<Contribuyentes<T>>>* sucesor = nullptr;

    while (nodoLider != nullptr) {
         cout<<"\nLider actual:\n";
         nodoLider->getData().print();
         cout << "--------------------" << endl;

         Clan<T> leaderData = nodoLider->getData();
         leaderData.setIsChief(false);
         leaderData.setWasChief(true);
         leaderData.setIsDead(true);
         nodoLider->setData(leaderData);

         sucesor = auxTree.buscarSucesor(nodoLider);

         if (sucesor == nullptr)
             break;
         nodoLider = sucesor;
    }
}