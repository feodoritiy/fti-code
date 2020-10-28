class Stats:
   def __init__(self):
      self.rounds = []
      self.total = range(0, 37)
      self.red_num = 0
      self.black_num = 0
      self.games = 0
      self.is_k12 = False
      self.red_black_cleaner=None # 'red' or 'black'
      
      self.games = [] # max_len = 12, [int]
      
      
   def _is_red(self, num):
      return num in [1, 3, 5, 7, 9, 12, 14, 16, 18, 19, 21, 23, 25, 27, 30, 32, 34, 36]
   
   def _games_max(self):
      unique = list(dict.fromkeys(self.games))
      rates = []
      
      for num in unique:
         rates += [self.games.count(num)]
         
      state = list(zip(unique, rates))
      state.sort(key=lambda r: r[1])
      state.reverse()
      
      max_rate = state[0][1]
      for num, i in zip(state, range(len(state))):
         if (max_rate > num[1]):
            state = state[:i]
            break            
         
      state = list(map(lambda n: n[0], state))
      state.sort()
      
      return state
   
   def _not_dropped_out (self):
      diff = [num for num in self.total if num not in self.games]
      diff.sort()
      return diff
   
   
   def add_game(self, num):
      len_games = len(self.games)      
      self.games += [num]
      if self.is_k12 or len_games > 11: 
         self.is_k12 = True
         
         is_red_remove = self._is_red(self.games[0])
         if is_red_remove: self.red_num -= 1
         else: self.black_num -= 1
         
         self.games = self.games[1:]
   
   
   def input(self):
      num = int(input('Новое число: '))
      if (num < 0): return False
      
      self.add_game(num)
      
      is_red = self._is_red(num)
      if is_red: self.red_num += 1
      else: self.black_num += 1
         
      return True
      
   def output(self):
      def spaced(arr): 
         arr = list(map(str, arr))
         return ' '.join(arr)
      
      print('----------------')
      print(f'За последние {len(self.games)} игр')
      print(f'Чаще всего выпадали: \n{spaced(self._games_max())}')
      print(f'Не выпадали: \n{spaced(self._not_dropped_out())}')
      print(f'К:{self.red_num}  Ч:{self.black_num}\n')
      
   def run(self):
      while True:
         if not self.input(): break
         self.output()
      
      print('До связи (frity corp.)')
      
      
      
stats = Stats()
stats.run()
      