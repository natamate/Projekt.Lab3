#ifndef AGHINCLUDE_H
#define AGHINCLUDE_H

#include <iostream>
using namespace std;

template <class T>
class aghContainer{
	public:
	//{
		//aghContainer <T>;
	//}
	//virtual void wypisz() = 0;
	virtual void append(T const& dodawanyElement) = 0;
	virtual ~aghContainer()
	{
	    cout << "wirtualny destruktor" << endl;
	}
	//virtual void resize(){}
	//virtual void wypisz(){}
	virtual aghContainer<T>& operator<<(T const& element){}
	//virtual aghContainer<T>& operator<<(aghContainer<T> const right){} //nie moze tak być??
	virtual bool insert(int place, T const& element){}
	virtual bool replace(int place, T const& element){}
	virtual int size() const{}
	virtual aghContainer& operator= (aghContainer const & w){}
    virtual T& at(int place) const{}
    virtual bool remove(int place){}
    virtual void clear(){}
    virtual bool isEmpty(){}
    virtual int indexOf(T const& _value, int _from = 0) const{}
    virtual bool contains(T const& _value, int _from = 0) const{}
    virtual bool operator==(aghContainer<T> const& right){}
    virtual bool operator!=(aghContainer<T> const& right){}
    virtual T& operator[](int n) const{}
    virtual aghContainer<T>& operator+=(T const& element){}
    //friend class aghVector;
};

template <class T>
class aghVector:public aghContainer<T>{
public:
	T *tab;
	int rozmiar;
    int OstWolny;

	aghVector()
	{
		rozmiar = 1;
		tab = new T [rozmiar];
		OstWolny = 0;
	}

	aghVector(int _rozmiar)
	{
		if (_rozmiar>0)
		{
			rozmiar = _rozmiar;
			tab = new T [rozmiar];
			OstWolny = 0;
		}
	}
	/*aghContainer<T>& operator= (aghContainer<T> const & w)
	{
	    if (this == &w)
				    return *this;
        else
        {
            if (tab!=NULL)
            {
                 delete [] tab;
            }
            rozmiar = w.rozmiar;
            OstWolny = w.OstWolny;
            tab = new T [rozmiar];
            for (int i = 0 ; i < rozmiar; i++)
                tab[i] = w.tab[i];
            return *this;
        }
    }*/
	aghVector<T> (aghVector<T>& kopia)
    {
        kopia.rozmiar=rozmiar;
        kopia.OstWolny = OstWolny;
        kopia.tab = new T [kopia.rozmiar];
        for (int i = 0 ; i < kopia.rozmiar; i++)
            kopia[i]=tab[i];
    }

    void clear()
    {
        delete [] tab;
        rozmiar = 0;
        OstWolny = 0;
    }

	~aghVector()
	{
		delete [] tab;
        rozmiar = 0;
        OstWolny = 0;
	}

	aghVector<T>& operator= (aghVector<T> const & w)
	{
	    if (this == &w)
				    return *this;
        else
        {
            if (tab!=NULL)
            {
                 delete [] tab;
            }
            rozmiar = w.rozmiar;
            OstWolny = w.OstWolny;
            tab = new T [rozmiar];
            for (int i = 0 ; i < rozmiar; i++)
                tab[i] = w.tab[i];
            return *this;
        }
    }

	void resize(int tmpSize)
	{
		aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
		for (int i=0;i<rozmiar--;i++)
		{
			tmpTab -> tab[i]=tab[i];
		}
		delete [] tab;

        rozmiar = tmpSize;
        tab = new T [rozmiar];
        for (int i = 0; i < rozmiar; i++)
            tab[i] = tmpTab -> tab[i];
	}

    bool insert(int place, T const& element)
    {
        if ((place >= 0) && (place <= rozmiar))
        {
            rozmiar++;
            resize(rozmiar);
            aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
            for (int i = 0 ; i < rozmiar; i++)
                tmpTab -> tab[i] = tab[i];

            for (int i = rozmiar; i > place; i--)
            {
                tab[i] = tab [i-1];
            }
            tab[place] = element;
            return true;
        }
        else return false;
    }

    bool replace(int place, T const& element)
    {
        if ((place >= 0) && (place <= rozmiar))
        {
            tab[place] = element;
            return true;
        }
        else return false;
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
		cout << "dodano element" << endl;
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
        int tmpRozmiar = 0;
        if (rozmiar<=right.rozmiar)
        {
            int tmpRozmiar = right.rozmiar - rozmiar;
        }
        else
        {
            int tmpRozmiar = rozmiar - right.rozmiar;
        }

        for (int i = 0; i < tmpRozmiar; i++)
            append(right.tab[i]);

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
             resize(rozmiar);
             aghVector<T> *tmpTab = new aghVector<T>(rozmiar);
             for (int i = 0 ; i < rozmiar; i++)
                 tmpTab -> tab[i] = tab[i];

             for (int i = place; i < rozmiar; i++)
             {
                 tab[i] = tab [i+1];
             }
             return true;
         }
         else return false;
    }

    bool isEmpty()
    {
            if (rozmiar  == 0)
                return true;
            else return false;
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

    bool operator==(aghVector<T> const& right) //trzeba jeszcze sprawdzic zgodnosc rozmiarów bo np 1,1 != 1 
    {
    	if (rozmiar!=right.rozmiar) return false;
        int RepeatElements = 0;
        if (rozmiar >= right.rozmiar)
        {
            for (int i = 0; i < rozmiar; i++)
            {
                if (tab[i] == right.tab[i])
                    RepeatElements++;
            }
            if (RepeatElements == rozmiar)
                return true;
            else return false;
        }
        else
        {
            for (int i = 0; i < right.rozmiar; i++)
            {
                if (tab[i] == right.tab[i])
                    RepeatElements++;
            }
            if (RepeatElements == right.rozmiar)
                return true;
            else return false;
        }
    }

    bool operator!=(aghVector<T> const& right)
    {
        return false;
        //analogicznie jw jesli jest dobrze
    }

    T& operator[](int n) const
    {
        if ((n >= 0) && (n <= rozmiar))
        {
            return tab[n];
        }
        else throw aghException(0, "Index out of range", __FILE__, __LINE__);

    }

};

#endif
