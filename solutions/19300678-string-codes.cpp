/*
If a=1, b=2, c=3,....z=26. Given a string, find all possible codes
that string can generate. Give a count as well as print the strings.

For example:
Input: "1123". You need to general all valid alphabet codes from this string.

Output List
aabc //a = 1, a = 1, b = 2, c = 3
kbc // since k is 11, b = 2, c= 3
alc // a = 1, l = 12, c = 3
aaw // a= 1, a =1, w= 23
kw // k = 11, w = 23
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE StringCodesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

void appendPrefix(std::vector<std::string> &result, char prefix, std::vector<std::string> &strings) {
  for (std::string str: strings) {
    result.push_back(str.insert(0, 1, prefix));
  }
}

char letterForCode(std::string code) {
  return 'a' + std::stoi(code) - 1;
}

bool isValidLetterCode(std::string code) {
  return letterForCode(code) >= 'a' && letterForCode(code) <= 'z';
}

std::vector<std::string> findStringsWithCode(std::string code) {
  if (code.length() == 0) {
    return std::vector<std::string>();
  }

  std::vector<std::string> prevStrings, prevMinus1Strings;
  prevStrings.push_back("");

  for (int length = 1 ; length <= code.length() ; ++length) {
    std::vector<std::string> newStrings;
    int nextDigitPosition = code.length() - length;

    std::string nextDigit = code.substr(nextDigitPosition, 1);
    if (isValidLetterCode(nextDigit)) {
      appendPrefix(newStrings, letterForCode(nextDigit), prevStrings);
    }

    if (length > 1) {
      std::string nextTwoDigits = code.substr(nextDigitPosition, 2);
      if (isValidLetterCode(nextTwoDigits)) {
        appendPrefix(newStrings, letterForCode(nextTwoDigits), prevMinus1Strings);
      }
    }

    prevMinus1Strings = prevStrings;
    prevStrings = newStrings;
  }

  return prevStrings;
}

#define CHECK_STR_CODE(code, expectedResultValues) { \
  std::vector<std::string> expectedResult = expectedResultValues, \
    actualResult = findStringsWithCode(code); \
  std::sort(expectedResult.begin(), expectedResult.end()); \
  std::sort(actualResult.begin(), actualResult.end()); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(), expectedResult.end(), \
    actualResult.begin(), actualResult.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( string_codes_tests ) {
  CHECK_STR_CODE("0", {})

  CHECK_STR_CODE("1", {"a"})
  CHECK_STR_CODE("9", {"i"})
  CHECK_STR_CODE("10", {"j"})
  CHECK_STR_CODE("11", ARRAY_ARG_PROTECT({
    "aa", "k"
  }))

  CHECK_STR_CODE("1123", ARRAY_ARG_PROTECT({
    "aabc", "kbc", "alc", "aaw", "kw"
  }))

}
