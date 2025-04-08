#include <iostream>
#include <string>
#include "tree.h"

using namespace std;

int main() {
    Tree<string> clanTree;
    clanTree.buildTreeFromCSV("data.csv");
    clanTree.readContribuyentesFromCSV("contribuyentes.csv");

    cout << "Arbol en PreOrder:" << endl;
    clanTree.preOrder(clanTree.getFounder());

    Node<Clan<string>, List<Contribuyentes<string>>>* liderActual = clanTree.buscarLider(clanTree.getFounder());
    if(liderActual) {
        cout << "\nLider Actual:" << endl;
        liderActual->getData().print();
    } else {
        cout << "\nNo se encontro lider." << endl;
    }

    cout << "\nModificacion de Nodo:" << endl;
    clanTree.modificarDatosNodo();

    cout << "\nActualizando Lider..." << endl;
    clanTree.actualizarLider();

    cout << "\nArbol Actualizado:" << endl;
    clanTree.preOrder(clanTree.getFounder());

    liderActual = clanTree.buscarLider(clanTree.getFounder());
    if(liderActual) {
        cout << "\nLider Actual:" << endl;
        liderActual->getData().print();
    } else {
        cout << "\nNo se encontro lider." << endl;
    }

    return 0;
}