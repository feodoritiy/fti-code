while True:
   try: 
      a, op, b = input('Введите действие: ').split(' ')
      a, b = map(float, [a, b])
      
      res = None
      
      if (op == '+'): res = a + b
      elif (op == '-'): res = a - b
      elif (op == '*'): res = a * b
      elif (op == '/'): res = a / b
      else: print(f'Неизвестная операция: {op}')
      
      if (not res is None):
         print(f'Результат: {res}')
      
   except ValueError as error:
      print('Ошибка: некорректный формат ввода операции. Используйте формат: число оператор число. Например: 1.2 + 5')
   
   except ZeroDivisionError as error:
      print('Ошибка: деление на 0')
      
   if (input('Вычислить снова?: ') != 'yes'):
      break
