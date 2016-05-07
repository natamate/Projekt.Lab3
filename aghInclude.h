#ifndef AGHINCLUDE_H
#define AGHINCLUDE_H

#include <iostream>
using namespace std;

template <class T>
class aghContainer{
	public:
	virtual void wypisz(){}
	virtual void append(T const& dodawanyElement){}
	virtual ~aghContainer(){}
	virtual int size() const{}
	virtual void insert(int nrIndeksu,T const& dodawanyElement){}
};

template <class T>
class aghVector:public aghContainer<T>{
public:
	T *tab;
	int rozmiar;
	bool *czyZajete;
	void uzupFalseCzyZajete(int dlTab)
	{
		for (int i=0;i<dlTab;i++)
		{
			czyZajete[i]=false;
		}
	}
	aghVector()
	{
		rozmiar = 1;
		tab = new T [rozmiar];
		czyZajete= new bool [rozmiar]; 
		uzupFalseCzyZajete(rozmiar);
	}
	
	aghVector(int _rozmiar)
	{
		if (_rozmiar>0)
		{
			rozmiar = _rozmiar;
			tab = new T [rozmiar];
			czyZajete= new bool [rozmiar];
 			uzupFalseCzyZajete(rozmiar);
		}
	}
	void wypisz()
	{
		for (int i =0 ; i< rozmiar; i++)
		{
			if (czyZajete[i]==true)
			{
				cout << tab[i] << ", ";
			}
		}		
		cout << endl;
	}

	~aghVector()
	{
		delete [] tab; //powinno sie te 3 ponizsze komentarze odkomentwać?
		//tab = NULL;
		delete [] czyZajete;
		//czyZajete=NULL; 
		//rozmiar = 0;
	}
	bool tabPelna()
	{
		bool pelna=true;
		for (int i;i<rozmiar;i++)
		{
			if (czyZajete[i]==false)
			{
				pelna=false;
				break;
			}
		}
		return pelna;
	}
	bool  ifNeedResize()
	{
		if (tabPelna())
		{
			return true;
		}
		else
		{
			return false;
		}
	}
	void resize()
	{
		int tmpSize=rozmiar;
		T* tmpTab=new T [tmpSize+1];
		bool *tmpCzyZajete=new bool [tmpSize+1];
		for (int i=0;i<rozmiar;i++)
		{
			tmpCzyZajete[i]=czyZajete[i];
			if (!tmpCzyZajete[i])
			{
				tmpTab[i]=tab[i];
			}	
		}	
		tmpCzyZajete[tmpSize+1]=false;
		delete [] tab;
		tab = tmpTab;

	}
	int najmniejszyPusty()
	{
		for (int i=0;i<rozmiar;i++)
		{
			if (czyZajete[i]==false)
			{
				return i;
			}
		}
	}
	void append(T const& dodawanyElement)	
	{
		if(ifNeedResize()) 
		{
			resize();
		}
		int indexDodania=najmniejszyPusty();
		tab[indexDodania]=dodawanyElement;
		czyZajete[indexDodania]=true;
		cout << "dodano element" << endl;
	}
	void insert(int nrIndeksu,T const& dodawanyElement)	
	{	
		while (nrIndeksu>=rozmiar)
		{
			resize();
		}
		if((0<=nrIndeksu)) 
		{
			tab[nrIndeksu]=dodawanyElement;
			czyZajete[nrIndeksu]=true;
			
		}
		else
		{ 
			{
				cout << "tu trzeba dodac wyrzucenie bledu"<< endl; //jak wypisuje
			}
		}
	}
	bool remove(int nrIndeksu) // powinno przepsac tablice?? 
	{
		if ((nrIndeksu>=0)&&(nrIndeksu<rozmiar)) //a co jak zarząda usuniecia ujemengo elementu??
		{
			if (czyZajete[nrIndeksu])
			{
				czyZajete[nrIndeksu]=false;
				return true;
			}
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
