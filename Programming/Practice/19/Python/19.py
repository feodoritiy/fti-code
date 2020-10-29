pass_len, pass_letters = [input(f'{name}: ') for name in ['password length', 'password letters']]
pass_len = int(pass_len)
passwords = ['']
new_passwords = []

for i in range(pass_len):
   for password in passwords:
      for letter in pass_letters:
         new_passwords += [password + letter]
   passwords = new_passwords; new_passwords = []

for password, i in zip(passwords, range(len(passwords))):
   if (not all( # all pass_letters in password
      [letter in password for letter in pass_letters]
   )):
      del passwords[i]

print(' '.join(passwords))