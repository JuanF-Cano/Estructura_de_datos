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
        Node* previous_;
      public:
        Node() {
          data_ = T();
          next_ = nullptr;
          previous_ = nullptr;
        }
        Node(const T element) {
          data_ = element;
          next_ = nullptr;
          previous_ = nullptr;
        }
        Node* GetNext() { return next_; }
        Node* GetPrevious() { return previous_; }
        T GetElement() { return data_; }
        void SetNext(Node* next) { next_ = next; }
        void SetPrevious(Node* previous) { previous_ = previous; }
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
      for (unsigned int i = 0; i < c; ++i) {
        push_back(element);
      }
    }
    List(const List<T>& list) {
      assert(list.size() > 0);
      Node* p = list.first_;
      first_ = new Node(p->GetElement()); 
  
      Node* previous = first_;
      p = p->GetNext(); 
  
      while (p != nullptr) {
        Node* current = new Node(p->GetElement());
        previous->SetNext(current);
        current->SetPrevious(previous);
        previous = current;
        p = p->GetNext();
      }
  
      last_ = previous; 
      size_ = list.size();
    }
    List& operator=(const List& list) {
      if (list.size() == 0) return *this;
      Node* p = list.first_;
      first_ = new Node(p->GetElement()); 
  
      Node* previous = first_;
      p = p->GetNext(); 
  
      while (p != nullptr) {
        Node* current = new Node(p->GetElement());
        previous->SetNext(current);
        current->SetPrevious(previous);
        previous = current;
        p = p->GetNext();
      }
  
      last_ = previous; 
      size_ = list.size();

      return *this;
    }
    unsigned int size() const { return size_; }
    bool empty() { return (size_ == 0); }
    void push_front(const T& element) {
      Node* n = new Node(element);
      n->SetNext(first_);
      
      if (empty()) {
        last_ = n;
      } else {
        first_->SetPrevious(n);
      }
      first_ = n;
      
      size_++;
    }
    void push_back(const T& element) {
      Node* n = new Node(element);
      n->SetPrevious(last_);
      
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
      Node* n = first_->GetNext();
      delete first_;
      
      first_ = n;
      
      if (n == nullptr) {
        last_ = n;
      } else {
        n->SetPrevious(nullptr);
      }

      size_--;
    }
    void pop_back() {
      assert(size_ > 0);
      Node* n = last_->GetPrevious();
      delete last_;

      last_ = n;

      if (n == nullptr) {
        first_ = n;
      } else {
        n->SetNext(nullptr); 
      }

      size_--;
    }
    void insert(unsigned int index, const T& element) {
      assert(index <= size_);
      Node* n = new Node(element);
  
      if (index == 0) { 
          n->SetNext(first_);
          if (first_ != nullptr) first_->SetPrevious(n);
          first_ = n;
          if (size_ == 0) last_ = n;
      } else if (index == size_) { 
          n->SetPrevious(last_);
          if (last_ != nullptr) last_->SetNext(n);
          last_ = n;
      } else { 
        if (index < size_ / 2) { 
          Node* side = first_;
          for (unsigned int i = 0; i < index - 1; i++) side = side->GetNext();
          Node* sideRight = side->GetNext();
          n->SetNext(sideRight);
          n->SetPrevious(side);
          side->SetNext(n);
          sideRight->SetPrevious(n);
        } else {
          Node* side = last_;
          for (unsigned int i = size_ - 1; i > index; i--) side = side->GetPrevious();
          Node* sideLeft = side->GetPrevious();
          n->SetPrevious(sideLeft);
          n->SetNext(side);
          side->SetPrevious(n);
          sideLeft->SetNext(n);
        }
      }

      size_++;
    } 
    void erase(unsigned int index) {
      assert(index < size_);

      if (index == 0) { 
          pop_front(); 
          return; 
      } 
      if (index == size_ - 1) { 
          pop_back(); 
          return; 
      }
  
      Node* toDelete;
      if (index < size_ / 2) { 
          toDelete = first_;
          for (unsigned int i = 0; i < index; i++) toDelete = toDelete->GetNext();
      } else { 
          toDelete = last_;
          for (unsigned int i = size_ - 1; i > index; i--) toDelete = toDelete->GetPrevious();
      }
  
      Node* before = toDelete->GetPrevious();
      Node* after = toDelete->GetNext();
      before->SetNext(after);
      after->SetPrevious(before);
  
      delete toDelete;
      size_--;
    } 
    void clear() {
      while (!empty()) pop_front();
    }
    void traverse_forward() {
      Node* current = first_;
      while (current != nullptr) {
        cout << current->GetElement() << " ";
        current = current->GetNext();
      }
      cout << endl;
    }
    
    void traverse_backward() {
      Node* current = last_;
      while (current != nullptr) {
        cout << current->GetElement() << " ";
        current = current->GetPrevious();
      }
      cout << endl;
    }
};

int main() {
  // Test default constructor
  List<int> list;
  cout << "Initial list (empty):\n";
  list.traverse_forward(); // Expected output: (empty line)
  
  // Test push_front
  list.push_front(3);
  list.push_front(2);
  list.push_front(1);
  cout << "After push_front(1), push_front(2), push_front(3):\n";
  list.traverse_forward(); // Expected output: 1 2 3
  
  // Test push_back
  list.push_back(4);
  list.push_back(5);
  cout << "After push_back(4), push_back(5):\n";
  list.traverse_forward(); // Expected output: 1 2 3 4 5
  
  // Test pop_front
  list.pop_front();
  cout << "After pop_front():\n";
  list.traverse_forward(); // Expected output: 2 3 4 5
  
  // Test pop_back
  list.pop_back();
  cout << "After pop_back():\n";
  list.traverse_forward(); // Expected output: 2 3 4
  
  // Test insert
  list.insert(1, 9);
  cout << "After insert(1, 9):\n";
  list.traverse_forward(); // Expected output: 2 9 3 4
  
  // Test erase
  list.erase(2);
  cout << "After erase(2):\n";
  list.traverse_forward(); // Expected output: 2 9 4
  
  // Test traverse_backward
  cout << "Traverse backward:\n";
  list.traverse_backward(); // Expected output: 4 9 2
  
  // Test copy constructor
  List<int> copyList(list);
  cout << "Copied list (from copy constructor):\n";
  copyList.traverse_forward(); // Expected output: 2 9 4
  
  // Test assignment operator
  List<int> assignedList;
  assignedList = list;
  cout << "Assigned list (from operator=):\n";
  assignedList.traverse_forward(); // Expected output: 2 9 4
  
  // Test clear
  list.clear();
  cout << "After clear():\n";
  list.traverse_forward(); // Expected output: (empty line)
  
  return 0;
}