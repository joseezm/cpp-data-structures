#include <iostream>
#include "nodo.h"
#include "lista.h"

using namespace std;

void parImpar(lista C, lista &P, lista &I){
    nodo* aux;
    aux=C.head;
    while(aux){
    if(((aux->valor)%2)==0)
        P.addnodo(aux->valor);
    else
        I.addnodo(aux->valor);
    aux=aux->next;
    }
}

int main()
{
    lista listaC;
    lista listaPar;
    lista listaImpar;

    listaC.addnodo(3);
    listaC.addnodo(6);
    listaC.addnodo(12);
    listaC.addnodo(25);
    listaC.addnodo(8);
    listaC.addnodo(9);
    listaC.addnodo(54);
    listaC.addnodo(11);
    listaC.addnodo(17);



    parImpar(listaC,listaPar,listaImpar);
    cout << "LISTA PAR" << endl << endl;
    listaPar.printlista();
    cout << "LISTA IMPAR" << endl << endl;
    listaImpar.printlista();


    return 0;
}
