import os, re, time
cls = lambda: os.system('clear' if os.name == 'posix' else 'cls')
cls()

class Console():
   @staticmethod
   def move_cursor(x, y):
      print(f'\033[{y+1};{x+1}f', end='')
   

class FormatString(str):
   END = '\033[0m'
   UP = '\033[1A'
   
   def __init__(self, string) -> None:
      super(str, string)
      
   def _format(self, n):
      return FormatString(f'\033[{n}m' + self + FormatString.END)
   
   @property
   def header(self): 
      return self._format(95)
   @property
   def blue(self): 
      return self._format(94)
   @property
   def cyan(self): 
      return self._format(96)
   @property
   def green(self): 
      return self._format(92)
   @property
   def warning(self): 
      return self._format(93)
   @property
   def fail(self): 
      return self._format(91)
   @property
   def bold(self): 
      return self._format(1)
   @property
   def underline(self): 
      return self._format(4)
   @property
   def normal(self):
      return self
   
class xstr(str):
   TAGS = {
      'bold': 'bold',
      'underline': 'underline',
      'purple': 'header',
      'blue': 'blue',
      'cyan': 'cyan',
      'green': 'green',
      'yellow': 'warning',
      'red': 'fail',
   }
   def __new__(cls, string, *args, **kwargs):
      res = string
      for tag, style in xstr.TAGS.items():
         res = re.sub(f'<{tag}\|'+r'(.*)'+f'>', getattr(FormatString(r'\1'), style), res)
      return super(xstr, cls).__new__(cls, res)
   
   def __init__(self, string: str):
      pass
      
   
class Pos:
   def __init__(self, x: int, y: int):
      self.x = x
      self.y = y
      
   @staticmethod
   def differ(pos1, pos2):
      return Pos(pos1.x-pos2.x, pos1.y-pos2.y)
   
class MazeChar(str):
   def __new__(cls, pattern, *args, **kwargs):
      # explicitly only pass pattern to the str constructor
      return super(MazeChar, cls).__new__(cls, pattern)
   def __init__(self, pattern, style):
      self.style = style
   
