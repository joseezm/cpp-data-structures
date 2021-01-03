#include <iostream>
using namespace std;



template<class T>
struct nodo2{
    T valor;
    nodo2<T>* hijos[3];

    nodo2(T v,nodo2<T>* d=NULL,nodo2<T>* i=NULL,nodo2<T>* u=NULL){
        valor=v;
        hijos[1]=d;
        hijos[0]=i;
        hijos[2]=u;
    }
    void imprimir(){
        cout<<valor<< "->hijos:";
        if(hijos[0])
        cout<<hijos[0]->valor;
        else
            cout<<"NULL";
        cout<<",";
        if(hijos[1])
        cout<<hijos[1]->valor;
        else
            cout<<"NULL";
        cout<<" padre:";
        if(hijos[2])
        cout<<hijos[2]->valor;
        else
            cout<<"NULL";
        cout<<endl;

        if( hijos[0])
            hijos[0]->imprimir();
        if(hijos[1])
            hijos[1]->imprimir();
    }
    void deleteAll(){
        if(hijos[0]!=NULL){
            hijos[0]->deleteAll();
        }
        if(hijos[1]!=NULL){
            hijos[1]->deleteAll();
        }
        delete this;
    }
};


template <class T>
struct arbol3{
    nodo2<T>*head;
    arbol3(){
        head=NULL;
    }
    arbol3(T n){
        head=new nodo2<T>(n);
    }
    arbol3(nodo2<T>*n=NULL){
        head=n;
    }
    void sethead(nodo2<T>*n=NULL){
        head=n;
    }
    void imprimir(){
        if(head==NULL){
            cout<<"arbol vacio";
            return;
        }
        head->imprimir();
    }
    bool buscar(T val,nodo2<T>**&n,nodo2<T>*&n2){
        n2=NULL;
        n=&head;
        while((*n)!=NULL){
            if((*n)->valor < val){
                n2=*n;
                n=&((*n)->hijos[1]);
            }else if((*n)->valor > val){
                n2=*n;
                n=&((*n)->hijos[0]);
            }else{
                return true;
            }
        }
        return false;
    }
    void Insert(T val){
        nodo2<T>**p;
        nodo2<T>*p2;
        if (!buscar(val,p,p2)){
            if(!(*p)){
                *p=new nodo2<T>(val,NULL,NULL,p2);
                //cout<<endl<<(*p)->valor<< "->"<<(*p)->hijos[2]->valor<<endl;
            }else if((*p)->valor<val){
                *p=new nodo2<T>(val,*p,NULL,p2);
                //cout<<endl<<(*p)->valor<< "->"<<(*p)->hijos[2]->valor<<endl;
            }else{
                *p=new nodo2<T>(val,NULL,*p,p2);
                //cout<<endl<<(*p)->valor<< "->"<<(*p)->hijos[2]->valor<<endl;
            }
        }
    }
    void eliminar(T val){
        nodo2<T>**p;
        nodo2<T>*p2;
        if (buscar(val,p,p2)){
            if((*p)->hijos[1] && (*p)->hijos[0]){
                nodo2<T>*aux=*p;
                p=&((*p)->hijos[1]);
                while((*p)->hijos[0])
                    p=&((*p)->hijos[0]);
                aux->valor=(*p)->valor;
            }
            nodo2<T>*aux=*p;
            *p=(*p)->hijos[!(*p)->hijos[0]];
            delete aux;
        }
    }
    void Print(nodo2<T>*p,int n){
        if(!p) return ;
        Print(p->hijos[1],n+1);
        for(int i=0;i<n;i++){
            cout<<"---";
        }
        cout<<p->valor<<endl;
        Print(p->hijos[0],n+1);
    }
};
int main()
{
    arbol3<int> a1(1);
    a1.Insert(8);
    a1.Insert(3);
    a1.Insert(7);
    a1.Insert(2);
    a1.Insert(9);
    a1.Print(a1.head,2);
    a1.eliminar(1);
    cout << endl;
    a1.Print(a1.head,2);


    return 0;
}
