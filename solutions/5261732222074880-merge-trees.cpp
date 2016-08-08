/*
how to merge two binary search tree into balanced binary search tree.. Let there be m elements in first tree and n elements in the other tree. Your merge function should take O(m+n) time with in constant space.

Examples:


A Balanced BST 1
90
/ \
70 110


A Balanced BST 2

60
/ \
5 800

output :-->
70
/ \
60 90
/ \
5	800
*/

#include <iostream>
#include <vector>
#include <cmath>
#define BOOST_TEST_MODULE MergeTreesTests
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

  int height() {
    int height = 1,
      leftHeight = 0, rightHeight = 0;
    if (nullptr != left) {
      leftHeight = left->height();
    }
    if (nullptr != right) {
      rightHeight = right->height();
    }
    return height + std::max(leftHeight, rightHeight);
  }

  bool isBalanced() {
    if (left == nullptr) {
      return right == nullptr || right->height() == 1;
    } else if (right == nullptr) {
      return left->height() == 1;
    } else {
      return left->isBalanced() && right->isBalanced()
        && std::abs(left->height() - right->height()) <= 1;
    }
  }
};

class BST {
public:

  void inOrderHelper(BSTNode *nextNode,
    std::vector<int> &result)
  {
    if (nextNode == nullptr) {
      return;
    }

    inOrderHelper(nextNode->left, result);
    result.push_back(nextNode->value);
    inOrderHelper(nextNode->right, result);
  }
  //----------------------------------------
  BSTNode *root;
  BST(): root(nullptr) {}
  BST(BSTNode *initRoot): root(initRoot) {}

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

  std::vector<int> inOrder() {
    std::vector<int> result;
    inOrderHelper(root, result);
    return result;
  }

  bool isBalanced() {
    return root == nullptr || root->isBalanced();
  }
};

//--------------------------------------------

BSTNode *rotateLeft(BSTNode *node) {
  BSTNode *root = node->right;
  node->right = root->left;
  root->left = node;
  return root;
}

BSTNode *rotateRight(BSTNode *node) {
  BSTNode *root = node->left;
  node->left = root->right;
  root->right = node;
  return root;
}

void unBalanceLeft(BSTNode *root) {
  BSTNode *nextNode = root;
  while (nextNode != nullptr) {
    if (nextNode->left != nullptr && nextNode->left->right != nullptr) {
      nextNode->left = rotateLeft(nextNode->left);
    } else {
      nextNode = nextNode->left;
    }
  }
}

void unBalanceRight(BSTNode *root) {
  BSTNode *nextNode = root;
  while (nextNode != nullptr) {
    if (nextNode->right != nullptr && nextNode->right->left != nullptr) {
      nextNode->right = rotateRight(nextNode->right);
    } else {
      nextNode = nextNode->right;
    }
  }
}

BSTNode *reverseLeftLinks(BSTNode *head) {
  BSTNode *node = head,
          *nextNode = node->left;

  while (node->left != nullptr) {
    nextNode = node->left;
    node->left->right = node;
    node->left = nullptr;

    node = nextNode;
  }

  return node;
}

BSTNode *bstToLinkedList(BSTNode *root) {
  unBalanceLeft(root);
  unBalanceRight(root);
  return reverseLeftLinks(root);
}

//--------------------------------------------

BSTNode *mergeLists(BSTNode *head1, BSTNode *head2) {
  BSTNode *node1 = head1, *node2 = head2,
    *mergedListHead = nullptr,
    *mergedListNode = mergedListHead,
    *nextMergedListNode;

   while (node1 != nullptr && node2 != nullptr) {
     if (node1->value < node2->value) {
       nextMergedListNode = node1;
       node1 = node1->right;
     } else {
       nextMergedListNode = node2;
       node2 = node2->right;
     }

     if (mergedListHead == nullptr) {
       mergedListHead = nextMergedListNode;
       mergedListNode = nextMergedListNode;
     } else {
       mergedListNode->right = nextMergedListNode;
       mergedListNode = nextMergedListNode;
     }
   }

   if (node1 != nullptr) {
     mergedListNode->right = node1;
   } else {
     mergedListNode->right = node2;
   }

   return mergedListHead;
}

//--------------------------------------------

BSTNode *linkedListToBalancedBST(BSTNode *head, int length, BSTNode **tail) {

  if (length == 0) {
    if (nullptr != tail) {
      *tail = head;
    }
    return nullptr;
  }
  if (length == 1) {
    if (nullptr != tail) {
      *tail = head->right;
    }
    head->left = nullptr;
    head->right = nullptr;
    return head;
  }

  BSTNode *root, *nextHead;

  int leftSubtreeSize = length / 2;
  BSTNode *left = linkedListToBalancedBST(head, leftSubtreeSize, &root);

  root->left = left;
  root->right = linkedListToBalancedBST(root->right,
    length - leftSubtreeSize - 1, tail);
  return root;
}

