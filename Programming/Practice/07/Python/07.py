# Площадь треугольника:
# 1. по 3 точкам
# 2. по 3 сторонам

mode = int(input('Какой формат ввода (1. стороны, 2. координаты):'))

a, b, c = [
   input('A:' if mode == 2 else 'a:'),
   input('B:' if mode == 2 else 'b:'),
   input('C:' if mode == 2 else 'c:')
]

if (mode == 2):
   aC, bC, cC = map(
      lambda el: list(map(float, el.split(' '))), 
      [a, b, c]
   )
   
   a = ((aC[0]-bC[0])**2 + (aC[1]-bC[1])**2)**0.5
   b = ((cC[0]-bC[0])**2 + (cC[1]-bC[1])**2)**0.5
   c = ((aC[0]-cC[0])**2 + (aC[1]-cC[1])**2)**0.5

a, b, c = map(float, [a, b, c])
p = (a+b+c)/2

s = (p*(p-a)*(p-b)*(p-c))**0.5

print(f'Площадь: {s}')
