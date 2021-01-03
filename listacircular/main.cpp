#include <iostream>
#include "nodo.h"
#include "listac.h"
#include <stdlib.h>
#include <time.h>

using namespace std;


int main()
{
    srand(time(NULL));
    listac lista1;


    int i=0;
    while(i<15){
        lista1.addnodo(rand()%100);
        i++;
    }

    lista1.addnodo(15);

    cout << "Lista 1: " << endl;
    lista1.printlista();

    cout << lista1.buscar(15)<<endl;



    return 0;
}
