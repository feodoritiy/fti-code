import os, re
from typing import Pattern
cls = lambda: os.system('clear' if os.name == 'posix' else 'cls')
cls()

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
   
class Pos:
   def __init__(self, x: int, y: int):
      self.x = x
      self.y = y
      
   @staticmethod
   def differ(pos1, pos2):
      return Pos(pos1.x-pos2.x, pos1.y-pos2.y)
   
class Maze:
   WALL = r'🬀'
   PLAYER = r'#'
   STEP = r'⋅'
   EXIT = r'(A|B|C|D|E|F|G)'
   REACHED = r'(a|b|c|d|e|f|g)'
   
   def __init__(self, pattern: str):
      pattern = pattern.strip().replace('#', Maze.WALL)
                                        
      self.pattern = pattern.split('\n')
      self.width = pattern.index('\n')
      self.height = pattern.count('\n')
      
      self.formated_pattern = ''
      
      self.player_x = 0
      self.player_y = 0
      
      
   def _move_cursor(self, x, y):
      print(f'\033[{y};0H')
      formated = self._format_source(self.pattern[y][:x])
      print(formated, end='')
      
      
   def _put(self, x: int, y: int, char: str):
      row = list(self.pattern[y])
      row[x] = char
      self.pattern[y] = ''.join(row)
      self._move_cursor(x, y)
      print(char)
      
   def _take(self, x: int, y: int):
      return self.pattern[y][x]
      
      
   def _format_single(self, char: str, format: str, need_return=False):
      format = format.split(' ')
      formated = FormatString(r'\1' if char[0] == '(' else char)
      for style in format: 
         formated = getattr(formated, style)
      formated = re.sub(char, formated, (need_return or self.formated_pattern))
      if (need_return):
         return formated
      else:
         self.formated_pattern = formated
   
   def _format(self):
      self.formated_pattern = '\n'.join(self.pattern)
      f = self._format_single
      f(Maze.WALL,    'fail')
      f(Maze.PLAYER,  'blue bold')
      f(Maze.EXIT,    'green bold')
      f(Maze.STEP,    'cyan')
      f(Maze.REACHED, 'blue bold')
      
   def _format_source(self, source):
      formated = source
      f = self._format_single
      
      formated = f(Maze.WALL,    'fail'      , formated)
      formated = f(Maze.PLAYER,  'blue bold' , formated)
      formated = f(Maze.EXIT,    'green bold', formated)
      formated = f(Maze.STEP,    'cyan'      , formated)
      formated = f(Maze.REACHED, 'blue bold' , formated)
      
      return formated
   
   def render(self):
      #cls()
      self._format()
      undo_print = '\r' * self.height
      print(self.formated_pattern, end=undo_print)
      
   
   def player(self, x: int, y: int):
      self._put(x, y, Maze.PLAYER)
      self.player_x = x
      self.player_y = y
      
   def step(self, x: int, y: int):
      self._put(x, y, Maze.STEP)
      
      
   def _check_pos(self, pos: Pos):
      pattern = self.pattern
      
      if (pos.x < 0 or pos.y < 0 or 
          pos.x > self.width or pos.y > self.height):
         return False
      
      char = pattern[pos.y][pos.x]
      def char_is(target):
         return re.match(target, char)
      
      if char_is(Maze.WALL): return 'wall'
      elif char_is(Maze.EXIT) or char_is(Maze.REACHED): return 'exit'
      elif char_is(Maze.PLAYER): return 'player'
      elif char_is(Maze.STEP): return 'step'
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
            return exits.keys()
         
         resume = []
               
            
      

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
maze.player(4, 1)

#maze.step(3, 1)
#maze.step(5, 1)
exits = maze.waterfall()
print(exits)