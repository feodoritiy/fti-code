n = int(input('Число для проверки на простоту: '))

def is_prime(number):
   if number % 2 == 0:
      return number == 2
   divider = 3
   while divider * divider <= number and number % divider != 0:
      divider += 2
   return divider * divider > number

print('Число', 'ПРОСТОЕ.' if is_prime(n) else 'составное.')
   
