#include <assert.h>
#include "Matrix.h"
#include "Iterator.h"

void testAll() {
    Matrix m(4, 4);
    assert(m.nrLines() == 4);
    assert(m.nrColumns() == 4);
    m.modify(1, 1, 5);
    assert(m.element(1, 1) == 5);
    m.modify(1, 1, 6);
    assert(m.element(1, 2) == NULL_TELEM);

    // Test iterator
//    Iterator<int> it(&m);
//
//    // Test nextRow()
//    assert(it.valid());
//    assert(it.getCurrent() == 6);
//    it.nextRow();
//    assert(it.valid());
//    assert(it.getCurrent() == NULL_TELEM);
//
//    // Test nextColumn()
//    it.nextColumn();
//    assert(it.valid());
//    assert(it.getCurrent() == NULL_TELEM);
//    it.nextColumn();
//    assert(!it.valid());
//
//    // Test getCurrent() after reaching the end
//    assert(it.getCurrent() == NULL_TELEM);
}
