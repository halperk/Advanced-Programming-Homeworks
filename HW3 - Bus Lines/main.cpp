/*******************************************

CS 204 (Fall 2021-2022)
Homework #3 - Bus Lines
Huseyin Alper Karadeniz (28029)
Date: 11/17/2021

********************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct busStop { /*Defines a struct to store the bus stop data in a doubly linked list.*/
	string busStopName; /*Saves the name of the bus stop.*/
	busStop* left; /*Saves the address of the previous bus stop.*/
	busStop* right; /*Saves the address of the next bus stop.*/
	
	busStop::busStop() {}
};

struct busLine { /*Defines a struct to store the bus line data in a singly linked list.*/
	string busLineName; /*Saves the name of the bus line.*/
	busLine* next; /*Saves the address of the next bus line in the list.*/
	busStop* busStops; /*Saves the address of the first bus stop in the bus line.*/
	
	busLine::busLine() {}
};

busLine* head = nullptr; /*Defines the head pointer as a global variable.*/

void printMainMenu() { /*Displays the main menu.*/
	cout << endl
	<< "I***********************************************I" << endl
	<< "I 0 - EXIT PROGRAM I" << endl
	<< "I 1 - PRINT LINES I" << endl
	<< "I 2 - ADD BUS LINE I" << endl
	<< "I 3 - ADD BUS STOP I" << endl
	<< "I 4 - DELETE BUS LINE I" << endl
	<< "I 5 - DELETE BUS STOP I" << endl
	<< "I 6 - PATH FINDER I" << endl
	<< "I***********************************************I" << endl
	<< ">>" << endl;
}

bool consistencyCheck() { /*Checks if there is any inconsistencies in the lists.*/
	busLine* currentBusLine = head;
	while(currentBusLine != NULL) { /*Visits bus lines.*/
		busStop* currentBusStop = currentBusLine->busStops;
		while(currentBusStop != NULL) { /*Visits bus stops inside of a bus line.*/
			busStop* rightBusStop = currentBusStop->right;
			if(rightBusStop && rightBusStop->left != currentBusStop) { /*Checks the node for inconsistencies.*/
				cout << "Inconsistency for " << currentBusLine->busLineName << " " << currentBusStop->busStopName << endl;
				return false; /*Returns false if there is inconsistencies.*/
			}
			currentBusStop = currentBusStop->right;
		}
		currentBusLine = currentBusLine->next;
	}
	return true; /*Returns true if there is no inconsistencies.*/
}

bool busLineExistence(string busLineName) { /*Finds if the bus line exists in the linked list.*/
	busLine* ptr = head; /*Starts from the head of bus lines.*/
	while(ptr != NULL) { /*Visits all bus lines one by one.*/
		if((ptr->busLineName) == busLineName) {
			return true; /*If the bus line name exists, returns true.*/
		}
		ptr = ptr->next;
	}
	return false; /*If the bus line name does not exist, returns false.*/
}

bool busStopExistence(string busStopName) { /*Finds if a bus stop exists in anywhere of the whole list.*/
	busLine* ptr = head; /*Starts from the head of bus lines.*/
	while(ptr != NULL) { /*Visits all bus lines one by one.*/
		busStop* ptr2 = ptr->busStops; /*Starts from the beginning of each bus line bus stops.*/
		while(ptr2 != NULL) { /*Visits all bus stops in a bus line one by one.*/
			if((ptr2->busStopName) == busStopName) {
				return true; /*If the bus stop name exists, returns true.*/
			}
			ptr2 = ptr2->right;
		}
		ptr = ptr->next;
	}
	return false; /*If the bus stop name does not exist, returns false.*/
}

void printBusLines() { /*Prints all bus lines with their bus stops.*/
	busLine* currentBusLine = head;
	while(currentBusLine != NULL) { /*Visits all bus lines one by one.*/
		cout << currentBusLine->busLineName << ": ";
		busStop* currentBusStop = currentBusLine->busStops;
		int stopCounter = 0; /*Counts bus stops to display the first bus stop different.*/
		while(currentBusStop != NULL) { /*Visits and displays bus stops one by one.*/
			if(stopCounter > 0) { /*Prints the bus stops other than the first one.*/
				cout << " <-> " << currentBusStop->busStopName;
			} else { /*Prints the first bus stop.*/
				cout << currentBusStop->busStopName;
			}
			currentBusStop = currentBusStop->right;
			stopCounter++;
		}
		currentBusLine = currentBusLine->next;
		cout << endl;
	}
}

