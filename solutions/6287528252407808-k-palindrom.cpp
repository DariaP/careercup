/*
Pots of gold game:
Two players A & B. There are pots of gold arranged in a line,
each containing some gold coins (the players can see how many coins
are there in each gold pot - perfect information).
They get alternating turns in which the player can pick a pot
from one of the ends of the line. The winner is the player
which has a higher number of coins at the end.
The objective is to "maximize" the number of coins collected by A,
assuming B also plays optimally. A starts the game.

The idea is to find an optimal strategy that makes A win
knowing that B is playing optimally as well.

abxaa

*/

#include <iostream>
#include <unordered_map>
#include <unordered_set>
#define BOOST_TEST_MODULE KPalindromTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

bool isPalindrom(std::string str) {
  for (int i = 0 ; i < str.length() / 2 ; ++i) {
    if (str[i] != str[str.length() - i - 1]) {
      return false;
    }
  }
  return true;
}

std::string cutFirstAndLastChar(std::string str) {
  return str.substr(1, str.length() - 2);
}

std::string cutFirstChar(std::string str) {
  return str.substr(1);
}

std::string cutLastChar(std::string str) {
  return str.substr(0, str.length() - 1);
}

class PartResults {
  std::unordered_map<std::string, std::unordered_set<int>> results;
public:
  PartResults() {}
  void add(std::string str, int k) {
    if (results.find(str) == results.end()) {
      results[str] = std::unordered_set<int>();
    }
    results[str].insert(k);
  }
  bool has(std::string str, int k) {
    return (results.find(str) != results.end() &&
      results[str].find(k) == results[str].end());
  }
};

bool isKPalindrom_recursiveHelper(std::string str, int k, PartResults &partResults) {

  if(partResults.has(str, k)) {
    return false;
  }

  if (k >= str.length() - 1) {
    return true;
  }

  bool result = false;

  if (k == 0) {
    result = isPalindrom(str);
  } else {
    if (str[0] == str[str.length() - 1] &&
        isKPalindrom_recursiveHelper(cutFirstAndLastChar(str), k, partResults))
    {
      result = true;
    } else if (isKPalindrom_recursiveHelper(cutFirstChar(str), k - 1, partResults)) {
      result = true;
    } else if (isKPalindrom_recursiveHelper(cutLastChar(str), k - 1, partResults)) {
      result = true;
    } else {
      result = false;
    }
  }

  if (!result) {
    partResults.add(str, k);
  }
  return result;
}

bool isKPalindrom(std::string str, int k) {
  PartResults partResults;
  return isKPalindrom_recursiveHelper(str, k, partResults);
}

#define CHECK_K_PALINDROM(str, k, expectedResult) { \
	bool actualResult = isKPalindrom(str, k); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__


BOOST_AUTO_TEST_CASE( k_palindrom_tests ) {
  CHECK_K_PALINDROM("", 0, true);
  CHECK_K_PALINDROM("a", 0, true);
  CHECK_K_PALINDROM("a", 1, true);
  CHECK_K_PALINDROM("aa", 0, true);
  CHECK_K_PALINDROM("ab", 0, false);
  CHECK_K_PALINDROM("ab", 1, true);
  CHECK_K_PALINDROM("aba", 0, true);

  CHECK_K_PALINDROM("abxa", 1, true);
  CHECK_K_PALINDROM("abdxa", 1, false);
  CHECK_K_PALINDROM("abddba", 0, true);
  CHECK_K_PALINDROM("abddba", 1, true);
  CHECK_K_PALINDROM("abddba", 6, true);
  CHECK_K_PALINDROM("abddba", 7, true);
  CHECK_K_PALINDROM("abcdef", 6, true);
  CHECK_K_PALINDROM("abcdef", 5, true);
  CHECK_K_PALINDROM("abcdef", 4, false);
  CHECK_K_PALINDROM("abcdea", 4, true);

  CHECK_K_PALINDROM("abababababab", 7, true);
  CHECK_K_PALINDROM("abcdefabcdef", 7, false);
}
