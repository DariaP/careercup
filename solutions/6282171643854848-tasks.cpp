/*
There are at most eight servers in a data center. Each server has got a capacity/memory limit. There can be at most 8 tasks that need to be scheduled on those servers. Each task requires certain capacity/memory to run, and each server can handle multiple tasks as long as the capacity limit is not hit. Write a program to see if all of the given tasks can be scheduled or not on the servers?

Ex:
Servers capacity limits: 8, 16, 8, 32
Tasks capacity needs: 18, 4, 8, 4, 6, 6, 8, 8
For this example, the program should say 'true'.

Ex2:
Server capacity limits: 1, 3
Task capacity needs: 4
For this example, program should return false.

32, 16, 8, 8, 0, 0, 0, 0
18, 8, 8, 8, 6, 6, 4, 4
*/

#include <iostream>
#include <vector>
#include <unordered_map>
#include <algorithm>
#define BOOST_TEST_MODULE TasksTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>

class Subproblem {

  std::vector<int> capacities;
  std::vector<int> tasks;
public:
  Subproblem() {}
  Subproblem(std::vector<int> &c, std::vector<int> &t):
    capacities(c.begin(), c.end()), tasks(t.begin(), t.end() ) {
      std::sort(capacities.begin(), capacities.end(), std::greater<int>());
      std::sort(tasks.begin(), tasks.end(), std::greater<int>());
    }

  std::string toString() {
    std::string result = "";
    for (int c: capacities) {
      result += "c";
      result += c;
    }
    for (int t: tasks) {
      result += "t";
      result += t;
    }
    return result;
  }

  int nTasks() {
    return tasks.size();
  }

  int nCapacities() {
    return capacities.size();
  }

  bool canScheduleBiggest(int iCapacity) {
    return tasks[0] <= capacities[iCapacity];
  }

  Subproblem scheduleBiggest(int iCapacity) {
    std::vector<int> newTasks(tasks.begin() + 1, tasks.end());
    std::vector<int> newCapacities(capacities.begin(), capacities.end());
    newCapacities[iCapacity] -= tasks[0];

    return Subproblem(newCapacities, newTasks);
  }
};

class SubProblemResults {
  std::unordered_map<std::string, bool> results;
public:
  SubProblemResults() {}
  bool has(Subproblem &s) {
    return results.find(s.toString()) != results.end();
  }
  bool get(Subproblem &s) {
    return results[s.toString()];
  }
  void add(Subproblem &s, bool result) {
    results[s.toString()] = result;
  }
};

bool canArrange_helper(Subproblem &s, SubProblemResults &subProblemResults) {
  if (s.nTasks() == 0) {
    return true;
  }

  for (int i = 0 ; i < s.nCapacities() ; i++) {
    if (s.canScheduleBiggest(i)) {
      Subproblem nextSubproblem = s.scheduleBiggest(i);
      if (canArrange_helper(nextSubproblem, subProblemResults)) {
        return true;
      }
    } else {
      break;
    }
  }

  return false;
}

bool canArrange(std::vector<int> capacities, std::vector<int> tasks) {
  SubProblemResults subProblemResults;
  Subproblem problem(capacities, tasks);
  return canArrange_helper(problem, subProblemResults);
}

#define CHECK_TASKS(capacitiesValues, tasksValues, expectedResult) { \
  std::vector<int> tasks = tasksValues, capacities = capacitiesValues; \
  bool actualResult = canArrange(capacities, tasks); \
  BOOST_CHECK_EQUAL(expectedResult, actualResult); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( tasks_tests ) {
  CHECK_TASKS({}, {}, true)
  CHECK_TASKS({1}, {1}, true)
  CHECK_TASKS({2}, {1}, true)
  CHECK_TASKS({1}, {2}, false)

  CHECK_TASKS(ARRAY_ARG_PROTECT({
    1, 2
  }), ARRAY_ARG_PROTECT({
    1, 2
  }), true)

  CHECK_TASKS(ARRAY_ARG_PROTECT({
    8, 16, 8, 32
  }), ARRAY_ARG_PROTECT({
    18, 4, 8, 4, 6, 6, 8, 8
  }), true)

  CHECK_TASKS(ARRAY_ARG_PROTECT({
    1, 3
  }), {4}, false)

}
