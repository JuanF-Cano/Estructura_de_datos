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

  Node* insert(Node* root, Node* node) {
    if (!root) return node;
    if (node->getElement() < root->getElement()) {
      root->setLeft(insert(root->getLeft(), node));
    } else if (node->getElement() > root->getElement()) {
      root->setRight(insert(root->getRight(), node));
    }

    return root;
  }

  void fixRemove(Node*& root, Node*& node) {
    while (node != root && node->getColor() == BLACK) {
      if (node == node->getParent()->getLeft()) {
        Node* sibling = node->getParent()->getRight();
        if (sibling->getColor() == RED) {
          sibling->setColor(BLACK);
          node->getParent()->setColor(RED);
          Node* parent = node->getParent();
          rotateLeft(root, parent);
          sibling = node->getParent()->getRight();
        }
        if (sibling->getLeft()->getColor() == BLACK && sibling->getRight()->getColor() == BLACK) {
          sibling->setColor(RED);
          node = node->getParent();
        } else {
          if (sibling->getRight()->getColor() == BLACK) {
            sibling->getLeft()->setColor(BLACK);
            sibling->setColor(RED);
            rotateRight(root, sibling);
            sibling = node->getParent()->getRight();
          }
          sibling->setColor(node->getParent()->getColor());
          node->getParent()->setColor(BLACK);
          sibling->getRight()->setColor(BLACK);
          Node* parent = node->getParent();
          rotateLeft(root, parent);
          node = root;
        }
      } else {
        Node* sibling = node->getParent()->getLeft();
        if (sibling->getColor() == RED) {
          sibling->setColor(BLACK);
          node->getParent()->setColor(RED);
          Node* parent = node->getParent(); 
          rotateRight(root, parent);
          sibling = node->getParent()->getLeft();
        }
        if (sibling->getRight()->getColor() == BLACK && sibling->getLeft()->getColor() == BLACK) {
          sibling->setColor(RED);
          node = node->getParent();
        } else {
          if (sibling->getLeft()->getColor() == BLACK) {
            sibling->getRight()->setColor(BLACK);
            sibling->setColor(RED);
            rotateLeft(root, sibling);
            sibling = node->getParent()->getLeft();
          }
          sibling->setColor(node->getParent()->getColor());
          node->getParent()->setColor(BLACK);
          sibling->getLeft()->setColor(BLACK);
          Node* parent = node->getParent(); 
          rotateRight(root, parent);
          node = root;
        }
      }
    }
    node->setColor(BLACK);
  }

  Node* remove(Node* root, const T& val) {
    if (!root) return root;

    if (val < root->getElement()) {
      root->setLeft(remove(root->getLeft(), val));
    } else if (val > root->getElement()) {
      root->setRight(remove(root->getRight(), val));
    } else {
      if (!root->getLeft() || !root->getRight()) {
        Node* temp = root->getLeft() ? root->getLeft() : root->getRight();
        if (!temp) {
          temp = root;
          root = nullptr;
        } else {
          *root = *temp;
        }
        delete temp;
      } else {
        Node* temp = minimum(root->getRight());
        root->setElement(temp->getElement());
        root->setRight(remove(root->getRight(), temp->getElement()));
      }
    }

    if (root && root->getColor() == BLACK) fixRemove(root_, root);

    return root;
  }

  Node* find(Node* node, const T& val) const {
    if (!node || node->getElement() == val) return node;
    if (val < node->getElement()) return find(node->getLeft(), val);
    return find(node->getRight(), val);
  }
  Node* minimum(Node* node) const {
    while (node && node->getLeft()) {
      node = node->getLeft();
    }
    return node;
  }
  Node* maximum(Node* node) const {
    while (node && node->getRight()) {
      node = node->getRight();
    }
    return node;
  }
  void clear(Node* node) {
    if (node) {
      clear(node->getLeft());
      clear(node->getRight());
      delete node;
    }
  }
  unsigned int height(Node* node) const {
    if (!node) return 0;
    int leftHeight = height(node->getLeft());
    int rightHeight = height(node->getRight());
    return max(leftHeight, rightHeight) + 1;
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

  Node* find(const T& val) const { return find(root_, val); }
  Node* minimum() const { return minimum(root_); }
  Node* maximum() const { return maximum(root_); }
  unsigned int height() const { return height(root_); }
  
  void insert(const T& val) {
    Node* node = new Node(val);
    root_ = insert(root_, node);
    fixInsert(root_, node);
    size_++;
  }

  void remove(const T& val) {
    root_ = remove(root_, val);
    size_--;
  }

  void clear() {
    clear(root_);
    root_ = nullptr;
    size_ = 0;
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
  
  cout << "Postorder traversal (left, right, root):" << endl;
  tree.postorderTraversal();
  // Expected: 1R 5B 15B 10R 25R 30B 20B
  
  // Check size and if tree is empty
  cout << "Tree size: " << tree.size() << endl;
  // Expected: 7
  
  cout << "Is tree empty?: " << (tree.empty() ? "Yes" : "No") << endl;
  // Expected: No

  // Finding an element
  if (tree.find(15)) cout << "Found 15 in the tree!" << endl;
  else cout << "15 not found." << endl;
  
  // Minimum and maximum
  cout << "Minimum: " << tree.minimum()->getElement() << endl;
  cout << "Maximum: " << tree.maximum()->getElement() << endl;
  
  // Tree height
  cout << "Tree height: " << tree.height() << endl;  

  cout << "Inorder traversal (left, root, right):" << endl;
  tree.inorderTraversal();
  // Expected: 1R 5B 10R 15B 20B 25R 30B
  
  tree.remove(10);
  cout << "After removing 10: ";
  tree.inorderTraversal();

  // Clear the tree
  tree.clear();
  cout << "Tree cleared, size: " << tree.size() << endl;
  
  return 0;
}