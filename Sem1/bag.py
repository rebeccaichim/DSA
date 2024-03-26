from iterator import Iterator

class Bag:
    def __init__(self):
        self.bag=[]
    def add(self,element):
        self.bag.append(element)
    def remove(self,element):
        self.bag.remove(element)
    def search(self,element):
        for el in self.bag:
            if element == el:
                return True
        return False
    def size(self):
        return len(self.bag)
    def nrOccurances(self,element):
        ct=0
        for el in self.bag:
            if el==element:
                ct+=1
        return ct
    def iterator(self):
        if self.bag != []:
            return Iterator(self)
        raise IndexError
