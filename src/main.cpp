#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

int main() {
    Tree<string> clanTree;
    clanTree.buildTreeFromCSV("data.csv");
    clanTree.readContribuyentesFromCSV("contribuyentes.csv");
    int op;
    Node<Clan<string>, List<Contribuyentes<string>>>* liderActual = clanTree.buscarLider(clanTree.getFounder());

    if(liderActual) {
        cout << "\nLider Actual:" << endl;
        liderActual->getData().print();
    } else {
        cout << "\nNo se encontro lider." << endl;
        return 0;
    }

    do{
        clanTree.actualizarLider();
        cout<<"Menu:\n1. Modificar nodo.\n2. Imprimir nodo.\n3. Imprimir arbol.\n4. Mostrar sucesion.\n5. Imprimir lider.\n0. Salir.\n";
        cin>>op;
        switch(op){
            case 1:{
                clanTree.modificarDatosNodo();
                cin.get();
            }
            break;
            case 2:{
                cout<<"Ingresa el Id del nodo a imprimir\n";
                string id;
                cin>>id;
                cout<<"\n";
                clanTree.findNode(clanTree.getFounder(),id)->getData().print();
                clanTree.findNode(clanTree.getFounder(),id)->getList().print();
                cin.get();
            }
            break;
            case 3:{
                clanTree.preOrder(clanTree.getFounder());
                cin.get();
            }
            break;
            case 4:{
                clanTree.mostrarLineaSucesion();
                cin.get();
            }
            break;
            case 5:{
                cout<<"\nLider actual:\n";
                liderActual = clanTree.buscarLider(clanTree.getFounder());
                liderActual->getData().print();
                cin.get();
            }
            break;
            case 0:
            cout<<"Saliendo.\n";
            cin.get();
            break;
            default:
            cout<<"Opcion invalida.\n";    
        }

    }while(op!=0);

    return 0;
}