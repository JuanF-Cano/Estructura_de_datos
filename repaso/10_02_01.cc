#include <iostream>

using namespace std;

typedef struct {
  double real;
  double img;
} ComplexNumber;

int main() {
  ComplexNumber a;
  a.real = 3.2;
  a.img = 0.0;

  cout << "(" << a.real << ", " << a.img << "i)" << endl;
  cout << &a << endl << &a.real << endl << &a.img << endl << endl;

  ComplexNumber* p = &a;
  cout << p << endl << &(p->real) + 1 << endl; 
  return 0;
}