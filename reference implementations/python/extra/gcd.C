
#include <iostream.h>

// Fundamental idea of Euclid's algorithm (one of the oldest known algorithms)
// gcd(a,0) = a
// gcd(a,b) = gcd(b,a%b)

int gcd (int a, int b) {
  int temp;
  while (b != 0) {
    temp = a % b;
    a = b;
    b = temp;
  }
  return(a);
}

int main () {
  int x, y;
  cout << "Enter two natural numbers: ";
  cin >> x >> y;
  cout << "gcd(" << x << ", " << y << ") = " << gcd(x,y) << endl;
  return(0);
}

