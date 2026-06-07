// Copyright 2021 NNTU-CS
#ifndef INCLUDE_BST_H_
#define INCLUDE_BST_H_
#include <algorithm>
#include <utility>
#include <string>
#include <vector>

template <typename T>
class BST {
 private:
    struct Node {
      T word;
      int frequency;
      Node* leftBranch;
      Node* rightBranch;
      explicit Node(const T& w)
        : word(w), frequency(1), leftBranch(nullptr), rightBranch(nullptr) {}
    };
    Node* root;
    Node* addNode(Node* node, const T& value) {
      if (!node) return new Node(value);
      if (value < node->word) node->leftBranch = addNode(node->leftBranch, value);
      else if (value > node->word) node->rightBranch = addNode(node->rightBranch, value);
      else node->frequency++;
      return node;
    }
    int searchNode(Node* node, const T& value) const {
      if (!node) return 0;
      if (value == node->word) return node->frequency;
      if (value < node->word) return searchNode(node->leftBranch, value);
      return searchNode(node->rightBranch, value);
    }
    int depthNode(Node* node) const {
      if (!node) return -1;
      int leftHeight = depthNode(node->leftBranch);
      int rightHeight = depthNode(node->rightBranch);
      return std::max(leftHeight, rightHeight) + 1;
    }
    void inorder(Node* node, std::vector<std::pair<T, int>>& out) const {
      if (!node) return;
      inorder(node->leftBranch, out);
      out.emplace_back(node->word, node->frequency);
      inorder(node->rightBranch, out);
    }
    void clear(Node* node) {
      if (!node) return;
      clear(node->leftBranch);
      clear(node->rightBranch);
      delete node;
    }

 public:
    BST() : root(nullptr) {}
    ~BST() { clear(root); }

    void insert(const T& value) { root = addNode(root, value); }

    int search(const T& value) const { return searchNode(root, value); }

    int depth() const { return depthNode(root); }

    void getFreqList(std::vector<std::pair<T, int>>& out) const {
      inorder(root, out);
    }
};

#endif  // INCLUDE_BST_H_
