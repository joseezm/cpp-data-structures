#ifndef NODO_H
#define NODO_H

class nodo
{
    public:
        int valor;
        nodo * next;

        nodo(int v, nodo* n = NULL){
            valor=v;
            next=n;
        }

};

#endif // NODO_H