void addBusLine() { /*Creates a bus line with bus stops and adds it to the linked list.*/
	/*Gets the name of the bus line from the user.*/
	string busLineName;
	cout << "Enter the name of the new bus line (0 for exit to main menu)." << endl;
	cin >> busLineName; /*Gets the name of the bus line.*/
	if(busLineName == "0") {return;} /*Returns to the main menu.*/
	while(busLineExistence(busLineName)) { /*Checks if the bus line name is already exists.*/
		cout << "Bus line already exists: enter a new one (0 for exit)" << endl;
		cin >> busLineName; /*Gets a new bus line name if it exists.*/
		if(busLineName == "0") {return;} /*Returns to the main menu.*/
	}
	/*Gets the bus stop names to be saved into the bus line.*/
	string busStopName;
	vector<string> busStopNames;
	cout <<	"Enter the name of the next bus stop (enter 0 to complete)" << endl;
	cin >> busStopName; /*Gets the name of the first bus stop.*/
	if(busStopName == "0") { /*If the user enters 0, then returns to the main menu with a proper message.*/
		cout << "You are not allowed to add an empty bus line" << endl;
		return;
	} else { /*Saves the name of the bus stop into a vector.*/
		busStopNames.push_back(busStopName);
	}
	while(busStopName != "0") { /*Gets all other bus stop names from the user and adds them to the bus stop name vector.*/
		cout << "Enter the name of the next bus stop (enter 0 to complete)" << endl;
		cin >> busStopName; /*Gets the bus stop name.*/
		if(busStopName != "0") { /*Checks if the bus stop name is already exist in the vector.*/
			if(find(busStopNames.begin(), busStopNames.end(), busStopName) != busStopNames.end()) {
				cout << "Bus stop already exists in the line" << endl; /*Gives an error if the bus stop name is already exist in the vector.*/
			} else {
				busStopNames.push_back(busStopName); /*Adds the bus stop name into the vector if it does not exist in the vector yet.*/
			}
		}		
	}
	/*Prints the bus line information to be saved.*/
	cout << "The bus line information is shown below" << endl; 
	cout << busLineName << ": "; /*Prints the name of the bus line.*/
	for(int i = 0; i < busStopNames.size(); i++) {
		if(i == 0) { /*Prints the name of the first bus stop.*/
			cout << busStopNames.at(i);
		} else { /*Prints the names of the bus stops other than the first one.*/
			cout << " <-> " << busStopNames.at(i);
		}
	}
	/*Gets a confirmation from the user to save new bus line to the bus lines linked list.*/
	cout << endl << "Are you sure? Enter (y/Y) for yes (n/N) for no?" << endl;
	string saveConfirmation;
	cin >> saveConfirmation; /*Gets the confirmation info.*/
	if(saveConfirmation == "y" || saveConfirmation == "Y") { /*If the user confirms to save, performs necessary operations.*/
		/*Creates a head for the bus stops.*/
		busStop* headBusStop = new busStop();
		headBusStop->busStopName = busStopNames.at(0);
		headBusStop->left = NULL;
		headBusStop->right = NULL;
		/*Creates other bus stop nodes and connects all of them to each other.*/
		busStop* previousBusStop = headBusStop; /*Defines a bus stop to store previous bus stops.*/
		for(int i = 1; i < busStopNames.size(); i++) { /*Adds the bus stops into the doubly linked list.*/
			/*Creates a bus stop to be added to the linked list.*/
			busStop* newBusStop = new busStop();
			newBusStop->busStopName = busStopNames.at(i);
			newBusStop->left = previousBusStop; /*Connects new bus stop to the previous one.*/
			newBusStop->right = NULL;
			previousBusStop->right = newBusStop; /*Connects previous bus stop to the new one.*/
			previousBusStop = newBusStop; /*Updates previous bus stop for further operations.*/
		}
		/*Creates a bus line node and puts the address of created bus stops inside of it.*/
		busLine* newBusLine = new busLine();
		newBusLine->busLineName = busLineName;
		newBusLine->next = head; /*Connects new bus line to the rest of the linked list.*/
		newBusLine->busStops = headBusStop; /*Connects the bus line with the bus stops.*/
		head = newBusLine; /*Makes new bus line to the head of the linked list.*/
		printBusLines(); /*Prints all the bus lines.*/
	} else if(saveConfirmation == "n" || saveConfirmation == "N") { /*If the user does not confirm, returns to the main menu.*/
		return;
	}
}

