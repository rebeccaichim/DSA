#pragma once
#include "SortedIndexedList.h"


//DO NOT CHANGE THIS PART
class ListIterator{
    friend class SortedIndexedList;
private:
    const SortedIndexedList& list;
    ListIterator(const SortedIndexedList& list);
    int currentIndex;

public:
    // Moves the iterator to the first position in the list
    void first();

    // Moves the iterator to the next position in the list
    void next();

    // Checks if the iterator is currently pointing to a valid position in the list
    bool valid() const;

    // Returns the element at the current position of the iterator
    TComp getCurrent() const;
};