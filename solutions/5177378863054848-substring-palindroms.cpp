/*
Write a function for retrieving the total number of substring palindromes.
For example the input is 'abba' then the possible palindromes= a, b, b, a, bb, abba
So the result is 6.
*/

#include <iostream>
#include <algorithm>
#define BOOST_TEST_MODULE SubstringPalindromsTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int countEvenLengthPalindroms(std::string str, int pivotIdx) {
  int maxStep = std::min(pivotIdx, (int)str.length() - 2 - pivotIdx),
    result = 0;
  for (int step = 0 ; step <= maxStep ; ++step) {
    if (str[pivotIdx - step] == str[pivotIdx + 1 + step]) {
      result++;
    } else {
      break;
    }
  }
  return result;
}

int countOddLengthPalindroms(std::string str)
{
  std::vector<int> oddLengthPalindroms(str.length(), 0);

  int pivotIdx = 0, result = 0;
  while (pivotIdx < str.length()) {
    int maxStep = std::min(pivotIdx, (int)str.length() - 1 - pivotIdx),
        step = std::min(oddLengthPalindroms[pivotIdx], maxStep);
    oddLengthPalindroms[pivotIdx] = step;
    while (step <= maxStep && str[pivotIdx + step] == str[pivotIdx - step]) {
      oddLengthPalindroms[pivotIdx]++;
      if (step != 0) {
        oddLengthPalindroms[pivotIdx + step] = std::max(
          oddLengthPalindroms[pivotIdx + step],
          oddLengthPalindroms[pivotIdx - step]
        );
      }
      step++;
    }
    result += oddLengthPalindroms[pivotIdx];
    pivotIdx++;
  }

  return result;
}

int countSubstrPalindroms(std::string str) {
  int result = countOddLengthPalindroms(str);
  for (int pivotIdx = 0 ; pivotIdx < str.length() ; ++pivotIdx) {
    result += countEvenLengthPalindroms(str, pivotIdx);
  }
  return result;
}

#define CHECK_PALINDROMS(str, expectedNumber) { \
  int actualNumber = countSubstrPalindroms(str); \
  BOOST_CHECK_EQUAL(expectedNumber, actualNumber); \
}

BOOST_AUTO_TEST_CASE( palindroms_tests ) {
  CHECK_PALINDROMS("", 0)
  CHECK_PALINDROMS("a", 1)
  CHECK_PALINDROMS("aa", 3)
  CHECK_PALINDROMS("aba", 4)
  CHECK_PALINDROMS("abab", 6)
  CHECK_PALINDROMS("ababa", 9)
  CHECK_PALINDROMS("abba", 6)

  //CHECK_PALINDROMS("abaxabaxabb", 22)
  CHECK_PALINDROMS("aaaaaaaa", 36)
}
