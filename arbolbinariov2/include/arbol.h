#ifndef ARBOL_H
#define ARBOL_H

#include<iostream>
using namespace std;

template < class T>
class nodo{
public:
    T valor;
    T* hijos[2];

};
class arbol{
public:
    T* head;
    bool buscar(T val,nodo<T>**&n){
        n=&head;
        while((*n)!=NULL){
            if((*n)->valor < val){
                n=&((*n)->hijos[1]);
            }else if((*n)->valor > val){
                n=&((*n)->hijos[0]);
            }else{
                return true;
            }
        }
        return false;
    }
    void insertar(T val){
        nodo<T>**p;
        if (!buscar(val,p)){
            if(!(*p)){
                *p=new nodo<T>(val);
            }else if((*p)->valor<val){
                *p=new nodo<T>(val,*p);
            }else{
                *p=new nodo<T>(val,NULL,*p);
            }
        }
    }
    void eliminar(T val){
        nodo<T>**p;
        if (buscar(val,p)){
            if((*p)->hijos[1] && (*p)->hijos[0]){
                nodo<T>*aux=*p;
                p=&((*p)->hijos[1]);
                while((*p)->hijos[0])
                    p=&((*p)->hijos[0]);
                aux->valor=(*p)->valor;
            }
            nodo<T>*aux=*p;
            *p=(*p)->hijos[!(*p)->hijos[0]];
            delete aux;
        }
    }

};




#endif // ARBOL_H
