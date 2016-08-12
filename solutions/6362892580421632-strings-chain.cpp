/*
you are given n-strings
you have to find whether a chain can be termed with all the strings given number n?
A chain can be formed b/w strings if last char of the 1st string matches
with 1st char of second string.

For example you are given

number of strings = 3

first string=sdfg

second string=dfgs

third string=ghjhk

they can be concatenated as ->

second first third

dfgs sdfg ghjhk (characters at concatenation points are same)

so concatenated string is-dfgsdfghjhk
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <unordered_set>
#define BOOST_TEST_MODULE StringsChainTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

#define LETTERS_COUNT 28

class AdjLists {

  void ensureHasNode(char node) {
    if (!hasNode(node)) {
      allNodes.insert(node);
      inLinks[node] = std::unordered_set<char>();
      outLinks[node] = std::unordered_set<char>();
      nIn[node] = 0;
      nOut[node] = 0;
    }
  }

  std::unordered_set<char> allNodes;
  std::unordered_map<char, std::unordered_set<char>> inLinks, outLinks;
  std::unordered_map<char, int> nIn, nOut;

public:

  AdjLists() {}

  bool hasNode(char node) {
    return allNodes.find(node) != allNodes.end();
  }

  void addLink(char from, char to) {
    ensureHasNode(from);
    ensureHasNode(to);
    inLinks[to].insert(from);
    outLinks[from].insert(to);
    nIn[to]++;
    nOut[from]++;
  }

  const std::unordered_set<char> &nodes() {
    return allNodes;
  }

  const std::unordered_set<char> links(char node) {
    return outLinks[node];
  }

  int nOutLinks(char node) {
    return nOut[node];
  }

  int nInLinks(char node) {
    return nIn[node];
  }

  int nNodes() {
    return allNodes.size();
  }
};

AdjLists findConnections(std::vector<std::string> strings) {
  AdjLists adjLists;
  for (std::string str: strings) {
    adjLists.addLink(str[0], str[str.length() - 1]);
  }
  return adjLists;
}

int findEulerStartIdx(AdjLists &adjLists) {
  for (char node: adjLists.nodes()) {
    if (adjLists.nOutLinks(node) == adjLists.nInLinks(node) + 1) {
      return node;
    }
  }
  return adjLists.nNodes() == 0 ? -1 : *adjLists.nodes().begin(); // TODO empty list
}

int countDFSNodes(AdjLists &adjLists, char startNode) {
  std::unordered_set<char> visited;
  int visitedNum = 0;
  char nextNode = startNode;

  while (-1 != nextNode) {
    visitedNum++;
    visited.insert(nextNode);

    char nextLinkedNode = -1;
    for (char linkedNode: adjLists.links(nextNode)) {
      if (visited.find(linkedNode) == visited.end()) {
        nextLinkedNode = linkedNode;
      }
    }
    nextNode = nextLinkedNode;
  }

  return visitedNum;
}

bool isConnected(AdjLists &adjLists) {
  int startIdx = findEulerStartIdx(adjLists);
  return countDFSNodes(adjLists, startIdx) == adjLists.nNodes();
}

bool hasEulerPath(AdjLists &adjLists) {
  bool foundStart = false, foundEnd = false;
  for (char node: adjLists.nodes()) {
    int inCount = adjLists.nInLinks(node),
      outCount = adjLists.nOutLinks(node);

    if (inCount != outCount) {
      if (inCount == outCount + 1) {
        if (foundEnd) return false;
        foundEnd = true;
      } else if (inCount + 1 == outCount) {
        if (foundStart) return false;
        foundStart = true;
      } else {
        return false;
      }
    }
  }
  return true;
}

bool canHaveChain(std::vector<std::string> strings) {
  AdjLists adjLists = findConnections(strings);
  return isConnected(adjLists) && hasEulerPath(adjLists);
}

#define CHECK_STR_CHAIN(stringsValues, expectedAnswer) { \
  bool actualAnswer = canHaveChain(std::vector<std::string>(stringsValues)); \
  BOOST_CHECK_EQUAL(expectedAnswer, actualAnswer); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( strings_chain_tests ) {
  CHECK_STR_CHAIN({}, true)
  CHECK_STR_CHAIN({"test"}, true)
  CHECK_STR_CHAIN({"t"}, true)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT(
    {"test", "true"}),
  true)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT(
    {"test", "wow"}),
  false)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT(
    {"test", "true", "a"}),
  false)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT(
    {"tea", "tree"}),
  false)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT({
    "sdfg", "dfgs", "ghjhk"
  }), true)

  CHECK_STR_CHAIN(ARRAY_ARG_PROTECT({
    "sdfg", "dfgs", "ghjhk", "a"
  }), false)

}
