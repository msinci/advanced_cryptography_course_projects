#include <fstream.h>
#include <iostream.h>

int main () {
  ifstream f1, f2;
  ofstream f3;
  int i,j;

  f1.open("n1");
  f2.open("n2");
  f3.open("n1n2");
  
  f1 >> i;
  f2 >> j;
  while (f1 && f2) {
    if (i < j) {
      while (i < j && f1 && f3) {
	f3 << i << endl;
	f1 >> i;
      }
    }
    else {
      while (j <= i && f2 && f3) {
	f3 << j << endl;
	f2 >> j;
      }
    }
  }
  while (f1) {
    f3 << i << endl;
    f1 >> i;
  }
  while (f2) {
    f3 << j << endl;
    f2 >> j;
  }
  return (0);
}
