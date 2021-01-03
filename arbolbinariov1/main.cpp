#pragma once
#include<iostream>

using namespace std;

template<class T>
class Node
{
    public:
	T data;
	Node<T> *izquierda, *derecha;

	Node(){
		izquierda = derecha = 0;
	}

	Node(const T& e, Node<T>* l = 0, Node<T> * r = 0){
		data = e; izquierda = l; derecha = r;
	}
};

template<class T>
class BTree
{
    public:
	Node<T>* root;

	void DeleteCases(Node<T> *& p){
		Node<T>* tmp = p;
		if (p != 0){
			if (!p->derecha)
				p = p->izquierda;
			else if (p->izquierda == 0)
				p = p->derecha;
			else{
				tmp = p->izquierda;
				while (tmp->derecha != 0){
					tmp = tmp->derecha;
					tmp->derecha = p->derecha;
					tmp = p;
					p = p->izquierda;
				}
				delete tmp;
			}
		}
	}

	BTree(){
		root = 0;
	}
	T* Search(T e, Node<T>* p){
		//p = root;
		while (p != 0){
			if (e == p->data)
				return &p->data;
			else if (e < p->data)
				p = p->izquierda;
			else
				p = p->derecha;
		}
		return 0;
	}
	void Insert( const T& e){
		Node<T> *p = root;
		Node<T> *prev = p;
		while (p != 0){
			prev = p;
			if (e < p->data)
				p = p->izquierda;
			else p = p->derecha;
		}
		if (root == 0)
			root = new Node<T>(e);
		else if (e < prev->data)
			prev->izquierda = new Node<T>(e);
		else prev->derecha = new Node<T>(e);
	}

	void Delete(const T e){
		Node<T>* p = root;
		Node<T>* prev = 0;
		Node<T>* temp = 0;

		while (p != 0){
			if (p->data == e)
				break;
			prev = p;
			if (e < p->data)
				p = p->izquierda;
			else p = p->derecha;
		}
		if( p != 0 && p->data == e){
            if (p->izquierda && p->derecha){
                if (prev->derecha == p)
                    prev->derecha =0;
                else if (prev->izquierda == p)
                    prev->izquierda==0;
                delete p;
                }
            else if (p->izquierda){
                temp=p;
                p->data = Rep(temp);
                delete temp;
            }
            else
                delete p;
		}
		else std::cout << "\nValue " << e << " is not in the Tree\n";

	}

	T Rep (Node <T> *&p){
	p = p->izquierda;
	for (;p->derecha; p=p->derecha);
	return p->data;
	}

    void Print(Node<T> *p,int n){
        if(!p) return ;
        Print(p->derecha,n+1);
        for(int i=0;i<n;i++){
            cout<<"---";
        }
        cout<<p->data<<endl;
        Print(p->izquierda,n+1);
    }
};

int main()
{
    BTree <int>a1;
    a1.Insert(1);
    a1.Insert(8);
    a1.Insert(3);
    a1.Insert(7);
    a1.Insert(2);
    a1.Insert(9);
    a1.Print(a1.root,2);
    cout << endl;
    a1.Delete(1);
    a1.Print(a1.root,2);

    return 0;
}
