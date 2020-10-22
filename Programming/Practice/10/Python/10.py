# x1, x2 = s : x1~[l1..r1], x2~[l2..r2]

sum, left1, right1, left2, right2 = map(int, input('s l1 r1 l2 r2: ').split(' '))

width1 = right1 - left1
width2 = right2 - left2

posible_x2 = sum - left1
if (posible_x2 > right2): # more then diaoasone 2
   distance_to_right = posible_x2 - right2
   if (distance_to_right <= width1): # solution exist
      x1 = left1 + distance_to_right
      x2 = right2
      print(x1, x2)
   else: # no solution
      print(-1)
elif (posible_x2 < left2): # less then diapasone 2
   distance_to_left = left2 - posible_x2
   if (distance_to_left <= width1): # solution exist
      x1 = left1 + distance_to_left
      x2 = left2
      print(x1, x2)
   else: # no solution
      print(-1)
else:
   print(left1, posible_x2)
   