void addBusStop() { /*Adds a bus stop inside of a bus line.*/
	/*Gets the name of the bus line from the user and checks its existence in the linked list.*/
	string busLineName;
	cout << "Enter the name of the bus line to insert a new bus stop (0 for main menu)" << endl;
	cin >> busLineName; /*Gets the name of the bus line.*/
	if(busLineName == "0") {return;}
	if(!busLineExistence(busLineName)) { /*Checks if the bus line name already exists and returns the main menu if it does not exist.*/
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
		return;
	}
	/*Finds the bus stops inside of that bus line and both saves them into a vector and prints to the console.*/
	vector<string> busStopsOnTarget; /*Creates a vector to store the names of the bus stops inside of the bus line.*/
	busLine* currentBusLine = head;
	while(currentBusLine != NULL) { /*Visits all bus lines one by one to find the targeted one.*/
		string currentBusLineName = currentBusLine->busLineName;
		if(currentBusLineName == busLineName) { /*When the targeted bus line found, saves its bus stops and prints them.*/
			cout << "The bus line information is shown below" << endl;
			cout << currentBusLineName << ": "; /*Prints the name of the bus line to the console.*/
			busStop* currentBusStop = currentBusLine->busStops;
			int stopCounter = 0; /*Counts bus stops to display the first bus stop different.*/
			while(currentBusStop != NULL) { /*Displays bus stops one by one.*/
				string currentBusStopName = currentBusStop->busStopName;
				busStopsOnTarget.push_back(currentBusStopName); /*Adds the bus stop name to the vector to be used in the upcoming parts.*/
				if(stopCounter > 0) { /*Prints the bus stops other than the first one.*/
					cout << " <-> " << currentBusStopName;
				} else { /*Prints the first bus stop in the list.*/
					cout << currentBusStopName;
				}
				currentBusStop = currentBusStop->right;
				stopCounter++;
			}
			cout << endl;
			break; /*Breaks the while loop when the targeted bus line found and the names of its bus stops are saved in a vector.*/
		}
		currentBusLine = currentBusLine->next;
	}
	/*Gets the name of the new bus stop and adds it into the linked list.*/
	string newBusStopName;
	cout << "Enter the name of the new bus stop" << endl;
	cin >> newBusStopName; /*Gets the name of the new bus stop.*/
	if(find(busStopsOnTarget.begin(), busStopsOnTarget.end(), newBusStopName) != busStopsOnTarget.end()) {
		cout << "Bus stop already exists. Going back to previous menu." << endl;
		return; /*If the name of the bus stop is already exists in the linked list, returns to the main menu.*/
	} else {
		/*Creates a new bus stop node with NULL pointers to be added to the linked list.*/
		busStop* newBusStop = new busStop();
		newBusStop->busStopName = newBusStopName;
		newBusStop->left = NULL;
		newBusStop->right = NULL;
		/*Gets the name of the previous bus stop to add the new one after that node.*/
		string previousStopName;
		cout << "Enter the name of the previous bus stop to put the new one after it (0 to put the new one as the first bus stop)" << endl;
		cin >> previousStopName; /*Gets the previous bus stop's name.*/
		if(previousStopName == "0") { /*Adds the bus stop at the beginning of the list if the user enters 0.*/
			currentBusLine->busStops->left = newBusStop;
			newBusStop->right = currentBusLine->busStops;
			currentBusLine->busStops = newBusStop;
		} else { /*Adds the bus stop at an address other than the first one.*/
			while(!(find(busStopsOnTarget.begin(), busStopsOnTarget.end(), previousStopName) != busStopsOnTarget.end())) {
				cout << "Bus stop does not exist. Typo? Enter again (0 for main menu)" << endl;
				cin >> previousStopName; /*If the given previous bus stop name is not in the list, gets it again.*/
				if(previousStopName == "0") {return;} /*Returns to the main menu.*/
			}
			/*Goes to the correct address to add new node to the list.*/
			busStop* currentBusStop = currentBusLine->busStops;
			while(currentBusStop != NULL) { /*Visits all bus stops one by one.*/
				string currentBusStopName = currentBusStop->busStopName;
				if(currentBusStopName == previousStopName) { /*Finds the address of the targeted bus stop.*/
					if(currentBusStop->right != NULL) { /*If the bus stop is not at the end of the list, performs necessary operations to add accordingly.*/
						newBusStop->right = currentBusStop->right;
						newBusStop->left = currentBusStop;
						currentBusStop->right = newBusStop;
						newBusStop->right->left = newBusStop;
					} else { /*If the bus stop at the end of the doubly linked list, performs operations to add.*/
						currentBusStop->right = newBusStop;
						newBusStop->left = currentBusStop;
					}
				}
				currentBusStop = currentBusStop->right;
			}
			cout << endl;
		}
		printBusLines(); /*Prints the updated bus lines table to the console.*/
	}
}

