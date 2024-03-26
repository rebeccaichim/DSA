#include "ListIterator.h"
#include "SortedIndexedList.h"
#include <stdexcept>

//Complexity:theta(1)
ListIterator::ListIterator(const SortedIndexedList& list) : list(list), currentIndex(0) {
    first();
}

//Complexity:theta(1)
void ListIterator::first() {
    currentIndex = 0;
}

//Complexity:theta(1)
void ListIterator::next() {
    if (!valid()) {
        // If the iterator is not valid (out of range), throw an exception
        throw std::exception();
    }
    // Move the iterator to the next position in the list
    currentIndex++;
}

//Complexity:theta(1)
bool ListIterator::valid() const {
    return currentIndex < list.size();
}

//Complexity:theta(1)
TComp ListIterator::getCurrent() const {
    if (!valid()) {
        // If the iterator is not valid (out of range), throw an exception
        throw std::exception();
    }
    // Get the element at the current position of the iterator
    return list.getElement(currentIndex);
}