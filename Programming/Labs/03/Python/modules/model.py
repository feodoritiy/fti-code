from random import randint
from .view import View, Pos, ViewCell



class ModelField(list):
   def __init__(self, field: list):
      self.field = field
      
      size = len(field)
      
      def get_square_diag(square_shift_x, square_shift_y, square_size, reversed = False):
         nonlocal field
         
         diag = []
         for i in range(square_size): # main main diag
            if not reversed:
               zx = i
               zy = i
            else:
               zx = square_size - 1 - i
               zy = i
            diag.append(field[square_shift_y + zy][square_shift_x + zx])
            
         return diag
      
      rows = field
      
      cols = [[] for cell in field[0]]
      for row in field:
         i = 0
         for cell in row:
            cols[i].append(cell)
            i += 1
            
      main_diags = []
      main_diags.append(get_square_diag(0, 0, size))
      for i in range(5, size): # paired main diags
         k = size - i
         main_diags.append(get_square_diag(k, 0, i))
         main_diags.append(get_square_diag(0, k, i))
      
      sub_diags = []
      sub_diags.append(get_square_diag(0, 0, size, True))
      for i in range(5, size): # paired sub diags
         k = size - i
         sub_diags.append(get_square_diag(k, k, i, True))
         sub_diags.append(get_square_diag(0, 0, i, True))
         
         
      self.rows = rows
      self.cols = cols
      self.main_diags = main_diags
      self.sub_diags = sub_diags
      


