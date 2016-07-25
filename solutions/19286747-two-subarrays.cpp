/*
Given an array of integers. Find two disjoint contiguous sub-arrays such that the absolute difference between the sum of two sub-array is maximum.
* The sub-arrays should not overlap.

eg- [2 -1 -2 1 -4 2 8] ans - (-1 -2 1 -4) (2 8), diff = 16
*/

#include <iostream>
#include <vector>
#define BOOST_TEST_MODULE TwoSubarraysTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Subarray {
  public:
    int start, end, sum;
    Subarray() {}
    Subarray(int initStart, int initEnd, int initSum):
     start(initStart),
     end(initEnd),
     sum(initSum) {}
};

class BestSubarray {
  public:
    Subarray bestSubarray, bestAdjSubarray;
    const std::vector<int> &array;

    BestSubarray(const std::vector<int> &initArray, int initStart = 0):
      array(initArray),
      bestSubarray(initStart, initStart, initArray[initStart]),
      bestAdjSubarray(initStart, initStart, initArray[initStart]) {}
};

class MinSubarray: public BestSubarray {
  public:
    MinSubarray(const std::vector<int> &initArray):
      BestSubarray(initArray, 0) {}

    void incEndIdx() {
      bestAdjSubarray.end++;

      int newValue = array[bestAdjSubarray.end];

      if (bestSubarray.sum > 0) {
        bestAdjSubarray.sum = newValue;
        bestAdjSubarray.start = bestAdjSubarray.end;
      } else {
        bestAdjSubarray.sum += newValue;
      }

      if (bestSubarray.sum > bestAdjSubarray.sum) {
        bestSubarray = bestAdjSubarray;
      }
    }
};

class MaxSubarray: public BestSubarray {
  public:
    MaxSubarray(const std::vector<int> &initArray):
      BestSubarray(initArray, initArray.size() - 1) {}

    void decStartIdx() {
      bestAdjSubarray.start--;

      int newValue = array[bestAdjSubarray.start];

      if (bestSubarray.sum < 0) {
        bestAdjSubarray.sum = newValue;
        bestAdjSubarray.end = bestAdjSubarray.start;
      } else {
        bestAdjSubarray.sum += newValue;
      }
      //std::cout << bestAdjSubarray.sum << std::endl;

      if (bestSubarray.sum < bestAdjSubarray.sum) {
        bestSubarray = bestAdjSubarray;
      }
    }
};

std::vector<Subarray> calcMaxSubarrays(std::vector<int> array) {
  std::vector<Subarray> maxSubarrays;
  MaxSubarray maxSubarray(array);

  while (maxSubarray.bestAdjSubarray.start >= 1) {
    //std::cout << maxSubarray.bestSubarray.sum << std::endl;
    maxSubarrays.push_back(maxSubarray.bestSubarray);
    maxSubarray.decStartIdx();
  }

  return maxSubarrays;
}

std::vector<int> subarray(std::vector<int> array, int start, int end) {
  std::vector<int> result;
  for (int i = start ; i <= end ; ++i) {
    result.push_back(array[i]);
  }
  return result;
}

std::pair<std::vector<int>, std::vector<int>>
  findTwoSubarrays(std::vector<int> array)
{
  std::vector<Subarray> maxSubarrays = calcMaxSubarrays(array);
  MinSubarray minSubarray(array);
  Subarray resMin, resMax;

  while (minSubarray.bestAdjSubarray.end <= array.size() - 2) {
    Subarray nextMin = minSubarray.bestSubarray,
             nextMax = maxSubarrays[maxSubarrays.size() - 1];

    maxSubarrays.pop_back();
    minSubarray.incEndIdx();

    if ((nextMax.sum - nextMin.sum) >
        (resMax.sum - resMin.sum))
    {
      resMin = nextMin;
      resMax = nextMax;
    }
  }

  return std::pair<std::vector<int>, std::vector<int>> (
    subarray(array, resMin.start, resMin.end),
    subarray(array, resMax.start, resMax.end)
  );
}

#define CHECK_TWO_SUBARRAYS(arrayValues, expectedSubrray1Values, expectedSubrray2Values) { \
	std::vector<int> array = arrayValues, \
    expectedSubrray1 = expectedSubrray1Values, \
    expectedSubrray2 = expectedSubrray2Values; \
  auto actualSubarrays = findTwoSubarrays(array); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedSubrray1.begin(), expectedSubrray1.end(), \
    actualSubarrays.first.begin(), actualSubarrays.first.end()); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedSubrray2.begin(), expectedSubrray2.end(), \
    actualSubarrays.second.begin(), actualSubarrays.second.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( two_subarrays_tests ) {
  CHECK_TWO_SUBARRAYS(
    ARRAY_ARG_PROTECT({2, -1, -2, 1, -4, 2, 8}),
    ARRAY_ARG_PROTECT({-1, -2, 1, -4}),
    ARRAY_ARG_PROTECT({2, 8})
  )
}
