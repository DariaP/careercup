/*
Given two strings a and b, find whether any anagram of string a is a sub-string of string b. For eg:
if a = xyz and b = afdgzyxksldfm then the program should return true.
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE AnagramSubstrTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::unordered_map<char, int> countLetters(std::string str) {
  std::unordered_map<char, int> result;
  for (char letter: str) {
    if (result.find(letter) == result.end()) {
      result[letter] = 1;
    } else {
      result[letter]++;
    }
  }
  return result;
}

bool hasAnagramSubstr(std::string str, std::string anagramSubstr) {
  std::unordered_map<char, int> anagramSubstrLetters = countLetters(anagramSubstr),
   currentSubstrLetters;

  int start = 0, end = -1;
  while ((end - start + 1) != anagramSubstr.length() && end < (int)str.length()) {
    char nextChar = str[++end];
    if (anagramSubstrLetters.find(nextChar) != anagramSubstrLetters.end()) {
      if (currentSubstrLetters.find(nextChar) == currentSubstrLetters.end()) {
        currentSubstrLetters[nextChar] = 1;
      } else {
        if (currentSubstrLetters[nextChar] < anagramSubstrLetters[nextChar]) {
          currentSubstrLetters[nextChar]++;
        } else {
          currentSubstrLetters.clear();
          start = end + 1;
        }
      }
    } else {
      currentSubstrLetters.clear();
      start = end + 1;
    }
  }

  return end < str.length();
}

#define CHECK_ANAGRAM_SUBSTR(str, anagramSubstr, expectedResult) { \
  bool actualResult = hasAnagramSubstr(str, anagramSubstr); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

BOOST_AUTO_TEST_CASE( anagram_substr_tests ) {
  CHECK_ANAGRAM_SUBSTR("a", "b", false);
  CHECK_ANAGRAM_SUBSTR("a", "a", true);
  CHECK_ANAGRAM_SUBSTR("ab", "b", true);
  CHECK_ANAGRAM_SUBSTR("abc", "ca", false);
  CHECK_ANAGRAM_SUBSTR("acb", "ca", true);
  CHECK_ANAGRAM_SUBSTR("acca", "caa", false);
  CHECK_ANAGRAM_SUBSTR("acca", "caacc", false);
  CHECK_ANAGRAM_SUBSTR("baccaxx", "caca", true);
  CHECK_ANAGRAM_SUBSTR("xyzksldfm", "xyz", true);
  CHECK_ANAGRAM_SUBSTR("afdgxyzksldfm", "xyz", true);
  CHECK_ANAGRAM_SUBSTR("afdgzyxksldfm", "xyz", true);
  CHECK_ANAGRAM_SUBSTR("afdgzykxzslxyxdfm", "xyz", false);
}
