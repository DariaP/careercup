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
*/

#include <iostream>
#include <vector>
#include <cmath>
#define BOOST_TEST_MODULE PotsOfGoldTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Choice {
public:
  int idx, sum;
  Choice(int i, int s) {
    idx = i; sum = s;
  }
};
int pickMin(std::vector<int> pots, int startIdx, int endIdx);
Choice pickMax(std::vector<int> pots, int startIdx, int endIdx);

int pickMin(std::vector<int> pots, int startIdx, int endIdx) {
  if (startIdx == endIdx) {
    return 0;
  }

  Choice pickFront = pickMax(pots, startIdx + 1, endIdx),
         pickEnd = pickMax(pots, startIdx, endIdx - 1);

  return (pickFront.sum < pickEnd.sum) ? pickFront.sum : pickEnd.sum;
}

Choice pickMax(std::vector<int> pots, int startIdx, int endIdx) {
  if (startIdx == endIdx) {
    return Choice(startIdx, pots[startIdx]);
  }

  int pickFrontSum = pots[startIdx] + pickMin(pots, startIdx + 1, endIdx),
      pickEndSum = pots[endIdx] + pickMin(pots, startIdx, endIdx - 1);

  if ( pickFrontSum > pickEndSum) {
    return Choice(startIdx, pickFrontSum);
  } else {
    return Choice(endIdx, pickEndSum);
  }
}

enum Player {
  A, B
};

void switchPlayer(Player &player) {
  if (player == Player::A) {
    player = Player::B;
  } else {
    player = Player::A;
  }
}

std::vector<int> play(std::vector<int> pots) {
  std::vector<int> aMoves;
  int start = 0, end = pots.size() - 1;
  Player player = Player::A;

  while (start <= end) {
    int move = pickMax(pots, start, end).idx;
    if (player == Player::A) {
      aMoves.push_back(move);
    }
    if (move == end) {
      end--;
    } else {
      start++;
    }
    switchPlayer(player);
  }
  return aMoves;
}

#include <iostream>
#include <vector>
#include <cmath>
#define BOOST_TEST_MODULE PotsOfGoldTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#define CHECK_STRATEGY(potsValues, expectedStrategyIdxs) { \
	std::vector<int> pots = potsValues, \
    expectedStrategy = expectedStrategyIdxs; \
  auto actualStrategy = play(pots); \
  BOOST_CHECK_EQUAL_COLLECTIONS(expectedStrategy.begin(), expectedStrategy.end(), \
    actualStrategy.begin(), actualStrategy.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__


BOOST_AUTO_TEST_CASE( pots_of_gold_tests ) {

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({1}),
    ARRAY_ARG_PROTECT({0})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({1, 2}),
    ARRAY_ARG_PROTECT({1})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({2, 1}),
    ARRAY_ARG_PROTECT({0})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({1, 2, 3}),
    ARRAY_ARG_PROTECT({2, 0})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({2, 1, 3}),
    ARRAY_ARG_PROTECT({2, 1})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({1, 2, 3, 4}),
    ARRAY_ARG_PROTECT({3, 1})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({2, 7, 2, 1}),
    ARRAY_ARG_PROTECT({3, 1})
  );

  CHECK_STRATEGY(
    ARRAY_ARG_PROTECT({2, 7, 29, 2, 1}),
    ARRAY_ARG_PROTECT({0, 3, 1})
  );
}
