/*
we will name a number "aggregated number" if this number has the following attribute:
just like the Fibonacci numbers
1,1,2,3,5,8,13.....

the digits in the number can divided into several parts, and the
later part is the sum of the former parts.

like 112358, because 1+1=2, 1+2=3, 2+3=5, 3+5=8
122436, because 12+24=36
1299111210, because 12+99=111, 99+111=210
112112224, because 112+112=224
so can you provide a function to check whether this number is aggregated number or not?
*/

#include <iostream>
#include <cmath>
#define BOOST_TEST_MODULE IsAggregatedTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int countDigits(int initNumber) {
  int result = 1, number = initNumber / 10;
  while (number != 0) {
    result += 1;
    number /= 10;
  }
  return result;
}

int cutLastDigits(int &number, int nDigits) {
    int divider = std::pow(10, nDigits);
    int result = number % divider;
    number = number / divider;
    return result;
}

bool validLastTwoNumbers(int initNumber, int lastLength, int nextToLastLength) {
  int number = initNumber;
  int last = cutLastDigits(number, lastLength),
    nextToLast = cutLastDigits(number, nextToLastLength);

  while (number != 0) {
    int expectedNext = last - nextToLast;

    if (countDigits(number) < countDigits(expectedNext)) {
      return false;
    } else {
      int actualNext = cutLastDigits(number, countDigits(expectedNext));
      if (expectedNext != actualNext) {
        return false;
      }
    }

    last = nextToLast;
    nextToLast = expectedNext;
  }
  return true;
}

bool isAggregated(int number) {
  if (number <= 0) {
    return false;
  }

  int nDigits = countDigits(number);
  for (int i = 1 ; i <= nDigits / 2 ; ++i) {
    for (int j = 1 ; (i + j) <= nDigits - 1 ; ++j) {
      if (validLastTwoNumbers(number, i, j)) {
        return true;
      }
    }
  }
  return false;
}

#define CHECK_IS_AGGREGATED(number, expectedResult) { \
  bool actualResult = isAggregated(number); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

BOOST_AUTO_TEST_CASE( is_aggregated_tests ) {
  CHECK_IS_AGGREGATED(112, true);
  CHECK_IS_AGGREGATED(11, false);
  CHECK_IS_AGGREGATED(1, false);
  CHECK_IS_AGGREGATED(0, false);
  CHECK_IS_AGGREGATED(-1, false);
  CHECK_IS_AGGREGATED(112358, true);
  CHECK_IS_AGGREGATED(122436, true);
  CHECK_IS_AGGREGATED(1299111210, true);
  CHECK_IS_AGGREGATED(112112224, true);
  CHECK_IS_AGGREGATED(112112225, false);
}
