#include <iostream>
#include <vector>

using namespace std;

class Vector {
  private:
    int* storage_;
    int size_;
    int capacity_;
    public:
    Vector() {
      capacity_ = 5;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new int[capacity_];
      size_ = 0;
    }
    Vector(int c) {
      capacity_ = c;
      //storage_ = (int*)malloc(sizeof(int)*capacity_);
      storage_ = new int[capacity_];
      size_ = 0;
    }
  private:
    void resize() {
      int capacity2 = capacity_ * 1.5; // capacity_ + 1 || capacity_ + 2 || capacity_ * 2 || capacity_ * 1,5 || ...
        int* newStorage = new int[capacity2];
        for (int i = 0; i < size_; i++) {
          newStorage[i] = storage_[i];
        }
        // free(storage_);
        delete [] storage_;
        storage_ = newStorage;
        capacity_ = capacity2;
    }
  public:
    void push_back(int element) {
      if (size_ == capacity_) {
        resize();
      }
      storage_[size_] = element;
      size_++;
    }
};

int main() {
  cout << "Vectors!" << endl;
  Vector x;

  return 0;
}
