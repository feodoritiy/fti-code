from random import randint
from math import sqrt
from multipledispatch import dispatch # pip install multipledispatch

def sort(arr, isAsc = True):
   sorted = False # Считаем что не отсортировано

   while not sorted:
      # two rand elements
      index1 = randint(0, len(arr) - 1)
      index2 = randint(0, len(arr) - 1)

      # swap
      arr[index2], arr[index1] = arr[index1], arr[index2]

      # check sorted
      sorted = True
      for i in range(1, len(arr)):
         if ((arr[i-1] > arr[i]) if( isAsc )else (arr[i - 1] < arr[i])):
            # if sequence bad break and False
            sorted = False
            break

   return arr


@dispatch(list, bool)
def BozoSort(arr, isAsc):
   res = None
   if (type(arr[0]) == list):
      # square
      linear = []
      rows = len(arr)
      cols = rows
      for i in range(rows):
         for j in range(cols):
            linear += [ arr[i][j] ]
      res = sort(linear, isAsc)
   else:
      # linear
      res = sort(arr, isAsc)
   
   print(*res)


@dispatch(int, int, int, bool)
def BozoSort(a, b, c, isAsc):
   print(*sort([a,b,c], isAsc))


arrLen = int(input('Введите длинну одномерного массива: '))
arrLenSqrt = int(sqrt(arrLen))
arr = list(map(int, input('Введите массив через пробел: ').split(' ')))

linear = arr

int1 = arr[0]
int2 = arr[1]
int3 = arr[2]

square = []
for i in range(arrLenSqrt):
   square += [[]]
   for j in range(arrLenSqrt):
      square[i] += [ linear[i * arrLenSqrt + j] ]
   
BozoSort(linear, True)
BozoSort(linear, False)

BozoSort(square, True)
BozoSort(square, False)

BozoSort(int1, int2, int3, True)
BozoSort(int1, int2, int3, False)
