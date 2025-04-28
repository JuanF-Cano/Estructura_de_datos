#include <iostream>
#include <cassert>

using namespace std;

template <typename T>
class RBT {
private:
  enum Color { RED, BLACK };

  class Node {
    private:
      T data_;
      Color color_;
      Node* left_;
      Node* right_;
      Node* parent_;
    public:
      Node(const T& data) {
        data_ = data;
        color_ = RED;
        left_ = nullptr;
        right_ = nullptr;
        parent_ = nullptr;
      }

      T getElement() const { return data_; }
      Node* getLeft() const { return left_; }
      Node* getRight() const { return right_; }
      Node* getParent() const { return parent_; }
      Color getColor() const { return color_; }

      void setElement(const T& val) { data_ = val; }
      void setLeft(Node* l) { left_ = l; if (l) l->parent_ = this; }
      void setRight(Node* r) { right_ = r; if (r) r->parent_ = this; }
      void setParent(Node* p) { parent_ = p; }
      void setColor(Color c) { color_ = c; }
    };

  Node* root_;
  unsigned int size_;

  void rotateLeft(Node*& root, Node*& x) {
    Node* y = x->getRight();
    x->setRight(y->getLeft());
    if (y->getLeft()) y->getLeft()->setParent(x);
    y->setParent(x->getParent());
    if (!x->getParent()) root = y;
    else if (x == x->getParent()->getLeft()) x->getParent()->setLeft(y);
    else x->getParent()->setRight(y);
    y->setLeft(x);
    x->setParent(y);
  }

  void rotateRight(Node*& root, Node*& x) {
    Node* y = x->getLeft();
    x->setLeft(y->getRight());
    if (y->getRight()) y->getRight()->setParent(x);
    y->setParent(x->getParent());
    if (!x->getParent()) root = y;
    else if (x == x->getParent()->getLeft()) x->getParent()->setLeft(y);
    else x->getParent()->setRight(y);
    y->setRight(x);
    x->setParent(y);
  }

  void fixInsert(Node*& root, Node*& n) {
    Node* parent = nullptr;
    Node* grandparent = nullptr;

    while (n != root && n->getColor() == RED && n->getParent()->getColor() == RED) {
      parent = n->getParent();
      grandparent = parent->getParent();

      if (parent == grandparent->getLeft()) {
        Node* uncle = grandparent->getRight();

        if (uncle && uncle->getColor() == RED) {
          grandparent->setColor(RED);
          parent->setColor(BLACK);
          uncle->setColor(BLACK);
          n = grandparent;
        } else {
          if (n == parent->getRight()) {
            rotateLeft(root, parent);
            n = parent;
            parent = n->getParent();
          }
          rotateRight(root, grandparent);
          Color aux = parent->getColor();
          parent->setColor(grandparent->getColor());
          grandparent->setColor(aux);
          n = parent;
        }
      } else {
        Node* uncle = grandparent->getLeft();

        if (uncle && uncle->getColor() == RED) {
          grandparent->setColor(RED);
          parent->setColor(BLACK);
          uncle->setColor(BLACK);
          n = grandparent;
        } else {
          if (n == parent->getLeft()) {
            rotateRight(root, parent);
            n = parent;
            parent = n->getParent();
          }
          rotateLeft(root, grandparent);
          Color aux = parent->getColor();
          parent->setColor(grandparent->getColor());
          grandparent->setColor(aux);
          n = parent;
        }
      }
    }
    root->setColor(BLACK);
  }

  void preorder(Node* node) const {
    if (node) {
      cout << node->getElement() << (node->getColor() == RED ? "R " : "B ");
      preorder(node->getLeft());
      preorder(node->getRight());
    }
  }
  void inorder(Node* node) const {
    if (node) {
      inorder(node->getLeft());
      cout << node->getElement() << (node->getColor() == RED ? "R " : "B ");
      inorder(node->getRight());
    }
  }
  void postorder(Node* node) const {
    if (node) {
      postorder(node->getLeft());
      postorder(node->getRight());
      cout << node->getElement() << (node->getColor() == RED ? "R " : "B ");
    }
  }
  Node* insert(Node* root, Node* node) {
    if (!root) return node;
    if (node->getElement() < root->getElement()) {
      root->setLeft(insert(root->getLeft(), node));
    } else if (node->getElement() > root->getElement()) {
      root->setRight(insert(root->getRight(), node));
    }

    return root;
  }

  public:
    RBT() {
      root_ = nullptr;
      size_ = 0;
    }
    RBT(const T& element) {
      root_ = new Node(element); 
      root_->setColor(BLACK);
      size_ = 1;
    }
    unsigned int size() const { return size_; }
    bool empty() const { return (size_ == 0); } 
    void inorderTraversal() const { inorder(root_); cout << endl; }
    void preorderTraversal() const { preorder(root_); cout << endl; }
    void postorderTraversal() const { postorder(root_); cout << endl; }
    
    void insert(const T& val) {
      Node* node = new Node(val);
      root_ = insert(root_, node);
      fixInsert(root_, node);
      size_++;
    }
};

int main() {
  RBT<int> tree;

  // Insert some elements
  tree.insert(10);
  tree.insert(20);
  tree.insert(30);
  tree.insert(15);
  tree.insert(25);
  tree.insert(5);
  tree.insert(1);

  cout << "Preorder traversal (root, left, right):" << endl;
  tree.preorderTraversal();
  // Expected: 20B 10R 5B 1R 15B 30B 25R 

  cout << "Inorder traversal (left, root, right):" << endl;
  tree.inorderTraversal();
  // Expected: 1R 5B 10B 15R 20B 25B 30R

  cout << "Postorder traversal (left, right, root):" << endl;
  tree.postorderTraversal();
  // Expected: 1R 5B 15B 10R 25R 30B 20B

  // Check size and if tree is empty
  cout << "Tree size: " << tree.size() << endl;
  // Expected: 7

  cout << "Is tree empty?: " << (tree.empty() ? "Yes" : "No") << endl;
  // Expected: No

  return 0;
}