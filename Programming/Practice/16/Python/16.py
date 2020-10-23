import re

ticket = r'a(\w\d\d|\d\w\d|\d\d\w)55661'

n = int(input('n: '))
nums = input('nums: ').split(' ')

bad = []

for num in nums:
   if re.match(ticket, num):
      bad += [num]
      
print(-1 if len(bad) == 0 else ' '.join(bad))
      