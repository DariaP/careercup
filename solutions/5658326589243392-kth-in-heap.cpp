/*
Given a max-heap represented as an array,
return the kth largest element without modifying the heap.

   10
 4    8
3 1  6 7

10, 4, 8, 3, 1, 6, 7
*/

#include <iostream>
#include <vector>
#include <queue>
#define BOOST_TEST_MODULE KthInHeapTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class QueueNode {
public:
  int idx, value;
  QueueNode(int initIdx, int initValue):
    idx(initIdx), value(initValue) {}
  bool operator<(const QueueNode &another) const {
    return value < another.value;
  }
};

std::pair<int, int> heapChildren(int parentIdx) {
  return std::pair<int, int>(2 * parentIdx + 1,
    2 * parentIdx + 2);
}

int kthInHeap(std::vector<int> heap, int k) {

  std::priority_queue<QueueNode> largestElements;
  largestElements.push(QueueNode(0, heap[0]));

  for (int i = 0 ; i < k ; ++i) {
    QueueNode nextLargest = largestElements.top();
    largestElements.pop();
    auto children = heapChildren(nextLargest.idx);
    if (children.first < heap.size()) {
      largestElements.push(QueueNode(children.first, heap[children.first]));
    }
    if (children.second < heap.size()) {
      largestElements.push(QueueNode(children.second, heap[children.second]));
    }
  }

  return largestElements.top().value;
}

#define CHECK_KTH_IN_HEAP(heapValues, k, expectedKth) { \
  std::vector<int> heap = heapValues; \
  int actualKth = kthInHeap(heap, k); \
  BOOST_CHECK_EQUAL(expectedKth, actualKth); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( kth_in_heap_tests ) {
  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 0, 10);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 1, 8);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 2, 7);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 3, 6);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 4, 4);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 5, 3);

  CHECK_KTH_IN_HEAP(ARRAY_ARG_PROTECT({
    10, 4, 8, 3, 1, 6, 7
  }), 6, 1);

  CHECK_KTH_IN_HEAP({1}, 0, 1);

}
