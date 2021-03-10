def create(array_length, array_first_el, array_step):
   return [array_first_el + i*array_step for i in range(array_length)]

def sort(array):
   return sorted(array)

_print = print
def print(array):
   return _print(array)

size = int(input('Array size: '))
first_el = int(input('First element: '))
step = int(input('Step: '))

arr = create(size, first_el, step)
arr = sort(arr)
print(arr)
