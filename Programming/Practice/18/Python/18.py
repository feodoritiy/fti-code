# Stupid Sigizmund

words = ['hallo', 'klempner', 'das', 'ist', 'fantastisch', 'fluggegecheimen']
letters = {}

for word in words:
   for letter in word:
      if letter in letters:
         letters[letter] += 1
      else:
         letters[letter] = 1
         
len_letters = len(letters.keys())
for letter in letters.keys():
   letters[letter] /= len_letters

stop_word = input('Стоп слово: ')
res = 1
for letter in stop_word:
   res *= letters[letter]
   
print('Вероятность угадать:', res)
