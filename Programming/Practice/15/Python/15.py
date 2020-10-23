import random, time

print('frity production 23.10.2020\n===========================')

while True:

   random.seed(time.time())
   n = random.randrange(0, 100)
   
   for i in range(5):
      u = int(input(f'Введите ваше число ({i+1}/5): '))
      
      if (u < n): print('Загаданное число БОЛЬШЕ')
      elif (u > n): print('Загаданное число Меньше')
      else: 
         print('Поздравляю! Вы угадали')
         break
   else:
      print(f'Вы проиграли. Было загадано: {n}')
   
   if (input('Играем снова? (1 - Да): ') != '1'):
      break
