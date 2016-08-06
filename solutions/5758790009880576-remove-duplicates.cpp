/*
Given a string which only contains lowercase. You need delete the repeated
letters only leave one, and try to make the lexicographical order
of new string is smallest.
i.e:
bcabc
You need delete 1 'b' and 1 'c', so you delete the first 'b' and first 'c',
the new string will be abc which is smallest.

ps: If you try to use greedy algorithm to solve this problem,
you must sure that you could pass this case:
cbacdcbc. answer is acdb not adcb

*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE StringCodesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<int> nextDuplicatePositions(std::string str) {
  std::unordered_map<char, int> prevPositions;
  std::vector<int> result(str.length(), -1);

  for (int i = 0 ; i < str.length() ; ++i) {
    char c = str[i];
    if (prevPositions.find(c) != prevPositions.end()) {
      result[prevPositions[c]] = i;
    }
    prevPositions[c] = i;
  }

  return result;
}

std::string makeString(std::vector<char> chars) {
  std::string result = "";

  for (char c: chars) {
    if (c != ' ') {
      result += c;
    }
  }

  return result;
}
template <class T>
void print(std::vector<T> resultChars) {
  for (T c: resultChars){
    std::cout << c << ',';
  }
  std::cout<<std::endl;
}

void cleanPrevDuplicate(std::vector<char> &resultChars, int i,
  const std::vector<int> &duplicates)
{
  int prevDuplicatePosition = duplicates.at(i);
  while (resultChars[prevDuplicatePosition] == ' ') {
    prevDuplicatePosition = duplicates[prevDuplicatePosition];
  }
  resultChars[prevDuplicatePosition] = ' ';
}

std::string removeDuplicates(std::string original) {
  auto duplicates = nextDuplicatePositions(original);

  std::vector<char> resultChars(original.length(), ' ');
  char currentFirstChar;
  for (int i = original.length() - 1 ; i >= 0 ; --i) {
    char nextChar = original[i];
    if (duplicates[i] == -1) {
      resultChars[i] = nextChar;
      currentFirstChar = nextChar;
    } else {
      if (nextChar < currentFirstChar) {
        resultChars[i] = nextChar;
        cleanPrevDuplicate(resultChars, i, duplicates);
        resultChars[duplicates[i]] = ' ';
        duplicates[i] = duplicates[duplicates[i]];
      }
    }
  }

  return makeString(resultChars);
}

#define CHECK_REMOVE_DUP(originalStr, expectedResult) { \
  auto actualResult = removeDuplicates(originalStr); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

BOOST_AUTO_TEST_CASE( string_codes_tests ) {
  CHECK_REMOVE_DUP("", "")
  CHECK_REMOVE_DUP("a", "a")
  CHECK_REMOVE_DUP("aa", "a")
  CHECK_REMOVE_DUP("abbcc", "abc")
  CHECK_REMOVE_DUP("abcbc", "abc")
  CHECK_REMOVE_DUP("bbcc", "bc")
  CHECK_REMOVE_DUP("bcabccb", "abc")
  CHECK_REMOVE_DUP("abc", "abc")
  CHECK_REMOVE_DUP("cbacdcbc", "acdb")
  CHECK_REMOVE_DUP("lmznopnbdfikmonqsvnlmznop", "bdfikmonqsvlzp")
}
