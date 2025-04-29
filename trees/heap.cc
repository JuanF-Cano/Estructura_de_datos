#include <iostream>
#include <cassert>
#include <utility>

using namespace std;

template <typename T>
class heap {
  private:
    T* heap_;
    unsigned int size_;
    unsigned int capacity_;

    void heapifyDown(int index) {
      int largest = index;
      int left = 2 * index + 1;
      int right = 2 * index + 2;

      if (left < size_ && heap_[left].first > heap_[largest].first) largest = left;
      if (right < size_ && heap_[right].first > heap_[largest].first) largest = right;

      if (largest != index) {
        swap(heap_[index], heap_[largest]);
        heapifyDown(largest);
      }
    }

    void heapifyUp(int index) {
      if (index && heap_[(index - 1) / 2].first < heap_[index].first) {
        swap(heap_[index], heap_[(index - 1) / 2]);
        heapifyUp((index - 1) / 2);
      }
    }

    void resize() {
      unsigned int capacity2 = (capacity_ * 3) / 2 + 1;
      T* newHeap = new T[capacity2];
      for (unsigned int i = 0; i < size_; i++) {
        newHeap[i] = heap_[i];
      }
      delete[] heap_;
      heap_ = newHeap;
      capacity_ = capacity2;
    }

  public:
    heap() {
      capacity_ = 5;
      heap_ = new T[capacity_];
      size_ = 0;
    }

    unsigned int size() const { return size_; }
    bool empty() const { return size_ == 0; }

    void insert(const T& element) {
      if (size_ == capacity_) resize();
      heap_[size_] = element;
      heapifyUp(size_);
      size_++;
    }

    T extractMax() {
      assert(size_ > 0 && "Heap is empty");
      T root = heap_[0];
      heap_[0] = heap_[--size_];
      heapifyDown(0);
      return root;
    }

    T getMax() const {
      assert(size_ > 0 && "Heap is empty");
      return heap_[0];
    }

    void print() const {
      cout << "Heap elements (priority, value): ";
      for (unsigned int i = 0; i < size_; ++i) {
        cout << "(" << heap_[i].first << ", " << heap_[i].second << ") ";
      }
      cout << endl;
    }
};

int main() {
  // Create a heap of pair<int, string>
  heap<pair<int, string>> h;

  // Insert elements into the heap
  h.insert({5, "Task A"});
  h.insert({3, "Task B"});
  h.insert({8, "Task C"});
  h.insert({1, "Task D"});
  h.insert({6, "Task E"});

  // Print current heap state
  // Expect: Elements ordered by priority (highest priority first)
  h.print();

  // Get and print the maximum element without removing it
  // Expect: (8, Task C)
  auto maxElement = h.getMax();
  cout << "Max element (peek): (" << maxElement.first << ", " << maxElement.second << ")" << endl;

  // Extract the maximum element
  auto extracted = h.extractMax();
  cout << "Extracted max: (" << extracted.first << ", " << extracted.second << ")" << endl;

  // Print heap after extracting max
  h.print();

  // Insert a new higher priority task
  h.insert({10, "Task F"});

  // Print heap after inserting new maximum
  h.print();

  // Extract max again
  auto extracted2 = h.extractMax();
  cout << "Extracted max: (" << extracted2.first << ", " << extracted2.second << ")" << endl;

  // Final heap state
  h.print();

  return 0;
}