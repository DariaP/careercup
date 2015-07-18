var normalize = require('../solutions/5665972218232832-norm-path.js');
var test = require('tap').test;

test('it resolves empty path', function ( t) {
  var result = normalize('');
  t.equals(result, '', 'empty path is alright');
  t.end();
});

test('it resolves root', function ( t) {
  var result = normalize('\\');
  t.equals(result, '\\', 'root is alright');
  t.end();
});

test('it resolves absolute path', function ( t) {
  var result = normalize('\\some\\folder\\');
  t.equals(result, '\\some\\folder\\', 'root is alright');
  t.end();
});

test('it resolves relative path', function ( t) {
  var result = normalize('some\\other\\folder\\');
  t.equals(result, 'some\\other\\folder\\', 'root is alright');
  t.end();
});

test('it resolves file path', function ( t) {
  var result = normalize('some\\other\\folder\\and\\file.ext');
  t.equals(result, 'some\\other\\folder\\and\\file.ext', 'root is alright');
  t.end();
});

test('it normalizes file path', function ( t) {
  var result = normalize('apple\\banana\\mango\\..\\grapes');
  t.equals(result, 'apple\\banana\\grapes', 'root is alright');
  t.end();
});

test('with several dots', function ( t) {
  var result = normalize('apple\\banana\\mango\\..\\grapes\\..\\cherries');
  t.equals(result, 'apple\\banana\\cherries', 'root is alright');
  t.end();
});

test('dots at the end', function ( t) {
  var result = normalize('apple\\banana\\..\\mango\\..\\grapes\\..');
  t.equals(result, 'apple', 'root is alright');
  t.end();
});

test('nested dots', function ( t) {
  var result = normalize('apple\\banana\\mango\\..\\..');
  t.equals(result, 'apple', 'root is alright');
  t.end();
});