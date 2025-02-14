#include <iostream>

using namespace std;

typedef struct {
  double real;
  double img;
} ComplexNumber;

ComplexNumber csum(ComplexNumber *a, ComplexNumber *b) {
  ComplexNumber r;
  r.real = (*a).real + (*b).real;
  r.img = (*a).img + (*b).img;

  return r;
}

int main() {
  ComplexNumber a;
  a.real = 10.0;
  a.img = 2.0;
  
  ComplexNumber b;
  b.real = 100.0;
  b.img = 20.0;

  ComplexNumber r = csum(&a, &b);

  cout << "Valor real: " << r.real << endl << "Valor img: " << r.img << endl;

  return 0;
}