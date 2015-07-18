/*
You are given an array representing integer. Write a function which increments this integer. 
Example: input [1,2,3] (represents 123) -> output [1,2,4]
*/

var base = 10;

function increment(array) {

  if( Object.prototype.toString.call(array) !== '[object Array]' ) {
    throw('Invalid input (array required)');
  }

  var plus1 = true;
  var result = array.reverse().map(function(number) {

    if (typeof(number) !== "number") {
      throw "Invalid input (array of numbers required)";
    }

    if (number < 0 || number > 9) {
      throw "Invalid input (numbers 0 to 9 required)";
    }

    var incNumber = number;
    if (plus1 === true) {
      incNumber = number + 1;
      if (incNumber === base) {
        incNumber = 0;
        plus1 = true;
      } else {
        plus1 = false;
      }
    }
    return incNumber;
  }).reverse();

  if (plus1 === true) {
    result.unshift(1);
  }

  return result;
}

module.exports = increment;