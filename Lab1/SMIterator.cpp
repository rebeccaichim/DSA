#include "SMIterator.h"
#include "SortedMap.h"
#include <exception>

using namespace std;

// Constructor: initialize the iterator with the given SortedMap and set the index to 0
SMIterator::SMIterator(const SortedMap& m) : map(m){
    this->index = 0;
}

// Set the index to 0 (the beginning of the map)
void SMIterator::first(){
    this->index = 0;
}

// Move to the next element in the map
void SMIterator::next(){
    // If the iterator is not valid (index >= map.length), throw an exception
    if (!this->valid()) {
        throw exception();
    }
    // otherwise, move to the next element in the map
    this->index++;
}

// Return true if the iterator is valid (index < map.length), false otherwise
bool SMIterator::valid() const{
    if (this->index < map.length)
        return true;
    return false;
}

// Return the current element in the map (the element at the current index)
TElem SMIterator::getCurrent() const{
    // If the iterator is not valid (index >= map.length), throw an exception
    if (this->valid()) {
        return map.elements[index];
    }
    throw exception();
}