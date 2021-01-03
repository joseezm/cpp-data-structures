#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template<class T>
class CNode
{
public:
	T m_data;
	CNode <T> * m_next, *m_prev;

	CNode(T x)
	{
		m_data = x;
		m_next = 0;
		m_prev = 0;
	}

};

template <class T, class C>
class CList
{
public:
	CNode<T> *m_head;
	CNode<T> *m_end;
	C cmp;
	bool flag = true;
	CList() { m_head = 0; }
	bool Find(T x, CNode <T> ** & p);
	bool Insert(T x);
	bool Remove(T x);
	void Print();
};

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
	Find(x, p);
	CNode <T> *n = new CNode <T>(x);

	if (flag) {
		n->m_prev = 0;
		m_end = n;
		flag = false;
	}
	else if (*p == NULL) {
		n->m_prev = m_end;
		m_end = n;
	}
	else {
		n->m_prev = (*p)->m_prev;
		(*p)->m_prev = n;
	}
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
	if(t!=m_end)
		t->m_next->m_prev = t->m_prev;
	else if (m_head == 0) cout << endl << "vacio" << endl;
	else m_end = t->m_prev;
	delete t;

	return 1;
}

template<class T, class C>
void CList <T, C> ::Print()
{
	CNode<T> **p;
	cout << endl;
	for (p = &m_head; *p; p = &((*p)->m_next))
		cout << "MEMORIA: " << *p << "		DATO: " <<  (*p)->m_data << "		NEXT: " << (*p)->m_next << "		PREV: " << (*p)->m_prev << endl ;
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
	srand(time(NULL));
	CList <int, fAsc> lista1;
	int i = 0;
	/*while (i < 25) {
		lista1.Insert(rand()%100);
		i++;
	}*/
	lista1.Insert(1);
	lista1.Insert(2);
	lista1.Insert(3);
	lista1.Insert(4);
	lista1.Insert(5);
	lista1.Print();
	lista1.Remove(3);
	lista1.Print();
	lista1.Remove(1);
	lista1.Remove(5);
	lista1.Print();
	lista1.Remove(2);
	lista1.Remove(4);
	lista1.Print();

	return 0;
}
