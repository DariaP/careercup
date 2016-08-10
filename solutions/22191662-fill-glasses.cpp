/*
There are some glasses with equal volume 1 litre. The glasses kept as follows
         1
       2   3
    4    5    6
  7    8    9   10
You can put water to only top glass. If you put more than 1 litre water to 1st glass, water overflow and fill equally both 2nd and 3rd glass. Glass 5 will get water from both 2nd glass and 3rd glass and so on..
If you have X litre of water and you put that water in top glass, so tell me how much water contained by jth glass in ith row.
Example. If you will put 2 litre on top.
1st – 1 litre
2nd – 1/2 litre
3rd - 1/
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE FillGlassesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

double calcNextAmount(std::vector<double> &amounts, int level, int i) {
  int leftParentIdx = amounts.size() - (level + 1),
    rightParentIdx = amounts.size() - level;
  double leftAmount = (amounts[leftParentIdx] > 1) ? (amounts[leftParentIdx] - 1) / 2 : 0,
    rightAmount = (amounts[rightParentIdx] > 1) ? (amounts[rightParentIdx] - 1) / 2 : 0;

  if (i == 0) {
    return rightAmount;
  } else if (i == level) {
    return leftAmount;
  } else {
    return leftAmount + rightAmount;
  }
}

void trim(std::vector<double> &amounts, int idx) {
  if (amounts[idx] > 1) {
    amounts[idx] = 1;
  }
}

std::vector<double> calcAmounts(double n) {
  std::vector<double> amounts;

  if (n < 0) return amounts;

  amounts.push_back(n);

  bool excessWaterOnBottomLevel = (n > 1);
  int level = 0;

  while (excessWaterOnBottomLevel) {
    excessWaterOnBottomLevel = false;
    level++;
    for (int i = 0 ; i < level + 1 ; ++i) {
      double nextAmount = calcNextAmount(amounts, level, i);
      if (nextAmount > 1) {
        excessWaterOnBottomLevel = true;
      }
      //std::cout << nextAmount << std::endl;
      amounts.push_back(nextAmount);
    }

    if (level > 0) {
      int prevLevelStart = amounts.size() - (level + 1) - level;
      for (int i = 0 ; i < level; ++i) {
        trim(amounts, prevLevelStart + i);
      }
    }
  }

  return amounts;
}

#define CHECK_FILL_GLASSES(n, expectedVolumesValues) { \
  std::vector<double> expectedVolumes = expectedVolumesValues, \
    actualVolumes = calcAmounts(n); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedVolumes.begin(), expectedVolumes.end(), \
    actualVolumes.begin(), actualVolumes.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( fill_glasses_tests ) {
  CHECK_FILL_GLASSES(0, {0})
  CHECK_FILL_GLASSES(-1, {})
  CHECK_FILL_GLASSES(1, {1})

  CHECK_FILL_GLASSES(2,
    ARRAY_ARG_PROTECT({
      1, 0.5, 0.5
    })
  )

  CHECK_FILL_GLASSES(3,
    ARRAY_ARG_PROTECT({
      1, 1, 1
    })
  )

  CHECK_FILL_GLASSES(4,
    ARRAY_ARG_PROTECT({
      1, 1, 1, 0.25, 0.5, 0.25
    })
  )

  CHECK_FILL_GLASSES(5,
    ARRAY_ARG_PROTECT({
      1, 1, 1, 0.5, 1, 0.5
    })
  )

  CHECK_FILL_GLASSES(6,
    ARRAY_ARG_PROTECT({
      1, 1, 1, 0.75, 1, 0.75, 0, 0.25, 0.25, 0
    })
  )

  CHECK_FILL_GLASSES(7,
    ARRAY_ARG_PROTECT({
      1, 1, 1, 1, 1, 1, 0, 0.5, 0.5, 0
    })
  )

  CHECK_FILL_GLASSES(8,
    ARRAY_ARG_PROTECT({
      1, 1, 1, 1, 1, 1, 0.125, 0.875, 0.875, 0.125
    })
  )

}
