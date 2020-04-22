#ifndef     _GLOBALDEFINITION_H_
#define     _GLOBALDEFINITION_H_

#include <string> 
#include <time.h>

using namespace std;

//============================================================================
// Forward Declation of Objects and Functions
//============================================================================

void opener();
int chooseAlgorithm();
string chooseBidKey();
int chooseBidManipulation();
bool continueProgram();

struct Bid;
Bid getBid();
void displayBid(Bid bid);
double strToDouble(string str, char ch);

clock_t startTimer();
void endTimer(clock_t starterTime);

//============================================================================
// Global definitions visible to all methods and classes
//============================================================================


void opener() {
	cout << " * The following is a collection of different data structures to hold and manipulate information." << endl;
	cout << " * The purpose of this exercise is to showcase the timing and capabilities of common structures." << endl;
	cout << " * Included in this activity are examples of a binary search tress, hash table, linked list, and vector sorting." << endl;
	cout << " * Please feel free to examine the contents of the files to better understand the development." << endl << endl;
}

/*Used to chose algorithm*/
int chooseAlgorithm() {
	int algorithmChoice;
	cout << "Select Algorithm Type:" << endl;
	cout << "  1. Binary Search Tree" << endl;
	cout << "  2. Hash Table" << endl;
	cout << "  3. Linked List" << endl;
	cout << "  4. Vector Sorting" << endl;
	cout << "  5. Go to Exit Screen" << endl;
	cout << "Enter choice: ";

	while (!(cin >> algorithmChoice)) {
		cout << endl;
		cout << "Please enter an integer from 1 to 5: ";
		cin.clear();
		cin.ignore(123, '\n');
	}

	cout << endl;

	return algorithmChoice;
}

/*Used to choose bid key*/
string chooseBidKey() {
	unsigned int userChoice;
	string selectedBidKey;

	cout << "Chose from the following:" << endl;
	cout << "1. Enter specific bid key" << endl;
	cout << "2. Use default bid key" << endl;
	cout << "Enter choice: ";	

	while (!(cin >> userChoice)) {
		cout << "Please enter an integer: ";
		cin.clear();
		cin.ignore(123, '\n');
	}

	cout << endl;

	if (userChoice == 1 || userChoice == 2) {
		switch (userChoice) {
		case 1:
			cout << "Enter specific bid key: ";
			cin >> selectedBidKey;
			return selectedBidKey;
			break;
		case 2:
			selectedBidKey = "98109";
			return selectedBidKey;
			break;
		}
	} else {
		cout << "That was not an acceptable answer." << endl;
		return chooseBidKey();
	}

}

/*Prompt used for two of the algorithms*/
int chooseBidManipulation() {
	unsigned int choice;

	cout << "Menu:" << endl;
	cout << "  1. Display All Bids" << endl;
	cout << "  2. Find Bid" << endl;
	cout << "  3. Remove Bid" << endl;
	cout << "  9. Exit" << endl;
	cout << "Enter choice: ";

	while (!(cin >> choice)) {
		cout << endl;
		cout << "Please enter an integer: ";
		cin.clear();
		cin.ignore(123, '\n');
	}

	return choice;

}

/*Used to check if the program will continue of close*/
bool continueProgram() {								
	char chooseToContinue;

	cout << "Please enter C to continue of Q to quit: ";

	while (!(cin >> chooseToContinue)) {
		cout << endl;
		cout << "Please enter C or Q ";
		cin.clear();
		cin.ignore(123, '\n');
	}

	if (chooseToContinue == 'c' || chooseToContinue == 'C') {
		return 1;
	} else if (chooseToContinue == 'q' || chooseToContinue == 'C') {
		return 0;
	} else {
		cout << "That was not an acceptable answer" << endl << endl;
		cin.clear(); // Clear error flags
		cin.ignore(numeric_limits<streamsize>::max(), '\n'); // Clear out the input buffer
		return continueProgram();
	}
} 

//============================================================================
// Bid Structure and Related Functions
//============================================================================

/*Define a structure to hold bid information*/
struct Bid {
	string bidId;
	string title;
	string fund;
	double amount = 0.0;
	Bid() {
		amount = 0.0;
	}
};


/*Used to check bid id*/
string checkIsInt() {
	cin.ignore();
	string bidTitle;
	cin >> bidTitle;
	for (int i = 0; i < bidTitle.length(); i++) {
		if (isdigit(bidTitle[i]) == false) {
			cout << "Must be an integer: ";
			return checkIsInt();
		}
	} return bidTitle;
}

/*Prompt to received bid information*/
Bid getBid() {
	Bid bid;

	cout << "Enter Id: ";
	bid.bidId = checkIsInt();

	cin.clear();
	cout << "Enter title: ";
	cin >> bid.title;

	cout << "Enter fund: ";
	bid.fund = checkIsInt();

	cout << "Enter amount: ";
	cin.ignore();
	string strAmount;
	cin >> strAmount;
	bid.amount = strToDouble(strAmount, '$');

	return bid;
}

/*Display the bid information to the console*/
void displayBid(Bid bid) {
	cout << "Bid ID " << bid.bidId << ": " << bid.title << " | Bid Amount: " << bid.amount << " | Bid Fund: "
		<< bid.fund << endl;
	return;
}

/*Simple C function to convert a string to a double
 * after stripping out unwanted char
 * credit: http://stackoverflow.com/a/24875936 */
double strToDouble(string str, char ch) {
	str.erase(remove(str.begin(), str.end(), ch), str.end());
	return atof(str.c_str());
}

//============================================================================
// Timer Functions
//============================================================================

/*Set timer to check speed of algorithms*/
clock_t startTimer() {
	clock_t startTime = clock();
	return startTime;
}

/*Check and print timer after process to check speed of algorithms*/
void endTimer(clock_t starterTime) {
	clock_t ticks = clock() - starterTime;
	cout << endl << "time: " << ticks << " clock ticks" << endl;
	cout << "time: " << ticks * 1.0 / CLOCKS_PER_SEC << " seconds" << endl << endl;
}

#endif  _GLOBALDEFINITION_H_