void deleteBusLineByName(string targetBusLineName) { /*Deletes a bus line from the list by finding it from its name.*/
	busLine* currentBusLine = head; /*Creates a bus line pointer.*/
	if(targetBusLineName == head->busLineName) { /*Deletes if the targeted bus line is the first bus line.*/
		head = head->next;
		busStop* ptrBusStop = currentBusLine->busStops;
		while(ptrBusStop != NULL) { /*Deletes all bus stops inside of the bus line.*/
			busStop* previousBusStop = ptrBusStop;
			ptrBusStop = ptrBusStop->right;
			delete previousBusStop; /*Deletes each bus stop node inside of the bus line one by one.*/
		}
		delete currentBusLine; /*Deletes the bus line node as well.*/
	} else { /*Deltes if the targeted bus line is not the first bus line in the list.*/
		while(currentBusLine->next != NULL) { /*Finds the target bus line to be deleted.*/
			if(targetBusLineName == currentBusLine->next->busLineName) {
				break; /*Exits from the while loop when the target bus line found.*/
			}
			currentBusLine = currentBusLine->next;
		}
		if(currentBusLine->next->next != NULL) { /*Checks if targeted bus line node is the last bus line.*/
			busLine* deletionBusLine = currentBusLine->next;
			currentBusLine->next = currentBusLine->next->next; /*Updates the next node of the previous bus line.*/
			busStop* ptrBusStop = deletionBusLine->busStops;
			while(ptrBusStop != NULL) { /*Deletes all bus stops inside of the bus line.*/
				busStop* previousBusStop = ptrBusStop;
				ptrBusStop = ptrBusStop->right;
				delete previousBusStop; /*Deletes each bus stop node inside of the bus line one by one.*/
			}
			delete deletionBusLine; /*Deletes the bus line node as well.*/
		} else { /*If it is the last bus line, performs necessary operation for deletion.*/
			busStop* ptrBusStop = currentBusLine->next->busStops;
			while(ptrBusStop != NULL) { /*Deletes all bus stops inside of the bus line.*/
				busStop* previousBusStop = ptrBusStop;
				ptrBusStop = ptrBusStop->right;
				delete previousBusStop; /*Deletes each bus stop node inside of the bus line one by one.*/
			}
			delete currentBusLine->next; /*Deletes the bus line node as well.*/
			currentBusLine->next = NULL; /*Updates the next node of the previous bus line as NULL pointer.*/
		}
	}
}

void deleteBusLine() { /*Deletes the bus line taken taken as user input.*/
	string targetBusLineName;
	cout << "Enter the name of the bus line to delete" << endl;
	cin >> targetBusLineName; /*Gets the name of the bus line to be deleted.*/
	if(!busLineExistence(targetBusLineName)) { /*Checks if the bus line exists in the linked list.*/
		cout << "Bus line cannot be found. Going back to the previous (main) menu." << endl;
		return; /*Returns to the main menu if the given bus line is not in the linked list.*/
	}
	deleteBusLineByName(targetBusLineName); /*Deletes the bus line from its name.*/
	cout << endl;
	printBusLines(); /*Prints the updated bus lines table to the console.*/

}

