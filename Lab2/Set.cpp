#include "Set.h" // include the header file for Set
#include "SetIterator.h" // include the header file for SetIterator
#include <iostream> // include the input/output stream library

Set::Set() { // constructor for Set that initializes head.next to nullptr
    head.next = nullptr;
}
//Best case: theta(1) - when the set is empty, and the element can be inserted at the head of the list.
//Average case: O(n) - when the element has to be inserted in the middle of the list or at the end of the list.
//Worst case: theta(n) - when the element has to be inserted at the end of the list.
bool Set::add(TElem e) { // method to add an element to the set
    SLLNode* currentNode = &head; // initialize currentNode to the head of the set
    while (currentNode->next != nullptr && currentNode->next->info < e) { // traverse the set until the end or the first element larger than e
        currentNode = currentNode->next;
    }
    if (currentNode->next != nullptr && currentNode->next->info == e) { // if e is already in the set, return false
        return false;
    }
    SLLNode* newNode = new SLLNode; // create a new node to hold e
    newNode->info = e;
    newNode->next = currentNode->next; // insert the new node in the correct position in the set
    currentNode->next = newNode;
    return true; // return true to indicate that e was added to the set
}
//Best case: theta(1) - when the element to remove is at the head of the list.
//Average case: O(n) - when the element to remove is in the middle of the list or at the end of the list.
//Worst case: theta(n) - when the element to remove is at the end of the list.
bool Set::remove(TElem e) { // method to remove an element from the set
    SLLNode* currentNode = &head; // initialize currentNode to the head of the set
    while (currentNode->next != nullptr && currentNode->next->info < e) { // traverse the set until the end or the first element larger than e
        currentNode = currentNode->next;
    }
    if (currentNode->next != nullptr && currentNode->next->info == e) { // if e is in the set, remove it and return true
        SLLNode* nodeToDelete = currentNode->next;
        currentNode->next = nodeToDelete->next;
        delete nodeToDelete;
        return true;
    }
    return false; // otherwise, return false to indicate that e was not found in the set
}
//Best case: theta(1) - when the element to search for is at the head of the list.
//Average case: O(n) - when the element to search for is located somewhere in the middle of the list or at the end
//Worst case: theta(n) - when the element to search for is at the end of the list or not in the list at all.
bool Set::search(TElem elem) const { // method to search for an element in the set
    SLLNode* currentNode = head.next; // initialize currentNode to the first element of the set
    while (currentNode != nullptr && currentNode->info < elem) { // traverse the set until the end or the first element larger than elem
        currentNode = currentNode->next;
    }
    if (currentNode != nullptr && currentNode->info == elem) { // if elem is in the set, return true
        return true;
    }
    return false; // otherwise, return false to indicate that elem was not found in the set
}
//theta(n)
int Set::size() const { // method to return the size of the set
    int size = 0; // initialize size to zero
    SLLNode* currentNode = head.next; // initialize currentNode to the first element of the set
    while (currentNode != nullptr) { // traverse the set and increment size for each element
        size++;
        currentNode = currentNode->next;
    }
    return size; // return the final value of size
}
//theta(1)
bool Set::isEmpty() const { // method to check if the set is empty
    return head.next == nullptr; // return true if the head of the set is null, false otherwise
}
//theta(n)
Set::~Set() { // destructor for Set that deallocates all nodes in the set
    SLLNode *currentNode = head.next; // initialize currentNode to the first element of the set
    while (currentNode != nullptr) { // traverse the set and deallocate each node
        SLLNode *nodeToDelete = currentNode; // create a pointer to the node to delete
        currentNode = currentNode->next; // move the currentNode pointer to the next node
        delete nodeToDelete; // deallocate the node
    }
}
//theta(1)
SetIterator Set::iterator() const {
    return SetIterator(*this); // return a new SetIterator object initialized with a copy of the current Set object
}