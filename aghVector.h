/**
* \file aghVector.h
* \author Kamil Dawidów
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
* \author Kamil Dawidów
* \date 26.05.2014
* \brief szablon klasy aghVector (pochodnej klasy aghContainer), opisuj¹cej obiekt - wektor, 
*/
// -------------------------------------------------------------------------
template <class T>
class aghVector: public aghContainer<T>
{
private:
    T* tab; ///< wskaŸnik do pocz¹tku tablicy elementów
    int size; ///< iloœæ elementów w pojemniku

    /// \brief Metoda alokuje tablicy o wyznaczonej iloœci elementów
    ///
    /// \param _size - nowa iloœæ elementów
    void alloc(int _size);

    /// \brief Metoda zwalnia zaalokowan¹ pamiêæ
    void dealloc();

    /// \brief Metoda przesuwa elementy o jeden w odpowiedni¹ stronê od podanego indeksu
    ///
    /// \param n - od elementu o tym indeksie w³¹cznie elementy zostan¹ przesuniête
    /// \param dir - kierunek przesuniêcia:
    /// \li 1 - w prawo
    /// \li -1 - w lewo
    void move(int n, int dir);

    /// \brief Metoda zmienia rozmiar tablicy
    ///
    /// \param k - zmiana rozmiaru:
    /// \li -1 - zmniejsza o jeden
    /// \li 1 - zwiêksza o jeden
    void resize(int k);
public:
    /// \brief Konstruktor bezparametrowy
    aghVector();

    /// \brief Konstruktor kopiuj¹cy
    ///
    /// \param pattern - referencja do obiektu macierzystego
    aghVector(aghVector<T>& pattern);

    /// \brief Destruktor
    ~aghVector();

    /// \brief Metoda  wstawia element w podane miejsce
    /// 
    /// \param n - miejsce, w które zostanie wstawiony element
    /// \param element - referencja do elementu, który zostanie wstawiony
    /// \return metoda zwraca:
    /// \li true - gdy uda siê wstawiæ element
    /// \li false - gdy nie uda siê wstawiæ elementu
    bool insert(int n, T const& element);

    /// \brief Metoda  zwraca wartoœæ elementu
    ///
    /// \param n - indeks zwracanego elementu
    T& at(int n) const;

    /// \brief Metoda  zwraca iloœæ elementów w pojemniku
    ///
    /// \return zwraca iloœæ elementów elementów
    int size(void) const;

    /// \brief Metoda usuwa wybrany element
    ///
    /// \param n - indeks usuwanego elementu
    /// \return zwraca:
    /// \li true - gdy uda siê usun¹æ element
    /// \li false - gdy nie uda siê usun¹æ elementu
    bool remove(int n);

    /// \brief {rze³adowanie operatora przypisania "="
    ///
    /// \param right - referencja do obiektu macierzystego
    /// \return zwraca referencjê do obiektu macierzystego
    aghVector<T>& operator=(aghVector<T> const& right);
};
// --------------------------------------------------------------

// Definicje metod
// --------------------------------------------------------------

template <class T>
aghVector<T>::aghVector()
{
    size = 0;
    tab = nullptr;
}
// --------------------------------------------------------------

template <class T>
aghVector::aghVector(const aghVector<T>& pattern)
{
    this->alloc(pattern.size);
    for (int i = 0; i < size; ++i)
        this->replace;
}
// --------------------------------------------------------------

template <class T>
aghVector<T>::~aghVector()
{
    this->dealloc();
}
// --------------------------------------------------------------

template <class T>
void aghVector<T>::alloc(int _size)
{
    tab = new T [_size];
    size = _size;
}
// --------------------------------------------------------------

template <class T>
void aghVector<T>::dealloc()
{
    delete [] tab;
    tab = nullptr;
    size = 0;
}

template <class T>
void aghVector<T>::move(int n, int dir)
{
    int localtabsize = size - n;
    T* localtab = new T[localtabsize];

    for (int i = 0; i < localtabsize; ++i)
        localtab[i] = tab[i + n];

    this->resize(dir);

    for (int i = 0; i < localtabsize; ++i)
        tab[i + n]
}
// --------------------------------------------------------------

template <class T>
void aghVector<T>::resize(int k)
{
    T* localtab = new T[size + k];
    for (int i = 0; i < size + k; ++i)
    {
        localtab[i] = tab[i];
    }
    this->dealloc();
    this->alloc(size + k);

    for (int i = 0; i < size; ++i)
    {
        tab[i] = localtab[i];
    }
    delete[] localtab;
}
// --------------------------------------------------------------

template <class T>
bool aghVector<T>::insert(int n, T const& element)
{
    if (n > size || n < 0)
        return false;
    if (n == size)
    {
        this->resize(1);
        tab[size] = element;
        ++size;
        return true;
    }
    else
    {

    }
}
// --------------------------------------------------------------

#endif