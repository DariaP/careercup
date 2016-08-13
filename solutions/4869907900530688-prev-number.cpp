/*
Find next higher number with same digits.

Example 1 : if num = 25468, o/p = 25486
Example 2 : if num = 21765, o/p = 25167
Example 3 : If num = 54321, o/p = 54321 (cause it's not possible
to gen a higher num than tiz with given digits ).
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE PrevNumberTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int findStartOfDescendingEnd(const std::vector<int> &digits) {
  int i = digits.size() - 1;
  while (i >= 1 && digits[i - 1] > digits[i]) --i;
  return i;
}

std::vector<int> getDigits(int initNumber) {
  int number = initNumber;
  std::vector<int> result;

  while (number != 0) {
    result.push_back(number % 10);
    number = number / 10;
  }

  std::reverse(result.begin(), result.end());
  return result;
}

int makeNumber(const std::vector<int> digits) {
  int result = 0;
  for (int digit: digits) {
    result = result * 10 + digit;
  }
  return result;
}

int findSuccessorIdx(const std::vector<int> &digits, int digitIdx) {
  int start = digitIdx + 1, end = digits.size() - 1,
    digit = digits[digitIdx];

  while (start != end) {
    int middle = (start + end) / 2;
    if (digits[middle] < digit) {
      start = middle + 1;
    } else {
      end = middle;
    }
  }
  return start;
}

void swap(std::vector<int> &array, int i, int j) {
  int buffer = array[i];
  array[i] = array[j];
  array[j] = buffer;
}

int prevNumber(int number) {
  std::vector<int> digits = getDigits(number);

  int i = findStartOfDescendingEnd(digits);
  if (i <= 0) {
    return number;
  }

  std::sort(digits.begin() + i, digits.end());
  int swapIdx = findSuccessorIdx(digits, i - 1);
  swap(digits, i - 1, swapIdx);

  return makeNumber(digits);
}


#define CHECK_PREV_NUMBER(number, expectedResult) { \
  int actualResult = prevNumber(number); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( prev_number_tests ) {
  CHECK_PREV_NUMBER(0, 0)
  CHECK_PREV_NUMBER(1, 1)
  CHECK_PREV_NUMBER(11, 11)
  CHECK_PREV_NUMBER(10, 10)
  CHECK_PREV_NUMBER(12, 21)
  CHECK_PREV_NUMBER(123, 132)
  CHECK_PREV_NUMBER(132, 213)
  CHECK_PREV_NUMBER(25468, 25486)
  CHECK_PREV_NUMBER(21765, 25167)
  CHECK_PREV_NUMBER(259641, 261459)
}
