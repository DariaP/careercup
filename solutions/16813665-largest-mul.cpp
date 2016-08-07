/*
Given a sequence of non-negative integers find a subsequence of length 3 having maximum product with the numbers of the subsequence being in ascending order.
Example:
Input: 6 7 8 1 2 3 9 10
Ouput: 8 9 10
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE StringCodesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class BSTNode {
public:
  BSTNode *left, *right;
  int value, idx;
  BSTNode(int initValue, int initIdx): value(initValue),
    left(nullptr), right(nullptr), idx(initIdx) {}

  void add(int newValue, int newIdx) {
    if (newValue < value || (newValue == value && newIdx < idx)) {
      if (left) {
        left->add(newValue, newIdx);
      } else {
        left = new BSTNode(newValue, newIdx);
      }
    } else {
      if (right) {
        right->add(newValue, newIdx);
      } else {
        right = new BSTNode(newValue, newIdx);
      }
    }
  }
};

class BST {
public:
  //----------------------------------------
  BSTNode *root;
  int nextIdx;

  BST(): root(nullptr), nextIdx(0) {}

  void add(int value) {
    if (root) {
      root->add(value, nextIdx);
    } else {
      root = new BSTNode(value, nextIdx);
    }
    nextIdx++;
  }

  int predcessor(int value) {
    BSTNode *nextNode = root;
    int result = -1;

    while (nextNode != nullptr) {
      if (value > nextNode->value || (nextNode->value == value && nextNode->idx > nextIdx)) {
        result = nextNode->idx;
        nextNode = nextNode->right;
      } else {
        if (nextNode->value == value) {
          result = nextNode->idx;
        }
        nextNode = nextNode->left;
      }
    }

    return result;
  }

};

std::vector<int> findPrevLargestIndices(std::vector<int> array) {
  std::vector<int> result;
  BST bst;

  for (int value: array) {
    result.push_back(bst.predcessor(value));
    bst.add(value);
  }

  return result;
}

std::vector<int> getNextSubseq(std::vector<int> &array,
  int idx,
  int n,
  std::vector<int> &prevLargesIdxs)
{
  std::vector<int> result;

  int nextIdx = idx;
  while (nextIdx != -1 && result.size() < n) {
    result.push_back(array[nextIdx]);
    nextIdx = prevLargesIdxs[nextIdx];
  }

  return result;
}

int calcProduct(std::vector<int> array) {
  int result = 1;
  for (int value: array) {
    result *= value;
  }
  return result;
}

std::vector<int> findMaxProductSubsequence(std::vector<int> array) {

  std::vector<int> prevLargesIdxs = findPrevLargestIndices(array);

  int maxProduct = 1;
  std::vector<int> result;

  for (int i = array.size() - 1 ; i >= 0 ; --i) {
    std::vector<int> nextSubseq = getNextSubseq(array, i, 3, prevLargesIdxs);
    if (nextSubseq.size() < 3) continue;
    int nextProduct = calcProduct(nextSubseq);
    if (nextProduct > maxProduct) {
      result = nextSubseq;
      maxProduct = nextProduct;
    }
  }

  return result;
}

#define CHECK_LARGEST_PRODUCT(arrayValues, expectedIndicesValues) { \
  std::vector<int> array = arrayValues, expectedIndices = expectedIndicesValues; \
  auto actualIndices = findMaxProductSubsequence(array); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedIndices.begin(), expectedIndices.end(), \
    actualIndices.begin(), actualIndices.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( string_codes_tests ) {
  CHECK_LARGEST_PRODUCT(ARRAY_ARG_PROTECT({
    6, 7, 8, 1, 2, 3, 9, 10
  }), ARRAY_ARG_PROTECT({
    10, 9, 8
  }))

  CHECK_LARGEST_PRODUCT(ARRAY_ARG_PROTECT({
    1, 2, 9, 9, 6, 10, 7, 8
  }), ARRAY_ARG_PROTECT({
    10, 9, 9
  }))

  CHECK_LARGEST_PRODUCT(ARRAY_ARG_PROTECT({
    1, 2, 1, 2, 3, 10, 7, 8, 9
  }), ARRAY_ARG_PROTECT({
    9, 8, 7
  }))

}
