/*
Given an array int32 arr[] of size n, return the number of
non-empty contigious subarrays whose sum lies in range [a, b]

That is, implement the following naive algorithm faster than O(n^2)


def naive_algorithm(lst, a, b):
    result = 0
    for i in xrange(len(lst)):
        for j in xrange(i, len(lst)):
            if a <= sum(lst[i:j + 1]) <= b:
                result += 1
    return result
Examples:


count([1,2,3], 0, 3) = 4 # [1], [2], [3], [1, 2]
count([-2,5,-1], -2, 2) = 3 # [-2], [-1], [-2, 5, -1]
You may assume that there are no overflows, that is sum(|x_i|) <= MAX_INT - 1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE SubarraysInRangeTests
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

bool inRange(int number, int a, int b) {
  return number >= a && number <= b;
}
int nSubarraysInRange(std::vector<int> array, int a, int b) {
  BST sums;
  sums.add(0);
  int sum = 0,
      result = 0;

  for (int number: array) {
    sum += number;
    result += nBetween(sums, sum - b, sum - a);
    sums.add(sum);
  }

  return result;
}

#define CHECK_SUBARRAYS_IN_RANGE(arrayValues, a, b, expectedN) { \
  std::vector<int> array = arrayValues; \
  int actualN = nSubarraysInRange(array, a, b); \
  BOOST_CHECK_EQUAL(actualN, expectedN); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( subarrays_in_range_tests ) {
  CHECK_SUBARRAYS_IN_RANGE({}, 0, 0, 0)
  CHECK_SUBARRAYS_IN_RANGE({}, 1, 3, 0)
  CHECK_SUBARRAYS_IN_RANGE({0}, 0, 0, 1)
  CHECK_SUBARRAYS_IN_RANGE({0}, -2, 2, 1)
  CHECK_SUBARRAYS_IN_RANGE({1}, 1, 1, 1)
  CHECK_SUBARRAYS_IN_RANGE({1}, 1, 10, 1)
  CHECK_SUBARRAYS_IN_RANGE(ARRAY_ARG_PROTECT({
    2, -1, 2
  }), 1, 2, 4);
  CHECK_SUBARRAYS_IN_RANGE(ARRAY_ARG_PROTECT({
    1, 2, 3
  }), 0, 3, 4);
  CHECK_SUBARRAYS_IN_RANGE(ARRAY_ARG_PROTECT({
    -2, 5, -1
  }), -2, 2, 3);

}
