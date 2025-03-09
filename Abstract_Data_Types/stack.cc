#include <vector>
#include <list>

using namespace std;

template <typename T>
class Stack {
  private:
    vector<T> storage_;
  public:
    void push(const T& element) { storage_.push_front(element); }
    void pop() { assert(!storage_.empty()); storage_.pop_front(); }
    T& top() { assert(!storage_.empty()); return storage_.front(); }
    bool empty() const { return storage_.empty(); }
    unsigned int size() const { return storage_.size(); }
};