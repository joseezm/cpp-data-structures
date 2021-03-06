#include "pch.h"
#include <iostream>
#include <stack>
#include <utility>
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

class CLIteIn {
public:
	stack<pair< CNode*,int> > pila;
	CNode *p_arbol;
	CLIteIn(CNode *v = 0) {
		pair<CNode*, int> par;
		if (!!v) {
			par.first = v;
			par.second = 0;
			pila.push(par);
			while (v->hijo[0]) {
				par.first = v->hijo[0];
				par.second = 0;
				pila.push(par);
				v = v->hijo[0];
			}
			par = pila.top();
			par.second = 2;
			pila.pop();
			pila.push(par);
		}
		p_arbol = par.first;
	}

	CLIteIn operator=(CLIteIn x) {
		stack<pair<CNode*, int>> aux;
		while (!x.pila.empty()) {
			aux.push(x.pila.top());
			x.pila.pop();
		}
		while (!aux.empty()) {
			pila.push(aux.top());
			aux.pop();
		}
		p_arbol = x.p_arbol;
		return *this;
	}

	bool operator!=(CLIteIn x) {
		if (x.pila.size() != pila.size()) return true;
		if (x.pila.empty() && pila.empty()) {
			return false;
		}
		stack<pair<CNode*, int>> aux1 = pila;
		stack<pair<CNode*, int>> aux2 = x.pila;
		while (!aux1.empty()) {
			pair<CNode*, int> par = aux1.top();
			pair<CNode*, int> xpar = aux2.top();
			if ((par.first != xpar.first))
				return true;
			else {
				aux1.pop(); aux2.pop();
			}
		}
		return false;
	}

