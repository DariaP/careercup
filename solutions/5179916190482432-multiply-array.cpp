/*
input [2,3,1,4]
output [12,8,24,6]

Multiply all fields except it's own position.

Restrictions:
1. no use of division
2. complexity in O(n)
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE MultiplyArrayTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<int> multiply(std::vector<int> array) {
  std::vector<int> result(array.size());

  int mulResult = 1;
  for (int i = 0 ; i < array.size() ; ++i) {
    result[i] = mulResult;
    mulResult *= array[i];
  }

  mulResult = 1;
  for (int i = array.size() - 1 ; i >= 0 ; --i) {
    result[i] *= mulResult;
    mulResult *= array[i];
  }

  return result;
}

std::vector<int> multiply_test(std::vector<int> array) {

  int mulResult = 1;
  for (int i = 0 ; i < array.size() ; ++i) {
    mulResult *= array[i];
  }

  std::vector<int> result(array.size());
  for (int i = 0 ; i < array.size() ; ++i) {
    result[i] = mulResult / array[i];
  }

  return result;
}

#define CHECK_MULTIPLY_ARRAY(arrayValues) { \
  std::vector<int> array = arrayValues; \
  std::vector<int> expectedResult = multiply_test(array); \
  std::vector<int> actualResult = multiply(array); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedResult.begin(), expectedResult.end(), \
    actualResult.begin(), actualResult.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( multiply_array_tests ) {
  CHECK_MULTIPLY_ARRAY(ARRAY_ARG_PROTECT({
    2, 3, 1, 4
  }))

  CHECK_MULTIPLY_ARRAY(ARRAY_ARG_PROTECT({}))

  CHECK_MULTIPLY_ARRAY(ARRAY_ARG_PROTECT({1}))
}
