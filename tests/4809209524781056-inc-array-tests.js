var increment = require('../solutions/4809209524781056-inc-array.js');
var test = require('tap').test;

test('it increments 0', function ( t) {
  var result = increment([0]);
  t.deepEqual(result, [1], 'zero is alright');
  t.end();
});

test('it increments 3', function ( t) {
  var result = increment([3]);
  t.deepEqual(result, [4], 'zero is alright');
  t.end();
});

test('it increments 9', function ( t) {
  var result = increment([9]);
  t.deepEqual(result, [1, 0], 'zero is alright');
  t.end();
});

test('it increments 100', function ( t) {
  var result = increment([1, 0, 0]);
  t.deepEqual(result, [1, 0, 1], 'zero is alright');
  t.end();
});

test('it increments 3299', function ( t) {
  var result = increment([3, 2, 9, 9]);
  t.deepEqual(result, [3, 3, 0, 0], 'zero is alright');
  t.end();
});

test('it increments 99999', function ( t) {
  var result = increment([9, 9, 9, 9, 9]);
  t.deepEqual(result, [1, 0, 0, 0, 0, 0], 'zero is alright');
  t.end();
});

test('invalid input: not an array', function ( t) {
  var callInc = function() {
  	increment(89);
  }
  t.throws(callInc, 'Invalid input (array required)');
  t.end();
});

test('invalid input: not an array of numbers', function ( t) {
  var callInc = function() {
  	increment([8, 9, 'H']);
  }
  t.throws(callInc, 'Invalid input (array of numbers required)');
  t.end();
});

test('invalid input: numbers > 9', function ( t) {
  var callInc = function() {
  	increment([9, 9, 10]);
  }
  t.throws(callInc, 'Invalid input (numbers 0 to 9 required)');
  t.end();
});

test('invalid input: numbers < 0', function ( t) {
  var callInc = function() {
  	increment([9, 9, -1]);
  }
  t.throws(callInc, 'Invalid input (numbers 0 to 9 required)');
  t.end();
});