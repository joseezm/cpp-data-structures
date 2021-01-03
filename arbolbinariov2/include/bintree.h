#ifndef BINTREE_H
#define BINTREE_H
#include "BinTree.cpp"

template<typename T>
class Nodo{
public:
    Nodo(T);
    T valor;
    Nodo<T>*Nodes[2];
};

template<class T>
class BinTree{
public:
    BinTree();
    Nodo<T>*Root;
    bool Find(T x,Nodo<T>**&p);
    Nodo<T>** Rep(Nodo<T>**q);
    bool Push(T x);
    bool Pop(T x);
    void InOrder(Nodo<T>*p);
    void Print(Nodo<T>*p,int);
    void Mostrar(Nodo<T>*p,int);
};

#endif // BINTREE_H
