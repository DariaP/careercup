var inspectArray = require('../solutions/21263687-count-elements.js'),
    test = require('tap').test;

test('it works with array that has every element', function(t) {
  var result = inspectArray([3,2,1,4]);
  t.similar(result,[1,1,1,1]);
  t.end();
});

test('it works with array that has every element in place', function(t) {
  var result = inspectArray([1,2,3,4]);
  t.similar(result,[1,1,1,1]);
  t.end();
});

test('it works with array that has every element shifted', function(t) {
  var result = inspectArray([4,1,2,3]);
  t.similar(result,[1,1,1,1]);
  t.end();
});

test('it works with array missing one elements', function(t) {
  var result = inspectArray([4,4,2,3]);
  t.similar(result,[0,1,1,2]);
  t.end();
});

test('it works with array missing some elements', function(t) {
  var result = inspectArray([4,4,3,3]);
  t.similar(result,[0,0,2,2]);
  t.end();
});

test('it works with array missing all but one element', function(t) {
  var result = inspectArray([4,4,4,4]);
  t.similar(result,[0,0,0,4]);
  t.end();
});

test('it works with single element array', function(t) {
  var result = inspectArray([1]);
  t.similar(result,[1]);
  t.end();
});

test('it works with empty array', function(t) {
  var result = inspectArray([]);
  t.similar(result,[]);
  t.end();
});