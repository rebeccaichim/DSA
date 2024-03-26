#include "Iterator.h"
// Preconditie: `matrix` este un pointer valid catre un tablou de dimensiune `numRows x numCols`
// si `numRows` si `numCols` sunt numere pozitive
// Postconditie: Un obiect Iterator este creat cu valorile initiale corespunzatoare
template<typename T>
Iterator<T>::Iterator(const T* matrix, int numRows, int numCols)
        : matrix_(matrix), numRows_(numRows), numCols_(numCols), currentRow_(0), currentCol_(0) {}

// Precondiție: -
// Postconditie: Returneaza `true` daca iteratorul este valid (se afla in interiorul matricei),
// altfel returneaza `false`
//theta(1)
template<typename T>
bool Iterator<T>::valid() const {
    return currentRow_ < numRows_ && currentCol_ < numCols_;
}
// Preconditie: Iteratorul este valid (se afla in interiorul matricei)
// Postconditie: Iteratorul este mutat la inceputul randului urmator si la prima coloana
//theta(1)
template<typename T>
void Iterator<T>::nextRow() {
    currentRow_++;
    currentCol_ = 0;
}
// Preconditie: Iteratorul este valid (se afla in interiorul matricei)
// Postconditie: Iteratorul este mutat la urmatoarea coloana in cadrul aceluiasi rand
// Daca iteratorul depaseste ultima coloana a randului curent, acesta este mutat
// la inceputul randului urmator si la prima coloana
//theta(1)
template<typename T>
void Iterator<T>::nextColumn() {
    currentCol_++;
    if (currentCol_ >= numCols_) {
        currentRow_++;
        currentCol_ = 0;
    }
}
// Preconditie: Iteratorul este valid (se afla in interiorul matricei)
// Postconditie: Returneaza o referinta constanta la elementul curent al matricei
//theta(1)
template<typename T>
const T& Iterator<T>::getCurrent() const {
    return matrix_[currentRow_ * numCols_ + currentCol_];
}