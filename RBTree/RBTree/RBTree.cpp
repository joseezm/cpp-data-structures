#include "pch.h"
#include <iostream> 
#include <queue>

using namespace std;

class RBNode {

public:

	int data;

	bool color;

	RBNode *izquierdo, *derecho, *padre;

	RBNode(int data) : data(data) {
		padre = izquierdo = derecho = NULL;
		color = 1;
	}

	RBNode *tio() {
		if (padre == NULL || padre->padre == NULL)
			return NULL;
		if (padre->enIzquierda())
			return padre->padre->derecho;
		else
			return padre->padre->izquierdo;
	}

	bool enIzquierda() { return this == padre->izquierdo; }
	RBNode *hermano() {
		if (padre == NULL)
			return NULL;
		if (enIzquierda())
			return padre->derecho;
		return padre->izquierdo;
	}

	void moverAbajo(RBNode *nPadres) {
		if (padre != NULL) {
			if (enIzquierda()) {
				padre->izquierdo = nPadres;
			}
			else {
				padre->derecho = nPadres;
			}
		}
		nPadres->padre = padre;
		padre = nPadres;
	}
	bool tieneHijoRojo() {
		return (izquierdo != NULL && izquierdo->color == 1) ||
			(derecho != NULL && derecho->color == 1);
	}
};

class RBTree {
public:
	RBNode *root;
	RBTree() { root = NULL; }
	RBNode *getRoot() { return root; }


	void RotacionIzquierda(RBNode *x) {
		RBNode *nPadres = x->derecho;
		if (x == root)
			root = nPadres;
		x->moverAbajo(nPadres);
		x->derecho = nPadres->izquierdo;

		if (nPadres->izquierdo != NULL)

			nPadres->izquierdo->padre = x;

		nPadres->izquierdo = x;
	}

	void RotacionDerecha(RBNode *x) {
		RBNode *nPadres = x->izquierdo;

		if (x == root)
			root = nPadres;
		x->moverAbajo(nPadres);

		x->izquierdo = nPadres->derecho;

		if (nPadres->derecho != NULL)

			nPadres->derecho->padre = x;

		nPadres->derecho = x;
	}

	void cambioColor(RBNode *x1, RBNode *x2) {
		bool temp;
		temp = x1->color;
		x1->color = x2->color;
		x2->color = temp;
	}

	void cambiarValor(RBNode *u, RBNode *v) {
		int temp;
		temp = u->data;
		u->data = v->data;
		v->data = temp;
	}

	void rojoRojo(RBNode *x) {
		if (x == root) {
			x->color = 0;
			return;
		}

		RBNode *padre = x->padre, *abuelo = padre->padre,
		*tio = x->tio();

		if (padre->color != 0) {

			if (tio != NULL && tio->color == 1) {
				padre->color = 0;
				tio->color = 0;
				abuelo->color = 1;
				rojoRojo(abuelo);
			}
			else {
				if (padre->enIzquierda()) {
					if (x->enIzquierda()) {
						cambioColor(padre, abuelo);
					}
					else {
						RotacionIzquierda(padre);
						cambioColor(x, abuelo);
					}
					RotacionDerecha(abuelo);
				}
				else {
					if (x->enIzquierda()) {
						RotacionDerecha(padre);
						cambioColor(x, abuelo);
					}
					else {
						cambioColor(padre, abuelo);
					}
					RotacionIzquierda(abuelo);
				}
			}
		}
	}

	RBNode *Rep(RBNode *x) {
		RBNode *temp = x;
		while (temp->derecho != NULL)
			temp = temp->derecho;
		return temp;
	}

	RBNode *BSTreemplazo(RBNode *x) {
		if (x->izquierdo != NULL && x->derecho != NULL)
			return Rep(x->izquierdo);
		if (x->izquierdo == NULL && x->derecho == NULL)
			return NULL;
		if (x->izquierdo != NULL)
			return x->izquierdo;
		else
			return x->derecho;
		}

