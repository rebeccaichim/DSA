class Iterator:
    def __init__(self,cnt):
        self.cnt=cnt
        if self.cnt.bag==[]:
            self.i=-1
        else:
            self.i=0
    def valid(self):
        if self.i < 0 or self.i > self.cnt.size():
            return False
        return True
    def first(self):
        if self.cnt.bag == []:
            return -1
        else:
            return 0
    def next(self):
        if self.valid():
            self.i+=1
            return self.i
            #if not self.valid(bag)
                #raise IndexError
        raise IndexError
    def getCurrent(self):
        if self.valid():
            return self.cnt.bag[self.i]
