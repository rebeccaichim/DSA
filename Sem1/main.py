from bag import Bag

b1=Bag()
for i in range(3,7):
    b1.add(i)
b1.add(6)

assert b1.bag == [3,4,5,6,6]

b1.remove(4)
assert b1.bag == [3,5,6,6]

assert b1.search(4) == False

assert b1.size() == 4

assert b1.nrOccurances(6) == 2

iterated_bag = b1.iterator()
assert iterated_bag.valid() == True
assert iterated_bag.first() == 0 #prima pozitie

iterated_bag.next()
assert iterated_bag.i == 1
assert iterated_bag.getCurrent() == 5