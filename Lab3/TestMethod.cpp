#include <cassert>
#include "ListIterator.h"
#include "SortedIndexedList.h"
#include "TestMethod.h"

bool relation2(TComp e1, TComp e2) {
    if (e1 <= e2) {
        return true;
    }
    else {
        return false;
    }
}

void testRemoveAll() {
    // Create the original list
    SortedIndexedList list = SortedIndexedList(relation2);
    list.add(1);
    list.add(2);
    list.add(3);
    list.add(4);
    list.add(5);

    // Create the other list
    SortedIndexedList otherList = SortedIndexedList(relation2);
    otherList.add(2);
    otherList.add(4);

    // Call the removeAll method
    list.removeAll(otherList);

    // Perform assertions to check the results
    assert(list.size() == 3);
    assert(list.getElement(0) == 1);
    assert(list.getElement(1) == 3);
    assert(list.getElement(2) == 5);
}