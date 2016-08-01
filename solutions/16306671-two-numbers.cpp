/*
You are given an integer array, where all numbers except for TWO numbers appear even number of times.
Q: Find out the two numbers which appear odd number of times.
*/

#include <iostream>
#include <vector>
#include <bitset>
#define BOOST_TEST_MODULE TwoNumbersTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int findPositionOfOne(int number) {
  int position = 0;
  while (number % 2 == 0) {
    position++;
    number = number >> 1;
  }
  return position;
}

bool hasOne(int number, int position) {
  int mask = 1 << position;
  return (number & mask) != 0;
}

std::pair<int, int> findTwoNumbers(std::vector<int> numbers) {

  int xorAll = 0;
  for (int number: numbers) {
    xorAll ^= number;
  }

  int diffBitsPosition = findPositionOfOne(xorAll);

  int xorAllWithOne = 0, xorAllWithZero = 0;
  for (int number: numbers) {
    if (hasOne(number, diffBitsPosition)) {
      xorAllWithOne ^= number;
    } else {
      xorAllWithZero ^= number;
    }
  }

  return std::pair<int, int>(xorAllWithOne, xorAllWithZero);
}

#define CHECK_TWO_NUMBERS(numbersArray, expectedResultArray) { \
	std::pair<int, int> expectedResult = expectedResultArray; \
  std::vector<int> numbers = numbersArray; \
  auto actualResult = findTwoNumbers(numbers); \
  if (expectedResult != actualResult) { \
    std::pair<int, int> anotherExpectedResult(expectedResult.second, expectedResult.first); \
    BOOST_CHECK_EQUAL(anotherExpectedResult, actualResult); \
  } else { \
    BOOST_CHECK_EQUAL(expectedResult, actualResult); \
  } \
}

namespace std {
    ostream &operator<<(ostream &stream, const std::pair<int, int> &p) {
      stream << "(" << p.first << ", " << p.second << ")";
      return stream;
    }
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__


BOOST_AUTO_TEST_CASE( two_numbers_tests ) {

  CHECK_TWO_NUMBERS(
    ARRAY_ARG_PROTECT({1, 2}),
    ARRAY_ARG_PROTECT({1, 2})
  )

  CHECK_TWO_NUMBERS(
    ARRAY_ARG_PROTECT({1, 2, 2, 3}),
    ARRAY_ARG_PROTECT({1, 3})
  )

  CHECK_TWO_NUMBERS(
    ARRAY_ARG_PROTECT({1, 3, 3, 3}),
    ARRAY_ARG_PROTECT({1, 3})
  )

  CHECK_TWO_NUMBERS(
    ARRAY_ARG_PROTECT({1, 2, 5, 2, 1, 5, 5, 6, 6, 9, 2, 2}),
    ARRAY_ARG_PROTECT({5, 9})
  )
}
