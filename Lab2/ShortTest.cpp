#include "ShortTest.h"
#include <assert.h>
#include "Set.h"
#include "SetIterator.h"
#include <iostream>

void testAll() {
    Set s;
    assert(s.isEmpty() == true);
    assert(s.size() == 0);
    assert(s.add(5)==true);
    assert(s.add(1)==true);
    assert(s.add(10)==true);
    assert(s.add(7)==true);
    assert(s.add(1)==false);
    assert(s.add(10)==false);
    assert(s.add(-3)==true);
    assert(s.size() == 5);
    assert(s.search(10) == true);
    assert(s.search(16) == false);
    assert(s.remove(1) == true);
    assert(s.remove(6) == false);
    assert(s.size() == 4);

    SetIterator it = s.iterator();
    it.first();
    int sum = 0;
    while (it.valid()) {
        TElem e = it.getCurrent();
        sum += e;
        it.next();
    }
    assert(sum == 19);

//    // Teste pentru metoda previous()
//    it.first();
//    it.previous(); // se așteaptă o excepție deoarece nu putem să mergem înainte de primul element
//    try {
//        it.previous();
//        assert(false); // trebuie să aruncăm o excepție, deci nu trebuie să ajungem aici
//    }
//    catch (std::runtime_error&) {
//        assert(true);
//    }
//    while (it.valid() && it.getCurrent() != 10) {
//        it.next(); // mutăm iteratorul la ultimul element
//    }
//    assert(it.getCurrent() == 10);
//    it.previous(); // mergem la elementul anterior
//    assert(it.getCurrent() == 7);
//    it.previous(); // mergem la elementul anterior
//    assert(it.getCurrent() == 5);
//    it.previous(); // mergem la elementul anterior
//    assert(it.getCurrent() == -3);
//    it.previous(); // mergem la elementul anterior
//    assert(it.getCurrent() == -3); // nu putem să mergem înainte de primul element, deci rămânem la același element
}