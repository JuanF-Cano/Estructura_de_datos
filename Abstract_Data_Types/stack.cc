#include <iostream>
#include <cassert>

using namespace std;

template <typename T> // Se va a considerar que T es un tipo de dato para se declare algo d la clase Vector
class Vector {
  private:
    T* storage_ ; // int* storage_;
    unsigned int capacity_;
    unsigned int size_;
  public:
    Vector() {
      capacity_ = 5;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new T[capacity_];
      size_ = 0;
    }
    Vector(unsigned int c, T element = T()) { // Elemento de clase T inicializado con el constructor de la clase T que no recibe parametros
      assert(c > 0);
      capacity_ = c;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < capacity_; i++) {
        storage_[i] = element;
      }
      size_ = capacity_;
    }
    Vector(initializer_list<T> list) {
      capacity_ = list.size() > 5 ? list.size() : 5;
      storage_ = new T[capacity_];
      size_ = list.size();
      unsigned int i = 0;
      for (const T& elem : list) {
        storage_[i++] = elem;
      }
    }
    Vector(const Vector<T>& v) {
      capacity_ = v.capacity_;
      size_ = v.size_;
      storage_ = new T[capacity_];
      for (unsigned int i = 0; i < size_; i++) {
        storage_[i] = v.storage_[i];
      }
    }
    Vector& operator=(initializer_list<T>) = delete;
    Vector& operator=(const Vector& v) {
      if (this != &v) {
        delete[] storage_;
        capacity_ = v.capacity_;
        size_ = v.size_;
        storage_ = new T[capacity_]; 
        for (unsigned int i = 0; i < size_; i++) {
          storage_[i] = v.storage_[i];
        }
      }
      return *this;
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
    bool empty() {
      return (size_ == 0);
    }
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
    void pop_back() {
      assert(size_ > 0);
      size_--;
    }
    void pop_front() {
      assert(size_ > 0);
      if (size_ > 0) {
        for (unsigned int i = 0; i < size_ - 1; i++) {
          storage_[i] = storage_[i + 1];
        }
        size_--;
      }
    }
    unsigned int size() const { return size_; }
    unsigned int capacity() const { return capacity_; }
    int waste() const { return capacity_ - size_; }
    T& at(unsigned int pos) {
      assert(pos < size_);
      return storage_[pos];
    }
    const T& operator[](unsigned int index) const { // const T& dice que va a devolver una referencia constante, osea que devuelve una referencia pero no deja modificar su valor 
      assert(index < size_);
      // El const luego de los parametros sirve para decir que el contenido no va a alterar ninguno de los elementos de la clase
      return storage_[index];
    }
    void shrink_to_fit(){
      T* storage2_ = new T[size_];
      for(unsigned int i = 0; i < size_; i++){
        storage2_[i] = storage_[i];
      }
      delete[] storage_;
      capacity_ = size_;
      storage_ = storage2_;
    }
    void insert(unsigned int index, const T& element) {
      assert(index <= size_);
      if (size_ == capacity_) {
        resize();
      }
      for (unsigned int i = size_; i > index; i--) {
        storage_[i] = storage_[i - 1];
      }
      storage_[index] = element;
      size_++;
    }
    void erase(unsigned int index) {
      assert(index < size_);
      for (unsigned int i = index; i < size_ - 1; i++) {
        storage_[i] = storage_[i + 1];
      } 
      size_--;
    }
};

template <typename T>
class Stack {
  private:
    Vector<T> storage_;
  public:
    void push(const T& element) { storage_.push_back(element); }
    void pop() { assert(!storage_.empty()); storage_.pop_back(); }
    T& top() { assert(!storage_.empty()); return storage_.at(storage_.size() - 1); }
    bool empty() const { return storage_.empty(); }
    unsigned int size() const { return storage_.size(); }
};

int main() {
  Stack<int> s;

  s.push(10);
  s.push(20);
  s.push(30);

  cout << "Top: " << s.top() << endl; // 30
  cout << "Size: " << s.size() << endl; // 3

  s.pop(); 

  cout << "Top after pop: " << s.top() << endl; // 20
  cout << "Size after pop: " << s.size() << endl; // 2

  return 0;
}
