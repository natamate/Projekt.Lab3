// File: aghInclude.h
// Author: Natalia Materek, Aleksander Lisiecki
// v 2.1 15.05.2016
// Plik zawiera deklaracje szablonu klasy aghVector
// wraz z implementacja metod klasy

#ifndef AGHINCLUDE_H
#define AGHINCLUDE_H
#include "aghException.h"
#include "aghContainer.h"
#include <iostream>
using namespace std;

template <class T>
class aghVector:public aghContainer<T>{
public:
	T *tab;
	int rozmiar;
    int OstWolny; //to zmienna przechowujaca indeks miejsca gdzie moze zostac wstawiony kolejny element, wykorzystywana m. in w metodzie append

	aghVector() //ten konstruktor przyjmuje wartosc 1 zeby pominac resize przy dodawaniu pierwszego elementu
	{
		rozmiar = 1;
		tab = new T [rozmiar];
		OstWolny = 0;
	}

	aghVector(int _rozmiar)
	{
		if (_rozmiar >= 0)
		{
			rozmiar = _rozmiar;
			tab = new T [rozmiar];
			OstWolny = 0;
		}
		else
        {
            throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
	}

	aghVector<T>& operator= (aghVector<T> const & w)
	{
	    if (this == &w)
		{
		    return *this;
		}
        else
        {
            if (tab!=NULL)
            {
                 delete [] tab;
            }
            rozmiar = w.rozmiar;
            OstWolny = w.OstWolny;
            tab = new T [rozmiar];
            przepisywanieTab(w.tab, tab, rozmiar);
            return *this;
        }
    }

	aghVector<T> (const aghVector<T>& kopia)
    {
        this -> rozmiar = kopia.rozmiar;
        this -> OstWolny = kopia.OstWolny;
        delete [] tab;
        tab = new T [rozmiar];
        przepisywanieTab(kopia.tab, tab, rozmiar);
    }

    aghVector<T> (const aghContainer<T> &ToCopy)
    {
        rozmiar = ToCopy.size();
		OstWolny = 0;
		tab = new T [rozmiar];
        for(int i = 0; i < rozmiar; ++i)
        {
            this->append(ToCopy.at(i));
        }
    }

    void clear()
    {
        delete [] tab;
        rozmiar = 0;
        OstWolny = 0;
    }

	~aghVector()
	{
        clear();
	}

    //funkcja przepisuje zawartosc tablicy source do tablicy destination
    void przepisywanieTab(T* source, T* destination, int lEl)
    {
         for (int i = 0; i < lEl; i++)
         {
                destination[i] = source[i];
         }
    }

	void resize(int tmpSize)
	{
	    if (tmpSize >= 0)
        {
            aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
            przepisywanieTab(tab, tmpTab -> tab, rozmiar);
            int tmpWolny = OstWolny;
            clear();
            OstWolny = tmpWolny;
            rozmiar = tmpSize;
            tab = new T [rozmiar];
            przepisywanieTab(tmpTab -> tab, tab, rozmiar);
        }
        else
        {
            throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
	}

    virtual bool insert(int place, T const& element)
    {
        if ((place >= 0) && (place <= rozmiar))
        {
            aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
            przepisywanieTab(tab, tmpTab -> tab, rozmiar);
            rozmiar++;
            resize(rozmiar);
            for (int i = rozmiar; i > place; i--)
            {
                tab[i] = tab [i-1];
            }
            tab[place] = element;
            return true;
        }
        else
        {
            return false;
        }
    }

    bool replace(int place, T const& element)
    {
        if ((place >= 0) && (place <= rozmiar))
        {
            tab[place] = element;
            return true;
        }
        else
        {
            return false;
        }
    }

	aghContainer<T>& operator+=(T const& element)
	{
		append(element);
		return *this;
	}

	void append(T const& dodawanyElement)
	{
	    if (OstWolny < rozmiar)
        {
            tab[OstWolny] = dodawanyElement;
            OstWolny++;
        }
        else
        {
            resize(++rozmiar);
            tab[OstWolny] = dodawanyElement;
            OstWolny++;
        }
	}

	int size() const
	{
		return rozmiar;
	}

    friend ostream& operator << (ostream & os, aghVector & wektor)
    {
        for (int i=0; i<wektor.rozmiar; i++)
            os << wektor.tab[i] << ", ";
        os << endl;
        return os;
    }

    aghVector<T>& operator<<(T const& element)
    {
        append(element);
        return *this;
    }

    aghVector<T>& operator<<(aghVector<T> const& right)
    {
        for (int i = 0; i < right.rozmiar; i++)
        {
            append(right.tab[i]);
        }
        return *this;
    }

    T& at(int place) const
    {
        if ((place >= 0) && (place < rozmiar))
        {
            return tab[place];
        }
        else
        {
			throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
    }

    bool remove(int place)
    {
         if ((place >= 0) && (place < rozmiar))
         {
            rozmiar--;
            for (int i = place; i < rozmiar; i++)
            {
                tab[i] = tab [i+1];
            }
            resize(rozmiar);
            return true;
         }
         else
         {
             return false;
         }
    }

    bool isEmpty()
    {
            if (rozmiar == 0)
            {
                return true;
            }
            else
            {
                return false;
            }
    }

    int indexOf(T const& _value, int _from = 0) const
    {
        for (int i = _from; i < rozmiar; i++)
        {
            if (tab[i] == _value)
            {
                return i;
            }
        }
        return -1;
    }

    bool contains(T const& _value, int _from = 0) const
    {
        for (int i = _from; i < rozmiar; i++)
        {
            if (tab[i] == _value)
            {
                return true;
            }
        }
        return false;
    }

    bool operator==(aghVector<T> const& right)
    {
    	if ((rozmiar != right.rozmiar) && (OstWolny != right.OstWolny))
        {
            return false;
        }
        for (int i = 0; i < rozmiar; i++)
        {
            if (tab[i] != right.tab[i])
            {
               return false;
            }
        }
            return true;
    }

    bool operator!=(aghVector<T> const& right)
    {
        if ((rozmiar != right.rozmiar) && (OstWolny != right.OstWolny))
        {
            return true;
        }
        for (int i = 0; i < rozmiar; i++)
        {
            if (tab[i] != right.tab[i])
            {
               return true;
            }
        }
            return false;
    }

    T& operator[](int n) const
    {
        if ((n >= 0) && (n <= rozmiar))
        {
            return tab[n];
        }
        else
        {
            throw aghException(0, "Index out of range", __FILE__, __LINE__);
        }
    }

};

#endif




