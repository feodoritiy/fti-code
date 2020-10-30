# Stupid Sigizmund

words = ['hallo', 'klempner', 'das', 'ist', 'fantastisch', 'fluggegecheimen']

meet = {}

for word in words:
   for letter in word:
      if letter in meet:
         meet[letter] += 1
      else:
         meet[letter] = 1
         
total_letters = len(''.join(words))

stop_word = input('Стоп слово: ')
res = 1 / (total_letters ** len(stop_word))
print(meet)
for letter in stop_word:
   res *= meet[letter]
   
print('Вероятность угадать:', res)