class Maze:
   CHARS = {
      'WALL': MazeChar(r'🬀',   'fail'),
      'PLAYER': MazeChar(r'#', 'blue bold'),
      'STEP': MazeChar(r'•',   'normal'),
      'PREV': MazeChar(r'⋅',   'cyan'),
      'EXIT': MazeChar(r'(A|B|C|D|E|F|G)',    'green bold'),
      'REACHED': MazeChar(r'(a|b|c|d|e|f|g)', 'blue bold'),
   }
   
   def __init__(self, pattern: str):
      pattern = pattern.strip().replace('#', Maze.CHARS['WALL'])
                                        
      self.pattern = pattern.split('\n')
      self.width = pattern.index('\n')
      self.height = pattern.count('\n')
      
      self.formated_pattern = ''
      
      self.player_x = 0
      self.player_y = 0
      
      
   def _put(self, x: int, y: int, char: str):
      row = list(self.pattern[y])
      row[x] = char
      self.pattern[y] = ''.join(row)
      Console.move_cursor(x, y)
      char = self._format_char(char)
      print(char)
      
   def _take(self, x: int, y: int):
      return self.pattern[y][x]
      
      
   def _format_single(self, source: str, char: str, format: str):
      format = format.split(' ')
      formated = FormatString(r'\1' if char[0] == '(' else char)
      for style in format: 
         formated = getattr(formated, style)
      source = re.sub(char, formated, source)
      return source
   
   def _format(self):
      source = '\n'.join(self.pattern)
      f = self._format_single
      res = source
      for char in Maze.CHARS.values():
         res = f(res, char, char.style)
      self.formated_pattern = res
      
   def _format_char(self, char: str):
      f = self._format_single
      res = char
      for char in Maze.CHARS.values():
         res = f(res, char, char.style)
      return res
      
   
   def move_cursor_down(self):
      Console.move_cursor(0, self.height+2)
   
   def render(self):
      cls()
      self._format()
      undo_print = '\r' * self.height
      print(self.formated_pattern, end=undo_print)
      
   
   def player(self, x: int, y: int):
      pos_type = self._check_pos(Pos(x, y))
      if (pos_type != 'free'):
         return False
      
      self._put(x, y, Maze.CHARS['PLAYER'])
      
      self.player_x = x
      self.player_y = y
      
      return True
      
   def step(self, x: int, y: int):
      self._put(x, y, Maze.CHARS['STEP'])
      
      
   def _check_pos(self, pos: Pos):
      pattern = self.pattern
      
      if (pos.x < 0 or pos.y < 0 or 
          pos.x > self.width or pos.y > self.height):
         return False
      
      char = pattern[pos.y][pos.x]
      def char_is(target):
         return re.match(target, char)
      
      if char_is(Maze.CHARS['WALL']): return 'wall'
      elif (char_is(Maze.CHARS['EXIT']) or
           char_is(Maze.CHARS['REACHED'])): return 'exit'
      elif char_is(Maze.CHARS['PLAYER']): return 'player'
      elif char_is(Maze.CHARS['PREV']): return 'step'
      elif char_is(Maze.CHARS['STEP']): return 'prev'
      else: return 'free'
      
   
   def waterfall(self):
      exits = {}
      
      def make_steps(i, ways):
         nonlocal exits
         
         way = ways[i]
         addon = []
         
         for direction in [Pos(1,0), Pos(-1,0), Pos(0,1), Pos(0,-1)]:
            new_pos = Pos.differ(way, direction)
            new_pos_type = self._check_pos(new_pos)
            if new_pos_type is 'free':
               addon += [new_pos]
               self.step(new_pos.x, new_pos.y)
            elif new_pos_type is 'prev':
               self._put(new_pos.x, new_pos.y, Maze.CHARS['PREV'])
            elif new_pos_type is 'exit':
               exit = self._take(new_pos.x, new_pos.y)
               self._put(new_pos.x, new_pos.y, exit.lower())
               exits[exit.upper()] = True
               
         ways += addon
         return addon if ( len(addon) > 0 ) else False
               
      
      ways = [Pos(self.player_x, self.player_y)]
      resume = []
      
      while True:
         for i in range(len(ways)):
            is_steps = make_steps(i, ways)
            resume += [is_steps]
         
         if (all(not r for r in resume)):
            return list(exits.keys())
         
         
         resume = []
         time.sleep(0.08)
            
      

maze = """
####B######################
# #       #   #      #    #
# # # ###### #### ####### #
# # # #       #   #       #
#   # # ######### # ##### #
# # # #   #       #     # #
### ### ### ############# #
# #   #     # #           #
# # #   ####### ###########
# # # #       # #         C
# # ##### ### # # ####### #
# # #     ### # #       # #
#   ##### ### # ######### #
######### ### #           #
# ####### ### #############
A           #   ###   #   #
# ############# ### # # # #
# ###       # # ### # # # #
# ######### # # ### # # # F
#       ### # #     # # # #
# ######### # ##### # # # #
# #######   #       #   # #
# ####### ######### #######
#         #########       #
#######E############D######
"""
maze = Maze(maze)
maze.render()
maze.move_cursor_down()

print(xstr('Добро пожаловать в <blue|Лабиринт> от <purple|frity corp.>'))
s = xstr('Введите координаты игрока <yellow|(x y)>: ')
x, y = map(int, input(s).split(' '))

player = maze.player(x-1, y-1)
maze.render()
if (not player):
   maze.move_cursor_down()
   print(xstr('<red|Ошибка:> Не верные координаты'))
   exit()

exits = maze.waterfall()
exits = ' '.join(exits)
Console.move_cursor(0, maze.height+2)
print(xstr(f'Найдены выходы: <purple|{exits}>'))