	void deleteNode(RBNode *v) {
		RBNode *u = BSTreemplazo(v);
		bool uvBlack = ((u == NULL || u->color == 0) && (v->color == 0));
		RBNode *padre = v->padre;
		if (u == NULL) {
			if (v == root) {
				root = NULL;
			}
			else {
				if (uvBlack) {
					dobleNegro(v);
				}
				else {
					if (v->hermano() != NULL)
						v->hermano()->color = 1;
				}
				if (v->enIzquierda()) {
					padre->izquierdo = NULL;
				}
				else {
					padre->derecho = NULL;
				}
			}
			delete v;
			return;
		}

		if (v->izquierdo == NULL || v->derecho == NULL) {
			if (v == root) {
				v->data = u->data;
				v->izquierdo = v->derecho = NULL;
				delete u;
			}
			else {
				if (v->enIzquierda()) {
					padre->izquierdo = u;
				}
				else {
					padre->derecho = u;
				}
				delete v;
				u->padre = padre;
				if (uvBlack) {
					dobleNegro(u);
				}
				else {
					u->color = 0;
				}
			}
			return;
		}
		cambiarValor(u, v);
		deleteNode(u);
	}

	void dobleNegro(RBNode *x) {

		if (x == root)
			return;
		RBNode *hermano = x->hermano(), *padre = x->padre;
		if (hermano == NULL) {
			dobleNegro(padre);
		}
		else {
			if (hermano->color == 1) {
				padre->color = 1;
				hermano->color = 0;
				if (hermano->enIzquierda()) {
					RotacionDerecha(padre);
				}
				else {
					RotacionIzquierda(padre);

				}

				dobleNegro(x);
			}
			else {
				if (hermano->tieneHijoRojo()) {
					if (hermano->izquierdo != NULL && hermano->izquierdo->color == 1) {
						if (hermano->enIzquierda()) {
							// izquierdo izquierdo 
							hermano->izquierdo->color = hermano->color;
							hermano->color = padre->color;
							RotacionDerecha(padre);
						}
						else {
							// derecho izquierdo 
							hermano->izquierdo->color = padre->color;
							RotacionDerecha(hermano);
							RotacionIzquierda(padre);
						}
					}
					else {
						if (hermano->enIzquierda()) {
							// izquierdo derecho 
							hermano->derecho->color = padre->color;
							RotacionIzquierda(hermano);
							RotacionDerecha(padre);
						}
						else {
							// derecho derecho 
							hermano->derecho->color = hermano->color;
							hermano->color = padre->color;
							RotacionIzquierda(padre);
						}
					}
					padre->color = 0;
				}
				else {
					hermano->color = 1;
					if (padre->color == 0)
						dobleNegro(padre);
					else
						padre->color = 0;
				}
			}
		}
	}


	RBNode *Find(int n) {
		RBNode *temp = root;
		while (temp != NULL) {
			if (n < temp->data) {
				if (temp->izquierdo == NULL)
					break;
				else
					temp = temp->izquierdo;
			}
			else if (n == temp->data) {
				break;
			}
			else {
				if (temp->derecho == NULL)
					break;
				else
					temp = temp->derecho;
			}
		}
		return temp;
	}

	void Insert(int n) {
		RBNode *newNode = new RBNode(n);
		if (root == NULL) {
			newNode->color = 0;
			root = newNode;
		}
		else {
			RBNode *temp = Find(n);
			if (temp->data == n) {
				return;
			}

			newNode->padre = temp;

			if (n < temp->data)
				temp->izquierdo = newNode;
			else
				temp->derecho = newNode;
			rojoRojo(newNode);
		}
	}

	void Delete(int n) {
		if (root == NULL)
			return;
		RBNode *v = Find(n), *u;
		if (v->data != n) {
			cout << "NO EXISTE :D" << n << endl;
			return;
		}
		deleteNode(v);
	}


	void Print(RBNode *p, int n) {
		if (!p) return;
		Print(p->derecho, n + 1);
		for (int i = 0; i < n; i++) {
			cout << "---";
		}
		cout << p->data;
		if (p->color == 1) cout << "(R)";
		else cout << "(N)";
		cout << endl;
		Print(p->izquierdo, n + 1);
	}
};



int main() {
	RBTree a1;
	a1.Insert(1);
	a1.Insert(8);
	a1.Insert(3);
	a1.Insert(2);
	a1.Insert(7);
	a1.Insert(9);
	a1.Insert(4);
	a1.Insert(5);
	a1.Insert(6);
	a1.Print(a1.root,1);

	cout << endl <<  endl;

	a1.Delete(1);
	a1.Delete(2);
	a1.Print(a1.root,1);

	cout << endl << endl;
	a1.Delete(5);
	a1.Print(a1.root, 1);


	return 0;
}
