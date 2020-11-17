#ifndef COMBINE
#define COMBINE

#include <cmath>
#include "./pragma_factorial.cpp"

int combine(int k, int n)
{
   return factorial(n) / (factorial(k) * factorial(n - k));
}

#endif