a, n = [int(input(f'{s}: ')) for s in ['Число', 'Степень']]
res = 1

for i in range(n):
   res *= a

print(res)