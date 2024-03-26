#pragma once
#include "SortedMap.h"


class SMIterator{
    friend class SortedMap;
private:
    const SortedMap& map;
    SMIterator(const SortedMap& mapionar);

    int index;

public:
    void first();
    void next();
    bool valid() const;
    TElem getCurrent() const;
};