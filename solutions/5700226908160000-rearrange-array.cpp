/*
Rearrange an array using swap with 0.

You have two arrays src, tgt, containing two permutations of the numbers 0..n-1.
You would like to rearrange src so that it equals tgt.
The only allowed operations is “swap a number with 0”,
e.g. {1,0,2,3} -> {1,3,2,0} (“swap 3 with 0”).
Write a program that prints to stdout the list of required operations.
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE RearrangeArrayTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<int> saveNumbersPositions(
  const std::vector<int> &array
) {
  std::vector<int> result(array.size());
  for (int i = 0 ; i < array.size() ; ++i) {
    result[array[i]] = i;
  }
  return result;
}

void swap0(std::vector<int> &src, int idx) {
  int buffer = src[0];
  src[0] = src[idx];
  src[idx] = buffer;
}

void swap(
  std::vector<int> &steps,
  std::vector<int> &src,
  std::vector<int> &srcNumbersPositions,
  int idx
) {
  steps.push_back(idx);
  srcNumbersPositions[src[0]] = idx;
  srcNumbersPositions[src[idx]] = 0;
  swap0(src, idx);
}

std::vector<int> getStepsToRearrange(
  const std::vector<int> &src, const std::vector<int> &trg
) {
  std::vector<int> steps,
    srcNumbersPositions = saveNumbersPositions(src),
    srcCopy(src.begin(), src.end());

  for (int i = src.size() - 1 ; i > 0 ; --i) {
    if (srcCopy[i] != trg[i]) {
      int trgPositionInSrc = srcNumbersPositions[trg[i]];
      if (trgPositionInSrc != 0) {
        swap(steps, srcCopy, srcNumbersPositions, trgPositionInSrc);
      }
      swap(steps, srcCopy, srcNumbersPositions, i);
    }
  }
  return steps;
}

#define CHECK_REARRANGE_ARRAY(srcValues, trgValues, expectedStepsValues) { \
  std::vector<int> expectedSteps = expectedStepsValues, \
    src = srcValues, trg = trgValues, \
    actualSteps = getStepsToRearrange(src, trg); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedSteps.begin(), expectedSteps.end(),  \
    actualSteps.begin(), actualSteps.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( rearrange_array_tests ) {
  CHECK_REARRANGE_ARRAY({}, {}, {})
  CHECK_REARRANGE_ARRAY({0}, {0}, {})
  CHECK_REARRANGE_ARRAY(
    ARRAY_ARG_PROTECT({
      1, 0
    }),
    ARRAY_ARG_PROTECT({
      1, 0
    }), {})

  CHECK_REARRANGE_ARRAY(
    ARRAY_ARG_PROTECT({
      1, 0
    }),
    ARRAY_ARG_PROTECT({
      0, 1
    }), {1}
  )

  CHECK_REARRANGE_ARRAY(
    ARRAY_ARG_PROTECT({
      1, 0, 2
    }),
    ARRAY_ARG_PROTECT({
      0, 1, 2
    }), {1}
  )

  CHECK_REARRANGE_ARRAY(
    ARRAY_ARG_PROTECT({
      1, 0, 2
    }),
    ARRAY_ARG_PROTECT({
      1, 2, 0
    }),
    ARRAY_ARG_PROTECT({
      1, 2, 1
    })
  )

  CHECK_REARRANGE_ARRAY(
    ARRAY_ARG_PROTECT({
      1, 0, 2, 3
    }),
    ARRAY_ARG_PROTECT({
      1, 3, 2, 0
    }),
    ARRAY_ARG_PROTECT({
      1, 3, 1
    })
  )
}
