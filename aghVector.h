/**
* \file aghVector.h
* \author Beata Gie�baga & Kamil Dawid�w
* \date 26.05.2014
* \brief Deklaracja i definicja szablonu klasy aghVector, pochodnej klasy aghContainer
*/
// -------------------------------------------------------------------------

#ifndef AGHVECTOR_H
#define AGHVECTOR_H
// ------------------------------

#include "aghContainer.h"
// ------------------------------

/**
* \class aghVector
* \author Beata Gie�baga & Kamil Dawid�w
* \date 26.05.2014
* \brief szablon klasy aghVector (pochodnej klasy aghContainer), opisuj�cej obiekt - wektor, 
*/
// -------------------------------------------------------------------------
template <class T>
class aghVector: public aghContainer<T>
{
private:
    T* tab; ///< wska�nik do pocz�tku tablicy element�w
    int length; ///< ilo�� element�w w pojemniku

    /// \brief Metoda alokuje tablicy o wyznaczonej ilo�ci element�w
    ///
    /// \param _length - nowa ilo�� element�w
    void alloc(int _length);

    /// \brief Metoda zwalnia zaalokowan� pami��
    void dealloc();

    /// \brief Metoda zmienia rozmiar tablicy
    ///
    /// \param k - zmiana rozmiaru:
    /// \li -1 - zmniejsza o jeden
    /// \li 1 - zwi�ksza o jeden
    void resize(int k);

public:
    /// \brief Konstruktor bezparametrowy
    aghVector();

    /// \brief Konstruktor kopiuj�cy
    ///
    /// \param pattern - referencja do obiektu macierzystego
    aghVector(const aghVector<T>& pattern);

    /// \brief Konstruktor kopiuj�cy przyjmuj�cy jako argument referencj� do obiektu klasy aghContainer
    ///
    /// \param pattern - referencja do obiektu macierzystego
    aghVector(const aghContainer<T>& pattern);

    /// \brief Destruktor
    ~aghVector();

    /// \brief Metoda  zwraca warto�� elementu
    ///
    /// \param n - indeks zwracanego elementu
    T& at(int n) const;

    /// \brief Metoda  zwraca ilo�� element�w w pojemniku
    ///
    /// \return zwraca ilo�� element�w element�w
    int size(void) const;

    /// \brief Metoda wstawia element w podane miejsce
    /// 
    /// \param n - miejsce, w kt�re zostanie wstawiony element
    /// \param element - referencja do elementu, kt�ry zostanie wstawiony
    /// \return metoda zwraca:
    /// \li true - gdy uda si� wstawi� element
    /// \li false - gdy nie uda si� wstawi� elementu
    bool insert(int n, T const& element);

    /// \brief Metoda usuwa wybrany element
    ///
    /// \param n - indeks usuwanego elementu
    /// \return zwraca:
    /// \li true - gdy uda si� usun�� element
    /// \li false - gdy nie uda si� usun�� elementu
    bool remove(int n);

    /// \brief Prze�adowanie operatora przypisania "="
    ///
    /// \param right - referencja do obiektu macierzystego
    /// \return zwraca referencj� do obiektu macierzystego
    aghVector<T>& operator=(aghVector<T> const& right);
};
// --------------------------------------------------------------

// Definicje metod

// --------------------------------------------------------------

template <class T>
void aghVector<T>::alloc(int _length)
{
    tab = new T[_length];
    length = _length;
}
// --------------------------------------------------------------

template <class T>
void aghVector<T>::dealloc()
{
    delete[] tab;
    tab = nullptr;
    length = 0;
}
// --------------------------------------------------------------

template <class T>
void aghVector<T>::resize(int k)
{
    T* localtab = tab;
    this->alloc(length + k);

    int helper = length;
    if (k == 1)
        --helper;

    for (int i = 0; i < helper; ++i)
        tab[i] = localtab[i];
    delete[] localtab;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector()
{
    length = 0;
    tab = nullptr;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector(const aghVector<T>& pattern)
{
    this->alloc(pattern.size());
    for (int i = 0; i < length; ++i)
        tab[i] = pattern.at(i);
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector(const aghContainer<T>& pattern)
{
    this->alloc(((const aghVector<T>&)pattern).size());
    for (int i = 0; i < length; ++i)
        tab[i] = ((const aghVector<T>&)pattern).at(i);
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::~aghVector()
{
    this->dealloc();
}
// --------------------------------------------------------------

template <class T>
T& aghVector<T>::at(int n) const
{
    if (n > this->size() || n < 0)
        throw aghException(0, "Index out of range", __FILE__, __LINE__);
    return tab[n];
}
// --------------------------------------------------------------

template <class T>
int aghVector<T>::size(void) const
{
    return length;
}
// ---------------------------------------------------------------

template <class T>
bool aghVector<T>::insert(int n, T const& element)
{
    if (n > length || n < 0)
        return false;
    this->resize(1);
    if (n != length - 1)
    {
        for (int i = length - 1; i > n; --i)
            tab[i] = tab[i - 1];
    }
    tab[n] = element;
    return true;
}
// --------------------------------------------------------------

template <class T>
bool aghVector<T>::remove(int n)
{
    if (n > length || n < 0)
        return false;
    for (int i = n; i < length - 1; ++i)
        tab[i] = tab[i + 1];
    this->resize(-1);
    return true;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>& aghVector<T>::operator=(aghVector<T> const& right)
{
    if (*this == right)
        return *this;
    this->dealloc();
    this->alloc(right.size());
    for (int i = 0; i < length; ++i)
        tab[i] = right.at(i);
    return *this;
}
// --------------------------------------------------------------

#endif