void deleteBusStop() { /*Deletes the bus stop inside of a bus line taken as user input.*/
	string busLineName;
	cout << "Enter the name of the bus line to delete a new bus stop (0 for main menu)" << endl;
	cin >> busLineName; /*Gets the name of the bus line.*/
	if(busLineName == "0") {return;}
	if(!busLineExistence(busLineName)) { // Checks if the bus line name already exists.
		cout << "Bus line cannot be found. Going back to previous menu." << endl;
		return; /*Returns to the main menu if the bus line name does not exist in the linked list.*/
	}
	/*Prints the bus stops in the bus line and saves them into a vector to be used in the upcoming parts.*/
	vector<string> busStopsOnTarget;
	busLine* currentBusLine = head;
	while(currentBusLine != NULL) { /*Visits all bus lines one by one.*/
		string currentBusLineName = currentBusLine->busLineName;
		if(currentBusLineName == busLineName) { /*When it finds the targeted bus line, performs operations.*/
			cout << "The bus line information is shown below" << endl;
			cout << currentBusLineName << ": "; /*Displays the bus line name.*/
			busStop* currentBusStop = currentBusLine->busStops;
			int stopCounter = 0; /*Counts bus stops to display the first bus stop different.*/
			while(currentBusStop != NULL) { /*Displays bus stops one by one.*/
				string currentBusStopName = currentBusStop->busStopName;
				busStopsOnTarget.push_back(currentBusStopName); /*Adds the bus stops to the bus stop names vector.*/
				if(stopCounter > 0) {
					cout << " <-> " << currentBusStopName; /*Displays the names of the bus stops other than the first one.*/
				} else {
					cout << currentBusStopName; /*Displays the name of the first bus stop.*/
				}
				currentBusStop = currentBusStop->right;
				stopCounter++;
			}
			cout << endl;
			break; /*Exits from the while loop when it finds the targeted bus line and saves the bus stops inside of it.*/
		}
		currentBusLine = currentBusLine->next;
	}
	/*Gets the name of the bus stop to be deleted from the bus line.*/
	string deletionBusStopName;
	cout << "Enter the name of the bus stop to delete (0 for main menu)" << endl;
	cin >> deletionBusStopName; /*Gets the name of the bus stop to be deleted.*/
	if(deletionBusStopName == "0") {return;}
	while(!(find(busStopsOnTarget.begin(), busStopsOnTarget.end(), deletionBusStopName) != busStopsOnTarget.end())) {
		cout << "Bus stop cannot be found. Enter the name of the bus stop to delete (0 for main menu)" << endl;
		cin >> deletionBusStopName; /*If the given bus stop does not exist in the bus line, again asks for it.*/
		if(deletionBusStopName == "0") {return;}
	}
	/*Visits all bus stops inside of the bus line and deletes the targeted one.*/
	busStop* currentBusStop = currentBusLine->busStops;
	while(currentBusStop != NULL) { /*Visits all bus stops one by one.*/
		string currentBusStopName = currentBusStop->busStopName;
		if(currentBusStopName == deletionBusStopName) { /*When it found the targeted bus stop name to be deleted, performs necessary operations.*/
			if(currentBusStop->left == NULL && currentBusStop->right == NULL) { /*Deletes the bus line if it is the last bus stop in the bus line.*/
				deleteBusLineByName(busLineName); /*Deletes the bus line with the bus stop inside of it.*/
			} else { /*Deletes the targeted bus stop from the bus line.*/
				if(currentBusStop->left == NULL) { /*Updates connections if the bus stop is at the beginning of the doubly linked list.*/
					currentBusLine->busStops = currentBusStop->right;
					currentBusStop->right->left = NULL;
				} else if(currentBusStop->right == NULL) { /*Updates connections if the bus stop is at the end of the doubly linked list.*/
					currentBusStop->left->right = NULL;
				} else { /*Updates connections if the bus stop is at an address neither the end of the list, nor the beginning of the list.*/
					currentBusStop->left->right = currentBusStop->right;
					currentBusStop->right->left = currentBusStop->left;
				}
				delete currentBusStop; /*Deletes the bus stop node.*/
			}
			break;
		}
		currentBusStop = currentBusStop->right;
	}
	cout << endl;
	printBusLines(); /*Prints the updated bus line table to the console.*/
	
}

bool doesExistIn(busLine* targetBusLine, string busStopName) {
	/*Checks if a specific bus stop exists in a given bus line.*/
	busStop* busStopPtr = targetBusLine->busStops;
	while(busStopPtr != NULL) {
		if(busStopPtr->busStopName == busStopName) {
			return true; /*Returns true if the target bus stop exists in the given bus line.*/
		}
		busStopPtr = busStopPtr->right;
	}
	return false; /*Returns false if the target bus stop does not exist in the given bus line.*/
}

bool doesBothExistIn(busLine* targetBusLine, string busStopName1, string busStopName2) {
	/*Checks if two target bus stops exist in a given bus line at the same time.*/
	if(doesExistIn(targetBusLine, busStopName1) && doesExistIn(targetBusLine, busStopName2)) {return true;}
	return false;
}

busLine* findBusLineByName(string busLineName) {
	/*Finds a specific bus line from its name.*/
	busLine* busLinePtr = head;
	while(busLinePtr != NULL) {
		if(busLineName == busLinePtr->busLineName) {
			return busLinePtr; /*If founds the target bus line, returns it.*/
		}
		busLinePtr = busLinePtr->next;
	}
	return NULL; /*If cannot found the target bus line, returns NULL.*/
}

