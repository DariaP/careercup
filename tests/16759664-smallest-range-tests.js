var smallestRangeSolver = require('../solutions/16759664-smallest-range.js');
var test = require('tap').test;

var lists = [
  [0, 4, 7],
  [-1, 4, 6, 19],
  [11, 45, 678]
];

test('joinSorted tests', function ( t) {
  var result = smallestRangeSolver.joinSorted(lists);
  t.deepEqual(result, [
     { number: -1, listIdx: 1 },
     { number: 0, listIdx: 0 },
     { number: 4, listIdx: 0 },
     { number: 4, listIdx: 1 },
     { number: 6, listIdx: 1 },
     { number: 7, listIdx: 0 },
     { number: 11, listIdx: 2 },
     { number: 19, listIdx: 1 },
     { number: 45, listIdx: 2 },
     { number: 678, listIdx: 2 }
    ], 'joins sorted lists');
  t.end();
});

function testSolver(t) {
  var allInts = smallestRangeSolver.joinSorted(lists);
  var solver = smallestRangeSolver.rangesIterator(allInts, lists.length);

  var range = solver.next();
  t.equals(range.toString(), "[-1, 11]", "range #1");

  var range = solver.next();
  t.equals(range.toString(), "[0, 11]", "range #2");

  var range = solver.next();
  t.equals(range.toString(), "[4, 11]", "range #3");

  var range = solver.next();
  t.equals(range.toString(), "[4, 11]", "range #4");

  var range = solver.next();
  t.equals(range.toString(), "[6, 11]", "range #5");

  var range = solver.next();
  t.equals(range.toString(), "[7, 19]", "range #6");

  var range = solver.next();
  t.equals(range, null, "6 ranges total");

  var range = solver.next();
  t.equals(range, null, "still returns null");

};

test('sliding range tests', testSolver );

test('it finds smallest ranhe', function(t) {
  var result = smallestRangeSolver.solve(lists);
  t.equals(result.toString(), '[6, 11]');
});
