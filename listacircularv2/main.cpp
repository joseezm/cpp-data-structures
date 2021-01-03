#include <iostream>
#include <stdlib.h>
#include <time.h>

using namespace std;

template<class T>
class CircularNode
{
    public:
    T m_data;
    CircularNode <T> * m_next;

    CircularNode (T x)
    {
        m_data=x;
        m_next=0;
    }

};

template <class T>
class CircularList
{
    public:
    CircularNode<T> *m_head;
    CircularNode<T> *m_end;
    bool flag=true;
    CircularList() {m_head = 0;}
    bool Find(T x, CircularNode <T> ** & p);
    bool Insert(T x);
    bool Remove (T x);
    bool Print();
};

template <class T>
bool CircularList<T> :: Find (T x,CircularNode <T> ** &p)
{
    p=&m_head;

    while ( *p  && cmp((*p)->m_data, x) ){
        p=&((*p)->m_next);
        if (*p== m_head) break;
    }
    return *p && (*p)->m_data==x;

}

template <class T>
bool CircularList<T> :: Insert(T x)
{
    CircularNode <T> **p;
    Find(x,p);
    CircularNode <T> *n = new CircularNode <T>(x);
    if (!flag){
        n->m_next = *p;
        *p = n;
        if (p == &m_head) m_end->m_next = n;
        else if (!cmp(x,m_end->m_data) && m_end->m_data != x) m_end=n;
    }
    else{
        n->m_next = n;
        *p = n;
        m_end = n;
        flag=false;
    }


    return 1;
}

template<class T>
bool CircularList <T> :: Remove (T x)
{
    CircularNode <T> **p;
    if(!Find(x,p)) return 0;
    CircularNode <T> *t = *p;
    if (*p==m_head) {
        m_head = t->m_next;
        m_end->m_next = m_head;
    }
    else if (*p==m_end) {
        CircularNode<T> **p;
        p=&m_head;
        while ((*p)->m_next != m_end){
            p=&((*p)->m_next);
        }
        m_end = *p;
    }
    if (m_head == m_end && x==m_head->m_data) t->m_next = 0;

    *p=t->m_next;
    delete t;
    return 1;
}

template<class T>
bool CircularList <T> :: Print ()
{
    CircularNode<T> **p;
    p=&m_head;
    while (*p){
        cout << "Memoria: " << int (*p) << "    Valor: "  <<(*p)->m_data << "   Next: " <<  int((*p)->m_next) << endl;
        p=&((*p)->m_next);
        if(*p==m_head) return 1;

    }
    if (!*p) cout << "vacio" << endl;
}


int main()
{
    srand(time(NULL));
    CircularList <int> lista1;
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
    lista1.Remove(5);
    lista1.Print();
    cout << endl;
    lista1.Remove(2);
    lista1.Print();
    cout << endl;
    lista1.Remove(4);
    lista1.Print();


    return 0;
}
