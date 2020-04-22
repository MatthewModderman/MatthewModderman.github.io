//============================================================================
// Name        : BinarySearchTree.cpp
// Author      : Matthew Modderman
// Copyright   : Copyright © 2017 SNHU COCE
// Description : Hello World in C++, Ansi-style
//============================================================================

#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "CSVparser.hpp"
#include "GlobalDefinitions.h"

using namespace std;

// Internal structure for tree node
struct binaryNode {
	Bid bid;
	binaryNode* left;
	binaryNode* right;

	//default Node constructor
	binaryNode() {
		left = nullptr;
		right = nullptr;
	}

	//initialize Node constructor with bid as argument
	binaryNode(Bid aBid) :binaryNode() {
		this->bid = aBid;
	}
};

//============================================================================
// Binary Search Tree class definition
//============================================================================

/* Define a class containing data members and methods to
 * implement a binary search tree */
class BinarySearchTree {

private:
	void addNode(binaryNode* node, Bid bid);
	void inOrder(binaryNode* node);

	binaryNode* removeNode(binaryNode* node, string bidId);

public:
	BinarySearchTree();
	virtual ~BinarySearchTree();
	void InOrder();
	void Insert(Bid bid);
	void Remove(string bidId);
	Bid Search(string bidId);

	binaryNode* root;
};

unsigned int sampleSize = 20000;


/*constructor*/
BinarySearchTree::BinarySearchTree() {
	// initialize housekeeping variables
	root = nullptr;
}

/*Destructor*/
BinarySearchTree::~BinarySearchTree() {
	// recurse from root deleting every node
}

/* Traverse the tree in order */
void BinarySearchTree::InOrder() {
	this->inOrder(root);
}
/* Insert a bid
 * @param bid The bid to insert */
void BinarySearchTree::Insert(Bid bid) {

	if (root == nullptr) {
		root = new binaryNode(bid);
	} else {
		this->addNode(root, bid);
	}
}

/*Remove a bid
 *@param bidId The bid id to search for */
void BinarySearchTree::Remove(string bidId) {

	this->removeNode(root, bidId);
}

binaryNode* BinarySearchTree::removeNode(binaryNode* node, string bidId) {
	bool found = 0;
	//if node is null, return to avoid crashing
	if (node == nullptr) {
		return node;
	}
	//recurse down to the left
	if (node->bid.bidId.compare(bidId) > 0) {
		node->left = removeNode(node->left, bidId);
	}
	//recurse down to the right
	else if (node->bid.bidId.compare(bidId) < 0) {
		node->right = removeNode(node->right, bidId);
	}
	//bidId found to remove
	else {
		found = 1;
		//no children
		if (node->left == nullptr && node->right == nullptr) {
			delete node;
			node = nullptr;
		}
		//child to left
		else if (node->left != nullptr && node->right == nullptr) {
			binaryNode* temp = node;
			node = node->left;
			delete temp;
		}
		//child to right
		else if (node->left == nullptr && node->right != nullptr) {
			binaryNode* temp = node;
			node = node->right;
			delete temp;
		}
		//child to left and right
		else {
			binaryNode* temp = node->right;
			while (temp->left != nullptr) {
				temp = temp->left;
			}
			node->bid = temp->bid;
			node->right = removeNode(node->right, temp->bid.bidId);
		}
	}

	return node;
}

/*Search for a bid*/
Bid BinarySearchTree::Search(string bidId) {
	//initialize current pointer to root for search
	binaryNode* current = root;

	//loop until search is found or bottom of tree
	while (current != nullptr) {
		//if the bidId matched, return bid
		if (current->bid.bidId.compare(bidId) == 0) {
			return current->bid;
		}
		//if argument is less than current bidId, traverse left
		else if (current->bid.bidId.compare(bidId) > 0) {
			current = current->left;
		}
		//if argument is more than current bidId, traverse right
		else if (current->bid.bidId.compare(bidId) < 0) {
			current = current->right;
		}
	}

	Bid bid;
	return bid;
}

/*Add a bid to some node (recursive)*/
void BinarySearchTree::addNode(binaryNode* node, Bid bid) {
	//check to see if it is less than current node; add to left subtree
	if (node->bid.bidId.compare(bid.bidId) > 0) {
		if (node->left == nullptr) {
			node->left = new binaryNode(bid);
		} else {
			this->addNode(node->left, bid);
		}
	}
	//add Node to right subtree
	else {
		if (node->right == nullptr) {
			node->right = new binaryNode(bid);
		} else {
			this->addNode(node->right, bid);
		}
	}
}

int countRows = 0;
void BinarySearchTree::inOrder(binaryNode* node) {
	//in order traversal algorithm
	if (node != nullptr) {
		inOrder(node->left);

		cout << "Row number: " << ++countRows << " | Bid ID: " << node->bid.bidId << " | " << node->bid.title << " | Bid Amount: ";
		cout << node->bid.amount << " | Fund Amount: " << node->bid.fund << endl;
		inOrder(node->right);
	}
}





/*Load a CSV file containing bids into a container
 * @param csvPath the path to the CSV file to load
 * @return a container holding all the bids read*/
void loadBids(string csvPath, BinarySearchTree* bst) {

	cout << "Loading CSV file " << csvPath << endl;

	// initialize the CSV Parser using the given path
	csv::Parser file = csv::Parser(csvPath);
	cout << sampleSize << " rows to load." << endl;
	cout << "Rows being placed in binary tree while loading." << endl;

	// read and display header row
	vector<string> header = file.getHeader();
	for (auto const& c : header) {
		cout << c << " | ";
	}
	cout << "" << endl;
	int countRows = 0;
	try {
		// loop to read rows of a CSV file
		for (unsigned int i = 0; i < sampleSize; i++) {
			countRows++;
			// Create a data structure and add to the collection of bids
			Bid bid;
			bid.bidId = file[i][1];
			bid.title = file[i][0];
			bid.fund = file[i][8];
			bid.amount = strToDouble(file[i][4], '$');

			cout << "Row number: " << countRows << " Bid ID: " << bid.bidId << " " << "Item: " << bid.title << ", Fund: " << bid.fund << ", Amount: " << bid.amount << endl;

			// push this bid to the end
			bst->Insert(bid);
		}

		cout << endl << countRows << " rows loaded into binary search tree" << endl;

	} catch (csv::Error & e) {
		std::cerr << e.what() << std::endl;
	}

}
