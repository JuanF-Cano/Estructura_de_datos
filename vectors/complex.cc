#include <iostream>

using namespace std;

class Complex {
    private:
      double real;
      double img;
    public:
      Complex() {
        real = 0.0;
        img = 0.0;
      }
    friend ostream& operator<<(ostream& os, const Complex& c); // friend std::ostream& operator<<(std::ostream& os, const Complex& c);
  };
  
  ostream& operator<<(ostream& os, const Complex& c) { // std::ostream& operator<<(std::ostream& os, const Complex& c) {
    os << "(" << c.real << ", " << c.img << "i)";
    return os;
  }