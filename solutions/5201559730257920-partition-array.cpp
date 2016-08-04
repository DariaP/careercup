/*
Give you an array which has n integers,it has both positive and negative integers.
Now you need sort this array in a special way.
After that,the negative integers should in the front,and the positive integers should in the back.
Also the relative position should not be changed.
eg. -1 1 3 -2 2 ans: -1 -2 1 3 2.
o(n)time complexity and o(1) space complexity is perfect.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE PartitionArrayTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

void swap(std::vector<int> &array, int i, int j) {
  int buff = array[i];
  array[i] = array[j];
  array[j] = buff;
}

void reverse(std::vector<int> &array, int startIdx, int endIdx) {
  for (int i = 0 ; i <= (endIdx - startIdx) / 2 ; ++i) {
    swap(array, startIdx + i, endIdx - i);
  }
}

void swapParts(std::vector<int> &array, int startIdx, int endIdx) {
  reverse(array, startIdx, endIdx);

  int middle = startIdx;
  while(array[middle] < 0 && middle < endIdx) {
    middle++;
  }

  reverse(array, startIdx, middle - 1);
  reverse(array, middle, endIdx);

}

void merge(std::vector<int> &array, int startIdx, int endIdx) {
  int swapStart = startIdx, swapEnd = endIdx;
  while (array[swapStart] < 0 && swapStart <= endIdx) swapStart++;
  while (array[swapEnd] > 0 && swapEnd >= startIdx) swapEnd--;

  if (swapStart < swapEnd) {
    swapParts(array, swapStart, swapEnd);
  }
}

void partitionHelper(std::vector<int> &array, int startIdx, int endIdx) {

    if (endIdx <= startIdx) {
      return;
    }

    if (endIdx == startIdx + 1) {
      if (array[startIdx] > 0 && array[endIdx] < 0) {
        swap(array, startIdx, endIdx);
      }
    } else {
      int middleIdx = (endIdx + startIdx) / 2;
      partitionHelper(array, startIdx, middleIdx);
      partitionHelper(array, middleIdx + 1, endIdx);
      merge(array, startIdx, endIdx);
    }

}

void partition(std::vector<int> &array) {
    partitionHelper(array, 0, array.size() - 1);
}

#define CHECK_PARTITION(arrayValues, expectedArrayValues) { \
  std::vector<int> array = arrayValues, expectedArray = expectedArrayValues; \
  partition(array); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedArray.begin(), expectedArray.end(), \
    array.begin(), array.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__


BOOST_AUTO_TEST_CASE( partition_array_tests ) {
  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({-1, 1, 3, -2, 2}),
    ARRAY_ARG_PROTECT({-1, -2, 1, 3, 2})
  )

  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({-1, 1, 3, -5, -2, 2}),
    ARRAY_ARG_PROTECT({-1, -5, -2, 1, 3, 2})
  )

  CHECK_PARTITION({},{})
  CHECK_PARTITION({1},{1})
  CHECK_PARTITION({-1},{-1})
  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({1, 2}),
    ARRAY_ARG_PROTECT({1, 2})
  )
  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({-1, -2}),
    ARRAY_ARG_PROTECT({-1, -2})
  )
  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({-1, 2}),
    ARRAY_ARG_PROTECT({-1, 2})
  )
  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({1, -2}),
    ARRAY_ARG_PROTECT({-2, 1})
  )

  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({1, 3, -1, 2, -5, -2}),
    ARRAY_ARG_PROTECT({-1, -5, -2, 1, 3, 2})
  )

  CHECK_PARTITION(
    ARRAY_ARG_PROTECT({1, -4, 3, -1, -9, -5, -2, 8}),
    ARRAY_ARG_PROTECT({-4, -1, -9, -5, -2, 1, 3, 8})
  )

}
