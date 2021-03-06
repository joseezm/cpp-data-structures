#include "pch.h"
#include <iostream>
using namespace std;

class CNode {
public:
	int data;
	CNode * hijo[2];
	CNode(int x) {
		data = x;
		hijo[0] = hijo[1] = 0;
	}
};

class BTree {
public:
	CNode *raiz;
	BTree() { raiz = 0; }
	bool Find(int x, CNode ** &p);
	bool Insert(int x);
	bool Delete(int x);
	void Print(CNode *p, int n);
	CNode ** Rep(CNode **p);
};

bool BTree::Find(int x, CNode ** &p) {
	p = &raiz;
	while (*p && (*p)->data != x) {
		p = &(*p)->hijo[(*p)->data < x];
	}
	return (*p) != 0;
}

bool BTree::Insert(int x) {
	CNode **p;
	if (Find(x, p)) return 0;
	*p = new CNode(x);
	return 1;
}

CNode** BTree::Rep(CNode**p) {
	p = &(*p)->hijo[0];
	for (p; (*p)->hijo[1]; p = &(*p)->hijo[1])
		return p;
}

bool BTree::Delete(int x) {
	CNode **p;
	if (!Find(x, p)) { return 0; }
	if ((*p)->hijo[0] && (*p)->hijo[1]) {
		CNode **q = Rep(p);
		(*p)->data = (*q)->data;
		p = q;
	}
	CNode *t = *p;
	*p = (*p)->hijo[(*p)->hijo[0] == 0];
	delete t;
	return 1;
}

void BTree::Print(CNode *p, int n) {
	if (!p) return;
	Print(p->hijo[1], n + 1);
	for (int i = 0; i < n; i++) {
		cout << "---";
	}
	cout << p->data << endl;
	Print(p->hijo[0], n + 1);
}




int main()
{
	BTree arbol1;
	arbol1.Insert(1);
	arbol1.Insert(8);
	arbol1.Insert(3);
	arbol1.Insert(7);
	arbol1.Insert(2);
	arbol1.Insert(9);
	//arbol1.Insert(-3);

	arbol1.Print(arbol1.raiz, 0);
	arbol1.Delete(1);
	arbol1.Print(arbol1.raiz, 0);
	cout << arbol1.raiz->data << endl;
}

