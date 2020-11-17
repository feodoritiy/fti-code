#ifndef TEILOR
#define TEILOR

#include <cmath>
#include "./pragma_factorial.cpp"

double teilor(double x, int k)
{
   double res = 0;

   for (int i = 0; i < k; i++)
      res += std::pow(-1, i) * std::pow(x, 2 * i + 1) / factorial(2 * i + 1);

   return res;
}

#endif