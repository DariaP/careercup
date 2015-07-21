var randomSelect = require('../solutions/5101461111308288-select-node.js');
var test = require('tap').test;
var Tree = require('bintrees').BinTree;

test('it selects values uniformly', function ( t) {

  var tree = new Tree(function(a, b) { return a - b; });
  var values = [2, -3, 4, 10, 22, 338];

  for (var i = 0 ; i < values.length ; ++i) {
    tree.insert(values[i]);
  }

/*  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));
  console.log(randomSelect(tree));*/

  
  var results = {};

  for (i = 0 ; i < 166500 * values.length ; ++i) {
    var value = randomSelect(tree);
    if (results[value]) {
      results[value] = results[value] + 1;
    } else {
      results[value] = 1;
    }
  }
  
  for (i = 0 ; i < results.length ; ++i) {
    t.equals(true, results[i] > 166000);
    t.equals(true, results[i] < 167000);
  }

  t.end();
});