busStop* findBusStopInLine(string busLineName, string busStopName) {
	/*Finds a specific bus stop from its name inside of a given bus line.*/
	busLine* busLinePtr = findBusLineByName(busLineName);
	while(busLinePtr != NULL) {
		busStop* busStopPtr = busLinePtr->busStops;
		while(busStopPtr != NULL) {
			if(busStopName == busStopPtr->busStopName) {
				return busStopPtr; /*If founds the target bus stop, returns it.*/
			}
			busStopPtr = busStopPtr->right;
		}
		busLinePtr = busLinePtr->next;
	}
	return NULL; /*If cannot found the target bus stop, returns NULL.*/
}

bool printDirectPaths(string startingBusStopName, string endingBusStopName) {
	/*Finds all direct paths from starting bus stop and ending bus stop.*/
	bool pathFound = false; /*Holds the information if a direct path is found, or not.*/
	busLine* busLinePtr = head;
	/*Visits all bus lines one by one to find a direct path between given bus stops.*/
	while(busLinePtr != NULL) {
		busStop* busStopPtr = busLinePtr->busStops;
		bool startingFound = false, endingFound = false;
		int busStopCounter = 0, startingPosition = 0, endingPosition = 0;
		while(busStopPtr != NULL) { /*Visits all bus stops inside of a bus line one by one.*/
			if(busStopPtr->busStopName == startingBusStopName) { /*If finds the starting bus stop, saves its position.*/
				startingPosition = busStopCounter;
				startingFound = true;
			} else if(busStopPtr->busStopName == endingBusStopName) { /*If finds the ending bus stop, saves its position.*/
				endingPosition = busStopCounter;
				endingFound = true;
			}
			busStopCounter++;
			busStopPtr = busStopPtr->right;
		}
		if(startingFound && endingFound) { /*If both starting and ending bus stops exist in the same bus line, prints the path.*/
			pathFound = true; /*Makes the path found boolean true to return it at the end of the function.*/
			cout << "You can go there by " << busLinePtr->busLineName << ": ";
			/*Checks if the starting position comes before the ending position in the bus line*/
			if(startingPosition < endingPosition) {
				/*Prints the starting bus stop to ending bus stop starting from the beginning to the end.*/
				busStop* ptrPrinter = findBusStopInLine(busLinePtr->busLineName, startingBusStopName);
				cout << ptrPrinter->busStopName;
				ptrPrinter = ptrPrinter->right;
				while(ptrPrinter->busStopName != endingBusStopName) {
					cout << "->" << ptrPrinter->busStopName;
					ptrPrinter = ptrPrinter->right; /*Goes right and then, prints the next bus stop.*/
				}
				cout << "->" << ptrPrinter->busStopName;
			} else {
				/*Prints the starting bus stop to ending bus stop starting from the end to the beginning.*/
				busStop* ptrPrinter = findBusStopInLine(busLinePtr->busLineName, startingBusStopName);
				cout << ptrPrinter->busStopName;
				ptrPrinter = ptrPrinter->left;
				while(ptrPrinter->busStopName != endingBusStopName) {
					cout << "->" << ptrPrinter->busStopName;
					ptrPrinter = ptrPrinter->left; /*Goes left and then, prints the next bus stop.*/
				}
				cout << "->" << ptrPrinter->busStopName;
			}
			cout << endl;
		}
		busLinePtr = busLinePtr->next;
	}
	return pathFound; /*Returns if a direct path found from the starting bus stop to the ending bus stop.*/
}

vector<busStop*> getBusStopsExcept(vector<string> previouslyUsedBusStops, busStop* firstStopInLine) {
	/*Challenge Parts*/
	/*Saves all bus stops except the given one inside of a bus line into a vector.*/
	vector<busStop*> resultBusStops;
	while(firstStopInLine != NULL) {
		if(!(find(previouslyUsedBusStops.begin(), previouslyUsedBusStops.end(), firstStopInLine->busStopName) != previouslyUsedBusStops.end())) {
			resultBusStops.push_back(firstStopInLine); /*Saves all bus stops other than the excepted one.*/
		}
		firstStopInLine = firstStopInLine->right;
	}
	return resultBusStops; /*Returns bus stops in a bus line except an excepted bus stop.*/
}

