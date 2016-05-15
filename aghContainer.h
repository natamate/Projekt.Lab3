// File: aghContainer.h
// Author: Natalia Materek, Aleksander Lisiecki
// v 1.1 12.05.2016
// Plik zawiera deklaracje szablonu klasy bazowej aghContainer

#ifndef AGHCONTAINER_H
#define AGHCONTAINER_H
#include <iostream>
using namespace std;

template <class T>
class aghContainer{
public:
	virtual void append(T const&) = 0;
	virtual ~aghContainer()
	{
	    cout << "wirtualny destruktor" << endl;
	}
	virtual aghContainer<T>& operator<<(T const&){}
	virtual bool insert(int, T const& ) = 0;
	virtual bool replace(int, T const& ) = 0;
	virtual int size(void) const{}
    virtual aghContainer& operator= (aghContainer const& ) {}
    virtual T& at(int) const{}
    virtual bool remove(int) = 0;
    virtual void clear(void){}
    virtual bool isEmpty(void){}
    virtual int indexOf(T const& _value, int _from = 0) const = 0;
    virtual bool contains(T const& _value, int _from = 0) const = 0;
    virtual bool operator==(aghContainer<T> const& right){}
    virtual bool operator!=(aghContainer<T> const& right){}
    virtual T& operator[](int n) const{}
    virtual aghContainer<T>& operator+=(T const& element){}
};

#endif
