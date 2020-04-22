//============================================================================
// Name        : LinkedList.cpp
// Author      : Matthew Modderman
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <iostream>
#include <time.h>

#include "CSVparser.hpp"
#include "GlobalDefinitions.h"

using namespace std;

//============================================================================
// Linked-List class definition
//============================================================================

/*Define a class containing data members and methods to
 * implement a linked-list.*/
class LinkedList {

private:
	// Initialize structure for entries
	struct listNode {
		Bid bid;
		listNode* next;
		//Default Constructor
		listNode() {
			next = nullptr;
		}
		//Initialize listNode with bid
		listNode(Bid aBid) {
			bid = aBid;
			next = nullptr;
		}
	};

	//Initialize pointers for listNode head & tail. Initialize variable for size.
	listNode* head;
	listNode* tail;
	int size = 0;

public:
	LinkedList();
	virtual ~LinkedList();
	void Append(Bid bid);
	void Prepend(Bid bid);
	void PrintList();
	void Remove(string bidId);
	Bid Search(string bidId);
	int Size();
};


// Default constructor

LinkedList::LinkedList() {
	// Initialize values for head and tail pointers.
	head = nullptr;
	tail = nullptr;
}


// Destructor that was never used

LinkedList::~LinkedList() {
}

//Append a new bid to the end of the list

void LinkedList::Append(Bid bid) {
	// Append entry to end of linked list
	listNode* node = new listNode(bid);

	if (head == nullptr) {
		head = node;
	} else {
		if (tail != nullptr) {
			tail->next = node;
		}
	}

	//change tail and increase size count
	tail = node;
	size++;

}

//Prepend a new bid to the start of the list

void LinkedList::Prepend(Bid bid) {
	// Prepend entry to beginning of linked list
	listNode* node = new  listNode(bid);

	if (head != nullptr) {
		node->next = head;
		head = node;
	} else {
		head = node;
		tail = node;
	}

	//Increase size after prepend
	size++;

}


//Simple output of all bids in the list

void LinkedList::PrintList() {
	// Print id, title, fund, amount of entries from head to tail
	listNode* curNode = head;
	int countRows = 0;
	while (curNode != nullptr) {
		cout << "Row number: " << ++countRows << " | Bid ID: " << curNode->bid.bidId << " " << " | " << curNode->bid.title << " | Bid Amount: ";
		cout << curNode->bid.amount << " | Fund Amount: " << curNode->bid.fund << endl;
		curNode = curNode->next;
	}
}


//Remove a specified bid

void LinkedList::Remove(string bidId) {
	// Find and remove entry in linked list based on bidId

	// delete the head note if it is a match
	if (head != nullptr) {
		if (head->bid.bidId.compare(bidId) == 0) {
			listNode* tempNode = head->next;
			delete head;
			head = tempNode;
			//Decrement for each entry removed
			size--;
		}
	}

	listNode* curNode = head;


	// delete node that is a match that is not the head listNode
	while (curNode->next != nullptr) {
		if (curNode->next->bid.bidId.compare(bidId) == 0) {
			//save next listNode (the one that is going to be removed)
			listNode* tempNode = curNode->next;

			//make the curNode point beyond the next listNode (the one being removed)
			curNode->next = tempNode->next;

			//delete listNode that matched
			delete tempNode;

			//reduce size count
			size--;

		}
		curNode = curNode->next;
	}
}

// Search for the specified bidId

Bid LinkedList::Search(string bidId) {
	// return location of listNode in linked list that matches argument
	listNode* curNode = head;

	while (curNode != nullptr) {
		if (curNode->bid.bidId.compare(bidId) == 0) {
			return curNode->bid;
		}
		curNode = curNode->next;
	}
}

// Return the current size (number of elements) in the list
int LinkedList::Size() {
	return size;
}


// Load a CSV file containing bids into a LinkedList
void loadBids(string csvPath, LinkedList* list) {

	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);
	cout << file.rowCount() << " rows to load." << endl;
	cout << "Rows being placed in linked list while loaded." << endl;

	// read and display header row
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;
	int countRows = 0;
	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < file.rowCount(); i++) {
			countRows++;

			// initialize a bid using data from current row (i)
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			cout << "Row number: " << countRows << " Bid ID: " << bid.bidId << " " << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// add this bid to the end
			list->Append(bid);
		}

		cout << endl << countRows << " rows loaded into linked list" << endl;

	} catch (csv::Error & e) {
		std::cerr << e.what() << std::endl;
	}
}
