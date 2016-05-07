#ifndef AGHINCLUDE_H
#define AGHINCLUDE_H

#include <iostream>
using namespace std;

template <class T>
class aghContainer{
	public:
	//aghContainer()
	//{
		//aghContainer <T>;
	//}
	//virtual void wypisz() = 0;
	virtual void append(T const& dodawanyElement){}
	//virtual void resize(){}
	//virtual void wypisz(){}
};

template <class T>
class aghVector:public aghContainer<T>{
public:
	T *tab;
	int rozmiar;
	int ostWolny; //najmniejszy numer indeksu tablicy z wolnym polem
	aghVector()
	{
		rozmiar = 1;
		tab = new T [rozmiar];
		ostWolny=0;
	}

	aghVector(int _rozmiar)
	{
		if (_rozmiar>0)
		{
			rozmiar = _rozmiar;
			tab = new T [rozmiar];
			ostWolny=0;
		}
	}

	/*void wypisz()
	{
		for (int i =0 ; i< ostWolny; i++)
			cout << tab[i] << ", ";
		cout << endl;
	}*/

	~aghVector()
	{
		delete [] tab;
		rozmiar = 0;
		ostWolny = 0;
	}

	bool  ifNeedResize()
	{
		if (ostWolny>=rozmiar)
		{
			return true;
		}
		else
		{
			return false;
		}
	}

	aghVector& operator= (aghVector const & w)
	{
	    if (this == &w)
				    return *this;
        else
        {
            if (tab!=NULL)
            {
                 delete [] tab;
            }
            rozmiar=w.rozmiar;
            ostWolny=w.ostWolny;

            tab = new T [rozmiar];
            for (int i = 0 ; i < rozmiar; i++)
                tab[i] = w.tab[i];
            return *this;
        }
    }

	void resize(int tmpSize)
	{
		rozmiar = tmpSize;
		//T* tmpTab=new T [rozmiar];
		aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
		tmpTab -> ostWolny=ostWolny;
		for (int i=0;i<rozmiar;i++)
		{
			tmpTab -> tab[i]=tab[i];
		}
		delete [] tab;

		tab=tmpTab->tab;// nie jestem przekoknana
	}

	void append(T const& dodawanyElement)
	{
		if(ifNeedResize())
		{
			resize(rozmiar++);
		}
		tab[ostWolny++]=dodawanyElement;
		cout << "dodano element" << endl;
	}

	bool remove(int x) // powinno przepsac tablice??
	{
		if (x<=rozmiar) //a co jak zarz¹da usuniecia ujemengo elementu??
		{
			//usun element z miejsca x
			return true;
		}
		else return false;
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

};

#endif