class Model:
   def __init__(self, view: View):
      self.view = view
      self.state = 'Шарик не выбран'
      self.selected = None
      self.score = 0
      self.lines = 0
      self.field = ModelField(view.field)
      
      self.restart()
      
      view.aside.controls.new_game.bind('<Button-1>', self.restart)
      view.aside.controls.step.bind('<Button-1>', self.step)
      
      for row in self.view.field:
         for cell in row:
            cell.on_click_handler = self._cell_click_handler
      
      
   def run_debug(self):
      
      if self._debug_has('md'):
         main_diags = self.field.main_diags
         
         for line, i in zip(main_diags, range(len(main_diags))):
            for cell in line:
               if cell.is_free:
                  cell.config(text=str(i), image='', width=7, height=4)
               else:
                  fg = None
                  if (cell.ball_tile == self.view.tiles.ball_aqua): fg='aqua'
                  if (cell.ball_tile == self.view.tiles.ball_blue): fg='blue'
                  if (cell.ball_tile == self.view.tiles.ball_red): fg='red'
                  if (cell.ball_tile == self.view.tiles.ball_pink): fg='pink'
                  if (cell.ball_tile == self.view.tiles.ball_yellow): fg='yellow'
                  if (cell.ball_tile == self.view.tiles.ball_violet): fg='violet'
                  if (cell.ball_tile == self.view.tiles.ball_green): fg='green'
                  cell.config(text=str(i), image='', width=7, height=4, foreground=fg)
      
   def restart(self, event = None):
      self.view.game_over_visibility = False
      self._clear_field()
      self.gen_hint()
      self.step()
      self.view.aside.info.update_score(0)
      self.view.aside.info.update_lines(0)
      self.state = 'шарик не выбран'
      
   def step(self, event = None):
      if self.state == 'игра окончена': return
      self.use_hint()
      self.gen_hint()
      
      
   def gen_hint(self):
      balls = []
      for i in range(3):
         balls.append(self._random_ball())
      self.view.aside.hint.update(balls)
   
   def use_hint(self):
      hint = self.view.aside.hint
      
      free = self._field_free_cells()
      print('free count:', len(free))
      
      for i in range(2, -1, -1):
         if len(free)-i <= 1: # if free cells less then hint count
            self.state = 'завершение игры'
            self.game_over()
            return
         else:
            cell = self._random_from(free)
            cell.put_ball(hint.model[i])
            free.pop()
            
            
   def game_over(self):
      
      print('GAME OVER')
      self.view.game_over_visibility = True
      self.state = 'игра окончена'
            
            
   def _debug_has(self, value):
      return value in self.view.aside.info.get_debug().split(';')
   
   
   def _random_from(self, list_of):
      return list_of[randint(0, len(list_of)-1)]         
         
   def _random_ball(self):
      tiles = self.view.tiles
      balls = [
         tiles.ball_aqua,
         tiles.ball_blue,
         tiles.ball_green,
         tiles.ball_pink,
         tiles.ball_red,
         tiles.ball_violet,
         tiles.ball_yellow
      ]
      
      return self._random_from(balls)
   
         
   def _field_free_cells(self):
      free = []
      field = self.view.field
      for row in field:
         for cell in row:
            if cell.is_free:
               free.append(cell)
      return free
   
   def _clear_field(self):
      field = self.view.field
      
      for row in field:
         for cell in row:
            cell.clear()
   
      
   def _cell_click_handler(self, cell: ViewCell, event):
      self.run_debug()
      
      if cell.is_free:
         # free cell
         if self.state == 'шарик не выбран':
            pass
         elif self.state == 'шарик выбран':
            reachable = self._cells_reachable(self.selected, cell)
            
            if reachable: # cell is reachable
               cell.put_ball(self.selected.ball_tile)
               
               self.selected.unselect_ball()
               self.selected.clear()
               self.selected = None
               
               self.state = 'шарик перемещён'
               
               lines = self._check_all_lines()
               
               for line in lines:
                  self.lines += 1
                  self.view.aside.info.update_lines(self.lines)
                  
                  for cell in line:
                     cell.unselect_ball()
                     cell.clear()
                     
                     self.score += 2
                     self.view.aside.info.update_score(self.score)
                     
               self.state = 'шарик не выбран'
               
               if not self._debug_has('god'):
                  if len(lines) == 0:
                     self.step()
               
            else: # cell is unreachable
               pass
      else:
         # ball
         if self.state == 'шарик не выбран':
            self.state = 'шарик выбран'
            self.selected = cell
            cell.select_ball()
         elif self.state == 'шарик выбран':
            self.selected.unselect_ball()
            self.selected = cell
            cell.select_ball()
            
   
   def _cells_reachable(self, a: ViewCell, b: ViewCell, print_check_way = False):
      
      def reset_cells_prev():
         field = self.view.field
         for row in field:
            for cell in row:
               cell.is_prev = False
      
      def step_all_directions(from_cell: ViewCell, target: ViewCell):
         steps = []
      
         left = Pos(1,0)
         right = Pos(-1,0)
         up = Pos(0,1)
         down = Pos(0,-1)
         for direction in [up, down, left, right]:
            print('direction:', direction.x, direction.y)
            sibling = from_cell.sibling_in(direction)
            
            if not sibling:
               continue
            
            if sibling == target:
               return True
            else:
               if sibling.is_free and not sibling.is_prev:
                  sibling.is_prev = True
                  if print_check_way:
                     sibling._blend_bg_ball(1, self.view.tiles.ball_yellow, 6)
                  steps.append(sibling)
                  print('> add step')
                  
               elif sibling.is_free and sibling.is_prev:
                  if print_check_way:
                     sibling._blend_bg_ball(1, self.view.tiles.ball_green, 6)
                  print('> is prev')
                  
               elif not sibling.is_free:
                  print('> is Ball')
                  
         return steps
      
      
      steps = [a]
      
      while True:
         print('steps count:', len(steps))
         new_steps_storage = []
         
         for step in steps:
            print('\nstep:', step.pos.x, step.pos.y)
            new_steps = step_all_directions(step, b)
            
            if new_steps is True: # found
               print('FOUND')
               reset_cells_prev()
               return True
            else: # steps made
               new_steps_storage += new_steps
         
         if len(new_steps_storage) == 0: # no new steps
            print('NO STEPS')
            reset_cells_prev
            return False
         steps = new_steps_storage
      
   def _check_all_lines(self):
      
      def check_lines(lines):
         sequences = []
      
         for line in lines:
            sequence = []
            prev_color = None
            
            def reset_sequence(color, cell = None):
               nonlocal sequence, prev_color
               
               if len(sequence) > 4:
                  sequences.append(sequence)
               
               prev_color = color
               sequence = [cell] if cell else []
               
            
            for cell in line:
               if cell.is_free:
                  reset_sequence(None)
                  continue
               
               else:
                  curr_color = cell.ball_tile
                  
                  if prev_color == None:
                     reset_sequence(curr_color, cell)
                     
                  elif curr_color == prev_color:
                     sequence.append(cell)
                     
                  else: # prev_color and curr_color != prev_color
                     reset_sequence(curr_color, cell)
                     
            reset_sequence(None)
            
         return sequences
      
      lines = []
      lines += check_lines(self.field.rows)
      lines += check_lines(self.field.cols)
      lines += check_lines(self.field.main_diags)
      lines += check_lines(self.field.sub_diags)
      
      # <DEBUG>
      
      if len(lines) > 0:
         print(f'\n\n{len(lines)} LINES!!!!!!!!!!!!!!!!!!!')
         
      # </DEBUG>
      
      return lines