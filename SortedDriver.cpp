// SortedDriver.cpp

// tom bailey   1445  25 mar 2014
// Construct sorted sequences and call functions that
//   process the sorted sequences.

// Modified by Jacob Williams, 11/5/2018, for COSC 2030 lab 6

#include "RandomUtilities.h"
#include "ContainerPrinting.h"
#include "unixTimer.h"              //CHANGE: this to unixTimer.h if on mac/linux
#include <list>
#include <iostream>
#include <vector>
#include <algorithm>

using namespace std;

// post: a sorted vector of listSize random doubles from
//         the range minNum to maxNum has been returned.
vector<double>
getNums(size_t listSize, double minNum, double maxNum)
{
	vector<double> theList;
	for (size_t i = 0; i < listSize; ++i)
	{
		theList.push_back(randReal(minNum, maxNum));
	}

	sort(begin(theList), end(theList));

	return theList;
}


// post: a sorted list of numWords words of length
//         wordLength with characters chosen randomly from
//         alphabet has been returned.
list<string>
getWords(size_t numWords, size_t wordLength, string alphabet)
{
	list<string> theWords;
	for (size_t i = 0; i < numWords; ++i)
	{
		string word;
		for (size_t j = 0; j < wordLength; ++j)
		{
			word += alphabet.at(randInt(0, alphabet.size()));
		}
		theWords.push_back(word);
	}

	theWords.sort();

	return theWords;
}


// pre:  number is not empty;
//       number is sorted from smallest to largest
// post: The most isolated entry in number has been returned
double mostIsolated(vector<double> & number) {
    if (number.empty()) {
        return 0;
    }

    double first = number[0];
    double second = 0;
    double third = 0;
    double leftIsolation = 0;
    double rightIsolation = 0;
    double isolation = 0;               // the nearest-neighbor formulation
    int isolatedIndex = 0;

    if (number.size() == 1) {
        return first;
    }

    for (int i = 1; i < number.size() - 1; i++) {

        // Chayce, Sydney, and Jagadish helped me realize that I need to compare both
        // left and right isolations.
        first = number[i-1];
        second = number[i];
        third = number[i+1];

        double newLeftIsolation = second - first;
        double newRightIsolation = third - second;
        double newIsolation = 0;

        // There is a corner case for the first number.
        if (i == 1) {
            newIsolation = newLeftIsolation;
        } else {
            newIsolation = min(newLeftIsolation, newRightIsolation);
        }

        // Update the index of the most-isolated number and the maximum isolation
        if (newIsolation > isolation && newLeftIsolation == newIsolation) {
            isolatedIndex = i - 1;
            isolation = newIsolation;
        } else if (newIsolation > isolation && newRightIsolation == newIsolation) {
            isolatedIndex = i;
            isolation = newIsolation;
        }

    }

    return number.at(isolatedIndex);
}


// pre:  A and B are sorted.
// post: The number of strings in A that do not occur in B
//         has been returned.
int unmatched(list<string> & A, list<string> & B) {
    int count = 0;
    bool done = false;
    std::list<string>::iterator itA = A.begin();
    std::list<string>::iterator itB = B.begin();

    // Jagadish helped me with the algorithm here!
    while (!done) {
        if (*itA < *itB) {
            itA++;
        } else if (*itA > *itB) {
            itB++;
        } else {
            count++;
            itA++;
        }

        if (itA == A.end()) done = true;
    }

    return A.size() - count;
}


int
main()
{
	cout << "Find the most isolated number" << endl
		<< "-----------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for numbers: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct a sorted list of numbers
		Timer get;
		get.start();
		vector<double> numbers = getNums(n, -n, n);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (n < 10)
			cout << numbers << endl << endl;

		// Report a most isolated isolated number
		Timer time;
		time.start();
		double isolated = mostIsolated(numbers);
		time.stop();
		cout << "The most isolated number is "
			<< isolated << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}


	cout << endl << endl;
	cout << "Count the unmatched words" << endl
		<< "-------------------------" << endl << endl;
	while (true)
	{
		cout << "Enter size for words lists: ";
		int n = 0;
		cin >> n;
		if (n <= 0)
			break;
		cout << "Enter word length: ";
		int wordSize;
		cin >> wordSize;
		cout << "Enter alphabet: ";
		string alphabet;
		cin >> alphabet;

		cout << "Enter seed for rand: ";
		unsigned int seed;
		cin >> seed;
		srand(seed);

		// Construct two sorted vectors of words
		Timer get;
		get.start();
		list<string> A = getWords(n, wordSize, alphabet);
		list<string> B = getWords(n, wordSize, alphabet);
		get.stop();
		cout << "Constructed in " << get() << " seconds"
			<< endl;

		if (wordSize * n < 60)
		{
			cout << "A is: " << A << endl
				<< "B is: " << B << endl;
		}

		// Report the number of words in the first sorted list
		//   that are not in the second sorted list
		Timer time;
		time.start();
		int count = unmatched(A, B);
		time.stop();
		cout << count
			<< " words in A were not in B" << endl
			<< "calculated in " << time() << " seconds"
			<< endl << endl;
	}

	return 0;
}
