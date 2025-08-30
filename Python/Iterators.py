class SquareIterator:
   def __init__(self, sequence):
      self._index = 0
      self._seq = sequence

   def __iter__(self):
      return self
   
   def __next__(self):
      if self._index < len(self._seq):
         sq = self._seq[self._index] ** 2
         self._index += 1
         return sq
      else:
         raise StopIteration
      

if __name__ == '__main__':
   for sq in SquareIterator([1,2,3,4,5]):
      print(sq)
