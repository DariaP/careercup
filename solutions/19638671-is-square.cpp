/*
Write a program to find whether a given number is a perfect square or not.
You can only use addition and subtraction
operation to find a solution with min. complexity.

i/p : 25
o/p : True

i/p : 44
o/p: False
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE IsSquareTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

bool isSquare(int number) {
  if (number == 0) return true;

  int sum = 0, i = 1;
  while (sum < number) {
    sum += i;
    if (sum == number) {
      return true;
    }
    i = i + 2;
  }
  return false;
}

#define CHECK_IS_SQUARE(number, expectedResult) { \
  bool actualResult = isSquare(number); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

BOOST_AUTO_TEST_CASE( is_square_tests ) {
  CHECK_IS_SQUARE(0, true);
  CHECK_IS_SQUARE(1, true);
  CHECK_IS_SQUARE(4, true);
  CHECK_IS_SQUARE(3, false);
  CHECK_IS_SQUARE(5, false);
  CHECK_IS_SQUARE(-1, false);
  CHECK_IS_SQUARE(225, true);
  CHECK_IS_SQUARE(25, true);
  CHECK_IS_SQUARE(44, false);
}
