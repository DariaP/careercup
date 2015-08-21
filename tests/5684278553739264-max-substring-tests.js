var maxSubstring = require('../solutions/5684278553739264-max-substring.js'),
    test = require('tap').test;

test('it works with string where all characters are unique', function(t) {
  var result = maxSubstring('abcdef');
  t.equals(result, 'abcdef');
  t.end();
});

test('it works with string that has duplicates and longest substr is at the beggining', function(t) {
  var result = maxSubstring('abcdecf');
  t.equals(result, 'abcde');
  t.end();
});

test('it works with string that has duplicates and longest substr is at the end', function(t) {
  var result = maxSubstring('abcdecfghi');
  t.equals(result, 'decfghi');
  t.end();
});

test('it works with string that has duplicates and longest substr is in the middle', function(t) {
  var result = maxSubstring('abcdebfghbi');
  t.equals(result, 'cdebfgh');
  t.end();
});

test('it works with single character string', function(t) {
  var result = maxSubstring('a');
  t.equals(result, 'a');
  t.end();
});

test('it works with empty string', function(t) {
  var result = maxSubstring('');
  t.equals(result, '');
  t.end();
});