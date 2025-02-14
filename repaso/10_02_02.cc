#include <iostream>

using namespace std;

typedef struct {
  int red;
  int green;
  int blue;
} RGBColor;

typedef struct {
  int row;
  int col;
  RGBColor* color;
} Pixel;

RGBColor CreateColor(int r, int g, int b) {
  RGBColor color;
  color.red = r;
  color.green = g;
  color.blue = b;

  return color;
}

void PrintColor(RGBColor* color) {
  cout << "(" << color->red << ", " << color->green << ", " << color->blue << ")" << endl;
}

int main() {
  RGBColor red = CreateColor(255, 0, 0);
  PrintColor(&red);

  Pixel p;
  p.row = 0;
  p.col = 0;
  p.color = &red;

  // Punteros dobles

  int a = 10;
  int *b = &a;
  int* *c = &b;

  cout << a << endl << *b << endl << **c << endl;
  cout << &a << endl << &*b << endl << *c << endl << &**c << endl;
  
  return 0;
}