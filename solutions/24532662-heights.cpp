/*
You are given two array, first array contain integer which represent heights of persons and second array contain how many persons in front of him are standing who are greater than him in term of height and forming a queue. Ex
A: 3 2 1
0 1
B: 0 1 1
It means in front of person of height 3 there is no person standing, person of height 2 there is one person in front of him who has greater height then he, similar to person of height 1. Your task to arrange them
Ouput should be.
3 1 2
Here - 3 is at front, 1 has 3 in front ,2 has 1 and 3 in front.
*/

#include <iostream>
#include <vector>
#include <cmath>
#define BOOST_TEST_MODULE HeightsTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Arrangement {

  class Node {
  public:
    Node *left, *right;
    int value;
    int availableLeft;
    bool available;
    Node() {
      left = nullptr;
      right = nullptr;
      availableLeft = 0;
      available = true;
    }
  };

  Node *root;

  Node *makeTree(int size) {
    if (size == 0) {
      return nullptr;
    } else {
      Node *root = new Node();
      int leftSubtreeSize = std::ceil(((double)size - 1) / 2);
      root->left = makeTree(leftSubtreeSize);
      root->right = makeTree(size - 1 - leftSubtreeSize);
      root->availableLeft = leftSubtreeSize;
      return root;
    }
  }

  void insertTo(Node *node, int value, int number) {
    if (node->availableLeft == number) {
      if (node->available) {
        node->available = false;
        node->value = value;
      } else {
        insertTo(node->right, value, number - node->availableLeft);
      }
    } else if (node->availableLeft > number) {
      node->availableLeft--;
      insertTo(node->left, value, number);
    } else {
      insertTo(node->right, value, number - node->availableLeft - (node->available ? 1 : 0));
    }
  }

  void inOrder(Node *node, std::vector<int> &result) {
    if (!node) {
      return;
    }

    if (node->left) {
      inOrder(node->left, result);
    }
    result.push_back(node->value);
    if (node->right) {
      inOrder(node->right, result);
    }
  }

public:
  Arrangement(int size) {
    root = makeTree(size);
  }

  void insert(int value, int number) {
    insertTo(root, value, number);
  }

  std::vector<int> order() {
    std::vector<int> result;
    inOrder(root, result);
    return result;
  }
};

std::vector<int> arrange(std::vector<int> heights, std::vector<int> numbers) {
  Arrangement arrangement(heights.size());

  for (int i = heights.size() - 1 ; i >= 0  ; --i) {
    arrangement.insert(heights[i], numbers[i]);
  }

  return arrangement.order();
}

#define CHECK_HEIGHTS(heightsValues, numbersValues, expectedArrangementValues) { \
	std::vector<int> heights = heightsValues, \
    numbers = numbersValues, \
    expectedArrangement = expectedArrangementValues; \
  auto actualArrangement = arrange(heights, numbers); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedArrangement.begin(), expectedArrangement.end(), \
    actualArrangement.begin(), actualArrangement.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( heights_tests ) {
  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({3, 2, 1}),
    ARRAY_ARG_PROTECT({0, 1, 1}),
    ARRAY_ARG_PROTECT({3, 1, 2})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({}),
    ARRAY_ARG_PROTECT({}),
    ARRAY_ARG_PROTECT({})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({1}),
    ARRAY_ARG_PROTECT({0}),
    ARRAY_ARG_PROTECT({1})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({2, 1}),
    ARRAY_ARG_PROTECT({0, 0}),
    ARRAY_ARG_PROTECT({1, 2})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({2, 1}),
    ARRAY_ARG_PROTECT({0, 1}),
    ARRAY_ARG_PROTECT({2, 1})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({6, 5, 4, 3, 2, 1}),
    ARRAY_ARG_PROTECT({0, 0, 0, 2, 2, 4}),
    ARRAY_ARG_PROTECT({4, 5, 2, 3, 1, 6})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({6, 5, 4, 3, 2, 1}),
    ARRAY_ARG_PROTECT({0, 0, 0, 0, 0, 0}),
    ARRAY_ARG_PROTECT({1, 2, 3, 4, 5, 6})
  )

  CHECK_HEIGHTS(
    ARRAY_ARG_PROTECT({5, 4, 3, 2, 1}),
    ARRAY_ARG_PROTECT({0, 0, 2, 0, 0}),
    ARRAY_ARG_PROTECT({1, 2, 4, 5, 3})
  )

}
