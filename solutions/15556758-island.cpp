/*
There is an island which is represented by square matrix NxN.
A person on the island is standing at any given co-ordinates (x,y).
He can move in any direction one step right, left, up, down on the island.
If he steps outside the island, he dies.

Let island is represented as (0,0) to (N-1,N-1) (i.e NxN matrix) &
person is standing at given co-ordinates (x,y).
He is allowed to move n steps on the island (along the matrix).
What is the probability that he is alive after he walks n steps on the island?

Write a psuedocode & then full code for function
" float probabilityofalive(int x,int y, int n) ".
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE IslandTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

enum Terrain {
    WATER,
    LAND
};

#define Water Terrain::WATER
#define Land Terrain::LAND

class Island {
public:
  int top, bottom, left, right;
  Island(int mapSize) {
    top = mapSize - 1;
    bottom = 0;
    left = mapSize - 1;
    right = 0;
  }

  int width() {
    return right - left + 1;
  }
  int height() {
    return bottom - top + 1;
  }

};

Island islandBoundaries(std::vector<std::vector<Terrain>> map) {

  Island result(map.size());

  for (int i = 0 ; i < map.size() ; ++i) {
    for (int j = 0 ; j < map.size() ; ++j) {
      if (map[i][j] == Land) {
        if (i < result.top) result.top = i;
        if (i > result.bottom) result.bottom = i;
        if (j < result.left) result.left = j;
        if (j > result.right) result.right = j;
      }
    }
  }

  return result;
}

class Matrix {
  std::vector<std::vector<float>> values;
public:
  Matrix(int height, int width, float initValue): values(height, std::vector<float>(width, initValue)) {}
  float at(int x, int y) {
    return values[x][y];
  }
  void set(int x, int y, float v) {
    values[x][y] = v;
  }
};

float probabilityOfAlive(std::vector<std::vector<Terrain>> map, int x, int y, int n) {

  Island island = islandBoundaries(map);

  Matrix buff1(island.height() + 2, island.width() + 2, 0),
         buff2(island.height() + 2, island.width() + 2, 0),
         *probabilities = &buff1,
         *newProbabilities = &buff2;

  probabilities->set(x + 1, y + 1, (map[x][y] == Land) ? 1 : 0);

  for (int s = 0 ; s < n ; ++s) {
    for (int i = 1 ; i < island.height() + 1 ; ++i) {
      for (int j = 1 ; j < island.width() + 1 ; ++j) {
        if (map[i + island.top - 1][j + island.left - 1] == Land) {
          newProbabilities->set(i, j, 0.25 * (
            probabilities->at(i - 1, j) + probabilities->at(i + 1, j) +
            probabilities->at(i, j - 1) + probabilities->at(i, j + 1)
          ));
        }
      }
    }
    auto buff = probabilities;
    probabilities = newProbabilities;
    newProbabilities = buff;
  }

  float result = 0;
  for (int i = 1 ; i < map.size() + 1 ; ++i) {
    for (int j = 1 ; j < map.size() + 1 ; ++j) {
      if (map[i - 1][j - 1] == Land) {
        result += probabilities->at(i, j);
      }
    }
  }
  return result;
}

#define CHECK_ISLAND(mapArray, x, y, n, expectedProbability) { \
  std::vector<std::vector<Terrain>> map = mapArray; \
	float actualProbability = probabilityOfAlive(map, x, y, n); \
  BOOST_CHECK_EQUAL(expectedProbability, actualProbability); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__


BOOST_AUTO_TEST_CASE( island_tests ) {
  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Water, Water, Water},
      {Water, Land,  Water},
      {Water, Water, Water}
    }), 1, 1, 1, 0
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Water, Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 1, 1
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Water, Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 2, 0.25
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Water, Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 3, 0.25
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Water, Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 4, 0.25 * 0.25
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Land,  Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 1, 1
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Land,  Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 2, (0.25 + 2 * 0.25 * 0.25)
  )

  CHECK_ISLAND(
    ARRAY_ARG_PROTECT({
      {Land,  Land, Water},
      {Land,  Land, Land},
      {Water, Land, Water}
    }), 1, 1, 3, (0.25 + 2 * 0.5 * 0.25 * 0.25)
  )

}
