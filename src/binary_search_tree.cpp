#include "assignment/binary_search_tree.hpp"

namespace assignment {

  BinarySearchTree::~BinarySearchTree() {
    BinarySearchTree::Clear();
  }

  void BinarySearchTree::Insert(int key, int value) {
    if (root_ == nullptr) {
      root_ = new Node(key, value);
    } else {
      insert(key, value, root_);
    }
  }

  bool BinarySearchTree::Remove(int key) {
    return remove(key, root_);
  }

  void BinarySearchTree::Clear() {
    clear(root_);
    root_ = nullptr;
  }

  std::optional<int> BinarySearchTree::Find(int key) const {
    Node* node = find(key, root_);
    if (node == nullptr) {
      return std::nullopt;
    } else {
      return node->value;
    }
  }

  bool BinarySearchTree::Contains(int key) const {
    return find(key, root_) != nullptr;
  }

  bool BinarySearchTree::IsEmpty() const {
    return root_ == nullptr;
  }

  std::optional<int> BinarySearchTree::FindMin() const {
    Node* node = find_min(root_);
    if (node == nullptr) {
      return std::nullopt;
    } else {
      return node->value;
    }
  }

  std::optional<int> BinarySearchTree::FindMax() const {
    Node* node = find_max(root_);
    if (node == nullptr) {
      return std::nullopt;
    } else {
      return node->value;
    }
  }

  Node* BinarySearchTree::root() const {
    return root_;
  }

  // вспомогательные методы

  void BinarySearchTree::insert(int key, int value, Node*& node) {
    if (key == node->key) {
      node->value = value;

    } else if (key < node->key) {
      if (node->left != nullptr) {
        insert(key, value,node->left);
      } else {
        node->left = new Node(key,value);
      }

    } else {
      if (node->right != nullptr) {
        insert(key, value,node->right);
      } else {
        node->right = new Node(key,value);
      }
    }
  }

  bool BinarySearchTree::remove(int key, Node*& node) {
    if (!Contains(key)) {
      return false;
    }

    if (key < node->key) {
      return remove(key, node->left);
    }
    if (key > node->key) {
      return remove(key, node->right);
    } else {
      if (node->right != nullptr && node->left != nullptr) {
        Node* min = find_min(node->right);
        node->key = min->key;
        node->value = min->value;
        return remove(min->key, node->right);
      }
      if (node->right != nullptr) {
        Node* node2 = node->right;
        delete node;
        node = node2;
        return true;
      } else {
        Node* node2 = node->left;
        delete node;
        node = node2;
        return true;
      }
    }
  }

  void BinarySearchTree::clear(Node* node) {
    if (node == nullptr) {
      return;
    }
    clear(node->left);
    clear(node->right);
    delete node;
  }

  Node* BinarySearchTree::find(int key, Node* node) const {
    if (node == nullptr) {
      return nullptr;
    } else if (key == node->key) {
      return node;
    } else if (key < node->key) {
      return find(key, node->left);
    } else {
      return find(key, node->right);
    }
  }

  Node* BinarySearchTree::find_min(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    while (node->left != nullptr) {
      node = node->left;
    }
    return node;
  }

  Node* BinarySearchTree::find_max(Node* node) const {
    if (node == nullptr) {
      return nullptr;
    }
    while (node->right != nullptr) {
      node = node->right;
    }
    return node;
  }

}  // namespace assignment