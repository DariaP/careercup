/*
Given 2 arrays.Imagine you are making bst from each array.
u need to tell whether 2 bsts will be identical or not
without actually constructing the tree.
Ex:
2 3 1
2 1 3
will construct the same tree
A1[]={2,1,3}
2
1 3

A2[]={2,3,1}
2
1 3*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE TwoBSTsTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int partition(std::vector<int> &array, int start, int end, int pivot) {
  std::vector<int> buffer(end - start + 1);
  int leftIdx = start, rightIdx = end;

  for (int i = start ; i <= end ; ++i) {
    int value = array[i];
    if (value < pivot) {
      buffer[leftIdx++] = value;
    } else if (value > pivot ){
      buffer[rightIdx--] = value;
    }
  }

  array[leftIdx] = pivot;
  for (int i = 0 ; i < leftIdx ; ++i) {
    array[start + i] = buffer[i];
  }
  for (int i = rightIdx + 1 ; i < array.size() ; ++i) {
    array[start + i] = buffer[array.size() - 1 - (rightIdx + 1) + i];
  }

  return leftIdx;
}

bool sameBST_helper(std::vector<int> array1, std::vector<int> array2, int start, int end) {

  if (start > end) {
    return true;
  }

  if (array1[start] != array2[start]) {
    return false;
  }

  int pivot1Idx = partition(array1, start, end, array1[start]),
      pivot2Idx = partition(array2, start, end, array2[start]);

  return (pivot1Idx == pivot2Idx) &&
    sameBST_helper(array1, array2, start, pivot1Idx - 1) &&
    sameBST_helper(array1, array2, pivot1Idx + 1, end);
}

bool sameBST(std::vector<int> array1, std::vector<int> array2) {
  if (array1.size() != array2.size()) {
    return false;
  }
  return sameBST_helper(array1, array2, 0, array1.size() - 1);
}

#define CHECK_SAME_BSTS(array1Values, array2Values, expectedAnswer) { \
  std::vector<int> array1 = array1Values, array2 = array2Values; \
  bool actualAnswer = sameBST(array1, array2); \
  BOOST_CHECK_EQUAL(actualAnswer, expectedAnswer); \
}
#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( two_bsts_tests ) {
  CHECK_SAME_BSTS({}, {}, true)
  CHECK_SAME_BSTS({1}, {1}, true)
  CHECK_SAME_BSTS({1}, {2}, false)

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      2,1
    }),
    ARRAY_ARG_PROTECT({
      2,3
    }),
    false
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      2,1
    }),
    ARRAY_ARG_PROTECT({
      1,2
    }),
    false
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      2,1
    }),
    ARRAY_ARG_PROTECT({
      2,1
    }),
    true
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      2,1,3
    }),
    ARRAY_ARG_PROTECT({
      2,3,1
    }),
    true
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      2,1,3
    }),
    ARRAY_ARG_PROTECT({
      3,2,1
    }),
    false
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      5,1,3
    }),
    ARRAY_ARG_PROTECT({
      5,3,1
    }),
    false
  )

  CHECK_SAME_BSTS(
    ARRAY_ARG_PROTECT({
      5,3,7,6,1
    }),
    ARRAY_ARG_PROTECT({
      5,7,6,3,1
    }),
    true
  )

}
