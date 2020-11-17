#pragma once

int factorial(int n)
{
   int res = 1;
   for (int i = 1; i < n + 1; i++)
      res *= i;
   return res;
}