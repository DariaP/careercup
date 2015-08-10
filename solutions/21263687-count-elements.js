/* 
You are given an array of n integers which can contain integers from 1 to n only . Some elements can be repeated multiple times and some other elements can be absent from the array . Write a running code on paper which takes O(1) space apart from the input array and O(n) time to print which elements are not present in the array and the count of every element which is there in the array along with the element number . 
NOTE: The array isn't necessarily sorted. 
*/

function inspectArray(array) {
  var nextIdx = 0, startSearchIdx = 1;
  var nextInt = array[nextIdx] - 1;
  array[nextIdx] = 0;

  while (nextIdx !== array.length) {
    if (array[nextInt] < 0) {
      array[nextInt] -= 1;
      nextIdx = findNextIdx(array, startSearchIdx);
      if (nextIdx !== array.length) {
        nextInt = array[nextIdx] - 1;
        array[nextIdx] = 0;      
        startSearchIdx = nextIdx + 1;
      }
    } else {
      var buffer = array[nextInt] - 1;
      array[nextInt] = -1;
      nextInt = buffer;
    }
  }

  for (var i = 0 ; i < array.length ; ++i) {
    if (array[i] < 0) {
      array[i] = -1 * array[i];      
    } else {
      array[i] = 0;
    }
  }

  return array;
}

function findNextIdx(array, startSearchIdx) {
  var idx = startSearchIdx;
  while (idx < array.length && array[idx] <= 0) {
    idx++;
  }
  return idx;
}

module.exports = inspectArray;