	CLIteIn operator++(int a) {
		pair<CNode*, int> par;
		par = pila.top();
		while (pila.size() >= 1 && par.second != 1) {
			CNode * nex = par.first;
			switch (par.second) {
			case 0:
				if (nex->hijo[0]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[0];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 2:
				if (nex->hijo[1]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[1];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 3:
				pila.pop();
				if (!pila.empty()) {
					par = pila.top();
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			default:
				break;
			}
			if (!pila.empty())
				par = pila.top();
			else {
				par.first = nullptr;
				par.second = 1;
			}
		}
		if (!pila.empty() && par.second < 3) {
			p_arbol = par.first;
			par.second++;
			pila.pop();
			pila.push(par);
		}
		else if (!pila.empty())
			pila.pop();
		return *this;
		return *this;
	}

	int operator*() {
		return p_arbol->data;
	}
};

class CItePos {
public:
	stack<pair<CNode*, int>> pila;
	CNode *p_arbol;
	CItePos(CNode * v = nullptr) {
		pair<CNode*, int> par;
		if (!!v) {
			par.first = v;
			par.second = 0;
			pila.push(par);
			while (v->hijo[0]) {
				par.first = v->hijo[0];
				par.second = 0;
				pila.push(par);
				v = v->hijo[0];
			}
			par = pila.top();
			par.second = 3;
			pila.pop();
			pila.push(par);
		}
		p_arbol = par.first;
	}
	CItePos operator=(CItePos m) {
		stack<pair<CNode*, int>> aux;
		while (!m.pila.empty()) {
			aux.push(m.pila.top());
			m.pila.pop();
		}
		while (!aux.empty()) {
			pila.push(aux.top());
			aux.pop();
		}
		p_arbol = m.p_arbol;
		return *this;
	}
	bool operator!=(CItePos j) {
		if (j.pila.size() != pila.size()) return true;
		if (j.pila.empty() && pila.empty()) {
			return false;
		}
		stack<pair<CNode*, int>> aux1 = pila;
		stack<pair<CNode*, int>> aux2 = j.pila;
		while (!aux1.empty()) {
			pair<CNode*, int> par = aux1.top();
			pair<CNode*, int> jpar = aux2.top();
			if ((par.first != jpar.first))
				return true;
			else {
				aux1.pop(); aux2.pop();
			}
		}
		return false;
	}
	CItePos operator++(int a) {
		pair<CNode*, int> par;
		par = pila.top();
		while (pila.size() >= 1 && par.second != 2) {
			CNode * nex = par.first;
			switch (par.second) {
			case 0:
				if (nex->hijo[0]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[0];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 1:
				if (nex->hijo[1]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[1];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 3:
				pila.pop();
				if (!pila.empty()) {
					par = pila.top();
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			default:
				break;
			}
			if (!pila.empty())
				par = pila.top();
			else {
				par.first = nullptr;
				par.second = 0;
			}
		}
		if (!pila.empty() && par.second < 3) {
			p_arbol = par.first;
			par.second++;
			pila.pop();
			pila.push(par);
		}
		else if (!pila.empty())
			pila.pop();
		return *this;
	}

	int & operator*() {
		return p_arbol->data;
	}
};

class CItePre {
public:
	stack<pair<CNode*, int>> pila;
	CNode *p_arbol;
	CItePre(CNode * m_r = nullptr) {
		pair<CNode*, int> par;
		if (!!m_r) {
			par.first = m_r;
			par.second = 1;
			pila.push(par);
		}
		p_arbol = par.first;
	}
	CItePre operator=(CItePre m) {
		stack<pair<CNode*, int>> aux;
		while (!m.pila.empty()) {
			aux.push(m.pila.top());
			m.pila.pop();
		}
		while (!aux.empty()) {
			pila.push(aux.top());
			aux.pop();
		}
		p_arbol = m.p_arbol;
		return *this;
	}
	bool operator!=(CItePre j) {
		if (j.pila.size() != pila.size()) return true;
		if (j.pila.empty() && pila.empty()) {
			return false;
		}
		stack<pair<CNode*, int>> aux1 = pila;
		stack<pair<CNode*, int>> aux2 = j.pila;
		while (!aux1.empty()) {
			pair<CNode*, int> par = aux1.top();
			pair<CNode*, int> m_jpair = aux2.top();
			if ((par.first != m_jpair.first))
				return true;
			else {
				aux1.pop(); aux2.pop();
			}
		}
		return false;
	}
	CItePre operator++(int a) {
		pair<CNode*, int> par;
		par = pila.top();
		while (pila.size() >= 1 && par.second != 0) {
			CNode * nex = par.first;
			switch (par.second) {
			case 1:
				if (nex->hijo[0]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[0];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 2:
				if (nex->hijo[1]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[1];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 3:
				pila.pop();
				if (!pila.empty()) {
					par = pila.top();
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			default:
				break;
			}
			if (!pila.empty())
				par = pila.top();
			else {
				par.first = nullptr;
				par.second = 0;
			}
		}
		if (!pila.empty() && par.second < 3) {
			p_arbol = par.first;
			par.second++;
			pila.pop();
			pila.push(par);
		}
		else if (!pila.empty())
			pila.pop();
		return *this;
	}

	int & operator*() {
		return p_arbol->data;
	}
};


class CIteRev {
public:
	stack<pair<CNode*, int>> pila;
	CNode *p_arbol;
	CIteRev(CNode * m_r = nullptr) {
		pair<CNode*, int> par;
		if (!!m_r) {
			par.first = m_r;
			par.second = 0;
			pila.push(par);
			while (m_r->hijo[1]) {
				par.first = m_r->hijo[1];
				par.second = 0;
				pila.push(par);
				m_r = m_r->hijo[1];
			}
			par = pila.top();
			par.second = 2;
			pila.pop();
			pila.push(par);
		}
		p_arbol = par.first;
	}
	CIteRev operator=(CIteRev m) {
		stack<pair<CNode*, int>> aux;
		while (!m.pila.empty()) {
			aux.push(m.pila.top());
			m.pila.pop();
		}
		while (!aux.empty()) {
			pila.push(aux.top());
			aux.pop();
		}
		p_arbol = m.p_arbol;
		return *this;
	}
	bool operator!=(CIteRev j) {
		if (j.pila.size() != pila.size()) return true;
		if (j.pila.empty() && pila.empty()) {
			return false;
		}
		stack<pair<CNode*, int>> aux1 = pila;
		stack<pair<CNode*, int>> aux2 = j.pila;
		while (!aux1.empty()) {
			pair<CNode*, int> par = aux1.top();
			pair<CNode*, int> m_jpair = aux2.top();
			if ((par.first != m_jpair.first))
				return true;
			else {
				aux1.pop(); aux2.pop();
			}
		}
		return false;
	}
	CIteRev operator++(int a) {
		pair<CNode*, int> par;
		par = pila.top();
		while (pila.size() >= 1 && par.second != 1) {
			CNode * nex = par.first;
			switch (par.second) {
			case 0:
				if (nex->hijo[1]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[1];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 2:
				if (nex->hijo[0]) {
					pair<CNode*, int> aux;
					aux.first = nex->hijo[0];
					aux.second = 0;
					pila.push(aux);
				}
				else {
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			case 3:
				pila.pop();
				if (!pila.empty()) {
					par = pila.top();
					par.second++;
					pila.pop();
					pila.push(par);
				}
				break;
			default:
				break;
			}
			if (!pila.empty())
				par = pila.top();
			else {
				par.first = nullptr;
				par.second = 1;
			}
		}
		if (!pila.empty() && par.second < 3) {
			p_arbol = par.first;
			par.second++;
			pila.pop();
			pila.push(par);
		}
		else if (!pila.empty())
			pila.pop();
		return *this;
	}

	int & operator*() {
		return p_arbol->data;
	}
};


class BTree {
public:
	typedef CLIteIn iteratorInOrder;
	typedef CItePos iteratorPosOrder;
	typedef CItePre iteratorPreOrder;
	typedef CIteRev iteratorReverse;

	CNode *raiz;
	BTree() { raiz = 0; }
	bool Find(int x, CNode ** &p);
	bool Insert(int x);
	bool Delete(int x);
	void Print(CNode *p, int n);
	CNode ** Rep(CNode **p);

	iteratorInOrder beginInOrder() {
		return iteratorInOrder(raiz);
	}
	iteratorInOrder endInOrder() {
		return iteratorInOrder(nullptr);
	}

	iteratorPosOrder beginPosOrder() {
		return iteratorPosOrder(raiz);
	}
	iteratorPosOrder endPosOrder() {
		return iteratorPosOrder(nullptr);
	}

	iteratorPreOrder beginPreOrder() {
		return iteratorPreOrder(raiz);
	}
	iteratorPreOrder endPreOrder() {
		return iteratorPreOrder(nullptr);
	}

	iteratorReverse beginReverse() {
		return iteratorReverse(raiz);
	}
	iteratorReverse endReverse() {
		return iteratorReverse(nullptr);
	}

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
	arbol1.Insert(4);
	arbol1.Insert(5);
	arbol1.Insert(6);
	arbol1.Print(arbol1.raiz, 0);
	cout << endl;

	cout<< "InOrder:  ";
	BTree::iteratorInOrder i;
	for (i = arbol1.beginInOrder(); i != arbol1.endInOrder(); i++) {
		cout << *i << " ";
	}

	cout << endl << "PreOrder:  ";

	BTree::iteratorPreOrder e;
	for (e = arbol1.beginPreOrder(); e != arbol1.endPreOrder(); e++) {
		cout << *e << " ";
	}

	cout << endl << "PosOrder:  ";

	BTree::iteratorPosOrder p;
	for (p = arbol1.beginPosOrder(); p != arbol1.endPosOrder(); p++) {
		cout << *p << " ";
	}

	cout << endl << "Reverse:  ";

	BTree::iteratorReverse r;
	for (r = arbol1.beginReverse(); r != arbol1.endReverse(); r++) {
		cout << *r << " ";
	}

	cout << endl;


}

