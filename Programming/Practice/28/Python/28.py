def print_factorization(n: int) -> None:
   ans = [] # list for data storage
   i = 2
   while (i * i < n): # for i < sqrt(n)
      if (n % i == 0): # if i is divider
         ans += [[i, 0]]; # add i to storage
         while n % i == 0: # and remove all i multipliers from current n
            n //= i # removing single i
            ans[len(ans)-1][1] += 1 # updating counter (on last pair)
      i += 1
   if n > 1: # if n has dividers differ from 1
      ans += [[n, 1]] # add n as divider one time
      
   sorted(ans, key=lambda pair: pair[0])
   
   i = 0
   for divider, count in ans:
      spec_char = '' if( i == 0 )else '*'; i += 1
      if count > 1:
         print(f'{spec_char}{divider}^{count}', end='')
      else:
         print(f'{spec_char}{divider}', end='')


n = int(input("Введите число: ")) # number to be factorized
print_factorization(n)
