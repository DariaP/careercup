var hashTable = require('../utils/hashTable.js');

function maxSubstring(string) {
	var start = 0, end = 0,
			chars = hashTable(),
			maxSubstr = {
				start: 0,
				end: 0
			};

	maxSubstr.length = function() { return (maxSubstr.end - maxSubstr.start + 1);};

	while (end !== string.length) {
		var newChar = string.charAt(end);

		if (chars.has(newChar)) {
			adjustStart(newChar);
		} else {
			chars.put(newChar, true);
		}

		if ((end - start + 1) > maxSubstr.length()) {
			maxSubstr.start = start,
			maxSubstr.end = end;
		}

		end++;
	}

	function adjustStart(duplicateChar) {
		for (var i = start ; i < end ; ++i) {
			if (string.charAt(i) === duplicateChar) {
				start = i + 1;
				break;
			}
		}
	}

	return string.substring(maxSubstr.start, maxSubstr.end + 1);
}

module.exports = maxSubstring;