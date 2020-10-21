# Встреча: состоиться или нет

time1, time2 = map(
   lambda time: list(map(int, time.split(':'))),
   [ input('Первое время:'),
      input('Второе время:') ]
)

num1 = time1[0]*60 + time1[1]
num2 = time2[0]*60 + time2[1]

print('Встреча состоится' if abs(num1 - num2) <= 15 else 'Встреча не состоится')