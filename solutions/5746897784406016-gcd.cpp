#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#define BOOST_TEST_MODULE GCDTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

typedef std::vector<std::vector<int>> Matrix;

class Submatrix {
public:
  int left, right, top, bottom;
  Submatrix(int l, int r, int t, int b) {
    left = l; right = r; top = t; bottom = b;
  }

  bool covers(Submatrix &another) {
    return another.left <= left && another.right >= right
     && another.top <= top && another.bottom >= bottom;
  }

  bool intersects(Submatrix &another) {
    int iLeft = std::max(left, another.left),
      iRight = std::min(right, another.right),
      iTop = std::max(top, another.top),
      iBottom = std::min(bottom, another.bottom);

    return iLeft <= iRight && iTop <= iBottom;
  }

  int size() {
    return (right - left + 1) * (bottom - top + 1);
  }

  std::vector<Submatrix> split() {
    std::vector<Submatrix> result;
    int leftBorder = (left + right) / 2,
      topBorder = (top + bottom) / 2;

    result.push_back(Submatrix(left, leftBorder, top, topBorder));
    result.push_back(Submatrix(left, leftBorder, topBorder + 1, bottom));
    result.push_back(Submatrix(leftBorder + 1, right, top, topBorder));
    result.push_back(Submatrix(leftBorder + 1, right, topBorder + 1, bottom));

    return result;
  }
};

class QuadNode {
public:
  int value;
  std::vector<QuadNode*> children;
  virtual bool intersects(Submatrix &submatrix)=0;
  virtual bool isLeaf()=0;
  virtual bool covers(Submatrix &submatrix) = 0;
};

class QuadTreeNode: public QuadNode {
public:
  Submatrix area;
  QuadTreeNode(Submatrix &initArea): area(initArea) {}
  bool isLeaf() {
    return false;
  }

  bool covers(Submatrix &submatrix) {
    return area.covers(submatrix);
  }

  bool intersects(Submatrix &submatrix) {
    return area.intersects(submatrix);
  }
};

class QuadLeafNode: public QuadNode {
public:
  int left, top;
  QuadLeafNode(int initValue) {
    value = initValue;
  }
  bool isLeaf() {
    return true;
  }
  bool covers(Submatrix &submatrix) {
    return intersects(submatrix);
  }
  bool intersects(Submatrix &submatrix) {
    return (submatrix.top <= top && submatrix.bottom >= top
      && submatrix.left <= left && submatrix.right >= left);
  }
};

int eulerGCD(int a, int b) {
  if (a < b) return eulerGCD(b, a);

  if (b == 0) {
    return a;
  }
  return eulerGCD(b, a % b);
}

QuadNode *preprocessMatrix(const Matrix &values, Submatrix interval) {
  if (interval.size() == 0) {
    return nullptr;
  }

  if (interval.size() == 1) {
    QuadLeafNode *leaf = new QuadLeafNode(values[interval.top][interval.left]);
    leaf->top = interval.top;
    leaf->left = interval.left;
    return leaf;
  } else {
    QuadTreeNode *node = new QuadTreeNode(interval);
    std::vector<Submatrix> subIntervals = interval.split();
    for (Submatrix subInterval: subIntervals) {
      QuadNode *child = preprocessMatrix(values, subInterval);
      if (nullptr != child) {
        node->children.push_back(child);
      }
    }
    return node;
  }
}

int eulerGCD(std::vector<int> numbers) {
  if (numbers.size() == 1) {
    return numbers[0];
  }
  int result = eulerGCD(numbers[0], numbers[1]);
  for (int i = 2 ; i < numbers.size() ; ++i) {
    result = eulerGCD(result, numbers[i]);
  }
  return result;
}

class GCDFinder {
  QuadNode* root;
  const Matrix &values;

  int calcGCDHelper(QuadNode *nextNode,
    Submatrix &submatrix)
  {
    std::vector<int> nodes;

    if (nextNode->covers(submatrix)) {
        return nextNode->value;
    }

    for (QuadNode *child: root->children) {
      if (child->intersects(submatrix)) {
        if (child->isLeaf()) {
          nodes.push_back(child->value);
        } else {
          nodes.push_back(calcGCDHelper(child, submatrix));
        }
      }
    }

    return eulerGCD(nodes);
  }

public:
  GCDFinder(Matrix &initValues): values(initValues) {
    root = preprocessMatrix(values, Submatrix(
      0, values.size() - 1, 0, values.size() - 1));
  }

  int calcGCD(Submatrix submatrix) {
    return calcGCDHelper(root, submatrix);
  }
};

#define TEST_GCD(a, b, expectedResult) { \
  int actualResult = eulerGCD(a, b); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({a, b}), expectedResult) \
}

#define TEST_VECTOR_GCD(values, expectedResult) { \
  int actualResult = eulerGCD(std::vector<int>(values)); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

#define TEST_SUBMATRIX_INTERSECTION(m1Values, m2Values, expectedAnswer) { \
  Submatrix m1(m1Values), m2(m2Values); \
  bool actualAnswer = m1.intersects(m2); \
  BOOST_CHECK_EQUAL(expectedAnswer, actualAnswer); \
  actualAnswer = m2.intersects(m1); \
  BOOST_CHECK_EQUAL(expectedAnswer, actualAnswer); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( gcd_tests ) {
  TEST_GCD(1, 1, 1)
  TEST_GCD(1, 2, 1)
  TEST_GCD(2, 2, 2)
  TEST_GCD(4, 2, 2)
  TEST_GCD(2, 4, 2)
  TEST_GCD(15, 25, 5)

  TEST_VECTOR_GCD({1}, 1)
  TEST_VECTOR_GCD({2}, 2)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    1, 2, 3
  }), 1)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    2, 2, 3
  }), 1)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    2, 2, 2
  }), 2)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    2, 4, 8
  }), 2)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    15, 25, 35
  }), 5)

  TEST_VECTOR_GCD(ARRAY_ARG_PROTECT({
    2, 4, 6
  }), 2)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      0, 0, 0, 0
    ), ARRAY_ARG_PROTECT(
      0, 0, 0, 0
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      0, 0, 0, 0
    ), ARRAY_ARG_PROTECT(
      1, 1, 1, 1
    ), false)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      0, 2, 0, 2
    ), ARRAY_ARG_PROTECT(
      1, 2, 1, 2
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      0, 2, 0, 2
    ), ARRAY_ARG_PROTECT(
      1, 3, 1, 3
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      0, 2, 0, 2
    ), ARRAY_ARG_PROTECT(
      0, 2, 0, 2
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      0, 2, 0, 2
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      0, 2, 2, 5
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      2, 5, 0, 2
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      2, 5, 2, 5
    ), true)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      0, 0, 2, 5
    ), false)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      0, 2, 4, 8
    ), false)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      6, 9, 2, 5
    ), false)

  TEST_SUBMATRIX_INTERSECTION(
    ARRAY_ARG_PROTECT(
      1, 4, 1, 3
    ), ARRAY_ARG_PROTECT(
      5, 5, 0, 2
    ), false)

}
