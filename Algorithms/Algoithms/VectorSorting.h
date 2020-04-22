//============================================================================
// Name        : VectorSorting.cpp
// Author      : Matthew Modderman
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"
#include "GlobalDefinitions.h"

using namespace std;

/* Load a CSV file containing bids into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read*/
vector<Bid> loadBids(string csvPath) {
	cout << "Loading CSV file " << csvPath << endl;

	// Define a vector data structure to hold a collection of bids.
	vector<Bid> bids;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);
	cout << file.rowCount() << " rows to load." << endl;
	cout << "Rows being placed in vector while loading." << endl;

	// read and display header row
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;
	int countRows = 0;
	try {
		// loop to read rows of a CSV file
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {
			countRows++;

			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			cout << "Row number: " << countRows << " Bid ID: " << bid.bidId << " " << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bids.push_back(bid);
		}

		cout << endl << countRows << " rows loaded into vector" << endl;

	} catch (csv::Error & e) {
		std::cerr << e.what() << std::endl;
	}
	return bids;
}

/* Partition the vector of bids into two parts, low and high
 * @param bids Address of the vector<Bid> instance to be partitioned
 * @param begin Beginning index to partition
 * @param end Ending index to partition*/
int partition(vector<Bid>& bids, int begin, int end) {
	int low = begin;
	int high = end;

	//pick the middle element as the pivot point
	int pivot = (begin + (end - begin)) / 2;

	bool done = false;
	while (!done) {

		//keep incrementing low if it is less than pivot
		while (bids.at(low).title.compare(bids.at(pivot).title) < 0) {
			++low;
		}

		//keep decrementing high if it is more than pivot
		while (bids.at(high).title.compare(bids.at(pivot).title) > 0) {
			--high;
		}

		// if there are 0 or 1 items remaining, return high
		if (low >= high) {
			done = true;
		} else {
			//swap (entire) bids at low and high positions
			swap(bids.at(low), bids.at(high));
			++low;
			--high;
		}
	}

	return high;
}

/* Perform a quick sort on bid title
 * @param bids address of the vector<Bid> instance to be sorted
 * @param begin the beginning index to sort on
 * @param end the ending index to sort on */
void quickSort(vector<Bid>& bids, int begin, int end) {
	//initialize midpoint
	int mid = 0;

	//If there are zero or one bids, then done
	if (begin >= end) {
		return;
	}

	//partition bids into low and high parts
	mid = partition(bids, begin, end);

	//recursively call quickSort using midpoint value as divider
	quickSort(bids, begin, mid);
	quickSort(bids, mid + 1, end);

}

/* Perform a selection sort on bid title
 * @param bid address of the vector<Bid>*/
void selectionSort(vector<Bid>& bids) {
	unsigned min;

	//outer loop to scroll through
	for (unsigned i = 0; i < bids.size(); ++i) {
		min = i;

		//inner loop to compare j and i
		for (unsigned j = i + 1; j < bids.size(); ++j) {
			if (bids.at(j).title.compare(bids.at(min).title) < 0) {
				min = j;
			}
		}

		//swap j and i if j < i
		if (min != i) {
			swap(bids.at(i), bids.at(min));
		}
	}
}

