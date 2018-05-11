
#include <iostream.h>

int exp (int b, int e) {
  int result;
  result = 1;
  while (e != 0) {
    result = result * b;
   e = e - 1;
  }
  return(result);
}

int main () {
  int b, e;
  cout << "Enter base and exponent: ";
  cin >> b >> e;
  cout << b << " to the " << e << " = " << exp(b,e) << endl;
  return(0);
}
