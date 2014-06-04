/**
* \file aghVector.h
* \author Beata Gie³baga & Kamil Dawidów
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
* \author Beata Gie³baga & Kamil Dawidów
* \date 26.05.2014
* \brief szablon klasy aghVector (pochodnej klasy aghContainer), opisuj¹cej obiekt - wektor, 
*/
// -------------------------------------------------------------------------
template <class T>
class aghVector: public aghContainer<T>
{
private:
    T* tab = nullptr; ///< wskaŸnik do pocz¹tku tablicy elementów
    int length = 0; ///< iloœæ elementów w pojemniku

    /// \brief Metoda alokuje tablicy o wyznaczonej iloœci elementów
    ///
    /// \param _length - nowa iloœæ elementów
    void alloc(int _length);

    /// \brief Metoda zwalnia zaalokowan¹ pamiêæ
    void dealloc();

    /// \brief Metoda rozsuwa w danym miejscu elementy lub usuwa element (czyli zsuwa elementy)
    ///
    /// \param n - indeks elementu
    /// \param k - usuwa element czy rozsuwa elementy:
    /// \li -1 - usuwa element
    /// \li 1 - rozsuwa elementy
    void editTable(int k, int n);

public:
    /// \brief Konstruktor bezparametrowy
    aghVector();

    /// \brief Konstruktor kopiuj¹cy
    ///
    /// \param pattern - referencja do obiektu macierzystego
    aghVector(const aghVector<T>& pattern);

    /// \brief Konstruktor kopiuj¹cy przyjmuj¹cy jako argument referencjê do obiektu klasy aghContainer
    ///
    /// \param pattern - referencja do obiektu macierzystego
    aghVector(const aghContainer<T>& pattern);

    /// \brief Destruktor
    ~aghVector();

    /// \brief Metoda  zwraca wartoœæ elementu
    ///
    /// \param n - indeks zwracanego elementu
    T& at(int n) const;

    /// \brief Metoda  zwraca iloœæ elementów w pojemniku
    ///
    /// \return zwraca iloœæ elementów elementów
    int size(void) const;

    /// \brief Metoda wstawia element w podane miejsce
    /// 
    /// \param n - miejsce, w które zostanie wstawiony element
    /// \param element - referencja do elementu, który zostanie wstawiony
    /// \return metoda zwraca:
    /// \li true - gdy uda siê wstawiæ element
    /// \li false - gdy nie uda siê wstawiæ elementu
    bool insert(int n, T const& element);

    /// \brief Metoda usuwa wybrany element
    ///
    /// \param n - indeks usuwanego elementu
    /// \return zwraca:
    /// \li true - gdy uda siê usun¹æ element
    /// \li false - gdy nie uda siê usun¹æ elementu
    bool remove(int n);

    /// \brief Prze³adowanie operatora przypisania "="
    ///
    /// \param right - referencja do obiektu macierzystego
    /// \return zwraca referencjê do obiektu macierzystego
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
void aghVector<T>::editTable(int k, int n)
{
    T* localtab = tab;
    this->alloc(length + k);

    for (int i = 0; i < n; ++i)
        tab[i] = localtab[i];

    if (k == 1)
    {
        for (int i = length - 1; i > n; --i)
            tab[i] = localtab[i - 1];
    }

    else
    {
        for (int i = n; i < length; ++i)
            tab[i] = localtab[i + 1];
    }
    
    delete[] localtab;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector()
{
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector(const aghVector<T>& pattern)
{
    this->operator=(pattern);
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector(const aghContainer<T>& pattern)
{
    this->aghContainer<T>::operator=(pattern);
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
    if (this->invalidIndex(n))
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
    if (n > this->size() || n < 0)
        return false;
    this->editTable(1, n);
    tab[n] = element;
    return true;
}
// --------------------------------------------------------------

template <class T>
bool aghVector<T>::remove(int n)
{
    if (this->invalidIndex(n))
        return false;
    this->editTable(-1, n);
    return true;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>& aghVector<T>::operator=(aghVector<T> const& right)
{
    this->aghContainer<T>::operator=(right);
    return *this;
}
// --------------------------------------------------------------

#endif