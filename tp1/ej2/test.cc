#include <iostream>
#include <set>

using namespace std;

bool comparar(int a, int b)
{
  return a == b;
}

int main()
{
  set<int> A, B;
  set<int, bool (*)(int, int)> C(&comparar);
  if (A == B)
    cout << "Son iguales" << endl;
  else
    cout << "Son distintos" << endl;
  if (A == C)
    cout << "Son iguales" << endl;
  else
    cout << "Son distintos" << endl;
  return 0;
}
