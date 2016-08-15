/*
You are given an array that contains integers.
The integers content is such that every integer occurs 3 times in that array
leaving one integer that appears only once.
Fastest way to find that single integer
-- using memory.
-- not using any external memory.

eg: [2,1,4,5,1,4,2,2,4,1]
*/


#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE FindValueTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int bitAt(int number, int pos) {
  int mask = 1 << pos;
  return (number & mask) == 0 ? 0 : 1;
}

std::vector<int> getBits(int number) {
  size_t bitsNumber = 8 * sizeof(int);
  std::vector<int> result(bitsNumber);
  for (int i = 0 ; i < bitsNumber ; ++i) {
    result[i] = bitAt(number, i);
  }
  return result;
}

void xorMod3(std::vector<int> &a, int b) {
  size_t bitsNumber = 8 * sizeof(int);
  for (int i = bitsNumber - 1 ; i >= 0 ; --i) {
    a[i] = (a[i] + bitAt(b, i)) % 3;
  }
}

int makeNumber(std::vector<int> bits) {
  int number = 0;
  for (int i = bits.size() - 1 ; i >= 0 ; --i) {
    number = (number << 1) + bits[i];
  }
  return number;
}

int findSingleNumber(std::vector<int> array) {
  std::vector<int> xorResult = getBits(array[0]);
  for (int i = 1 ; i < array.size() ; ++i) {
    xorMod3(xorResult, array[i]);
  }
  return makeNumber(xorResult);
}

#define CHECK_FIND(arrayValues, expectedResult) { \
  std::vector<int> array = arrayValues; \
  int actualResult = findSingleNumber(array); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( find_value_tests ) {
  CHECK_FIND({1}, 1)
  CHECK_FIND({2}, 2)
  CHECK_FIND({10}, 10)
  CHECK_FIND({-234}, -234)

  CHECK_FIND(ARRAY_ARG_PROTECT({
    2, 1, 1, 2, -43, 2, 1
  }), -43)

  CHECK_FIND(ARRAY_ARG_PROTECT({
    -2, 1, 1, -2, 43, -2, 1
  }), 43)

  CHECK_FIND(ARRAY_ARG_PROTECT({
    2, 1, 4, 5, 1, 4, 2, 2, 4, 1
  }), 5)
}
