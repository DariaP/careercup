/*
A tree, (NOT NECESSARILY BINARY), has nodes numbered 0 to N-1.
 An array has indices ranging from 0 to N-1.
 The indices denote the node ids and values denote the ids of parents.
 A value of -1 at some index k denotes that node with id k is the root. For ex:

3 3 3 -1 2
0 0 0 0 0

In the above, nodes with ids 0, 1 & 2 have 3 as parent.
3 is the root as its parent = -1 and 2 is the parent of node id 4.

Given such an array, find the height of the tree.
*/

#include <iostream>
#include <vector>
#include <unordered_set>
#define BOOST_TEST_MODULE TreeHeightTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

std::vector<std::unordered_set<int>> findChildren(const std::vector<int> &parents) {
  std::vector<std::unordered_set<int>> children(parents.size());

  for (int i = 0 ; i < parents.size() ; ++i) {
    if (parents.at(i) != -1) {
      children[parents.at(i)].insert(i);
    }
  }

  return children;
}

int findRoot(const std::vector<int> &parents) {
  for (int i = 0 ; i < parents.size() ; ++i) {
    if (parents.at(i) == -1) {
      return i;
    }
  }
  return -1;
}

std::vector<int> findLeaves(const std::vector<std::unordered_set<int>> &children) {
  std::vector<int> leaves;

  for (int i = 0 ; i < children.size() ; ++i) {
    if (children.at(i).empty()) {
      leaves.push_back(i);
    }
  }

  return leaves;
}

int height(std::vector<std::unordered_set<int>> &children,
  const std::vector<int> parents)
{
  int root = findRoot(parents);

  std::vector<int> leaves = findLeaves(children),
    subtreeHeight(parents.size(), 1);

  while (!leaves.empty()) {
    std::vector<int> newLeaves;
    for (int nextLeaf: leaves) {
      int nextParent = parents.at(nextLeaf);
      if (nextParent == -1) {
        continue;
      }

      subtreeHeight[nextParent] = subtreeHeight[nextLeaf] + 1;

      children[nextParent].erase(nextLeaf);
      if (children[nextParent].empty()) {
        newLeaves.push_back(nextParent);
      }
    }
    leaves = newLeaves;
  }

  return subtreeHeight[root];
}

bool valid(const std::vector<int> parents) {
  bool oneRoot = false;
  for (int parent: parents) {
    if (parent == -1) {
      if (oneRoot) {
        return false;
      } else {
        oneRoot = true;
      }
    } else {
      if (parent >= parents.size() || parent < 0) {
        return false;
      }
    }
  }

  return oneRoot;
}

int height(const std::vector<int> parents) {
  if (parents.size() == 0) {
    return 0;
  }

  if (!valid(parents)) {
    return -1;
  }

  std::vector<std::unordered_set<int>> children = findChildren(parents);
  return height(children, parents);
}

#define CHECK_TREE_HEIGHT(parentsValues, expectedHeight) { \
  std::vector<int> parents = parentsValues; \
  int actualHeight = height(parents); \
  BOOST_CHECK_EQUAL(expectedHeight, actualHeight); \
}
#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( tree_height_tests ) {

  CHECK_TREE_HEIGHT({1}, -1)
  CHECK_TREE_HEIGHT({-2}, -1)
  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      -1, -1
    }),
    -1
  )
  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      1, 0
    }),
    -1
  )

  CHECK_TREE_HEIGHT({}, 0)
  CHECK_TREE_HEIGHT({-1}, 1)
  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      -1, 0
    }),
    2
  )
  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      -1, 0, 0
    }),
    2
  )

  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      -1, 0, 1
    }),
    3
  )

  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      -1, 0, 0, 0, 0, 0, 0
    }),
    2
  )

  CHECK_TREE_HEIGHT(
    ARRAY_ARG_PROTECT({
      3, 3, 3, -1, 2
    }),
    3
  )
}
