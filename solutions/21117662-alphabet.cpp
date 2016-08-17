/*
Imagine an alphabet of words. Example:
a ==> 1
b ==> 2
c ==> 3
.
z ==> 26
ab ==> 27
ac ==> 28
.
az ==> 51
bc ==> 52
and so on.

Such that the sequence of characters need to be in ascending order only (ab is valid but ba is not). Given any word print its index if valid and 0 if not.

Input	Output
ab	27
ba	0
aez	441

Note: Brute-force is not allowed.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE AlphabetTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#define CHECK_SUBARRAYS_IN_RANGE(arrayValues, a, b, expectedN) { \
  std::vector<int> array = arrayValues; \
  int actualN = nSubarraysInRange(array, a, b); \
  BOOST_CHECK_EQUAL(actualN, expectedN); \
}

int calcNextNumbers(std::vector<int> &numbers) {
  int prevNumber = 0, nextSum = 0;
  for (int i = numbers.size() - 1 ; i >= 0 ; --i) {
    nextSum += prevNumber;
    prevNumber = numbers[i];
    numbers[i] = nextSum;
  }
  return (nextSum + prevNumber);
}

int sumRange(std::vector<int> &numbers, int from, int to) {
  int sum = 0;
  for (int i = from ; i < to ; ++i) {
    sum += numbers[i];
  }
  return sum;
}

int letterNumber(std::string str) {
  int number = 1;
  int totalNumberOfPrevLength = 0;
  std::vector<int> numStartingFrom(26, 1);

  for (int i = 0 ; i < str.length() ; ++i) {
    char nextLetter = str[str.length() - 1 - i];
    number += totalNumberOfPrevLength;
    if (i == str.length() - 1) {
      number += sumRange(numStartingFrom, 0, nextLetter - 'a');
    } else {
      char prevChar = str[str.length() - 2 - i];
      number += sumRange(numStartingFrom, prevChar + 1 - 'a', nextLetter - 'a');
    }
    totalNumberOfPrevLength = calcNextNumbers(numStartingFrom);
  }
  return number;
}

#define CHECK_STRING(str, expectedNumber) { \
  int actualNumber = letterNumber(str); \
  BOOST_CHECK_EQUAL(expectedNumber, actualNumber); \
}

#define CHECK_STRINGS(maxLength) { \
  auto testSet = generate(maxLength); \
  for (auto testCase: testSet) { \
    int actualNumber = letterNumber(testCase.first); \
    BOOST_CHECK_EQUAL(testCase.second, actualNumber); \
    if (testCase.second != actualNumber) { \
      std::cout << testCase.first << " " << testCase.second << std::endl; \
      break; \
    } \
  } \
}

std::vector<std::pair<std::string, int>> generate(int maxLength) {
  std::vector<std::pair<std::string, int>> result;
  int i = 1;
  result.push_back(std::pair<std::string, int>("", 0));

  for (int length = 1 ; length <= maxLength ; ++length) {
    std::vector<std::pair<std::string, int>> nextResult;
    for (auto prev: result) {
      std::string prevStr = prev.first;
      char lastChar = (prevStr.length() == 0) ? ('a' - 1) :
        lastChar = prevStr[prevStr.length() - 1];

      for (char nextChar = lastChar + 1 ; nextChar <= 'z' ; ++nextChar) {
        nextResult.push_back(std::pair<std::string, int>(prevStr + nextChar, i++));
      }
    }
    result = nextResult;
  }
  return result;
}

#define CHECK_NUMBERS(n, length, expectedNumbersValues) { \
  std::vector<int> numbers(n, 1), expectedNumbers = expectedNumbersValues; \
  for (int i = 1 ; i < length ; ++i) { \
    calcNextNumbers(numbers); \
  } \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedNumbers.begin(), expectedNumbers.end(), \
    numbers.begin(), numbers.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( alphabet_tests ) {
  CHECK_NUMBERS(5, 1, ARRAY_ARG_PROTECT({
    1, 1, 1, 1, 1
  }))
  CHECK_NUMBERS(5, 2, ARRAY_ARG_PROTECT({
    4, 3, 2, 1, 0
  }))
  CHECK_NUMBERS(5, 3, ARRAY_ARG_PROTECT({
    6, 3, 1, 0, 0
  }))
  CHECK_STRINGS(1)
  CHECK_STRINGS(2)
  CHECK_STRINGS(3)
  CHECK_STRINGS(4)
  CHECK_STRINGS(5)
  CHECK_STRINGS(6)
}
