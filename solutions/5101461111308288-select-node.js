/*
Given an unbalanced binary tree, write code to select a node at random 
(each node has an equal probability of being selected).
*/

var gen = require('random-seed'),
    seed = (new Date()).getTime().toString();

var random = gen.create(seed); 

function randomSelect(tree) {
  var num = random(tree.size);

  var it=tree.iterator(), item, i = 0;

  while((item = it.next()) !== null) {
    if (i == num) {
      return item;
    } else { 
      i++; 
    }
  }
}

module.exports = randomSelect;