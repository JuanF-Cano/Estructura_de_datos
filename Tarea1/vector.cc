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
    void print() {
      cout << "{";
      if (size_ == 0) {
          cout << "}" << endl;
          return;
      }
      unsigned int i;
      for (i = 0; i < size_ - 1; i++) {
          cout << storage_[i] << ", ";
      }
      cout << storage_[i] << "}" << endl;
  }
};

Vector<int> removeDuplicates(const Vector<int>& v) {
  Vector<int> v2;
  bool isDuplicate;
  for (unsigned int i = 0; i < v.size(); i++) {
    int element = v[i];
    isDuplicate = false;
    for (unsigned int j = 0; j < v2.size(); j++) {
      if (v2[j] == element) {
        isDuplicate = true;
        break;
      }
    }
    if (!isDuplicate) {
      v2.push_back(element);
    }
  }
  return v2;
}

template <typename T>
Vector<T> mergeSortedVectors(Vector<T>& v1, Vector<T>& v2) {
  Vector<T> v;
  unsigned i = 0, j = 0;
  while (i < v1.size() && j < v2.size()) {
    if (v1[i] < v2[j]) {
      v.push_back(v1[i]);
      i++;
    } else {
      v.push_back(v2[j]);
      j++;
    }
  }
  while (i < v1.size()) {
    v.push_back(v1[i]);
    i++;
  }
  while (j < v2.size()) {
    v.push_back(v2[j]);
    j++;
  }

  return v;
}

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
  Vector<int> myVector;

  // Test push_back
  myVector.push_back(10);
  myVector.push_back(20);
  myVector.push_back(30);

  cout << myVector.size() << endl; // Expected: 3
  cout << myVector.capacity() << endl; // Expected: Initial capacity, e.g., 4 or 8

  // Test pop_back
  myVector.pop_back();
  cout << myVector.size() << endl; // Expected: 2

  // Test at with valid and invalid indices
  cout << myVector.at(0) << endl; // Expected: 10
  cout << myVector.at(1) << endl; // Expected: 20

  // Border case: Accessing an out-of-bounds index
  cout << myVector.at(2) << endl; // Should crash!

  // Border case: pop_back on empty vector
  Vector<int> emptyVector;
  emptyVector.pop_back(); // should crash! 
  
  Vector<int> numbers = {1, 2, 2, 3, 4, 4, 5};
  Vector<int> uniqueNumbers = removeDuplicates(numbers);
  
  uniqueNumbers.print(); // Expected: {1, 2, 3, 4, 5}
  
  Vector<int> numbers2 = {1,1,1,1,1,1};
  Vector<int> uniqueNumbers2 = removeDuplicates(numbers2);
  uniqueNumbers2.print(); // Expected: {1}
  
  Vector<int> numbers3 = {};
  Vector<int> uniqueNumbers3 = removeDuplicates(numbers3);
  uniqueNumbers3.print(); // Expected: {}
  
  Vector<int> numbers4 = {1};
  Vector<int> uniqueNumbers4 = removeDuplicates(numbers4);
  uniqueNumbers4.print(); // Expected: {1}

  Vector<int> vector1 = {1, 3, 5};
  Vector<int> vector2 = {2, 4, 6};
  Vector<int> mergedVector = mergeSortedVectors(vector1, vector2);
  
  mergedVector.print(); // Expected: {1, 2, 3, 4, 5, 6}
  
  Vector<int> vector3 = {1, 2, 3};
  Vector<int> vector4 = {};
  Vector<int> mergedVector2 = mergeSortedVectors(vector3, vector4);
  mergedVector2.print(); // Expected: {1, 2, 3}
  
  Vector<int> vector5 = {};
  Vector<int> vector6 = {4,5,6};
  Vector<int> mergedVector3 = mergeSortedVectors(vector5, vector6);
  mergedVector3.print(); // Expected: {4, 5, 6}
  
  Vector<int> vector7 = {1,1,1,1};
  Vector<int> vector8 = {1,1,1,1};
  Vector<int> mergedVector4 = mergeSortedVectors(vector7, vector8);
  mergedVector4.print(); // Expected: {1,1,1,1,1,1,1,1}

  return 0;
}