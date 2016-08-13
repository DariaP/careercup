/*
WAP to modify the array such that arr[I] = arr[arr[I]].
Do this in place i.e. with out using additional memory.

example : if a = {2,3,1,0}
o/p = a = {1,0,3,2}

Note : The array contains 0 to n-1 integers.
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE SwapArrayTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

int getOriginalValue(int value, int max) {
  if (value >= max) {
    return value / max - 1;
  } else {
    return value;
  }
}

void swap(std::vector<int> &array) {
  int base = array.size();
  for (int i = 0 ; i < array.size() ; ++i) {
    array[i] = (array[i] + 1) * base + getOriginalValue(array[array[i]], base);
  }
  for (int i = 0 ; i < array.size() ; ++i) {
    array[i] = array[i] % base;
  }
}


#define CHECK_SWAP_ARRAY(arrayValues) { \
  std::vector<int> array = arrayValues, newArray; \
  for (int idx: array) { newArray.push_back(array[idx]); } \
  swap(array); \
  BOOST_CHECK_EQUAL_COLLECTIONS(newArray.begin(), newArray.end(),  \
    array.begin(), array.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( swap_array_tests ) {
  CHECK_SWAP_ARRAY({});
  CHECK_SWAP_ARRAY({0});
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    0, 1
  }))
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    1, 0
  }))
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    2, 3, 1, 0
  }))
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    0, 1, 2, 3
  }))
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    1, 0, 3, 2
  }))
  CHECK_SWAP_ARRAY(ARRAY_ARG_PROTECT({
    1, 3, 2, 0
  }))

}
