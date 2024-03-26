#include "Matrix.h"
#include <cmath>
#include <iostream>
#include <tuple>
using namespace std;

//complexity: theta(capacity_)
Matrix::Matrix(int nrLines, int nrCols) {
    nrLines_ = nrLines;
    nrColumns_ = nrCols;
    count_ = 0;
    capacity_ = 5;
    keys_ = new tuple<int, int, TElem>[capacity_];
    for (int i = 0; i < capacity_; i++) {
        keys_[i] = make_tuple(-1, -1, 0);
    }
}
//complexity: theta(1)
Matrix::~Matrix() {
    delete[] keys_;
}
//complexity: theta(1)
int Matrix::nrLines() const {
    return nrLines_;
}
//complexity: theta(1)
int Matrix::nrColumns() const {
    return nrColumns_;
}
//complexity: theta(1)
// Functia h1: calculeaza indexul bazat pe valorile randului si coloanei
// folosind o formula simpla si capacitatea matricei
int Matrix::h1(int r, int c) const {
    return abs(r * nrColumns_ + c) % capacity_;
}
//complexity: theta(1)
// Functia h2: calculeaza indexul bazat pe valorile randului si coloanei
// folosind o alta formula simpla si capacitatea matricei cu o valoare mai mica
// Se scade 2 pentru a exclude 0 si capacity_-1 ca valori hash
// Se adauga 1 pentru a ne asigura ca rezultatul este >= 1
int Matrix::h2(int r, int c) const {
    return abs(r * nrColumns_ + c) % (capacity_ - 2) + 1;
}
//best: theta(1), average: theta(capacity_), worst: theta(capacity_)
// Cauta un element in matrice
// Returneaza indexul elementului daca acesta este gasit, altfel returneaza -1
// Se verifica daca coordonata liniei din tupla de la indexul h din array-ul keys!=-1
// Se utilizeaza o sondare patratica pentru rezolvare
int Matrix::find(int r, int c) const {
    int h = h1(r, c);
    int step = 1;
    int originalH = h;

    while (get<0>(keys_[h]) != -1) {
        if (get<0>(keys_[h]) == r && get<1>(keys_[h]) == c) {
            return h;
        }
        h = (originalH + step * step) % capacity_;
        step++;
    }
    return -1;
}
//best: theta(1), average: theta(n), worst: theta(n)
// Returneaza elementul de pe pozitia (i, j) din matrice
// Daca pozitia este invalida, arunca o exceptie de tipul out_of_range
// Se foloseste metoda find pentru a gasi indexul elementului
// Daca elementul nu este gasit, se returneaza valoarea 0
TElem Matrix::element(int i, int j) const {
    if (i < 0 || i >= nrLines_ || j < 0 || j >= nrColumns_) {
        throw out_of_range("Invalid position");
    }

    int idx = find(i, j);
    if (idx != -1) {
        return get<2>(keys_[idx]);
    } else {
        return NULL_TELEM;
    }
}


//best: theta(1), average: theta(capacity), worst: theta(capacity)
// Modifica valoarea de pe pozitia (i, j) din matrice cu valoarea e
// Daca pozitia este invalida, arunca o exceptie
// Daca elementul exista deja in matrice, returneaza valoarea veche si actualizeaza valoarea cu e
// Daca numarul de elemente depaseste capacitatea matricei, se dubleaza capacitatea prin apelarea metodei resize_up
// Daca numarul de elemente este mai mic sau egal cu un sfert din capacitatea matricei si capacitatea este mai mare decat
// capacitatea initiala, se injumatateste capacitatea prin apelarea metodei resize_down
// Se utilizeaza o sondare patratica pentru inserarea elementului in cazul in care slotul e ocupat
TElem Matrix::modify(int i, int j, TElem e) {
    if (i < 0 || i >= nrLines_ || j < 0 || j >= nrColumns_) {
        throw out_of_range("Invalid position");
    }

    int idx = find(i, j);
    if (e != 0) {
        if (idx != -1) {
            // Actualizeaza elementul existent in matrice
            TElem old = get<2>(keys_[idx]);
            get<2>(keys_[idx]) = e;
            return old;
        } else {
            // Adauga un element nou in matrice
            if (count_ >= capacity_ / 2) {
                resize_up(capacity_ );
            }

            int h = h1(i, j);
            int step = 1;
            int originalH = h;

            while (get<0>(keys_[h]) != -1) {
                h = (originalH + step * step) % capacity_;
                step++;
            }

            keys_[h] = make_tuple(i, j, e);
            count_++;

            return 0;
        }
    } else {
        if (idx != -1) {
            // Elimina elementul existent din matrice
            TElem old = get<2>(keys_[idx]);
            get<0>(keys_[idx]) = -1;
            get<1>(keys_[idx]) = -1;
            get<2>(keys_[idx]) = NULL_TELEM;
            count_--;

            if (count_ <= capacity_ / 4 && capacity_ > 5) {
                resize_down(capacity_ );
            }

            return old;
        }
        return 0;
    }
}


//complexity: theta(newCapacity)
// Redimensioneaza matricea cu o noua capacitate mai mare
// Se aloca un nou vector de perechi (tupluri) cu noua capacitate
// Toate elementele nesetate vor fi initializate cu valorile implicite (-1, -1, 0)
// Se face rehash pentru fiecare element din matrice utilizand noua funcție de hash
// Se elibereaza memoria alocata initial si se actualizeaza capacitatea
void Matrix::resize_up(int newCapacity) {
    newCapacity=capacity_*2;
    tuple<int, int, TElem>* newKeys = new tuple<int, int, TElem>[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newKeys[i] = make_tuple(-1, -1, 0);
    }

    for (int i = 0; i < capacity_; i++) {
        if (get<0>(keys_[i]) != -1) {
            int index = h1(get<0>(keys_[i]), get<1>(keys_[i]));
            int step = 1;

            while (get<0>(newKeys[index]) != -1) {
                index = (index + step * h2(get<0>(keys_[i]), get<1>(keys_[i]))) % newCapacity;
                step++;
            }

            newKeys[index] = keys_[i];
        }
    }

    delete[] keys_;
    keys_ = newKeys;
    capacity_ = newCapacity;
}

//complexity: theta(newCapacity)
// Redimensioneaza matricea cu o noua capacitate mai mica
// Se aloca un nou vector de perechi (tupluri) cu noua capacitate
// Toate elementele nesetate vor fi initializate cu valorile implicite (-1, -1, 0)
// Se face rehash pentru fiecare element din matrice utilizand noua functie de hash
// Se elibereaza memoria alocata initial si se actualizează capacitatea
void Matrix::resize_down(int newCapacity) {
    newCapacity=capacity_/2;
    tuple<int, int, TElem>* newKeys = new tuple<int, int, TElem>[newCapacity];
    for (int i = 0; i < newCapacity; i++) {
        newKeys[i] = make_tuple(-1, -1, 0);
    }

    for (int i = 0; i < capacity_; i++) {
        if (get<0>(keys_[i]) != -1) {
            int index = h1(get<0>(keys_[i]), get<1>(keys_[i]));
            int step = 1;

            while (get<0>(newKeys[index]) != -1) {
                index = (index + step * h2(get<0>(keys_[i]), get<1>(keys_[i]))) % newCapacity;
                step++;
            }

            newKeys[index] = keys_[i];
        }
    }

    delete[] keys_;
    keys_ = newKeys;
    capacity_ = newCapacity;
}