int listLength(BSTNode *head) {
  BSTNode *node = head;
  int length = 0;
  while (node != nullptr) {
    node = node->right;
    length++;
  }
  return length;
}

BSTNode *linkedListToBalancedBST(BSTNode *head) {
  int length = listLength(head);
  return linkedListToBalancedBST(head, length, nullptr);
}

//--------------------------------------------

BST merge(BST &tree1, BST &tree2) {
  if (tree1.root == nullptr) {
    return tree2;
  }
  if (tree2.root == nullptr) {
    return tree1;
  }

  BSTNode *head1 = bstToLinkedList(tree1.root),
          *head2 = bstToLinkedList(tree2.root);

  BSTNode *head = mergeLists(head1, head2);

  return BST(linkedListToBalancedBST(head));
}

std::vector<int> sort(std::vector<int> array1, std::vector<int> array2) {
  std::vector<int> result(array1.begin(), array1.end());
  result.insert(result.begin(), array2.begin(), array2.end());
  std::sort(result.begin(), result.end());
  return result;
}

#define CHECK_MERGE_TREES(tree1NodesArray, tree2NodesArray) { \
  std::vector<int> tree1Nodes = tree1NodesArray, \
    tree2Nodes = tree2NodesArray; \
  BST tree1, tree2; \
  tree1.add(tree1Nodes); tree2.add(tree2Nodes); \
  std::vector<int> treesNodes = sort(tree1Nodes, tree2Nodes); \
  BST result = merge(tree1, tree2); \
  bool balanced = result.isBalanced(); \
  BOOST_CHECK_EQUAL(balanced, true); \
  std::vector<int> treeNodes = result.inOrder(); \
  BOOST_CHECK_EQUAL_COLLECTIONS(treesNodes.begin(), treesNodes.end(), \
    treeNodes.begin(), treeNodes.end()); \
}

std::vector<int> listToArray(BSTNode *head) {
  std::vector<int> values;

  BSTNode *node = head;
  while (node != nullptr) {
    values.push_back(node->value);
    node = node->right;
  }

  return values;
}

#define CHECK_TREES_TO_LIST(treeNodesArray) { \
  std::vector<int> treeNodes = treeNodesArray; \
  BST tree; \
  tree.add(treeNodes); \
  BSTNode *head = bstToLinkedList(tree.root); \
  std::vector<int> listNodes = listToArray(head); \
  std::sort(treeNodes.begin(), treeNodes.end()); \
  BOOST_CHECK_EQUAL_COLLECTIONS(treeNodes.begin(), treeNodes.end(), \
    listNodes.begin(), listNodes.end()); \
}

#define CHECK_MERGE_LISTS(tree1NodesArray, tree2NodesArray) { \
  std::vector<int> tree1Nodes = tree1NodesArray, \
    tree2Nodes = tree2NodesArray; \
  BST tree1, tree2; \
  tree1.add(tree1Nodes); tree2.add(tree2Nodes); \
  std::vector<int> treesNodes = sort(tree1Nodes, tree2Nodes); \
  BSTNode *head1 = bstToLinkedList(tree1.root), \
    *head2 = bstToLinkedList(tree2.root), \
    *head = mergeLists(head1, head2); \
  std::vector<int> listNodes = listToArray(head); \
  BOOST_CHECK_EQUAL_COLLECTIONS(treesNodes.begin(), treesNodes.end(), \
    listNodes.begin(), listNodes.end()); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( mergeTrees_tests ) {
  CHECK_MERGE_TREES(
    ARRAY_ARG_PROTECT({
      90, 70, 110
    }),
    ARRAY_ARG_PROTECT({
      60, 5, 800
    })
  )

  CHECK_MERGE_TREES(
    {90},
    ARRAY_ARG_PROTECT({
      60, 5, 800
    })
  )

  CHECK_MERGE_TREES(
    ARRAY_ARG_PROTECT({
      60, 5, 800
    }),
    {90}
  )

  CHECK_MERGE_TREES(
    {80}, {90}
  )

  CHECK_MERGE_TREES(
    {80}, {}
  )

  CHECK_MERGE_TREES(
    {}, {80}
  )

  CHECK_MERGE_TREES(
    {}, {}
  )

  CHECK_MERGE_TREES(
    ARRAY_ARG_PROTECT({
      60, 5, 800
    }),
    {}
  )

  CHECK_MERGE_TREES(
    ARRAY_ARG_PROTECT({
      60, 5, 800
    }),
    ARRAY_ARG_PROTECT({
      50, 25, 75, 20, 35, 79, 19, 22, 30, 40,
      85, 18, 45, 82, 90, 81, 83, 95, 80, 91, 96, 92
    })
  )
}
