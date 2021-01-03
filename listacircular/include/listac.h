#ifndef LISTAC_H
#define LISTAC_H
#include <iostream>
#include "nodo.h"

using namespace std;

class listac
{
    public:
        nodo *head = NULL;
        nodo *ultimo = NULL;

        void addnodo(int n){
           if(!(buscar(n))){
            nodo* nuevo_nodo = new nodo(n);
            if (head==NULL){
            head=nuevo_nodo;
            head->next=head;
            ultimo=head;
           }
           else{
            ultimo->next=nuevo_nodo;
            nuevo_nodo->next=head;
            ultimo=nuevo_nodo;
            ultimo->next=head;
           }
           }
        }

        void printlista(){
            if(head){
            nodo *aux;
            aux=head;
            do{
                cout << "Mem: " << int(aux) << "     Valor: " << aux->valor << "     Next: " << int(aux->next) << endl;
                //cout << aux->valor << "->";
                aux=aux->next;
            }while(aux!=head);

            cout << endl;
            }
            else
                cout <<"LISTA VACIA"<<endl;
        }

        bool buscar(int n){
            nodo *aux;
            aux=head;
            if (aux==NULL)
                return false;
            do{
                if(aux->valor==n){
                    return true;
                }
                aux=aux->next;
            }while(aux!=head);

            return false;
        }

        void eliminarElemento(int n){
            nodo*aux;
            nodo*aux_a=NULL;
            aux=head;
            do{
                aux_a=aux;
                aux=aux->next;
                ultimo->next=head;

            }while(aux!=head && aux->valor!=n);

            if (aux==NULL)
                cout << "Lista Vacia D= "  << endl;

            else if(aux_a==NULL){
                head=head->next;
                ultimo->next=head;
                delete aux;
            }

            else{
                aux_a->next=aux->next;
                ultimo->next=head;
                delete aux;
            }
            ultimo->next=head;
        }

        void borrarLista(){
            nodo*aux;
            while(head){
                aux=head;
                head=head->next;
                ultimo->next=head;
                delete aux;

                if(head==ultimo){
                    aux=head;
                    head=ultimo;
                    delete aux;
                    delete head;
                }
                delete ultimo;
                head=NULL;
                ultimo=NULL;
            }


        }


};

#endif // LISTAC_H
