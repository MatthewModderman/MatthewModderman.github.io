#include <algorithm>
#include <climits>
#include <iostream>
#include <string>
#include <time.h>
#include <vector>

#include "GlobalDefinitions.h"
#include "CSVparser.hpp"
#include "BinarySearchTree.h"
#include "HashTable.h"		
#include "LinkedList.h"
#include "VectorSorting.h"

using namespace std;

int main() {

	/*Project Introduction*/
	opener();
	bool continueThisProgram = 1;

	do {

		/*Algorithm, csvPath, manipulations, bidkey, and time variable initialization*/
		int algorithmChoice = 0; 
		while (algorithmChoice > 5 || algorithmChoice < 1) {
			algorithmChoice = chooseAlgorithm();
		}

		string csvPath = "eBid_Monthly_Sales_Dec_2016.csv";
		int manipulateBids = 0;
		string bidKey;
		clock_t ticks;

		//============================================================================
		// First Choice was Binary Search Tree
		//============================================================================
		if (algorithmChoice == 1) {
			BinarySearchTree* bst = new BinarySearchTree();
			Bid bid;

			/*Load Bids and show timer*/
			ticks = startTimer();	//Initialize a timer variable before
			loadBids(csvPath, bst);
			endTimer(ticks);		//End a timer after 

			while (manipulateBids != 9) {

				manipulateBids = chooseBidManipulation();

				switch (manipulateBids) {

				case 1:
					/*Display all bids and timer*/
					ticks = startTimer();
					bst->InOrder();
					endTimer(ticks);
					break;

				case 2:
					/*Find bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bst->Search(bidKey);

					if (!bid.bidId.empty()) {
						displayBid(bid);
					} else {
						cout << "Bid Id " << bidKey << " not found." << endl;
					}
					endTimer(ticks);
					break;

				case 3:
					/*Remove bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bst->Search(bidKey);

					if (!bid.bidId.empty()) {
						bst->Remove(bidKey);
						cout << "Bid ID " << bidKey << ": " << bid.title << " was removed." << endl;
					} else {

						cout << "Bid ID " << bidKey << " does not exist." << endl;
					}

					endTimer(ticks);
					break;

				case 9:
					break;
				}
			}

			delete bst;
		} 
		
		//============================================================================
		// Second Choice was Hash Table
		//============================================================================

		else if (algorithmChoice == 2) {
			HashTable* bidTable = new HashTable();
			Bid bid;

			/*Load Bids and show timer*/
			ticks = startTimer();
			loadBids(csvPath, bidTable);
			endTimer(ticks);

			while (manipulateBids != 9) {

				manipulateBids = chooseBidManipulation();

				switch (manipulateBids) {

				case 1:
					/*Display all bids and timer*/
					ticks = startTimer();
					bidTable->PrintAll();
					endTimer(ticks);
					break;

				case 2:
					/*Find bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bidTable->Search(bidKey);

					if (!bid.bidId.empty()) {
						displayBid(bid);
					} else {
						cout << "Bid Id " << bidKey << " not found." << endl;
					}

					endTimer(ticks);
					break;

				case 3:
					/*Remove bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bidTable->Search(bidKey);

					if (!bid.bidId.empty()) {
						bidTable->Remove(bidKey);
						cout << "Bid ID " << bidKey << ": " << bid.title << " was removed." << endl;
					} else {
						cout << "Bid ID " << bidKey << " does not exist." << endl;
					}

					endTimer(ticks);
					break;

				case 9:
					break;
				}
			}

			delete bidTable;

		} 
		
		//============================================================================
		// Third Choice was Linked List
		//============================================================================

		else if (algorithmChoice == 3) {
			LinkedList* bidList = new LinkedList();
			Bid bid;

			/*Load Bids and show timer*/
			ticks = startTimer();
			loadBids(csvPath, bidList);
			endTimer(ticks);

			while (manipulateBids != 9) {
				cout << "Menu:" << endl;
				cout << "  1. Enter a Bid" << endl;
				cout << "  2. Display All Bids" << endl;
				cout << "  3. Find Bid" << endl;
				cout << "  4. Remove Bid" << endl;
				cout << "  5. Prepend Bid" << endl;
				cout << "  9. Exit" << endl;
				cout << "Enter choice: ";

				while (!(cin >> manipulateBids)) {
					cout << endl;
					cout << "Please enter an integer: ";
					cin.clear();
					cin.ignore(123, '\n');
				}

				switch (manipulateBids) {
				case 1:
					/*Append bid and show timer*/
					bid = getBid();
					ticks = startTimer();
					bidList->Append(bid);
					displayBid(bid);
					endTimer(ticks);
					break;

				case 2:
					/*Display all bids and timer*/
					ticks = startTimer();
					bidList->PrintList();
					endTimer(ticks);
					break;

				case 3:
					/*Find bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bidList->Search(bidKey);

					if (!bid.bidId.empty()) {
						displayBid(bid);
					} else {
						cout << "Bid Id " << bidKey << " not found." << endl;
					}

					endTimer(ticks);
					break;

				case 4:
					/*Remove bid and show timer*/
					bidKey = chooseBidKey();
					ticks = startTimer();
					bid = bidList->Search(bidKey);

					if (!bid.bidId.empty()) {
						bidList->Remove(bidKey);
						cout << "Bid ID " << bidKey << ": " << bid.title << " was removed." << endl;
					} else {
						cout << "Bid ID " << bidKey << " does not exist." << endl;
					}

					endTimer(ticks);
					break;

				case 5:
					/*Prepend bid and show timer*/
					bid = getBid();
					ticks = startTimer();
					bidList->Prepend(bid);
					displayBid(bid);
					endTimer(ticks);
					break;

				case 9:
					break;
				}
			}

			delete bidList;

		} 
		
		//============================================================================
		// Fourth Choice was Vector Sorting
		//============================================================================
		
		else if (algorithmChoice == 4) {
			vector<Bid> bids;

			/*Load Bids and show timer*/
			ticks = startTimer();
			bids = loadBids(csvPath);
			endTimer(ticks);

			while (manipulateBids != 9) {
				cout << "Menu:" << endl;
				cout << "  1. Display All Bids" << endl;
				cout << "  2. Selection Sort All Bids" << endl;
				cout << "  3. Quick Sort All Bids" << endl;
				cout << "  9. Exit" << endl;
				cout << "Enter choice: ";

				while (!(cin >> manipulateBids)) {
					cout << endl;
					cout << "Please enter an integer: ";
					cin.clear();
					cin.ignore(123, '\n');
				}

				switch (manipulateBids) {
				case 1:
					/*Display all bids and timer*/
					ticks = startTimer();
					for (unsigned int i = 0; i < bids.size(); ++i) {
						displayBid(bids[i]);
					} cout << endl;
					endTimer(ticks);
					break;
				case 2:
					/*Display selection sort all bids and timer*/
					ticks = startTimer();
					selectionSort(bids);
					cout << bids.size() << " bids read" << endl;
					endTimer(ticks);
					break;
				case 3:
					/*Display quick sort all bids and timer*/
					ticks = startTimer();
					quickSort(bids, 0, bids.size() - 1);
					cout << bids.size() << " bids read" << endl;
					endTimer(ticks);
					break;
				}
			}

		} 

		//============================================================================
		// Fifth Choices Breaks From Switch to check to Continue Program
		//============================================================================
		else if (algorithmChoice == 5) {
			continueThisProgram = continueProgram();
		}

	} while (continueThisProgram); // Check if exiting or continuing program
}