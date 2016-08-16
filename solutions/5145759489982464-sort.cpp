/*
Given an array of integers, sort the array into a wave like array, namely
a1 >= a2 <= a3 >= a4 <= a5.....
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE SortTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

bool isSorted(std::vector<int> &array) {
  bool nextSmallerOrEqual = true;
  for (int i = 1 ; i < array.size() ; ++i) {
    if ((nextSmallerOrEqual && array[i] > array[i - 1]) ||
      (!nextSmallerOrEqual && array[i] < array[i - 1]))
    {
      return false;
    }
    nextSmallerOrEqual = !nextSmallerOrEqual;
  }
  return true;
}

void swap(std::vector<int> &array, int i, int j) {
  int buff = array[i];
  array[i] = array[j];
  array[j] = buff;
}

void sort(std::vector<int> &array) {
  bool nextSmallerOrEqual = true;
  for (int i = 1 ; i < array.size() ; ++i) {
    if ((nextSmallerOrEqual && array[i] > array[i - 1]) ||
      (!nextSmallerOrEqual && array[i] < array[i - 1]))
    {
      swap(array, i, i - 1);
    }
    nextSmallerOrEqual = !nextSmallerOrEqual;
  }
}

#define CHECK_SORT_ALL(n) { \
  std::vector<std::vector<int>> testCases = allPermutations(n, n); \
  for (auto nextCase: testCases) { \
    CHECK_SORT(nextCase); \
  } \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

std::vector<std::vector<int>> allPermutations(int n, int maxValue) {
  if (n == 0) {
    return std::vector<std::vector<int>>({{}});
  }
  std::vector<std::vector<int>> result;
  for (int i = 1 ; i <= maxValue ; ++i) {
    auto partPermutations = allPermutations(n - 1, maxValue);
    for (auto part: partPermutations) {
      std::vector<int> copy(part.begin(), part.end());
      copy.push_back(i);
      result.push_back(copy);
    }
  }
  return result;
}

#define CHECK_SORT(arrayValues) { \
  std::vector<int> array = arrayValues; \
  sort(array); \
  bool sorted = isSorted(array); \
  BOOST_CHECK_EQUAL(sorted, true); \
}

BOOST_AUTO_TEST_CASE( sort_tests ) {
  CHECK_SORT_ALL(3)
  CHECK_SORT_ALL(4)
  CHECK_SORT_ALL(5)
  CHECK_SORT_ALL(6)
  CHECK_SORT_ALL(7)

  CHECK_SORT(ARRAY_ARG_PROTECT({
    1, 2, 3, 4, 5, 6
  }))
}
