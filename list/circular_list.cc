#include <cassert>
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
      Node(const T& element) {
        data_ = element;
        next_ = nullptr;
      }
      Node* GetNext() { return next_; }
      T GetElement() { return data_; }
      void SetNext(Node* next) { next_ = next; }
    };
    Node* first_;
    Node* last_;
    unsigned int size_;
  public:
    List() {
      first_ = nullptr;
      last_ = nullptr;
      size_ = 0;
    }
    List(unsigned int c, T element = T()) {
      for (size_t i = 0; i < c; ++i) {
        push_back(element);
      }
    }
    List(const List<T>& list) {
      assert(list.size() > 0);
      Node* p = list.first_;
      first_ = new Node(p->GetElement()); 

      Node* current = first_; 
      p = p->GetNext(); 

      while (p != nullptr) {
        current->SetNext(new Node(p->GetElement())); 
        current = current->GetNext(); 
        p = p->GetNext(); 
      }

      last_ = current;
      current->SetNext(first_);
      size_ = list.size();
    }
    List& operator=(const List& list) {
      if (list.size() == 0) return *this;
      
      Node* p = list.first_;
      first_ = new Node(p->GetElement());

      Node* current = first_; 
      p = p->GetNext(); 

      while (p != nullptr) {
        current->SetNext(new Node(p->GetElement())); 
        current = current->GetNext(); 
        p = p->GetNext(); 
      }

      last_ = current;
      current->SetNext(first_);
      size_ = list.size();

      return *this;
    }  
    unsigned int size() const { return size_; }
    bool empty() { return (first_ == nullptr); } // return (size == 0) }
    void push_front(const T& element) {
      Node* n = new Node(element);
      
      if (size_ == 0) {
        first_ = n;
        last_ = n;
        n->SetNext(n);
      } else {
        n->SetNext(first_);
        first_ = n;
        last_->SetNext(first_);
      }

      size_++;
    }
    void push_back(const T& element) {
      Node* n = new Node(element);
      if (empty()) {
        first_ = n;
        last_ = n;
        n->SetNext(n);
      } else {
        last_->SetNext(n);
        last_ = n;
        last_->SetNext(first_);
      }
      size_++;
    }
    void pop_front() {
      assert(size_ > 0);
      
      if (size_ == 1) {
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
      } else {
        Node* temp = first_;
        first_ = first_->GetNext();
        last_->SetNext(first_);
        delete temp;
      }

      size_--;
    }
    void pop_back() {
      assert(size_ > 0);

      if (size_ == 1) {
        delete first_;
        first_ = nullptr;
        last_ = nullptr;
      } else {
        Node* prev = first_;
        while (prev->GetNext() != last_) {
          prev = prev->GetNext();
        }
        delete last_;
        last_ = prev;
        last_->SetNext(first_);
      }

      size_--;
    }
    void insert(unsigned int index, const T& element) {
      assert(index <= size_);
      Node* n = new Node(element);

      if (index == 0) {
        n->SetNext(first_);
        first_ = n;
        if (size_ == 0) last_ = n;
        last_->SetNext(first_);
      } else {
        Node* prev = first_;
        for (unsigned int i = 0; i < index - 1; i++) prev = prev->GetNext();
        n->SetNext(prev->GetNext());
        prev->SetNext(n);
      }

      if (index == size_) last_ = n;
      size_++;
    }
    void erase(unsigned int index) {
      assert(index < size_);

      if (index == 0) {
        Node* temp = first_;
        if (size_ == 1) {
            first_ = nullptr;
            last_ = nullptr;
        } else {
            first_ = first_->GetNext();
            last_->SetNext(first_);
        }
        delete temp;
      } else {
        Node* prev = first_;
        for (unsigned int i = 0; i < index - 1; i++) prev = prev->GetNext();
        Node* n = prev->GetNext();
        prev->SetNext(n->GetNext());
        if (index == size_ - 1) {
          last_ = prev;
          last_->SetNext(first_);
        };
        delete n;
      }

      size_--;
    }
    void clear() {
      Node* node = first_;
      Node* next = first_;
      do {
        next = node->GetNext();
        delete node;
        node = next;
      } while (node != last_);
      first_ = nullptr;
      last_ = nullptr;
      size_ = 0;
    }
};


#include <iostream>

int main() {
    List<int> list;

    // Initial state
    cout << "Initial size: " << list.size() << endl; // Expected: 0

    // Test: Insert elements at the front
    list.push_front(10);
    cout << "Size after push_front(10): " << list.size() << endl; // Expected: 1

    list.push_front(5);
    cout << "Size after push_front(5): " << list.size() << endl; // Expected: 2

    // Test: Insert elements at the back
    list.push_back(15);
    cout << "Size after push_back(15): " << list.size() << endl; // Expected: 3

    list.push_back(20);
    cout << "Size after push_back(20): " << list.size() << endl; // Expected: 4

    // Test: Remove elements from the front
    list.pop_front();
    cout << "Size after pop_front(): " << list.size() << endl; // Expected: 3

    // Test: Remove elements from the back
    list.pop_back();
    cout << "Size after pop_back(): " << list.size() << endl; // Expected: 2

    // Test: Insert at specific positions
    list.insert(1, 12);
    cout << "Size after insert(1, 12): " << list.size() << endl; // Expected: 3

    list.insert(3, 18);
    cout << "Size after insert(3, 18): " << list.size() << endl; // Expected: 4

    // Test: Erase elements at specific positions
    list.erase(2);
    cout << "Size after erase(2): " << list.size() << endl; // Expected: 3

    // Test: Clear the list
    list.clear();
    cout << "Size after clear(): " << list.size() << endl; // Expected: 0

    return 0;
}