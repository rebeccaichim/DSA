#include "SetIterator.h" // include the header file for SetIterator
#include "Set.h" // include the header file for Set
#include<iostream> // include the input/output stream library
//theta(1)
SetIterator::SetIterator(const Set& s) : set(s) { // constructor for SetIterator that takes a reference to a Set
    currentElement = set.head.next; // initialize currentElement to the first element of the set
}
//theta(1)
void SetIterator::first() { // method to set currentElement to the first element of the set
    currentElement = set.head.next;
}
//theta(1)
void SetIterator::next() { // method to move currentElement to the next element of the set
    if (!valid()) { // check if the iterator is valid (currentElement is not null)
        throw std::runtime_error("Invalid iterator"); // throw a runtime error if the iterator is invalid
    }
    currentElement = currentElement->next; // move currentElement to the next element of the set
}
//theta(1)
TElem SetIterator::getCurrent() { // method to return the current element of the set
    if (!valid()) { // check if the iterator is valid (currentElement is not null)
        throw std::runtime_error("Invalid iterator"); // throw a runtime error if the iterator is invalid
    }
    return currentElement->info; // return the current element of the set
}
//theta(1)
bool SetIterator::valid() const { // method to check if the iterator is valid (currentElement is not null)
    return currentElement != nullptr; // return true if currentElement is not null, false otherwise
}
//best: theta(1)
//average: O(n)
//worst: theta(n)
void SetIterator::previous()
{
    if (!valid()) { // check if the iterator is valid (currentElement is not null)
        throw std::runtime_error("Invalid iterator position");
    }
    if (currentElement == set.head.next) { // check if the iterator is at the beginning of the set
        throw std::runtime_error("Iterator already at beginning of set");
    }
    SLLNode* prevElement = set.head.next; // start at the beginning of the set
    while (prevElement->next != currentElement) { // find the previous element in the set
        prevElement = prevElement->next;
    }
    currentElement = prevElement; // set currentElement to the previous element in the set
}
//function previous() {
//    if currentElement is null {
//        throw "Invalid iterator position"
//    }
//    if currentElement equals set.head.next {
//        throw "Iterator already at beginning of set"
//    }
//    let prevElement = set.head.next
//    while prevElement.next does not equal currentElement {
//        prevElement = prevElement.next
//    }
//    currentElement = prevElement
//}