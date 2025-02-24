#include <iostream>
#include <cassert>

using namespace std;

template <typename T> // Se va a considerar que T es un tipo de dato para se declare algo d la clase Vector
class Vector {
  private:
    T* storage_ ;// int* storage_;
    unsigned int capacity_;
    unsigned int size_;
    public:
    Vector() {
      capacity_ = 20;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new T[capacity_];
      size_ = 0;
    }
    Vector(int c, T element = T()) { // Elemento de clase T inicializado con el constructor de la clase T que no recibe parametros
      capacity_ = c;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < capacity_; i++) {
        storage_[i] = element;
      }
      size_ = capacity_;
    }
  private:
    void resize() {
      unsigned int capacity2 = capacity_ * 1.5; // capacity_ + 1 || capacity_ + 2 || capacity_ * 2 || capacity_ * 1,5 || ...OtrasOpciones
      T* newStorage = new T[capacity2];
      for (unsigned int i = 0; i < size_; i++) {
        newStorage[i] = storage_[i];
      }
      // free(storage_);
      delete [] storage_; // Liberar memoria anterior
      storage_ = newStorage;
      capacity_ = capacity2;
    }
  public:
    void push_back(const T& element) { // Se pone T& para que se cree una referencia del elemento.
      if (size_ == capacity_) {
        resize();
      }
      storage_[size_] = element;
      size_++;
    }
    void push_front(const T& element) {
      if (size_ == capacity_) {
        resize();
      }
      for (int i = size_; i > 0; i--) {
        storage_[i] = storage_[i - 1];
      }
      storage_[0] = element;
      size_++;
    }
    void pop_front() {
      if (size_ > 0) {
        for (unsigned int i = 0; i < size_ - 1; i++) {
          storage_[i] = storage_[i + 1];  // Mueve elementos a la izquierda
        }
        size_--;
      }
    }
    void pop_back() {
      size_--;
    }
    unsigned int size() {
      return size_;
    }
    void print() {
      for (unsigned int i = 0; i < size_; i++) {
        cout << storage_[i] << " ";
      }
      cout << endl;
    }
    T at(unsigned int pos) {
      assert(pos >= 0 && pos < size_);
      return storage_[pos];
    }
    const T& operator[](unsigned int index) const { // const T& dice que va a devolver una referencia constante, osea que devuelve una referencia pero no deja modificar su valor 
      // El const luego de los parametros sirve para decir que el contenido no va a alterar ninguno de los elementos de la clase
      return storage_[index];
    }
};

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

int main() {
  cout << "Vectors!" << endl;
  Vector<int> v1; // El "template <typename T>" hace que no se deba de poner solo Vector, sino Vector<type>
  Vector<char> v2(5, 'x');
  Vector<Complex> v3(5);

  for (int i = 0; i < 10; i++) {
    v1.push_back(i + 1);
  }

  // v1.pop_back();
  // v1.size();
  /* 
  v2.print();
  v3.print(); */
  v1.push_front(8);
  v1.print();

  return 0;
}
