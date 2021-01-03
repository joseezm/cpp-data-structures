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

    CNode (T x)
    {
        m_data=x;
        m_next=0;
    }

};

template <class T, class C>
class CList
{
    public:
    CNode<T> *m_head;
    C cmp;
    CList() {m_head = 0;}
    bool Find(T x, CNode <T> ** & p);
    bool Insert(T x);
    bool Remove (T x);
    void Print();
};

template <class T,class C>
bool CList<T,C> :: Find (T x,CNode <T> ** &p)
{
    for (p=&m_head; *p && cmp((*p)->m_data, x); p=&((*p)->m_next));
    return *p && (*p)->m_data==x;

}

template <class T, class C>
bool CList<T,C> :: Insert(T x)
{
    CNode <T> **p;
    if (Find(x,p)) return 0;
    CNode <T> *n = new CNode <T>(x);
    n->m_next = *p;
    *p = n;
    return 1;
}

template<class T, class C>
bool CList <T,C> :: Remove (T x)
{
    CNode <T> **p;
    if(!Find(x,p)) return 0;
    CNode <T> *t = *p;
    *p=t->m_next;
    delete t;
    return 1;
}

template<class T, class C>
void CList <T,C> :: Print ()
{
    CNode<T> **p;
    for (p=&m_head; *p ; p=&((*p)->m_next))
    cout <<  (*p)->m_data << " -> " ;
}

/*************************************/

class fAsc{
  public:
  inline bool operator()(int a, int b){return a<b;}
};

class fDesc{
  public:
  inline bool operator()(int a, int b){return a>b;}
};

int main()
{
    srand(time(NULL));
    CList <int,fAsc> lista1;
    int i=0;
    while(i<25){
    lista1.Insert(i);
    i++;
    }
    lista1.Print();
    return 0;
}
