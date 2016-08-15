/*
Given a number N, write a program that returns all possible
combinations of numbers that add up to N, as lists. (Exclude the N+0=N)

For example, if N=4 return {{1,1,1,1},{1,1,2},{2,2},{1,3}}
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE AllSumTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<std::vector<int>> findAllCombinations(int number) {
  std::vector<std::vector<int>> result = {};

  std::vector<int> lastResult = std::vector<int>(number, 1);
  int lastResultSum = number;

  while (true) {
    result.push_back(std::vector<int>(lastResult.begin(), lastResult.end()));
    // backtrack to next branch

    if (lastResult.size() == 1) {
      break;
    }

    lastResultSum -= lastResult[lastResult.size() - 1];
    lastResult.pop_back();

    lastResult[lastResult.size() - 1]++;
    lastResultSum++;

    if (lastResultSum < number) {
      int lastNumberInResult = lastResult[lastResult.size() - 1];

      while ( (number - lastResultSum) >= lastNumberInResult) {
        lastResult.push_back(lastNumberInResult);
        lastResultSum += lastNumberInResult;
      }
      lastResult[lastResult.size() - 1] += number - lastResultSum;
      lastResultSum = number;
    }
  }

  return result;
}

namespace std {
  ostream& operator<< (ostream &stream, vector<int> v) {
    stream << "{";
    for (int n: v) {
      stream << n << " ";
    }
    stream << "}";
    return stream;
  }
}

#define CHECK_ALL_SUM(number, expectedResultValues) { \
  std::vector<std::vector<int>> expectedResult = expectedResultValues, \
    actualResult = findAllCombinations(number); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(), expectedResult.end(),  \
    actualResult.begin(), actualResult.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( all_sum_tests ) {
  CHECK_ALL_SUM(1, {{1}})

  CHECK_ALL_SUM(2, ARRAY_ARG_PROTECT({
    {1, 1},
    {2}
  }))

  CHECK_ALL_SUM(3, ARRAY_ARG_PROTECT({
    {1, 1, 1},
    {1, 2},
    {3}
  }))

  CHECK_ALL_SUM(4, ARRAY_ARG_PROTECT({
    {1, 1, 1, 1},
    {1, 1, 2},
    {1, 3},
    {2, 2},
    {4}
  }))

  CHECK_ALL_SUM(5, ARRAY_ARG_PROTECT({
    {1, 1, 1, 1, 1},
    {1, 1, 1, 2},
    {1, 1, 3},
    {1, 2, 2},
    {1, 4},
    {2, 3},
    {5}
  }))

  CHECK_ALL_SUM(6, ARRAY_ARG_PROTECT({
    {1, 1, 1, 1, 1, 1},
    {1, 1, 1, 1, 2},
    {1, 1, 1, 3},
    {1, 1, 2, 2},
    {1, 1, 4},
    {1, 2, 3},
    {1, 5},
    {2, 2, 2},
    {2, 4},
    {3, 3},
    {6}
  }))

}
