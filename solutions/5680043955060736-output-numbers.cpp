/*
Output top N positive integer in string comparison order. For example, let's say N=1000, then you need to output in string comparison order as below:
1, 10, 100, 1000, 101, 102, ... 109, 11, 110, ...
*/

#include <iostream>
#include <vector>
#include <bitset>
#define BOOST_TEST_MODULE OutputNumbersTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int getNextNumber(int prevNumber, int n) {
  if (prevNumber * 10 <= n) {
    return prevNumber * 10;
  } else {
    int nextNumber = prevNumber;
    while (nextNumber % 10 == 9 || (nextNumber + 1) > n) {
      nextNumber /= 10;
    }
    return nextNumber + 1;
  }
}

std::vector<int> sortNumbers(int n) {
  std::vector<int> result;
  if (n <= 0) {
    return result;
  }

  int nextNumber = 1;
  while (result.size() < n) {
    result.push_back(nextNumber);
    nextNumber = getNextNumber(nextNumber, n);
  }

  return result;
}

#define CHECK_OUTPUT_NUMBERS(n, expectedSequenceValues) { \
  std::vector<int> expectedSequence = expectedSequenceValues, \
    actualSequence = sortNumbers(n); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedSequence.begin(), expectedSequence.end(), \
    actualSequence.begin(), actualSequence.end()); \
}

#define CHECK_OUTPUT_NUMBERS_FIRST_N(n, expectedSequenceValues) { \
  std::vector<int> expectedSequence = expectedSequenceValues, \
    actualSequence = sortNumbers(n); \
  actualSequence.resize(expectedSequence.size()); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedSequence.begin(), expectedSequence.end(), \
    actualSequence.begin(), actualSequence.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( anagram_substr_tests ) {

  CHECK_OUTPUT_NUMBERS(-2, {});
  CHECK_OUTPUT_NUMBERS(0, {});
  CHECK_OUTPUT_NUMBERS(1, {1});

  CHECK_OUTPUT_NUMBERS(9, ARRAY_ARG_PROTECT({
    1, 2, 3, 4, 5, 6, 7, 8, 9
  }));

  CHECK_OUTPUT_NUMBERS(10, ARRAY_ARG_PROTECT({
    1, 10, 2, 3, 4, 5, 6, 7, 8, 9
  }));

  CHECK_OUTPUT_NUMBERS(11, ARRAY_ARG_PROTECT({
    1, 10, 11, 2, 3, 4, 5, 6, 7, 8, 9
  }));

  CHECK_OUTPUT_NUMBERS(19, ARRAY_ARG_PROTECT({
    1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 3, 4, 5, 6, 7, 8, 9
  }));

  CHECK_OUTPUT_NUMBERS(20, ARRAY_ARG_PROTECT({
    1, 10, 11, 12, 13, 14, 15, 16, 17, 18, 19, 2, 20, 3, 4, 5, 6, 7, 8, 9
  }));

  CHECK_OUTPUT_NUMBERS_FIRST_N(1000, ARRAY_ARG_PROTECT({
    1, 10, 100, 1000, 101, 102, 103, 104, 105, 106,
    107, 108, 109, 11, 110, 111, 112, 113, 114,
    115, 116, 117, 118, 119, 12, 120, 121}));

}
