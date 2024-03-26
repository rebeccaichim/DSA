#pragma once
#include "Set.h"

class SetIterator
{
    //DO NOT CHANGE THIS PART
    friend class Set;
private:
    //DO NOT CHANGE THIS PART
    const Set& set;
    SetIterator(const Set& s);

    //TODO - Representation
    SLLNode *currentElement;
    SLLNode *prevElement; // Adaugam un nou membru pentru a tine evidenta elementului anterior

public:
    void first();
    void next();
    void previous(); // Declaram metoda previous
    TElem getCurrent();
    bool valid() const;
};
