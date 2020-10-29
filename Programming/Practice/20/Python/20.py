class SingleAlko:
   def __init__(self, name, price, capacity):
      self.name = name
      self.price = int(price)
      self.v = int(capacity)

money = int(input('Ваш баланс: '))
alko_num = int(input('Сколько типов алкоголя?: '))

alko_arr = []
alko_v_arr = []

for i in range(alko_num):
   alko_data = input(': ').split(' ')
   alko = SingleAlko(*alko_data)
   alko_arr += [alko]
   alko_v_arr += [ alko.v * (money // alko.price) ]
   
max_v = max(alko_v_arr)
target = alko_arr[alko_v_arr.index(max_v)]

n = money // target.price

if not n:
   print(-1)
else:
   print(f'{target.name} {n}')
   print(n * target.v)
   print(money - n * target.price)
   
