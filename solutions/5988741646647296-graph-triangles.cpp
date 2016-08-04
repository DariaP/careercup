/*
Given a undirected graph with corresponding edges. Find the number of possible triangles?
Example:
0 1
0 2
0 3
1 2
1 4

Answer:
1
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#define BOOST_TEST_MODULE GraphTrianglesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class AdjList {
public:
  int value;
  std::unordered_set<int> smaller, larger;
  AdjList() {}
  AdjList(int initValue): value(initValue) {}
  void add(int linkedValue) {
    if (linkedValue < value) {
      smaller.insert(linkedValue);
    } else {
      larger.insert(linkedValue);
    }
  }
  bool linked(int linkedValue) {
    if(linkedValue < value) {
      return smaller.find(linkedValue) != smaller.end();
    } else {
      return larger.find(linkedValue) != larger.end();
    }
  }

};

class AdjLists {
public:
  std::unordered_map<int, AdjList> lists;
  AdjLists() {}
  void add(int value1, int value2) {
    if (lists.find(value1) == lists.end()) {
      lists[value1] = AdjList(value1);
    }
    lists[value1].add(value2);
  }
  bool linked(int value1, int value2) {
    return lists.find(value1) != lists.end() &&
      lists[value1].linked(value2);
  }
};

AdjLists makeAdjLists(std::vector<std::pair<int, int>> graph) {
  AdjLists result;
  for (auto link: graph) {
    result.add(link.first, link.second);
    result.add(link.second, link.first);
  }
  return result;
}

int findNumberOfTriangles(std::vector<std::pair<int, int>> links) {
  AdjLists adjLists = makeAdjLists(links);
  int counter = 0;

  for (auto node: adjLists.lists) {
    AdjList list = node.second;
    for (int link1: list.smaller) {
      for (int link2: list.larger) {
        if (adjLists.linked(link1, link2)) {
          counter++;
        }
      }
    }
  }

  return counter;
}

#define CHECK_TRIANGLES(linksValues, expectedNumber) { \
	std::vector<std::pair<int, int>> links = linksValues; \
  int actualNumber = findNumberOfTriangles(links); \
  BOOST_CHECK_EQUAL(expectedNumber, actualNumber); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( triangles_tests ) {

  CHECK_TRIANGLES(
    ARRAY_ARG_PROTECT({
      {0, 1},
      {2, 1},
      {0, 2},
      {4, 1}
    }), 1
  )
}
