#include "pch.h"
#include <iostream>
#include <vector>

using namespace std;

template <class T>
class AVLNode {
public:
	T data;
	int altura;
	AVLNode *izquierdo, *derecho, *padre;

	AVLNode(T k, AVLNode *p) : data(k), altura(0), padre(p),
		izquierdo(NULL), derecho(NULL) {}

	~AVLNode() {
		delete izquierdo;
		delete derecho;
	}
};

template <class T>
class AVLTree {
public:
	AVLTree(void);
	~AVLTree(void);
	bool Insert(T data);
	void Delete(const T data);
	void printBalance();
	T maximo(T a, T b) {
		if (a > b) return a;
		else return b;
	}

	AVLNode<T> *root;

	AVLNode<T>* rotarIzquierda(AVLNode<T> *a);
	AVLNode<T>* rotarDerecha(AVLNode<T> *a);
	AVLNode<T>* rotarIzDer(AVLNode<T> *n);
	AVLNode<T>* rotarDerIz(AVLNode<T> *n);
	void rebalance(AVLNode<T> *n);
	int altura(AVLNode<T> *n);
	void Balancear(AVLNode<T> *n);
	void Print(AVLNode<T> *p, T n);
	void printBonito();
};

template <class T>
void AVLTree<T>::rebalance(AVLNode<T> *n) {
	Balancear(n);

	if (n->altura == -2) {
		if (altura(n->izquierdo->izquierdo) >= altura(n->izquierdo->derecho))
			n = rotarDerecha(n);
		else
			n = rotarIzDer(n);
	}
	else if (n->altura == 2) {
		if (altura(n->derecho->derecho) >= altura(n->derecho->izquierdo))
			n = rotarIzquierda(n);
		else
			n = rotarDerIz(n);
	}

	if (n->padre != NULL) {
		rebalance(n->padre);
	}
	else {
		root = n;
	}
}

template <class T>
AVLNode<T>* AVLTree<T>::rotarIzquierda(AVLNode<T> *a) {
	AVLNode<T> *b = a->derecho;
	b->padre = a->padre;
	a->derecho = b->izquierdo;

	if (a->derecho != NULL)
		a->derecho->padre = a;

	b->izquierdo = a;
	a->padre = b;

	if (b->padre != NULL) {
		if (b->padre->derecho == a) {
			b->padre->derecho = b;
		}
		else {
			b->padre->izquierdo = b;
		}
	}

	Balancear(a);
	Balancear(b);
	return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotarDerecha(AVLNode<T> *a) {
	AVLNode<T> *b = a->izquierdo;
	b->padre = a->padre;
	a->izquierdo = b->derecho;

	if (a->izquierdo != NULL)
		a->izquierdo->padre = a;

	b->derecho = a;
	a->padre = b;

	if (b->padre != NULL) {
		if (b->padre->derecho == a) {
			b->padre->derecho = b;
		}
		else {
			b->padre->izquierdo = b;
		}
	}

	Balancear(a);
	Balancear(b);
	return b;
}

template <class T>
AVLNode<T>* AVLTree<T>::rotarIzDer(AVLNode<T> *n) {
	n->izquierdo = rotarIzquierda(n->izquierdo);
	return rotarDerecha(n);
}

template <class T>
AVLNode<T>* AVLTree<T>::rotarDerIz(AVLNode<T> *n) {
	n->derecho = rotarDerecha(n->derecho);
	return rotarIzquierda(n);
}

template <class T>
int AVLTree<T>::altura(AVLNode<T> *n) {
	if (n == NULL)
		return -1;
	return 1 + maximo(altura(n->izquierdo), altura(n->derecho));
}

template <class T>
void AVLTree<T>::Balancear(AVLNode<T> *n) {
	n->altura = altura(n->derecho) - altura(n->izquierdo);
}


template <class T>
AVLTree<T>::AVLTree(void) : root(NULL) {}

template <class T>
AVLTree<T>::~AVLTree(void) {
	delete root;
}

template <class T>
bool AVLTree<T>::Insert(T data) {
	if (root == NULL) {
		root = new AVLNode<T>(data, NULL);
	}
	else {
		AVLNode<T>
			*n = root,
			*padre;

		while (true) {
			if (n->data == data)
				return false;

			padre = n;

			bool goLeft = n->data > data;
			n = goLeft ? n->izquierdo : n->derecho;

			if (n == NULL) {
				if (goLeft) {
					padre->izquierdo = new AVLNode<T>(data, padre);
				}
				else {
					padre->derecho = new AVLNode<T>(data, padre);
				}

				rebalance(padre);
				break;
			}
		}
	}

	return true;
}

template <class T>
void AVLTree<T>::Delete(const T delKey) {
	if (root == NULL)
		return;

	AVLNode<T>
		*n = root,
		*padre = root,
		*delNode = NULL,
		*child = root;

	while (child != NULL) {
		padre = n;
		n = child;
		child = delKey >= n->data ? n->derecho : n->izquierdo;
		if (delKey == n->data)
			delNode = n;
	}

	if (delNode != NULL) {
		delNode->data = n->data;

		child = n->izquierdo != NULL ? n->izquierdo : n->derecho;

		if (root->data == delKey) {
			root = child;
		}
		else {
			if (padre->izquierdo == n) {
				padre->izquierdo = child;
			}
			else {
				padre->derecho = child;
			}

			rebalance(padre);
		}
	}
}

template <class T>
void AVLTree<T>::printBalance() {
	printBalance(root);
	cout << endl;
}

template<class T>
void AVLTree<T>::Print(AVLNode<T> *p, T n) {
	if (!p) return;
	Print(p->derecho, n + 1);
	for (int i = 0; i < n; i++) {
		cout << "---";
	}
	cout << p->data << endl;
	Print(p->izquierdo, n + 1);
}

template <class T>
void AVLTree <T>:: printBonito() {
	vector <AVLNode<T>* > c;
	c.push_back(root);
	int len;
	while (c.size() != 0) {
		len = c.size();
		for (int i = 0; i < len; i++) {
			if (c[i]) {
				cout << " " << c[i]->data << " ";
				c.push_back(c[i]->izquierdo);
				c.push_back(c[i]->derecho);
			}
			else
				cout << "-";

		}
		cout << endl;
		c.erase(c.begin(), c.begin() + len);
	}
}

int main(void)
{
	AVLTree<int> t;

	t.Insert(1);
	t.Insert(8);
	t.Insert(3);
	t.Insert(2);
	t.Insert(7);
	t.Insert(9);
	t.Insert(4);
	t.Insert(5);
	t.Insert(6);

	t.Print(t.root, 0);

	cout << endl << endl;
	t.Delete(1);
	t.Delete(2);
	t.Delete(3);
	t.Delete(7);

	t.Print(t.root, 0);

	//cout << endl << endl;

	//t.Delete(2);

	//t.Print(t.root, 0);

}

