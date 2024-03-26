#include "SortedIndexedList.h"
#include "ListIterator.h"
#include <stdexcept>
SortedIndexedList::SortedIndexedList(Relation r) {
    // Initialize the SortedIndexedList with the given relation
    capacity = 10;
    head = -1;
    tail = -1;
    next = new int[capacity];
    prev = new int[capacity];
    elements = new TComp[capacity];
    relation = r;
    firstEmpty = 0;
    numberOfElements = 0;

    // Initialize the next and prev arrays
    for (int i = 0; i < capacity - 1; i++) {
        next[i] = i + 1;
        prev[i + 1] = i;
    }
    next[capacity - 1] = -1;
}

// Return the number of elements in the list
//Complexity: theta(1)
int SortedIndexedList::size() const {
    return numberOfElements;
}

// Check if the list is empty
//Complexity: theta(1)
bool SortedIndexedList::isEmpty() const {
    return numberOfElements == 0;
}

//Complexity: theta(pos)
TComp SortedIndexedList::getElement(int pos) const {
    if (pos < 0 || pos >= numberOfElements) {
        // If the position is invalid, throw an exception
        throw std::exception();
    }

    // Traverse the list to the specified position
    int current = head;
    while (pos > 0) {
        current = next[current];
        pos--;
    }

    // Return the element at the specified position
    return elements[current];
}

//Best case: theta(1) when the element should be inserted at the beginning of the list
//Average case: theta(n), where n is the number of elements in the list
//Worst case: theta(n) when the element should be inserted at the end of the list or when the list needs to be resized
void SortedIndexedList::add(TComp e) {
    // If the list is full, resize the capacity
    if (numberOfElements == capacity) {
        resize();
    }

    int current = head;
    int previous = -1;

    // Find the correct position to insert the element based on the relation
    while (current != -1 && relation(elements[current], e)) {
        previous = current;
        current = next[current];
    }

    // Get a new element index from the firstEmpty pool
    int newElementIndex = firstEmpty;
    firstEmpty = next[firstEmpty];

    // Insert the element at the new element index
    elements[newElementIndex] = e;
    next[newElementIndex] = current;
    prev[newElementIndex] = previous;

    // Update the head and tail if necessary
    if (previous == -1) {
        head = newElementIndex;
    } else {
        next[previous] = newElementIndex;
    }

    if (current == -1) {
        tail = newElementIndex;
    } else {
        prev[current] = newElementIndex;
    }
    // Increase the number of elements
    numberOfElements++;
}

//Best case: theta(1) when pos is 0 (removing the head element)
//Average case: theta(n), where n is the number of elements in the list
//Worst case: theta(n) when pos is size()-1 (removing the tail element)
TComp SortedIndexedList::remove(int pos) {
    if (pos < 0 || pos >= numberOfElements) {
        // If the position is invalid, throw an exception
        throw std::exception();
    }

    // Traverse the list to the specified position
    int current = head;
    while (pos > 0) {
        current = next[current];
        pos--;
    }

    // Get the element to be removed
    TComp removedElement = elements[current];

    // Update the head and tail if necessary
    if (prev[current] == -1) {
        head = next[current];
    } else {
        next[prev[current]] = next[current];
    }

    if (next[current] == -1) {
        tail = prev[current];
    } else {
        prev[next[current]] = prev[current];
    }

    // Move the removed element index to the firstEmpty pool
    next[current] = firstEmpty;
    firstEmpty = current;

    // Decrease the number of elements
    numberOfElements--;

    // Return the removed element
    return removedElement;
}

//Best case: theta(1) when the element is found at the head of the list
//Average case: theta(n), where n is the number of elements in the list
//Worst case: theta(n) when the element is not found or when the element is found at the tail of the list
int SortedIndexedList::search(TComp e) const {
    // Search for the element in the list based on the relation
    int current = head;
    int position = 0;

    while (current != -1 && relation(elements[current], e)) {
        if (elements[current] == e) {
            // Return the position if the element is found
            return position;
        }

        current = next[current];
        position++;
    }

    // Return -1 if the element is not found
    return -1;
}

//Complexity: theta(n)
void SortedIndexedList::resize() {
    // Double the capacity of the list
    int newCapacity = capacity * 2;

    int* newNext = new int[newCapacity];
    int* newPrev = new int[newCapacity];
    TComp* newElements = new TComp[newCapacity];

    // Copy the existing elements, next, and prev arrays to the new arrays
    for (int i = 0; i < capacity; i++) {
        newNext[i] = next[i];
        newPrev[i] = prev[i];
        newElements[i] = elements[i];
    }

    // Initialize the next and prev arrays for the new capacity
    for (int i = capacity; i < newCapacity - 1; i++) {
        newNext[i] = i + 1;
        newPrev[i] = i - 1;
    }

    newNext[newCapacity - 1] = -1;
    newPrev[capacity] = -1;
    newPrev[newCapacity - 1] = capacity - 1;

    // Delete the old arrays
    delete[] next;
    delete[] prev;
    delete[] elements;

    // Assign the new arrays to the member variables
    next = newNext;
    prev = newPrev;
    elements = newElements;

    // Update the firstEmpty index and capacity
    firstEmpty = capacity;
    capacity = newCapacity;
}

