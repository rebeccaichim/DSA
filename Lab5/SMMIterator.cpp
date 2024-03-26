#include "SMMIterator.h"
#include "SortedMultiMap.h"
#include <iostream>

// Traverse the sorted binary search tree in DFS order (left - root - right) and add the elements to an array
// Best case: Theta(1), Worst case: Theta(n), Average case: Theta(n)
void SMMIterator::DFS(Node *node)
{
    if (node == NULL)
        return;

    this->DFS(node->left);

    for (int i = 0; i < node->size; ++i)
        this->elements[this->numberOfElements++] = TElem(node->key, node->values[i]);

    this->DFS(node->right);
}
// Constructs an iterator for the SortedMultiMap
// Best case: Theta(1), Worst case: Theta(n), Average case: Theta(n)
SMMIterator::SMMIterator(const SortedMultiMap &d) : map(d)
{
    this->capacity = this->map.sizeOfBST;
    this->elements = new TElem[this->capacity];
    this->currentElement = 0;
    this->numberOfElements = 0;
    this->DFS(this->map.root);
}
// Sets the iterator to the first element of the collection
// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
void SMMIterator::first()
{
    this->currentElement = 0;
}

// Moves the iterator to the next element in the collection
// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
void SMMIterator::next()
{
    if (!this->valid())
        throw std::exception();
    this->currentElement++;
}
// Checks if the iterator is still valid (there are more elements to iterate over)
// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
bool SMMIterator::valid() const
{
    return this->currentElement < this->numberOfElements;
}
// Returns the current element of the iterator
// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
TElem SMMIterator::getCurrent() const
{
    if (!this->valid())
        throw std::exception();
    return this->elements[this->currentElement];
}
// Destructor for the SMMIterator class
// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
SMMIterator::~SMMIterator()
{
    delete[] this->elements;
}

// Best case: Theta(1), Worst case: Theta(1), Average case: Theta(1)
TElem SMMIterator::getPrevious() const
{
    if (this->previousElement == -1)
        throw std::exception();

    return this->elements[this->previousElement];
}


