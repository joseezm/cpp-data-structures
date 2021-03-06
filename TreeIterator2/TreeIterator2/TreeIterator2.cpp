// TreeIterator2.cpp : Este archivo contiene la función "main". La ejecución del programa comienza y termina ahí.
//

#include "pch.h"
#include <iostream>

using namespace std;

template <class T>
class nodo {
public:
	T valor;
	nodo *rama[2];
	nodo(T V, nodo* A = NULL, nodo* B = NULL) {
		valor = V;
		rama[0] = A;
		rama[1] = B;
	}
};

template <class T>
class nodo_ {
public:
	int valor;
	nodo<T>* a;
	nodo_<T>* next;
	nodo_(int V, nodo<T>* A, nodo_<T>* N = NULL) {
		valor = V;
		next = N;
		a = A;
	}
};

template <class T>
class stack {
public:
	nodo_<T>* head = NULL;

	void add(int V, nodo<T>* A) {
		head = new nodo_<T>(V, A, head);
	}

	void add_end(int V, nodo<T>* A) {
		nodo_<T>** t = &head;
		while (*t) { t = &((*t)->next); }
		*t = new nodo_<T>(V, A);
	}

	bool remove() {
		if (head == NULL) { return false; }
		nodo_<T>* t;
		t = head;
		head = head->next;
		delete t;
		return true;
	}

	void vaciar() {
		while (head) {
			remove();
		}
	}

	stack operator = (stack<T> x) {
		vaciar();
		nodo_<T>* t = x.head;
		while (t) {
			add_end(t->valor, t->a);
			t = t->next;
		}
		return *this;
	}

};

class PreOrder { public: int a = 0, b = 1, c = 2; };
class InOrder { public: int a = 1, b = 0, c = 2; };
class PostOrder { public: int a = 2, b = 0, c = 1; };
class Reverse { public: int a = 1, b = 2, c = 0; };

template <class T, class C>
class iterador {
public:
	C d;
	stack<T> j;
	nodo<T>* a;
	int n = 0;
	iterador(int n_ = 0, nodo<T>* a1 = 0) {
		n = n_;
		a = a1;
	}

	iterador operator = (iterador x) {
		a = x.a;
		n = x.n;
		return (*this)++;
	}

	bool operator != (iterador x) {
		return (a != x.a) || ((a == x.a) && (n != x.n));
	}

	iterador operator ++ (int) {
		if (j.head) {
			n = d.a + 1;
			j.head->valor = n;
		}
		else {
			j.head = new nodo_<T>(0, a);
		}
		while (n != d.a) {
			if (n == d.b) {
				j.head->valor = d.b + 1;
				if (j.head->a->rama[0]) { j.add(0, j.head->a->rama[0]); }
			}

			else if (n == d.c) {
				j.head->valor = d.c + 1;
				if (j.head->a->rama[1]) { j.add(0, j.head->a->rama[1]); }
			}

			else if (n == 3) {
				if (j.head->next) { j.remove(); }
				else {
					n = 3;
					a = j.head->a;
					return *this;
				}
			}

			n = j.head->valor;
		}
		a = j.head->a;
		return *this;
	}

	int operator*() {
		j.head->valor = 1; n = 1;
		return a->valor;
	}
};

template <class T, class C>
class BinaryTree {
public:
	typedef iterador<T, C> iterator;
	iterator begin() { return iterator(0, head); }
	iterator end() { return iterator(3, head); }

	nodo<T>* head = NULL;

	bool buscar(T V, nodo<T>** &N) {
		N = &head;
		while (*N) {
			if ((*N)->valor > V) { N = &((*N)->rama[0]); }
			else if ((*N)->valor < V) { N = &((*N)->rama[1]); }
			else { return true; }
		}
		return false;
	}

	void add(int V) {
		nodo<T>** p;
		if (buscar(V, p)) return;
		*p = new nodo<T>(V);
		return;
	}

	void remove(int val) {
		nodo<T>**p;
		if (buscar(val, p)) {
			if ((*p)->rama[1] && (*p)->rama[0]) {
				nodo<T>*aux = *p;
				p = &((*p)->rama[1]);
				while ((*p)->rama[0])
					p = &((*p)->rama[0]);
				aux->valor = (*p)->valor;
			}
			nodo<T>*aux = *p;
			*p = (*p)->rama[!(*p)->rama[0]];
			delete aux;
		}
	}

	void eliminar_arbol() {
		nodo<T>* a = head;
		while (head) {
			remove(a->valor);
			a = head;
		}
	}

	void Print(nodo<int> *p, int n) {
		if (!p) return;
		Print(p->rama[1], n + 1);
		for (int i = 0; i < n; i++) {
			cout << "---";
		}
		cout << p->valor << endl;
		Print(p->rama[0], n + 1);
	}

};

int main() {
	BinaryTree<int,InOrder> A;

	A.add(1);
	A.add(8);
	A.add(3);
	A.add(7);
	A.add(2);
	A.add(9);
	A.add(4);
	A.add(5);
	A.add(6);

	
	A.Print(A.head, 0);
	
	cout<< endl << "InOrder : "; BinaryTree<int,InOrder>::iterator i;
	
	for (i = A.begin(); i != A.end(); i++) {
		cout << *i << " ";
	}

	BinaryTree<int, PreOrder> B;

	B.add(1);
	B.add(8);
	B.add(3);
	B.add(7);
	B.add(2);
	B.add(9);
	B.add(4);
	B.add(5);
	B.add(6);

	cout << endl << "PreOrder :"; BinaryTree<int, PreOrder>::iterator p;

	for (p = B.begin(); p != B.end(); p++) {
		cout << *p << " ";
	}

	BinaryTree<int, PostOrder> C;

	C.add(1);
	C.add(8);
	C.add(3);
	C.add(7);
	C.add(2);
	C.add(9);
	C.add(4);
	C.add(5);
	C.add(6);

	cout << endl << "PostOrder : "; BinaryTree<int, PostOrder>::iterator ps;

	for (ps = C.begin(); ps != C.end(); ps++) {
		cout << *ps << " ";
	}

	BinaryTree<int, Reverse> D;

	D.add(1);
	D.add(8);
	D.add(3);
	D.add(7);
	D.add(2);
	D.add(9);
	D.add(4);
	D.add(5);
	D.add(6);

	cout << endl << "Reverse : "; BinaryTree<int, Reverse>::iterator r;

	for (r = D.begin(); r != D.end(); r++) {
		cout << *r << " ";
	}


	return 0;
}