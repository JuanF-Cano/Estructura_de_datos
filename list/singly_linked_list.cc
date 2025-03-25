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
      size_ = list.size();

      return *this;
    }  
    unsigned int size() const { return size_; }
    bool empty() { return (first_ == nullptr); } // return (size == 0) }
    void push_front(const T& element) {
      Node* n = new Node(element);
      n->SetNext(first_);
      first_ = n;
      if (size_ == 0) last_ = n;
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
    void pop_front() {
      assert(size_ > 0);
      Node* temp = first_;
      first_ = first_->GetNext();
      delete temp;
      size_--;
      if (size_ == 0) last_ = nullptr;
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
        last_->SetNext(nullptr);
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
        Node* n = first_->GetNext();
        delete first_;
        first_ = n;
        if (size_ == 1) last_ = nullptr;
      } else {
        Node* prev = first_;
        for (unsigned int i = 0; i < index - 1; i++) prev = prev->GetNext();
        Node* n = prev->GetNext();
        prev->SetNext(n->GetNext());
        if (index == size_ - 1) last_ = prev;
        delete n;
      }

      size_--;
    }
    void clear() {
      Node* node = first_;
      Node* next = first_;
      while (node != nullptr) {
        next = node->GetNext();
        delete node;
        node = next;
      }
      first_ = nullptr;
      last_ = nullptr;
      size_ = 0;
    }
};

int main() {
  List<int> myList;

  // Testing push_front and push_back
  myList.push_front(10);
  myList.push_front(20);
  myList.push_back(30);
  myList.push_back(40);
  cout << "After push_front and push_back, size: " << myList.size() << endl; 
  // Expected output: "After push_front and push_back, size: 4"

  // Testing pop_front
  myList.pop_front(); // Removes 20 (first element)
  cout << "After pop_front, size: " << myList.size() << endl;
  // Expected output: "After pop_front, size: 3"

  // Testing pop_back
  myList.pop_back(); // Removes 40 (last element)
  cout << "After pop_back, size: " << myList.size() << endl;
  // Expected output: "After pop_back, size: 2"

  // Testing insert
  myList.insert(1, 25); // Inserts 25 at index 1
  cout << "After insert at index 1, size: " << myList.size() << endl;
  // Expected output: "After insert at index 1, size: 3"

  // Testing erase
  myList.erase(1); // Removes element at index 1 (25)
  cout << "After erase at index 1, size: " << myList.size() << endl;
  // Expected output: "After erase at index 1, size: 2"

  // Testing copy constructor
  List<int> copiedList(myList);
  cout << "After copy constructor, copiedList size: " << copiedList.size() << endl;
  // Expected output: "After copy constructor, copiedList size: 2"

  // Testing assignment operator
  List<int> assignedList;
  assignedList = myList;
  cout << "After assignment operator, assignedList size: " << assignedList.size() << endl;
  // Expected output: "After assignment operator, assignedList size: 2"

  // Testing clear
  myList.clear();
  cout << "After clear, myList size: " << myList.size() << endl;
  // Expected output: "After clear, myList size: 0"

  return 0;
}