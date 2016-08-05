/*
Given an unsorted array of integers, you need to return maximum possible n
 such that the array consists at least n values greater than or equals to n.
 Array can contain duplicate values.
Sample input : [1, 2, 3, 4] -- output : 2
Sample input : [900, 2, 901, 3, 1000] -- output: 3
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE NOfArrayTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<int> countNumbers(std::vector<int> array) {
  std::vector<int> numbersCounts(array.size() + 1, 0);

  for (int number: array) {
    if (number >= 0 && number <= array.size()) {
      numbersCounts[number]++;
    } else if (number > array.size()) {
      numbersCounts[array.size()]++;
    }
  }

  return numbersCounts;
}

int findN(std::vector<int> array) {
  auto numbersCounts = countNumbers(array);

  int n = array.size(),
   nextCount = numbersCounts[n];
  while (nextCount < n) {
    n--;
    nextCount += numbersCounts[n];
  }

  return n;
}

#define CHECK_N_OF_ARRAY(arrayValues, expectedN) { \
  std::vector<int> array = arrayValues; \
  int actualN = findN(array); \
  BOOST_CHECK_EQUAL(expectedN, actualN); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( is_square_tests ) {

  CHECK_N_OF_ARRAY(ARRAY_ARG_PROTECT({
    1, 2, 3, 4
  }), 2)

  CHECK_N_OF_ARRAY(ARRAY_ARG_PROTECT({
    900, 2, 901, 3, 1000
  }), 3)

}
