#ifndef LISTA_H
#define LISTA_H
#include <iostream>
#include "nodo.h"

using namespace std;

class lista
{
    public:
        nodo *head = NULL;

        void addnodo(int n){
            if(!(buscar(n))){
                nodo* nuevo_nodo = new nodo(n);
                nodo* aux1 = head;
                nodo* aux2;

                while((aux1!=NULL) && (aux1->valor < n )){
                    aux2=aux1;
                    aux1=aux1->next;
                }
                if (head == aux1){
                    head=nuevo_nodo;
                }
                else
                    aux2->next = nuevo_nodo;

                nuevo_nodo->next=aux1;
                }
            else
                cout << "elemento repetido" << endl;
        }

        void printlista(){
            nodo *aux;
            aux=head;
            nodo*aux2=NULL;
            while(aux){
                cout << "Mem: " << int(aux) << "     Valor: " << aux->valor << "     Next: " << int(aux->next) << endl;
                aux2=aux;
                aux=aux->next;
            }
            cout << endl;
        }

        bool buscar(int n){
            nodo *aux;
            aux=head;
            while(aux){
                if(aux->valor==n){
                    return true;
                }
                aux=aux->next;
            }
            return false;
        }

        void eliminarElemento(int n){
            nodo*aux;
            nodo*aux_a=NULL;
            aux=head;
            while(aux && aux->valor!=n){
                aux_a=aux;
                aux=aux->next;
            }

            if (aux==NULL)
                cout << "lista vacia" << endl;

            else if(aux_a==NULL){
                head=head->next;
                delete aux;
            }

            else{
                aux_a->next=aux->next;
                delete aux;
            }
        }

        void borrarLista(){
            nodo*aux;
            while(head){
                aux=head;
                head=aux->next;
                delete aux;
            }
        }


};

#endif // LISTA_H
