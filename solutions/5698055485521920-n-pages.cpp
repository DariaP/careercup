/*
A book contains with pages numbered from 1 - N.
Imagine now that you concatenate all page numbers in the book such
that you obtain a sequence of numbers which can be represented as a string.
You can compute number of occurences 'k' of certain digit 'd' in this string.

For example, let N=12, d=1, hence

s = '123456789101112' => k=5

since digit '1' occure five times in that string.

Problem: Write a method that, given a digit 'd' and number of its occurences 'k',
returns a number of pages N. More precisely, return a lower and upper bound of this number N.

Example:
input: d=4, k=1;
output {4, 13} - the book has 4-14 pages

input d=4 k=0;
output {1, 3} - the book has 1-3 pages
*/


#include <iostream>
#include <vector>
#include <unordered_map>
#define BOOST_TEST_MODULE NPagesTests
#define BOOST_TEST_MAIN
#define BOOST_TEST_DYN_LINK
#include <boost/test/unit_test.hpp>
int countDigits(int number)
{
    int digits = 0;
    while (0 != number) {
        number /= 10;
        digits++;
    }
    return digits;
}


int occurences(int digit, int number) {
  int nDigits = countDigits(number),
		nOccurences = 0,
		pow10 = 1;

	for (int i = 0 ; i < nDigits ; ++i) {

		nOccurences += pow10 * (number / (pow10 * 10));

    int remainder = number % (pow10 * 10);
		if (remainder / pow10 > digit) {
			nOccurences += pow10;
		} else if (remainder / pow10 == digit) {
			nOccurences += (remainder % pow10 + 1);
		}

    if (digit == 0) {
      nOccurences -= pow10;
    }

		pow10 *= 10;
	}
//std::cout << number << " occ: " << nOccurences << std:: endl;
	return nOccurences;
}

int binarySearchForLowerBound(int lowerBound, int upperBound,
  int nDigits, int digit)
{
  int lowerBoundOccurences = occurences(digit, lowerBound);
  if (lowerBoundOccurences == nDigits) {
    return lowerBound;
  }

  int upperBoundOccurences = occurences(digit, upperBound);
  if (upperBoundOccurences < nDigits) {
    return upperBound + 1;
  }

  int middle = (upperBound + lowerBound) / 2,
    middleOccurences = occurences(digit, middle);

  if (middleOccurences >= nDigits) {
    return binarySearchForLowerBound(lowerBound, middle - 1, nDigits, digit);
  } else {
    return binarySearchForLowerBound(middle + 1, upperBound, nDigits, digit);
  }
}

int lowerBound(int nDigits, int digit) {
  int upperBoundNDigits = 1,
    lowerBoundNDigits = 0,
    upperBound = 10, lowerBound = 0,
    zeroUpperBoundNDigits = 1,
    zeroDec = 1;

  while (upperBoundNDigits < nDigits) {
    lowerBound = upperBound;
    lowerBoundNDigits = upperBoundNDigits;
    if (digit != 0) {
      upperBoundNDigits = upperBoundNDigits * 10 + upperBound;
    } else {
      zeroUpperBoundNDigits = zeroUpperBoundNDigits * 10 + upperBound;
      zeroDec += upperBound;
      upperBoundNDigits = zeroUpperBoundNDigits - zeroDec;
    }

    upperBound = upperBound * 10;
  }

  return binarySearchForLowerBound(lowerBound, upperBound, nDigits, digit);
}

std::pair<int, int> numberWithDigits(int digit, int nDigits) {

  return std::pair<int, int>(lowerBound(nDigits, digit),
    lowerBound(nDigits + 1, digit) - 1);
}

std::pair<int, int> generateTestCases(int digit, int nDigits) {
    char digitChar = '0' + digit;
    int lowerBound = 0, nDigitsSoFar = 0, nextDigit = 0;
    while (nDigitsSoFar < nDigits) {
      nextDigit++; lowerBound++;
      std::string digitStr = std::to_string(nextDigit);
      for (char c: digitStr) {
        if (c == digitChar) {
          nDigitsSoFar++;
        }
      }
    }

    if (nDigitsSoFar > nDigits) {
      return std::pair<int, int>(-1, -1);
    }

    int upperBound = lowerBound;
    while (nDigitsSoFar == nDigits) {
      nextDigit++; upperBound++;
      std::string digitStr = std::to_string(nextDigit);
      for (char c: digitStr) {
        if (c == digitChar) {
          nDigitsSoFar++;
        }
      }
    }

    return std::pair<int, int>(lowerBound, upperBound - 1);
}

namespace std {
  ostream& operator<<(ostream &stream, const pair<int, int> &p) {
    stream << "{" << p.first << "," << p.second << "}";
    return stream;
  }
}
#define CHECK_NUMBERS(digit, nDigits) { \
  std::pair<int, int> expectedResult = generateTestCases(digit, nDigits); \
  if (expectedResult.first != -1) { \
    std::pair<int, int> actualResult = numberWithDigits(digit, nDigits); \
    BOOST_CHECK_EQUAL(expectedResult, actualResult); \
  } \
}
#define ARRAY_ARG_PROTECT(...) __VA_ARGS__

BOOST_AUTO_TEST_CASE( n_pages_tests ) {
  for (int digit = 0 ; digit < 10 ; ++digit) {
    for (int occurences = 0 ; occurences < 1001 ; occurences++) {
      CHECK_NUMBERS(digit, occurences)
    }
  }
}
