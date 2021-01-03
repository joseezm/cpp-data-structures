#include<iostream>
using namespace std;


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
    bool Insert(T x);
    bool Delete(T x);
    void InOrder(Nodo<T>*p);
    void Print(Nodo<T>*p,int);
    void Mostrar(Nodo<T>*p,int);
};

template<typename T>
Nodo<T>::Nodo(T x){
    valor=x;
    Nodes[0]=nullptr;
    Nodes[1]=nullptr;
}

template<class T>
BinTree<T>::BinTree(){
    Root=nullptr;
}

template<class T>
bool BinTree<T>::Find(T x,Nodo<T>**&p){
    p=&Root;
    while(*p && (*p)->valor!=x){
        p=&(*p)->Nodes[(*p)->valor<x];
    }
    return *p;
}

template<class T>
Nodo<T>** BinTree<T>::Rep(Nodo<T>**p){
    p=&Root;
    p=&(*p)->Nodes[0];
    for(p;(*p)->Nodes[1];p=&(*p)->Nodes[1]){cout<<"Der "<<endl;}
    return p;
}

template<class T>
bool BinTree<T>::Insert(T x){
    Nodo<T>**p;
    if(Find(x,p)){return 0;}
    *p=new Nodo<T>(x);
    return 1;
}

template<class T>
bool BinTree<T>::Delete(T x){
    Nodo<T>**p;
    if(!Find(x,p)){return 0;}
    if((*p)->Nodes[0] && (*p)->Nodes[1]){
        //cout<<"Entro "<<endl;
        Nodo<T>**q=Rep(p);
        (*p)->valor=(*q)->valor;
        p=q;
    }
    Nodo<T>*t=*p;
    *p=(*p)->Nodes[(*p)->Nodes[0]==0];
    delete t;
    return 1;
}

template<class T>
void BinTree<T>::InOrder(Nodo<T>*p){
    if(!p) return ;
    InOrder(p->Nodes[0]);
    cout<<p->valor<<" ";
    InOrder(p->Nodes[1]);
}

template<class T>
void BinTree<T>::Print(Nodo<T>*p,int n){
    if(!p) return ;
    Print(p->Nodes[1],n+1);
    for(int i=0;i<n;i++){
        cout<<"---";
    }
    cout<<p->valor<<endl;
    Print(p->Nodes[0],n+1);
}

/*void BinTree<T>::Mostar(Nodo<T>*p,int aux){
    if(!p) return ;
    Print(p->Nodes[1],n+1);
    for(int i=0;i<n;i++){
        cout<<"  ";
    }
    cout<<p->valor<<endl;
    Print(p->Nodes[0],n+1);
}*/


int main(){
    int aux=2;
    BinTree<int> a1;
    a1.Insert(1);
    a1.Insert(3);
    a1.Insert(8);
    a1.Insert(7);
    a1.Insert(2);
    a1.Insert(9);
    a1.Print(a1.Root,2);
    a1.Delete(3);
    cout << endl;
    a1.Print(a1.Root,2);
    return 0;
}
