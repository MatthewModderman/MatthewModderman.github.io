//============================================================================
// Name        : HashTable.cpp
// Author      : Matthew Modderman
// Copyright   : Copyright © 2017 SNHU COCE
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string> // atoi
#include <time.h>
#include <vector>

#include "CSVparser.hpp"
#include "GlobalDefinitions.h"

using namespace std;


//============================================================================
// Hash Table class definition
//============================================================================

const unsigned int DEFAULT_SIZE = 179;

/* Define a class containing data members and methods to
 * implement a hash table with chaining */
class HashTable {

private:
	// Private structure in HashTable class to hold bids
	struct hashTableNode {
		Bid bid;
		unsigned key;
		hashTableNode* next;

		//default constructor
		hashTableNode() {
			key = UINT_MAX;
			next = nullptr;
		}

		//initialize a bid
		hashTableNode(Bid aBid) : hashTableNode() {
			bid = aBid;
		}

		//initialize a bid and a key
		hashTableNode(Bid aBid, unsigned aKey) : hashTableNode(aBid) {
			key = aKey;
		}
	};

	vector<hashTableNode> nodes;
	unsigned tableSize = DEFAULT_SIZE;

public:
	//public methods for HashTable class
	HashTable();
	HashTable(unsigned size);
	unsigned int hash(unsigned key);
	virtual ~HashTable();
	void Insert(Bid bid);
	void PrintAll();
	void Remove(string bidId);
	Bid Search(string bidId);

};

/* Default Constructor*/
HashTable::HashTable() {
	// Resize HashTable to size of tableSize if no argument given
	nodes.resize(tableSize);
}

/*constructor*/
HashTable::HashTable(unsigned size) {
	//Resize HashTable to given size if argument given
	this->tableSize = size;
	nodes.resize(tableSize);
}

/*Destructor*/
HashTable::~HashTable() {
	//Erase nodes from the beginning of vector if destructor called
	nodes.erase(nodes.begin());
}

/* Calculate the hash value of a given key.
 * Note that key is specifically defined as
 * unsigned int to prevent undefined results
 * of a negative list index.
 * @param key The key to hash
 * @return The calculated hash */
unsigned int HashTable::hash(unsigned key) {
	// Hash value calculated by argument modulo tableSize
	return key % tableSize;
}

/* Insert a bid
 * @param bid The bid to insert */
void HashTable::Insert(Bid bid) {
	// Calculate key of bid first (hash)
	unsigned key = hash(atoi(bid.bidId.c_str()));

	//try and retrieve node using the key
	hashTableNode* oldNode = &(nodes.at(key));

	//if no entry at node(key)
	if (oldNode == nullptr) {
		hashTableNode* newNode = new hashTableNode(bid, key);
		nodes.insert(nodes.begin() + key, (*newNode));
	} else {
		//node found
		if (oldNode->key == UINT_MAX) {
			oldNode->key = key;
			oldNode->bid = bid;
			oldNode->next = nullptr;
		} else {
			//find the next open node (last one)
			while (oldNode->next != nullptr) {
				oldNode = oldNode->next;
			}
			oldNode->next = new hashTableNode(bid, key);
		}
	}
}

/* Print all bids in HashTable */
int CountRows = 0;
void HashTable::PrintAll() {
	//iterate all nodes from begin to end
	for (auto iter = nodes.begin(); iter != nodes.end(); ++iter) {

		//make sure node key is not unused
		if (iter->key != UINT_MAX) {

			//pointer to the next node
			hashTableNode* curNode = iter->next;

			//if the curNode is not nullptr, print all of the information
			while (curNode != nullptr) {
				cout << "Row number: " << ++CountRows << " | Bid ID: " << curNode->bid.bidId << " | " << curNode->bid.title << " | Bid Amount: ";
				cout << curNode->bid.fund << " | Fund Amount: " << curNode->bid.amount << endl;
				curNode = curNode->next;
			}
		}
	}
}

/* Remove a bid
 * @param bidId The bid id to search for */
void HashTable::Remove(string bidId) {
	//Remove bid based on bid key
	unsigned key = hash(atoi(bidId.c_str()));
	nodes.erase(nodes.begin() + key);
}

/* Search for the specified bidId
 * @param bidId The bid id to search for */
Bid HashTable::Search(string bidId) {
	// Implement logic to search for and return a bid
	Bid bid;

	//calculate the key for the bid
	unsigned key = hash(atoi(bidId.c_str()));

	//try to retrieve node using the key
	hashTableNode* node = &(nodes.at(key));

	//if no entry found
	if (node == nullptr || node->key == UINT_MAX) {
		return bid;
	}

	//if node found matches key
	while (node != nullptr) {
		if (node->key != UINT_MAX && node->bid.bidId.compare(bidId) == 0) {
			return node->bid;
		}
		//walk the list to find a match
		node = node->next;
	}
	return bid;
}



/*Load a CSV file containing bids into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read*/
void loadBids(string csvPath, HashTable* hashTable) {

	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);
	cout << file.rowCount() << " rows to load." << endl;
	cout << "Rows being placed in hash table while loading." << endl;

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
			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			cout << "Row number: " << countRows << " Bid ID: " << bid.bidId << " " << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			hashTable->Insert(bid);
		}

		cout << endl << countRows << " rows loaded into hash table" << endl;

	} catch (csv::Error & e) {
		std::cerr << e.what() << std::endl;
	}
}



