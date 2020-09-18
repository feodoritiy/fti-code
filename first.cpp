#include <iostream>
#include <string>

using namespace std;

// api for pretty print
void header();
void description(char message[]);
// write line
void wl(char message[]);
void wl(int message);
void wl(double message);

void task1()
{
  description("Посчитать 2+2*2");
  cout << "\"Результат выражения 2+2*2 = " << 2 + 2 * 2 << "\"" << endl;
}

void task2()
{
  description("Разница между присваиванием в int и в double");
  int a = 3, b = 3.14;
  double ad = 3, bd = 3.14;
  cout
      << a << endl
      << b << endl
      << ad << endl
      << bd << endl;
}

void task3()
{
  description("Операции над числами");
  double a, b;
  cout << "Введите a и b:\n", cin >> a >> b;
  int ai = a, bi = b;

  wl("int : int"), wl(ai + bi), wl(ai - bi), wl(ai * bi), wl(ai / bi);
  wl("dbl : dbl"), wl(a + b), wl(a - b), wl(a * b), wl(a / b);
  wl("int : dbl"), wl(ai + b), wl(ai - b), wl(ai * b), wl(ai / b);
  wl("dbl : int"), wl(a + bi), wl(a - bi), wl(a * bi), wl(a / bi);
}

void task4()
{
  description("Свап переменных с темпом и без");
  int a, b;
  cout << "Введите a, b: \n", cin >> a >> b;

  int c, d;
  c = a;
  d = b; // refresh values
  wl(c), wl(d);
  c = c + d;
  d = c - d;
  c = c - d;
  wl(c), wl(d);

  c = a;
  d = b; // refresh values
  int temp;
  wl(c), wl(d);
  temp = c;
  c = d;
  d = temp;
  wl(c), wl(d);
}

void task5()
{
  description("Падение объекта");
  const double g = 9.8;
  double x0, v0, t;

  cout << "x0 v0 t: ", cin >> x0 >> v0 >> t;

  double res;
  res = x0 + v0 * t + (g * t * t) / 2;

  cout << "res: " << res;
}

int main()
{
  header();

  task1();
  task2();
  task3();
  task4();
  task5();

  return 0;
}

// api for pretty print
void header()
{
  cout << "Nikonov Fedor PI-201(2)" << endl;
}

int descriptionCounter = 0;
void description(char message[])
{
  cout << "\nЗадача №" << ++descriptionCounter << " " << message << endl;
}

void wl(char message[]) { cout << endl
                               << message; }
void wl(int message) { cout << endl
                            << message; }
void wl(double message) { cout << endl
                               << message; }