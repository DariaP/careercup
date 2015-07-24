/*You have k lists of sorted integers. Find the smallest range that includes at least one number from each of the k lists. 

For example, 
List 1: [4, 10, 15, 24, 26] 
List 2: [0, 9, 12, 20] 
List 3: [5, 18, 22, 30] 

The smallest range here would be [20, 24] as it contains 24 from list 1, 20 from list 2, and 22 from list 3.*/

function solve(lists) {

  var allLists = joinSorted(lists);

  var ranges = rangesIterator(allLists, lists.length);
  var smallestRange = {
        lowerBound: allLists[0].number,
        upperBound: allLists[allLists.length - 1].number
      },
      nextRange;

  do {
    var nextRange = ranges.next();
    if ( nextRange && nextRange.smallerThan(smallestRange) ) {
      smallestRange = currentRange;
    }
  } while ( nextRange );

  return smallestRange;
}

function rangesIterator(array, nLists) {

  var lowerBound = 0,
      upperBound = 0;

  var missingListIdx = -1;

  return {

    next: function() {

      if (end()) return null;

      if (upperBound == 0) {
        initUpperBound();
        return currentRange();
      } else {
        moveLowerBoundForward();
        if ( tryAdjustUpperBound() ) {
          return currentRange();
        } else {
          return null;
        }
      }
    }
  };

  function moveLowerBoundForward() {
    if (end()) return;
    missingListIdx = array[lowerBound].listIdx;
    lowerBound = lowerBound + 1;
  }

  function tryAdjustUpperBound() {

    if (end()) return false;

    for (var i = lowerBound ; i <= upperBound ; ++i) {
      if (array[i].listIdx == missingListIdx) {
        return true;
      }
    }

    while (!end() && array[upperBound].listIdx != missingListIdx ) {
      upperBound = upperBound + 1;
    }

    return !end();
  }

  function initUpperBound() {
    for (var i = 0 ; i < nLists ; ++i) {
      missingListIdx = i;
      // first range allways exists - 
      // no need to check return status
      tryAdjustUpperBound(); 
    }
  }

  function end() {
    return upperBound >= array.length;
  }

  function currentRange() {
    var range = {
      lowerBound: array[lowerBound].number,
      upperBound: array[upperBound].number
    };

    range.smallerThan = function(otherRange) {
      return (range.upperBound - range.lowerBound) < (otherRange.upperBound - otherRange.lowerBound);
    };

    range.toString = function() {
      return "[" + range.lowerBound + ", " + range.upperBound + "]";
    }

    return range;
  }
}

function joinSorted(lists) {

  var result = [];

  for (var i = 0 ; i < lists.length ; ++i) {
    result = result.concat(
      lists[i].map(function(number) {
        return {
          number: number,
          listIdx: i
        };
      })
    );
  }

  result.sort(function(a,b) {
    return a.number - b.number;
  });

  return result;
}

module.exports = {
  solve: solve,
  joinSorted: joinSorted,
  rangesIterator: rangesIterator
};