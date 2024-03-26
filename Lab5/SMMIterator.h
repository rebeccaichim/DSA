#pragma once

#include "SortedMultiMap.h"

class SMMIterator
{
    friend class SortedMultiMap;

private:
    const SortedMultiMap& map;
    TElem* elements;
    int currentElement;
    int previousElement;
    int numberOfElements;
    int capacity;

    void DFS(Node* node);

public:
    SMMIterator(const SortedMultiMap& map);
    void first();
    void next();
    void previous();
    bool valid() const;
    TElem getCurrent() const;
    TElem getPrevious() const;
    ~SMMIterator();
};
