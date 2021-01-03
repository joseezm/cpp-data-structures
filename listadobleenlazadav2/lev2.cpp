#include <iostream>

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
    CNode <T> * m_head;
    bool Find(T x, CNode <T> ** & p);
    bool Insert(T x);
    bool Remove (T x);
};

template <class T, class C>
bool CList<T,C> :: Find (T x, CNode <T> ** &p)
{
    for (p=&m_head; *p && (*p)->m_data < x; p=&((*p)->m_next));
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

/*************************************/

class fAsc{
  public:
  inline bool operator()(int a, int b){return a>b;}
};

class fDesc{
  public:
  inline bool operator()(int a, int b){return a<b;}
};

int main()
{
    CList <int,fAsc> lista1();
    lista1.Insert(4);
    return 0;
}