vector<string> getPossibleBusLines(string busStopName, vector<string> previouslyUsedBusLines) {
	/*Challenge Parts*/
	vector<string> busLineNamesContainingBusStop;
	busLine* busLinePtr = head;
	while(busLinePtr != NULL) {
		if(!(find(previouslyUsedBusLines.begin(), previouslyUsedBusLines.end(), busLinePtr->busLineName) != previouslyUsedBusLines.end())) {
			busStop* busStopPtr = busLinePtr->busStops;
			while(busStopPtr != NULL) {
				if(busStopName == busStopPtr->busStopName) {
					busLineNamesContainingBusStop.push_back(busLinePtr->busLineName);
				}
				busStopPtr = busStopPtr->right;
			}
		}
		busLinePtr = busLinePtr->next;
	}
	return busLineNamesContainingBusStop;
}

bool recursiveInterchange(vector<string> previouslyUsedBusLines, vector<string> previouslyUsedBusStops, string initBusLine, string initBusStop, string endStopName) {
	/*Challenge Parts*/
	bool pathFound = false;
	previouslyUsedBusLines.push_back(initBusLine);
	previouslyUsedBusStops.push_back(initBusStop);
	vector<string> possibleLinesToTry = getPossibleBusLines(initBusStop, previouslyUsedBusLines);
	for(unsigned int i = 0; i < possibleLinesToTry.size(); i++) {
		busLine* targetBusLine = findBusLineByName(possibleLinesToTry.at(i));
		vector<busStop*> possibleStopsToTry = getBusStopsExcept(previouslyUsedBusStops, targetBusLine->busStops);
		for(unsigned int j = 0; j < possibleStopsToTry.size(); j++) {
			string possibleBusStopName = possibleStopsToTry.at(j)->busStopName;
			if(possibleBusStopName == endStopName) {
				previouslyUsedBusLines.push_back(targetBusLine->busLineName);
				previouslyUsedBusStops.push_back(possibleStopsToTry.at(j)->busStopName);
				cout << endl;
				
				for(int m = 0; m < previouslyUsedBusLines.size(); m++) {
					cout << previouslyUsedBusLines.at(m) << ": " << endl;
				}

				cout << endl;
				pathFound = true;
				/*There is just 8 minutes left to the submission deadline, I could not print the path with the exact bus stop names yet.*/

			} else {
				recursiveInterchange(previouslyUsedBusLines, previouslyUsedBusStops, targetBusLine->busLineName, possibleStopsToTry.at(j)->busStopName, endStopName);
			}
		}
	}
	return pathFound;
} 

bool printInterchangePaths(string startingBusStopName, string endingBusStopName) {
	bool pathFound = false;

	busLine* busLinePtr = head;
	while(busLinePtr != NULL) {
		/*Eliminates the bus line if it has a direct path in it. */
		if(doesBothExistIn(busLinePtr, startingBusStopName, endingBusStopName)) {
			continue;
		}
		/*Continues the bus line if it has a direct path in it. */
		busStop* busStopPtr = busLinePtr->busStops;
		while(busStopPtr != NULL) {
			if(busStopPtr->busStopName == startingBusStopName) {
				/*It found a bus line in which the target bus stop exists.*/
				vector<string> previouslyUsedBusLines;
				vector<string> previouslyUsedBusStops;
				string initBusLine = busLinePtr->busLineName;
				string initBusStop = busStopPtr->busStopName;
				/*Finds and prints all possible paths with a recursive function.*/
				pathFound = recursiveInterchange(previouslyUsedBusLines, previouslyUsedBusStops, initBusLine, initBusStop, endingBusStopName);
			}
			busStopPtr = busStopPtr->right;
		}
		busLinePtr = busLinePtr->next;
	}

	return pathFound;
}

void findPath() { /*Finds the paths to go from a bus stop to another one.*/
	/*Gets the starting and ending bus stops from the user.*/
	string startingStop, endingStop;
	cout << "Where are you now?" << endl;
	cin >> startingStop; /*Gets the name of the starting bus stop.*/
	if(!busStopExistence(startingStop)) {
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return; /*Returns to the main menu if the targeted bus stop does not exist in the list.*/
	}
	cout << "Where do you want to go?" << endl;
	cin >> endingStop; /*Gets the name of the ending bus stop.*/
	if(!busStopExistence(endingStop)) {
		cout << "Bus stop does not exist in the table. Going back to previous menu." << endl;
		return; /*Returns to the main menu if the targeted bus stop does not exist in the list.*/
	}

	/*Finds and prints all possible paths to go from the starting bus stop to the ending bus stop.*/
	bool directPathFound = printDirectPaths(startingStop, endingStop);
	/*Challenge Part*/
	bool interchangePathFound = printInterchangePaths(startingStop, endingStop); /*If I can complete on time, I will upload this part as well.*/

	/*Prints a proper message if there is no path found to go from the starting bus stop to the ending bus stop.*/
	if(!directPathFound && !interchangePathFound) {
		cout << "Sorry no path from " << startingStop << " to " << endingStop << " could be found." << endl;
	}

}

