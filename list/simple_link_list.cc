#include <iostream>

using namespace std;

template <typename T>
class List {
  private:
    class Node {
      private:
        T data_;
        Node* next_;
      public:
        Node() {
          data_ = T();
          next_ = nullptr;
        }
        Node(const T& d) {
          data_ = d;
          next_ = nullptr;
        }
        void SetNext(Node* next) {
          next_ = next;
        }
    };
    Node* first_;
    Node* last_;
    unsigned int size_;
  public:
    List() {
      first_ = nullptr;
      size_ = 0;
    }
    unsigned int size() const { return size_; }
    bool empty() { return (first_ == nullptr) } //return (size == 0) }
    void push_front(const T& element) {
      Node* n = new Node(element);
      n->SetNext(first_);
      first_ = n;
      if (empty()) last_ = n;
      size_++;
    }
    void push_back(const T& element) {
      Node* n = new Node(element);
      if (empty()) {
        first_ = n;
      } else {
        last_->SetNext(n);
      }
      last_ = n;
      size_++;
    }
};

int main() {
  return 0;
}