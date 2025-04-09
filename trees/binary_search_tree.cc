#include <cassert>
#include <iostream>

using namespace std;

template <typename T>
class BST {
  private:
    class Node {
      private: 
        T data_;
        Node* left_;
        Node* right_;

      public:
        Node() {
          data_ = 0;
          left_ = nullptr;
          right_ = nullptr;
        }
        Node(const T& element) {
          data_ = element;
          left_ = nullptr;
          right_ = nullptr;
        }
        T getElement() { return data_; }
        Node* getLeft() { return left_; }
        Node* getRight() { return right_; }
        void setElement(const T element) { data_ = element; }
        void setLeft(Node* next) { left_ = next; }
        void setRight(Node* next) { right_ = next; }
    };

    Node* root_;
    unsigned int size_;

    Node* insert(Node* node, T val) {
      if (!node) return new Node(val);
      if (val < node->getElement()) node->setLeft(insert(node->getLeft(), val));
      else if (val > node->getElement()) node->setRight(insert(node->getRight(), val));
      return node;
    }
    void inorder(Node* node){
      if(node != nullptr){
        inorder(node->getLeft());
        cout << node->getElement()<< " ";
        inorder(node->getRight());
      }
    }
    void preorder(Node* node){
      if(node != nullptr){
        cout << node->getElement() <<" ";
        preorder(node->getLeft());
        preorder(node->getRight());
      }
    }
    void postorder(Node* node){
      if(node != nullptr){
        postorder(node->getLeft());
        postorder(node->getRight());
        cout << node->getElement() << " ";
      }
    }
    bool find(Node* node, const T& element) {
      if (node == nullptr) { return false; }
      if (element == node->getElement()){ return true; }
      else if (element < node->getElement()) {
        return find(node->getLeft(), element);
      }
      else {
        return find(node->getRight(), element);
      } 
    }
    Node* findMin(Node* node) {
      assert(node != nullptr);
      while (node->getLeft()) {
        node = node->getLeft();
      }
      return node;
    }
    Node* remove(Node* node, const T& value) {
      assert(size_ != 0);
      if (!node){ return nullptr; }
      if (value < node->getElement()){
        node->setLeft(remove(node->getLeft(), value));
      } else if (value > node->getElement()){
        node->setRight(remove(node->getRight(), value)); 
      } else {
        if (!node->getLeft() || !node->getRight()) { 
          Node* temp = node->getLeft() ? node->getLeft() : node->getRight();
          delete node;
          return temp;
        }
        Node* minNode = findMin(node->getRight());
        node->setElement(minNode->getElement());
        node->setRight(remove(node->getRight(), minNode->getElement()));
      }
      return node;
    }

  public:
    BST() {
      root_ = nullptr;
      size_ = 0; 
    }
    BST(const T& element) {
      root_ = new Node(element); 
      size_ = 1;
    }
    unsigned int size(){ return size_; }
    void insert(const T& element){ 
      if (!find(element)) {
        root_ = insert(root_, element); 
        size_++; 
      }
    }
    void inorder() { inorder(root_); }
    void preorder() { preorder(root_); }
    void postorder() { postorder(root_); }
    bool find(const T& element) { return find(root_, element); }
    void remove(const T& value) { 
        assert(find(root_, value));
        root_ = remove(root_, value);
        size_--;
    }
    Node* root() { return root_; }
};

int main() {
  // Create an empty BST
  BST<int> tree;
  cout << "Initial size: " << tree.size() << endl; // expected: 0

  // Insert elements
  tree.insert(10);
  tree.insert(5);
  tree.insert(15);
  tree.insert(3);
  tree.insert(7);
  tree.insert(12);
  tree.insert(17);
  tree.insert(1);

  cout << "Size after inserting 8 elements: " << tree.size() << endl; // expected: 8

  // Try to insert a duplicate
  tree.insert(10); // should not insert duplicate
  cout << "Size after inserting a duplicate: " << tree.size() << endl; // expected: 8

  // Inorder traversal
  cout << "Inorder traversal: ";
  tree.inorder(); // expected: 1 3 5 7 10 12 15 17
  cout << endl;

  // Preorder traversal
  cout << "Preorder traversal: ";
  tree.preorder(); // expected: 10 5 3 1 7 15 12 17
  cout << endl;

  // Postorder traversal
  cout << "Postorder traversal: ";
  tree.postorder(); // expected: 1 3 7 5 12 17 15 10
  cout << endl;

  // Find test
  cout << "Find 7: " << tree.find(7) << endl; // expected: 1 (true)
  cout << "Find 100: " << tree.find(100) << endl; // expected: 0 (false)

  // Remove a leaf node
  int removeLeaf = 1;
  cout << "Removing leaf node " << removeLeaf << endl;
  tree.remove(removeLeaf); // node 1 is a leaf
  cout << "Inorder after removing leaf " << removeLeaf << ": ";
  tree.inorder(); // expected: 3 5 7 10 12 15 17
  cout << endl;

  // Remove a node with one child
  int removeOneChild = 3;
  cout << "Removing node with one child " << removeOneChild << endl;
  tree.remove(removeOneChild); // node 3 has no children after 1 was removed
  cout << "Inorder after removing node " << removeOneChild << ": ";
  tree.inorder(); // expected: 5 7 10 12 15 17
  cout << endl;

  // Remove a node with two children
  int removeTwoChildren = 10;
  cout << "Removing node with two children " << removeTwoChildren << endl;
  tree.remove(removeTwoChildren); // node 10 has two children
  cout << "Inorder after removing node " << removeTwoChildren << ": ";
  tree.inorder(); // expected: 5 7 12 15 17
  cout << endl;

  // Final size check
  cout << "Final size: " << tree.size() << endl; // expected: 5

  return 0;
}