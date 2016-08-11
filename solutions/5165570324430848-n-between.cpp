/*
Given a Binary Search tree of integers, you need to return
the number of nodes having values between two given integers.
You can assume that you already have some extra information at each node
(number of children in left and right subtrees !!).*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE NBetweenTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class BSTNode {
public:
  BSTNode *left, *right;
  int subtreeSize;
  int value;

  BSTNode(int initValue): value(initValue),
    left(nullptr), right(nullptr), subtreeSize(1) {}

  void add(int newValue) {
    subtreeSize++;
    if (newValue <= value) {
      if (left) {
        left->add(newValue);
      } else {
        left = new BSTNode(newValue);
      }
    } else {
      if (right) {
        right->add(newValue);
      } else {
        right = new BSTNode(newValue);
      }
    }
  }

  int size() {
    return subtreeSize;
  }

  int rightSubtreeSize() {
    return (nullptr == right) ? 0 : right->size();
  }
};

class BST {
public:
  BSTNode *root;
  BST(): root(nullptr) {}

  void add(std::vector<int> values) {
    for (int value:values) {
      add(value);
    }
  }

  void add(int value) {
    if (root) {
      root->add(value);
    } else {
      root = new BSTNode(value);
    }
  }
};

int nLarger(BSTNode *root, int number, bool includeEqual) {
  if (root == nullptr) {
    return 0;
  }

  if (root->value == number) {
    return root->rightSubtreeSize() + (includeEqual ? 1 : 0);
  } else if (root->value > number) {
    return nLarger(root->left, number, includeEqual) + 1 + root->rightSubtreeSize();
  } else {
    return nLarger(root->right, number, includeEqual);
  }
}

int nBetween(BST &tree, int a, int b) {
  if (b < a) return 0;
  return nLarger(tree.root, a, true) - nLarger(tree.root, b, false);
}

#define CHECK_N_BETWEEN(treeValues, a, b, expectedN) { \
  BST tree; \
  tree.add(std::vector<int>(treeValues)); \
  int actualN = nBetween(tree, a, b); \
  BOOST_CHECK_EQUAL(actualN, expectedN); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( n_between_tests ) {
  CHECK_N_BETWEEN({}, 2, 4, 0)
  CHECK_N_BETWEEN({}, 0, 0, 0)
  CHECK_N_BETWEEN({1}, 2, 4, 0)
  CHECK_N_BETWEEN({1}, 1, 1, 1)
  CHECK_N_BETWEEN({1}, 2, 1, 0)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 1, 2, 2)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 2, 1, 0)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 0, 1, 1)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 0, 2, 2)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 0, 3, 2)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 1, 3, 2)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 2, 3, 1)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 2, 2, 1)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 3, 3, 0)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2
  }), 2, 4, 1)


  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    1, 2, 3, 4, 5
  }), 2, 4, 3)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    5, 4, 3, 2, 1
  }), 2, 4, 3)

  CHECK_N_BETWEEN(ARRAY_ARG_PROTECT({
    3, 4, 1, 5, 2
  }), 2, 4, 3)

}
