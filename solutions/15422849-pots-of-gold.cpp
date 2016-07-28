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
#include <unordered_map>
#include <unordered_set>
#define BOOST_TEST_MODULE PotsOfGoldTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Move {
public:
  int idx, sum;
  Move() { idx = -1; }
  Move(int i, int s) {
    idx = i; sum = s;
  }
  bool valid() {
    return idx != -1;
  }
};

class Moves {
  std::vector<std::vector<Move>> moves;

public:
  Moves(int size): moves(size) {}

  void save(int start, int end, Move move) {
    if (moves[start].size() == 0) {
      moves[start] = std::vector<Move>(moves.size());
    }
    moves[start][end] = move;
  }

  bool has(int start, int end) {
    return moves[start].size() != 0 && moves[start][end].valid();
  }

  Move get(int start, int end) {
    return moves[start][end];
  }
};

int pickMin(std::vector<int> pots, int startIdx, int endIdx, Moves &moves);
Move pickMax(std::vector<int> pots, int startIdx, int endIdx, Moves &moves);

int pickMin(std::vector<int> pots, int startIdx, int endIdx, Moves &moves) {

  if (startIdx == endIdx) {
    return 0;
  }

  Move pickFront = pickMax(pots, startIdx + 1, endIdx, moves),
         pickEnd = pickMax(pots, startIdx, endIdx - 1, moves);

  return (pickFront.sum < pickEnd.sum) ? pickFront.sum : pickEnd.sum;
}

Move pickMax(std::vector<int> pots, int startIdx, int endIdx, Moves &moves) {

  if (moves.has(startIdx, endIdx)) {
    return moves.get(startIdx, endIdx);
  }

  if (startIdx == endIdx) {
    Move lastMove = Move(startIdx, pots[startIdx]);
    moves.save(startIdx, endIdx, lastMove);
    return lastMove;
  }

  int pickFrontSum = pots[startIdx] + pickMin(pots, startIdx + 1, endIdx, moves),
      pickEndSum = pots[endIdx] + pickMin(pots, startIdx, endIdx - 1, moves);

  Move bestMove = ( pickFrontSum > pickEndSum) ?
    Move(startIdx, pickFrontSum) :
    Move(endIdx, pickEndSum);

  moves.save(startIdx, endIdx, bestMove);
  return bestMove;
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

Moves calcMoves(std::vector<int> pots) {
  Moves moves(pots.size());
  if (pots.size() > 0) {
    pickMax(pots, 0, pots.size() - 1, moves);
  }
  if (pots.size() > 1) {
    pickMax(pots, 1, pots.size() - 1, moves);
    pickMax(pots, 0, pots.size() - 2, moves);
  }
  return moves;
}

std::vector<int> play(std::vector<int> pots) {

  Moves allAMoves = calcMoves(pots);

  std::vector<int> aMoves;
  int start = 0, end = pots.size() - 1;
  Player player = Player::A;

  while (start <= end) {
    int move = allAMoves.get(start, end).idx;
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
