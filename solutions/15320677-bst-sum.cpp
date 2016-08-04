/*
Given a BST and a value x. Find two nodes in the tree whose sum is equal x.
Additional space: O(height of the tree). It is not allowed to modify the tree
*/

#include <iostream>
#include <vector>
#include <typeinfo>
#define BOOST_TEST_MODULE BSTSumTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class BSTNode {
public:
  BSTNode *left, *right;
  int value;
  BSTNode(int initValue): value(initValue), left(nullptr), right(nullptr) {}
  void add(int newValue) {
    if (newValue <= value) {
      if (left) {
        left->add(newValue);
      } else {
        left = new BSTNode(newValue);
      }
    } else {
      if (right) {
        right->add(newValue);
      } else {
        right = new BSTNode(newValue);
      }
    }
  }
};

class BST {
public:
  class BSTIterator {
    bool findFirstValue;
    void checkFirst() {
      if (findFirstValue) {
        findFirst(tree->root);
        findFirstValue = false;
      }
    }
    BST *tree;
  protected:
    BSTIterator(BST *initTree): nextNode(nullptr),
      findFirstValue(true), tree(initTree) {}
    BSTNode *nextNode;

    virtual void findFirst(BSTNode *root) {};
    virtual void findNext() {};

  public:
    int get() {
      checkFirst();
      return nextNode->value;
    }
    void next() {
      checkFirst();
      findNext();
    }
    bool end() {
      checkFirst();
      return nextNode == nullptr;
    }
  };

  class InOrderIterator: public BSTIterator {
    std::vector<BSTNode*> path;

    void findFirst(BSTNode *root) {
      BSTNode *nextLeft = root;
      while (nextLeft != nullptr) {
        path.push_back(nextLeft);
        nextLeft = nextLeft->left;
      }
      nextNode = path[path.size() - 1];
    }

    void findNext() {
      if (nextNode->right) {
        findFirst(nextNode->right);
      } else {
        BSTNode *lastNode = nextNode;
        while (path.size() != 1) {
          path.pop_back();
          BSTNode *lastParent = path[path.size() - 1];
          if (lastParent->left == lastNode) {
            nextNode = lastParent;
            return;
          }
          lastNode = lastParent;
        }
        path.pop_back();
        nextNode = nullptr;
      }
    }
  public:
    InOrderIterator(BST *tree): BSTIterator(tree) {};
  };

  class InOrderReverseIterator: public BSTIterator {
    std::vector<BSTNode*> path;
    void findFirst(BSTNode *root) {
      BSTNode *nextRight = root;
      while (nextRight != nullptr) {
        path.push_back(nextRight);
        nextRight = nextRight->right;
      }
      nextNode = path[path.size() - 1];
    }
    void findNext() {
      if (nextNode->left) {
        findFirst(nextNode->left);
      } else {
        BSTNode *lastNode = nextNode;
        while (path.size() != 1) {
          path.pop_back();
          BSTNode *lastParent = path[path.size() - 1];
          if (lastParent->right == lastNode) {
            nextNode = lastParent;
            return;
          }
          lastNode = lastParent;
        }
        path.pop_back();
        nextNode = nullptr;
      }
    }
  public:
    InOrderReverseIterator(BST *tree): BSTIterator(tree) {};
  };

  //----------------------------------------
  BSTNode *root;
  BST(): root(nullptr) {}

  void add(std::vector<int> values) {
    for (int value:values) {
      add(value);
    }
  }

  void add(int value) {
    if (root) {
      root->add(value);
    } else {
      root = new BSTNode(value);
    }
  }

  InOrderIterator inOrderIterator() {
    return InOrderIterator(this);
  }

  InOrderReverseIterator inOrderReverseIterator() {
    return InOrderReverseIterator(this);
  }

};

std::pair<int, int> *findNodesWithSum(BST &tree, int sum) {
  auto first = tree.inOrderIterator();
  auto second = tree.inOrderReverseIterator();

  while(!first.end() && !second.end()) {
    int nextSum = first.get() + second.get();
    if(nextSum == sum) {
      return new std::pair<int, int>(first.get(), second.get());
    } else if (nextSum > sum) {
      second.next();
    } else {
      first.next();
    }
  }
  return nullptr;
}

void inOrder(BST &tree) {
  BST::InOrderIterator it = tree.inOrderIterator();
  while(!it.end()) {
    std::cout << it.get() << " ";
    it.next();
  }
  std::cout << std::endl;

  auto itr = tree.inOrderReverseIterator();
  while(!itr.end()) {
    std::cout << itr.get() << " ";
    itr.next();
  }
  std::cout << std::endl;
}

#define CHECK_BST_SUM(bstValues, sum, expectedResultValues) { \
  std::pair<int, int> expectedResult = expectedResultValues; \
  BST tree; tree.add(bstValues); \
  std::pair<int, int> *actualResult = findNodesWithSum(tree, sum); \
  BOOST_CHECK_EQUAL(expectedResult, *actualResult); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

namespace std {
    ostream &operator<<(ostream &stream, const std::pair<int, int> &p) {
      stream << "(" << p.first << ", " << p.second << ")";
      return stream;
    }
}

BOOST_AUTO_TEST_CASE( bst_sum_tests ) {
  CHECK_BST_SUM(
    ARRAY_ARG_PROTECT({1, 2, 3, 5}), 4,
    ARRAY_ARG_PROTECT({1, 3})
  )
}
