#include <iostream>
#include "nodo.h"
#include "lista.h"
#include <stdlib.h>
#include <time.h>

using namespace std;

void concatenar(lista lista1, lista lista2, lista &listaC ){
    nodo *aux;
    aux = lista1.head;
    while (aux){
        listaC.addnodo(aux->valor);
        aux=aux->next;
    }
    aux=lista2.head;
    while (aux){
        listaC.addnodo(aux->valor);
        aux=aux->next;
    }


}


int main()
{
    srand(time(NULL));
    lista lista1;
    lista lista2;
    lista listaC;

    int i=0;
    while(i<15){
        lista1.addnodo(rand()%100);
        lista2.addnodo(rand()%100);
        i++;
    }

    cout << "Lista 1: " << endl;
    lista1.printlista();
    cout << endl << "Lista 2: " << endl;
    lista2.printlista();
    concatenar(lista1,lista2,listaC);
    cout << endl << "Lista Concatenada: "<< endl;
    listaC.printlista();


    return 0;
}
