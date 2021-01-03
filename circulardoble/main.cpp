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
    CNode <T> * m_prev;

    CNode (T x)
    {
        m_data=x;
        m_next=0;
        m_prev=0;
    }

};

template <class T, class C>
class CList
{
    public:
    CNode<T> *m_head;
    CNode<T> *m_end;
    C cmp;
    bool flag=true;
    CList() {m_head = 0;}
    bool Find(T x, CNode <T> ** & p);
    bool Insert(T x);
    bool Remove (T x);
    bool Print();
};

template <class T,class C>
bool CList<T,C> :: Find (T x,CNode <T> ** &p)
{
    p=&m_head;

    while ( *p  && cmp((*p)->m_data, x) ){
        p=&((*p)->m_next);
        if (*p== m_head) break;
    }
    return *p && (*p)->m_data==x;

}

template <class T, class C>
bool CList<T,C> :: Insert(T x)
{
    CNode <T> **p;
    Find(x,p);
    CNode <T> *n = new CNode <T>(x);

    if (!flag){
        n->m_next = *p;
        n->m_prev = (*p)->m_prev;
        n->m_next->m_prev = n;
        *p = n;
        if (p == &m_head){
            m_end->m_next = n;
            n->m_prev = m_end;
        }
        else if (!cmp(x,m_end->m_data) && m_end->m_data != x) m_end=n;
    }
    else{
        n->m_next = n;
        n->m_prev = n;
        *p = n;
        m_end = n;
        flag=false;
    }

    m_head->m_prev = m_end;

    return 1;
}

template<class T, class C>
bool CList <T,C> :: Remove (T x)
{
    CNode <T> **p;
    if(!Find(x,p)) return 0;
    CNode <T> *t = *p;
    if (*p==m_head) {
        m_head = t->m_next;
        m_end->m_next = m_head;
    }
    else if (*p==m_end) {
        CNode<T> **p;
        p=&m_head;
        while ((*p)->m_next != m_end){
            p=&((*p)->m_next);
        }
        m_end = *p;
    }
    if (m_head == m_end && x==m_head->m_data) t->m_next = 0;

    if(t!=m_end)
		t->m_next->m_prev = t->m_prev;
	else m_end = t->m_prev;

    m_head->m_prev=m_end;
    *p=t->m_next;
    delete t;
    return 1;
}

template<class T, class C>
bool CList <T,C> :: Print ()
{
    CNode<T> **p;
    p=&m_head;
    while (*p){
        cout << "Memoria: " << int (*p) << "    Valor: "  <<(*p)->m_data << "   Next: " <<  int((*p)->m_next) << "   Prev: " <<  int((*p)->m_prev) << endl;
        p=&((*p)->m_next);
        if(*p==m_head) return 1;


    }
    if (!*p) cout << "vacio" << endl;
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
    /*while(i<200){
    lista1.Insert(1+rand()%1000);
    i++;
    }*/
    lista1.Insert(1);
    lista1.Insert(2);
    lista1.Insert(3);
    lista1.Insert(4);
    lista1.Insert(5);
    lista1.Print();
    cout << endl;
    lista1.Remove(3);
    lista1.Print();
    cout << endl;
    lista1.Remove(1);
    lista1.Print();
    cout << endl;
    lista1.Remove(5);
    lista1.Print();
    cout << endl;
    lista1.Remove(2);
    lista1.Remove(4);
    lista1.Print();
    cout <<  endl;


    return 0;
}
