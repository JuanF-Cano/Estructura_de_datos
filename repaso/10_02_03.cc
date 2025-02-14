#include <iostream>

using namespace std;

class RGBColor {
  private:
    int red;
    int green;
    int blue;
  
  public:
    RGBColor(){
      cout << "Constructor 1 Called" << endl;
      red = 0;
      green = 0;
      blue = 0;
    }
    RGBColor(int c){
      cout << "Constructor 2 Called" << endl;
      red = c;
      green = c;
      blue = c;
    }
    RGBColor(int r, int g, int b){
      cout << "Cnstructor 3 Called" << endl;
      red = r;
      green = g;
      blue = b;
    }

    void print() {
      cout << "(" << red << ", " << green << ", " << blue << endl;
    }
};

int main() {
  RGBColor black;
  RGBColor gray(124);
  RGBColor red(255, 0, 0);

  black.print();
  gray.print();
  red.print();

  return 0;
}