//Complexity: theta(1)
ListIterator SortedIndexedList::iterator() {
    // Create and return a ListIterator object for the current SortedIndexedList
    return ListIterator(*this);
}

//Complexity: theta(1)
SortedIndexedList::~SortedIndexedList() {
    // Destructor to deallocate the dynamically allocated arrays
    delete[] next;
    delete[] prev;
    delete[] elements;
}

//best: theta(1) daca e un singur element
//average: theta(n) daca e undeva in lista
//worst: theta(n) daca e ultimul element din lista
//Precondiția:
//Obiectul curent SortedIndexedList pe care se apeleaza functia trebuie sa fie initializat si sa contina cel putin un element
//Obiectul otherList dat ca parametru trebuie sa fie initializat si sa contina cel putin un element
//Elementele din ambele liste trebuie sa fie ordonate crescator

//Postcondiția:

//Toate elementele din obiectul otherList care apar si in obiectul curent SortedIndexedList au fost eliminate din obiectul curent
//Elementele ramase in obiectul curent SortedIndexedList sunt în continuare ordonate crescator
//Numarul total de elemente din obiectul curent SortedIndexedList a fost actualizat în consecinta
void SortedIndexedList::removeAll(const SortedIndexedList& otherList) {
    int currentThis = head;
    int currentOther = otherList.head;
    int previousThis = -1;

    // Parcurgem ambele liste simultan
    while (currentThis != -1 && currentOther != -1) {
        if (elements[currentThis] < otherList.elements[currentOther]) {
            // Daca elementul din lista originala este mai mic decat cel din lista data
            // avansam in lista originala
            previousThis = currentThis;
            currentThis = next[currentThis];
        }
        else if (elements[currentThis] > otherList.elements[currentOther]) {
            // Daca elementul din lista originala este mai mare decat cel din lista data
            // avansam in lista data
            currentOther = otherList.next[currentOther];
        }
        else {
            // Daca elementele sunt egale, eliminam elementul din lista originala
            int toRemove = currentThis;
            currentThis = next[currentThis];

            // Updateaza legaturile elementului precedent din lista originala
            if (previousThis == -1) {
                head = next[toRemove];
            } else {
                next[previousThis] = next[toRemove];
            }

            // Updateaza legaturile elementului urmator din lista originala
            if (next[toRemove] == -1) {
                tail = previousThis;
            } else {
                prev[next[toRemove]] = previousThis;
            }

            // Adauga indicele elementului eliminat în primul spatiu gol disponibil
            next[toRemove] = firstEmpty;
            firstEmpty = toRemove;

            // Scade numarul de elemente din lista originala
            numberOfElements--;
        }
    }
}

//functia removeAll(otherList: SortedIndexedList) {
//    currentThis = head
//    currentOther = otherList.head
//    previousThis = -1
//
//    // Parcurgem ambele liste simultan
//    cat timp (currentThis ≠ -1 ȘI currentOther ≠ -1) {
//        daca (elements[currentThis] < otherList.elements[currentOther]) {
//            // Daca elementul din lista originala este mai mic decat cel din lista data
//            // avansam in lista originala
//            previousThis = currentThis
//            currentThis = next[currentThis]
//        } altfel daca (elements[currentThis] > otherList.elements[currentOther]) {
//            // Daca elementul din lista originala este mai mare decat cel din lista data
//            // avansam in lista data
//            currentOther = otherList.next[currentOther]
//        } altfel {
//            // Daca elementele sunt egale, eliminam elementul din lista originala
//            toRemove = currentThis
//            currentThis = next[currentThis]
//
//            // Updateaza legaturile elementului precedent din lista originala
//            daca (previousThis == -1) {
//                head = next[toRemove]
//            } altfel {
//                next[previousThis] = next[toRemove]
//            }
//
//            // Updateaza legaturile elementului urmator din lista originala
//            daca (next[toRemove] == -1) {
//                tail = previousThis
//            } altfel {
//                prev[next[toRemove]] = previousThis
//            }
//
//            // Adauga indicele elementului eliminat in primul spatiu gol disponibil
//            next[toRemove] = firstEmpty
//            firstEmpty = toRemove
//
//            // Scade numarul de elemente din lista originala
//            numberOfElements--
//        }
//    }
//}