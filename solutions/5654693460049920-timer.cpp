/*
Given a timer time() with nanosecond accuracy and given the interface

interface RealTimeCounter:
    void increment()
    int getCountInLastSecond()
    int getCountInLastMinute()
    int getCountInLastHour()
    int getCountInLastDay()
implement the interface.

The getCountInLastX functions should return the number of
times increment was called in the last X.

1 3 5 9 11

14

10^9 hits in a second;
60 * 60 * 24

*/

#include <iostream>
#include <queue>
#include <ctime>
#define BOOST_TEST_MODULE StringCodesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>


long currentTime = 0;
void incTime(int amount = 1) {
  currentTime += amount;
}
long time() {
  return currentTime;
}

class LastMinuteCounter {
  std::queue<long> hitsInSeconds;
  long minuteStart,
   counter, lastSecondCounter;

  int timerAccuracy;

  void update(long now) {
    long minuteAgo = now - (long)59 * timerAccuracy;

    while (minuteStart < minuteAgo) {
      minuteStart += timerAccuracy;

      if (!hitsInSeconds.empty()) {
        counter -= hitsInSeconds.front();
        hitsInSeconds.pop();
      }

      hitsInSeconds.push(lastSecondCounter);
      counter+= lastSecondCounter;
      lastSecondCounter = 0;
    }
  }

public:
  LastMinuteCounter(long initTimerAccuracy) {
    minuteStart = time();
    lastSecondCounter = 0;
    counter = 0;

    timerAccuracy = initTimerAccuracy;
  }

  void increment(long now) {
    update(now);
    lastSecondCounter++;
  }

  int getCount() {
    long now = time();
    update(now);
    return counter + lastSecondCounter;
  }
};

class RealTimeCounter {
  std::queue<long> lastSecondHits,
                   prevSecondHits;

  LastMinuteCounter LastMinuteCounter;

  int timerAccuracy;


  static const int nanosecInSec = 1000000000;

  void updateSecondsTimer(long now) {
    long secondAgo = now - timerAccuracy;

    while (!lastSecondHits.empty() && lastSecondHits.front() < secondAgo) {
      lastSecondHits.pop();
    }
  }

public:

  RealTimeCounter(int initTimerAccuracy = nanosecInSec):
    timerAccuracy(initTimerAccuracy),
    LastMinuteCounter(initTimerAccuracy) {}

  void increment() {
    long now = time();

    updateSecondsTimer(now);
    lastSecondHits.push(now);

    LastMinuteCounter.increment(now);
  }

  long getCountInLastSecond() {
    long now = time();
    updateSecondsTimer(now);
    return lastSecondHits.size();
  }

  long getCountInLastMinute() {
    return LastMinuteCounter.getCount();
  }

  int getCountInLastHour() {return 0;}
  int getCountInLastDay() {return 0;}
};

std::pair<std::vector<long>,std::vector<long>> getCounts(std::vector<long> increments,
  long timerAccuracy)
{
  std::pair<std::vector<long>,std::vector<long>> result;
  RealTimeCounter counter(timerAccuracy);

  for (long i: increments) {
    result.first.push_back(counter.getCountInLastSecond());
    result.second.push_back(counter.getCountInLastMinute());
    std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;
    currentTime = i;
    counter.increment();
  }

  // check in a nanosecond
  currentTime++;
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  //check in an almost a second
  currentTime = timerAccuracy;
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  incTime();
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  //check in two seconds
  incTime(timerAccuracy);
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  //check in an almost a minute
  incTime(58 * timerAccuracy - 1);
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  //check in a minute
  incTime();
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  //check in a minute
  incTime(60 * timerAccuracy);
  result.first.push_back(counter.getCountInLastSecond());
  result.second.push_back(counter.getCountInLastMinute());
  std::cout << time() << ": " << counter.getCountInLastSecond() << " " << counter.getCountInLastMinute() << std::endl;

  return result;
}

#define CHECK_COUNTER(startTime, incrementsValues, expectedSecondHitsValues, expectedMinuteHitsValues, timerAccuracy) { \
  currentTime = startTime; \
  std::vector<long> increments = incrementsValues, \
    expectedSecondHits = expectedSecondHitsValues, \
    expectedMinuteHits = expectedMinuteHitsValues; \
  auto actualResult = getCounts(increments, timerAccuracy); \
}

#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( string_codes_tests ) {
  CHECK_COUNTER(0, {0}, ARRAY_ARG_PROTECT({
    0, 1, 1, 0, 0, 0, 0, 0
  }), ARRAY_ARG_PROTECT({
    0, 1, 1, 1, 1, 1, 0, 0
  }), 10)

  CHECK_COUNTER(0, {1}, ARRAY_ARG_PROTECT({
    0, 0, 1, 1, 1, 0, 0, 0, 0
  }), ARRAY_ARG_PROTECT({
    0, 0, 1, 1, 1, 1, 1, 0, 0
  }), 10)
}
