#include "pch.h"
#include <iostream>
using namespace std;

class CVIte {
public:
	int m_i;
	int *m_v;

	CVIte(int *v = 0, int i = 0) {
		m_v = v;
		m_i = i;
	}

	CVIte operator=(CVIte x) {
		m_i = x.m_i;
		m_v = x.m_v;
		return *this;
	}

	bool operator!= (CVIte x) {
		return m_i != x.m_i;
	}

	CVIte operator++ (int) {
		m_i=m_i+1;
		return *this;
	}

	int & operator *() {
		return m_v[m_i];
	}

};

class CVRIte {
public:
	int m_i;
	int *m_v;

	CVRIte(int *v = 0, int i = 0) {
		m_v = v;
		m_i = i;
	}

	CVRIte operator=(CVRIte x) {
		m_i = x.m_i;
		m_v = x.m_v;
		return *this;
	}

	bool operator!= (CVRIte x) {
		return m_i != x.m_i;
	}

	CVRIte operator++ (int) {
		m_i = m_i - 1;
		return *this;
	}

	int & operator *() {
		return m_v[m_i];
	}

};

class Vector {
public:
	typedef  CVIte iterator;
	typedef  CVRIte reverse_iterator;
	int m_n;
	int *m_v;
	Vector(int n) {
		m_n = n;
		m_v = new int[n];
	}

	int & operator[](int x) {
		return *(m_v + x);
	}

	iterator begin() {
		return iterator(m_v, 0);
	}

	iterator end() {
		return iterator(m_v, m_n);
	}

	reverse_iterator r_begin() {
		return reverse_iterator(m_v, m_n-1);
	}

	reverse_iterator r_end() {
		return reverse_iterator(m_v, -1);
	}
};


int main()
{
	Vector x(5);
	x[0] = 2;
	x[1] = 3;
	x[2] = 4;
	x[3] = 5;
	x[4] = 6;


	Vector::iterator i;
	for (i = x.begin(); i != x.end(); i++ ) {
		cout << *i << " ";
	}

	cout << endl;

	Vector::reverse_iterator e;
	for (e = x.r_begin(); e != x.r_end(); e++) {
		cout << *e << " ";
	}
}
