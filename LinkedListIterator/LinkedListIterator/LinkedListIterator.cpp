#include "pch.h"
#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;


template<class T>
class CNode
{
public:
	T m_data;
	CNode <T> * m_next;

	CNode(T x)
	{
		m_data = x;
		m_next = 0;
	}

};

template<class T>
class CLIte {
public:
	CNode<T> * m_v;
	CLIte(CNode<T> *v = 0) {
		m_v = v;
	}

	CLIte operator=(CLIte x) {
		m_v = x.m_v;
		return *this;
	}

	bool operator!=(CLIte x) {
		return m_v != x.m_v;
	}

	CLIte operator++() {
		m_v = m_v->m_next;
		return *this;
	}

	T operator*() {
		return m_v->m_data;
	}
};



template <class T, class C>
class CList
{
public:
	typedef CLIte <T> iterator;
	CNode<T> *m_head;
	C cmp;
	CList() { m_head = 0; }
	bool Find(T x, CNode <T> ** & p);
	bool Insert(T x);
	bool Remove(T x);
	void Print();
	CNode <T> * b_end();

	iterator begin() {
		return iterator(m_head);
	}
	iterator end() {
		return iterator(b_end());
	}
};

template <class T, class C>
CNode<T> * CList<T, C> ::b_end() {
	CNode <T> *i;
	for (i = m_head; i; i = i->m_next);
	return i;
}

template <class T, class C>
bool CList<T, C> ::Find(T x, CNode <T> ** &p)
{
	for (p = &m_head; *p && cmp((*p)->m_data, x); p = &((*p)->m_next));
	return *p && (*p)->m_data == x;

}

template <class T, class C>
bool CList<T, C> ::Insert(T x)
{
	CNode <T> **p;
	if (Find(x, p)) return 0;
	CNode <T> *n = new CNode <T>(x);
	n->m_next = *p;
	*p = n;
	return 1;
}

template<class T, class C>
bool CList <T, C> ::Remove(T x)
{
	CNode <T> **p;
	if (!Find(x, p)) return 0;
	CNode <T> *t = *p;
	*p = t->m_next;
	delete t;
	return 1;
}

template<class T, class C>
void CList <T, C> ::Print()
{
	CNode<T> **p;
	for (p = &m_head; *p; p = &((*p)->m_next))
		cout << (*p)->m_data << " -> ";
}

/*************************************/

class fAsc {
public:
	inline bool operator()(int a, int b) { return a < b; }
};

class fDesc {
public:
	inline bool operator()(int a, int b) { return a > b; }
};

int main()
{
	CList <int, fAsc > lista1;
	lista1.Insert(5);
	lista1.Insert(13);
	lista1.Insert(2);
	lista1.Insert(29);
	lista1.Insert(8);
	CList<int, fAsc>::iterator i;

	for (i = lista1.begin(); i != lista1.end(); i.m_v=i.m_v->m_next) {
		cout << *i << " ";
	}


	//lista1.Print();
	return 0;
}