void processMainMenu() { /*Displays the main menu and calls all the necessary functions from there.*/
	char input;
	do {
		if(!consistencyCheck()) { /*Checks if there is any inconsistencies inside of the linked list.*/
			cout << "There are inconsistencies. Exit." << endl;
			return;
		}
		printMainMenu(); /*Prints the details of the main menu to the console.*/
		cout << "Please enter your option " << endl;
		cin >> input; /*Gets the option as user input.*/
		switch(input) {
			case '0':
				cout << "Thanks for using our program" << endl;
				return;
			case '1':
				printBusLines();
				break;
			case '2':
				addBusLine();
				break;
			case '3':
				addBusStop();
				break;
			case '4':
				deleteBusLine();
				break;
			case '5':
				deleteBusStop();
				break;
			case '6':
				findPath();
				break;
			default:
			cout << "Invalid option: please enter again" << endl;
			}
	} while(true);
}

void busLineInitialization(string busLineName, vector<string> busStopNames, int lineCount) { /*Initializes a bus line.*/
	if(!busLineExistence(busLineName)) { /*Checks if the bus line does not exist in the linked list.*/
		/*Creates the head bus stop with NULL pointers to be updated in the upcoming parts.*/
		busStop* headBusStop = new busStop();
		headBusStop->busStopName = busStopNames.at(0);
		headBusStop->left = NULL;
		headBusStop->right = NULL;
		/*Creates all other bus stops and connects them to each other.*/
		busStop* previousBusStop = headBusStop;
		for(int i = 1; i < busStopNames.size(); i++) {
			/*Creates a bus stop node for each bus stop and connects it with the previous bus stop.*/
			busStop* newBusStop = new busStop();
			newBusStop->busStopName = busStopNames.at(i);
			newBusStop->left = previousBusStop; /*Connects new bus stop with previous bus stop.*/
			newBusStop->right = NULL;
			previousBusStop->right = newBusStop; /*Connects previous bus stop with new bus stop.*/
			previousBusStop = newBusStop; /*Updates previous bus stop for the next operation.*/
		}
		/*Creates a new bus line and connects it to the bus stop list created.*/
		busLine* newBusLine = new busLine();
		newBusLine->busLineName = busLineName;
		newBusLine->next = NULL;
		newBusLine->busStops = headBusStop;
		/*Goes until the last bus line node and adds the new one after that node.*/
		if(lineCount != 0) {
			busLine* ptr = head;
			while(ptr->next != NULL) { /*Goes until the last bus line and stops there.*/
				ptr = ptr->next;
			}
			ptr->next = newBusLine; /*Adds the node to the end of the bus lines linked list.*/
		} else {
			head = newBusLine; /*Adds it as head if it is the only bus line in the list.*/
		}
	}

}

void initializeProgram() { /*Initializes the program by opening the bus lines data file and saving them into 2D linked list.*/
	string fileName = "busLines.txt", fileLine;
	ifstream fileInput;
	int lineCount = 0;
	fileInput.open(fileName.c_str()); /*Opens the data file.*/
	while(getline(fileInput, fileLine)) { /*Reads the .txt file line by line and adds elements by creating a linked list.*/
		istringstream lineStream(fileLine);
		vector<string> busStopNames; /*Creates a vector of string in order to store all bus stops in a bus line.*/
		string busLineName, busStopName;
		lineStream >> busLineName; /*Gets the information in the line by seperating them. First of them is the bus line name.*/
		busLineName.pop_back(); /*Converts the bus line name into a proper format by deleting its last letter.*/
		while(lineStream >> busStopName) {
			busStopNames.push_back(busStopName); /*Adds the name of the bus stop into the vector consisting of bus stops in that line.*/
		}
		busLineInitialization(busLineName, busStopNames, lineCount); /*Initializes bus lines by using bus stop names.*/
		lineCount++;
	}
}

int main() {

	initializeProgram();
	processMainMenu();

	return 0;
}