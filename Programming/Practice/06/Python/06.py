# Решение линейных уравнений

import math
    
a, b, c = map(float, [
   input('a:'), 
   input('b:'),
   input('c:')
])
res = 0

if (a == 0):
   res = -c / b
else:
   descr = math.sqrt(b*b - 4*a*c)
   res = [
      (-b + descr) / 2*a,
      (-b - descr) / 2*a
   ]

print(res)