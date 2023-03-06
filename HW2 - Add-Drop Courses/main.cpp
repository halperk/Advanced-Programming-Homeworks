/*******************************************

CS 204 (Fall 2021-2022)
Homework #2 - Add/Drop Courses
Huseyin Alper Karadeniz (28029)
Date: 10/30/2021

********************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
using namespace std;

struct courseNode { // Creates a course node struct.
	string courseCode, courseName;
	vector<int> studentsAttendingIDs;
	courseNode *next;
	
	courseNode::courseNode() {}
};

courseNode *findCourseNode(courseNode *head, string courseCode) { // Finds course's node from the course code.
	courseNode *ptr = head; // Creates a node pointer to move in the list.
	while(ptr->next != NULL) { // Checks the nodes before the last one.
		if(ptr->courseCode == courseCode) { // Checks course codes.
			return ptr; // Returns the node pointer where the course exists.
		};
		ptr = ptr->next; // Moves to the next node.
	}
	if(ptr->courseCode == courseCode) { // Checks the last course's code.
		return ptr; // Returns the node pointer where the course exists.
	};
	return NULL; // Returns NULL if course does not exist in the list.
}

void sortVector(vector<int> &studentsAttendingIDs) { // Sorts given student IDs in ascending order.
	int tmpIndex;
	for(int i=0; i<studentsAttendingIDs.size()-1; i++) {
		int minID = studentsAttendingIDs.at(i);
		tmpIndex = i;
		for(int j=i+1; j<studentsAttendingIDs.size(); j++) {
			if(minID > studentsAttendingIDs.at(j)) {
				minID = studentsAttendingIDs.at(j);
				tmpIndex = j;
			}
		}
		swap(studentsAttendingIDs.at(i), studentsAttendingIDs.at(tmpIndex));
	}
}

bool updateStudentIDs(courseNode *courseSearched, int studentID) { // Updates student IDs in a node by adding a new student ID.
	vector<int> studentsAttendingIDs;
	studentsAttendingIDs = courseSearched->studentsAttendingIDs; // Gets old student IDs from the node.
	if(find(studentsAttendingIDs.begin(), studentsAttendingIDs.end(), studentID) != studentsAttendingIDs.end()) { // Checks if the student ID in the node.
		return true; // Returns true if the given student ID is in the node so that already added to the student IDs vector.
	} else {
		studentsAttendingIDs.push_back(studentID);
		sortVector(studentsAttendingIDs); // Sorts student IDs in ascending order.
		courseSearched->studentsAttendingIDs = studentsAttendingIDs; // Sets new student IDs to the node.
		return false; // Returns false if the given student ID is not in the node, and is added with this function.
	}
}

bool deleteStudentIDs(courseNode *courseSearched, int studentID) { // Updates student IDs in a node by removing a student ID.
	vector<int> studentsAttendingIDs;
	studentsAttendingIDs = courseSearched->studentsAttendingIDs; // Gets old student IDs from the node.
	if(find(studentsAttendingIDs.begin(), studentsAttendingIDs.end(), studentID) != studentsAttendingIDs.end()) { // Checks if student ID is on the node.
		int deletionIndex;
		for(int i=0; i<studentsAttendingIDs.size(); i++) { // Finds the index of the student ID to be removed from the node.
			int studentIDChecked = studentsAttendingIDs.at(i);
			if(studentIDChecked == studentID) {
				deletionIndex = i;
			}
		}
		studentsAttendingIDs.erase(studentsAttendingIDs.begin() + deletionIndex); // Removes student ID from the node.
		courseSearched->studentsAttendingIDs = studentsAttendingIDs; // Sets new student IDs to the node.
		return false; // Returns false if the student ID was on the node and deleted with this function.
	} else {
		return true; // Returns true if the student ID wasn't on the node.
	}
}

courseNode *addCourseNode(courseNode *head, string courseCode, string courseName, int studentID) { // Adds a new node to the linked list.
	courseNode *node = new courseNode(); // Creates a course node called node and sets the variables in it.
	vector<int> studentsAttendingIDs;
	studentsAttendingIDs.push_back(studentID);
	node->courseCode = courseCode;
	node->courseName = courseName;
	node->studentsAttendingIDs = studentsAttendingIDs;
	node->next = NULL;
	courseNode *ptr = head; // Defines a course node to move along the linked list starting from the head node.
	if(ptr->courseName > courseName) { // If the first node of the linked list has a later course name, new node will be new head.
		node->next = head;
		return node; // Returns node as a course node to change the head of the linked list as the new node.
	}
	while(ptr->next != NULL && ptr->next->courseName < courseName) { // Checks remaining nodes of the linked list, stops at a specific node.
		ptr = ptr->next; // Goes until the node where the course name of the next node is later than the course name of the new node.
	}
	node->next = ptr->next;
	ptr->next = node;
	return head; // Returns head without any changes.
}

courseNode *addElement(courseNode *head, string courseCode, string courseName, int studentID, int elementCount) { // Adds a new element to the linked list.
	if(elementCount != 0) { // Checks if it is the first node in the linked list, or not.
		courseNode *courseSearched = new courseNode(); // Creates a pointer for the searched course.
		courseSearched = findCourseNode(head, courseCode); // Finds the searched course's node.
		if(courseSearched != NULL) { // The course exists in the linked list; so, just updates the student IDs vector by adding the new one.
			updateStudentIDs(courseSearched, studentID); // Updates the attending students' IDs.
		} else { // The course does not exist in the linked list; so, adds the student ID with the course information in a node.
			head = addCourseNode(head, courseCode, courseName, studentID); // Create a new node according to the information given.
		}
	} else { // It is the first element and the first node.
		head->courseCode = courseCode;
		head->courseName = courseName;
		vector<int> studentsAttendingIDs;
		studentsAttendingIDs.push_back(studentID);
		head->studentsAttendingIDs = studentsAttendingIDs;
		head->next = NULL;
	}
	return head; // Returns the head node of the linked list. 
}

courseNode *addElementOption(courseNode *head, string courseCode, string courseName, int studentID, char &operation) { // Adds a new element to the linked list from the options.
	courseNode *courseSearched = new courseNode(); // Creates a pointer for the searched course.
	courseSearched = findCourseNode(head, courseCode); // Finds the course's node.
	if(courseSearched != NULL) { // The course exists in the linked list. Checks if the given student ID is already added, or not; if not, adds it to the vector.
		bool alreadyAdded = updateStudentIDs(courseSearched, studentID); // Updates the attending students' IDs, returns the info about the already added process.
		if (alreadyAdded == true) {
			operation = '1'; // The node (course) exists in the list and the ID was in the node, it was already there.
		} else {
			operation = '2'; // The node (course) exists in the list, but the ID wasn't in the node, it was added by this function.
		}
	} else { // The course does not exist in the linked list.
		operation = '3'; // The node (course) does not exist in the list; so, it is added by this function.
		head = addCourseNode(head, courseCode, courseName, studentID); // Creates a new node according to the information given.
	}
	return head; // Returns the head node of the linked list. 
}

courseNode *deleteElementOption(courseNode *head, string courseCode, string courseName, int studentID, char &operation) {
	courseNode *courseSearched = new courseNode(); // Creates a pointer for the searched course.
	courseSearched = findCourseNode(head, courseCode); // Finds the course's node.
	if(courseSearched != NULL) { // The course exists in the linked list. Checks if the given student ID is already deleted, or not; if yes, deletes it from the vector.
		bool alreadyDeleted = deleteStudentIDs(courseSearched, studentID); // Updates the attending students' IDs, returns the info about the already deleted process.
		if (alreadyDeleted == false) {
			operation = '1'; // The node (course) exists in the list and the ID was in the node, it was deleted by this function. 
		} else {
			operation = '2'; // The node (course) exists in the list, but the ID wasn't in the node, it was already deleted.
		}
	} else { // The course does not exist in the linked list.
		operation = '3'; // The node (course) does not exist in the list.
	}
	return head; // Returns the head node of the linked list. 
}

void displayNodeInformation(courseNode *node) { // Prints information of a node to the screen in general format.
	cout << node->courseName << " " << node->courseCode << ":";
	vector<int> studentsAttendingIDs = node->studentsAttendingIDs;
	for(int i=0; i<studentsAttendingIDs.size(); i++) {
		cout << " " << studentsAttendingIDs.at(i);
	}
	cout << endl;
}

void displayNodeInformationEnd(courseNode *node) { // Prints information of a node to the screen in final format.
	cout << node->courseCode << " " << node->courseName;
	vector<int> studentsAttendingIDs = node->studentsAttendingIDs;
	if(studentsAttendingIDs.size() < 4) {
		cout << " -> This course will be closed";
	} else {
		cout << ":";
		for(int i=0; i<studentsAttendingIDs.size(); i++) {
			cout << " " << studentsAttendingIDs.at(i);
		}
	}
	cout << endl;
}

void displayAllNodes(courseNode *head) { // Prints all the nodes in general format.
	courseNode *ptr = head;
	while(ptr->next != NULL) {
		displayNodeInformation(ptr);
		ptr = ptr->next;
	}
	displayNodeInformation(ptr);
}

void displayAllNodesEnd(courseNode *head) { // Prints all the nodes in final format.
	courseNode *ptr = head;
	while(ptr->next != NULL) {
		displayNodeInformationEnd(ptr);
		ptr = ptr->next;
	}
	displayNodeInformationEnd(ptr);
}

int getOption() { // Gets an option by the console and returns it.
	int optionSelected;
	cout << endl << "Please select one of the choices:" << endl
		<< "1. Add to List" << endl << "2. Drop from List" << endl
		<< "3. Display List" << endl << "4. Finish Add/Drop and Exit" << endl;
	cin >> optionSelected;
	return optionSelected;
}

bool isStudentID(string str) { // Checks if a string is in the student ID format, or not.
	return ((str.at(0) <= '9') && (str.at(0) >= '0'));
}

void deleteAllNodes(courseNode *head) { // Deletes all nodes so that the linked list.
	courseNode *ptr = head;
    while(ptr != NULL) { // Goes to the all nodes one by one.
		courseNode *old = ptr;
		ptr = ptr->next;
		delete old;
	}
}

int main() {

	courseNode *head = new courseNode();
	string fileName, fileLine;
	ifstream fileInput;
	cout << "Please enter file name: ";
	cin >> fileName; // Gets the file name.
	fileInput.open(fileName.c_str()); // Opens the file.
	cout << "Successfully opened file " << fileName << endl;
	
	int elementCount = 0; // Counts element count.

	while(getline(fileInput, fileLine)) { // Reads the .txt file line by line and adds elements by creating a linked list.
		istringstream lineStream(fileLine);
		string courseCode, courseName;
		int studentID;
		lineStream >> courseCode >> courseName >> studentID; // Gets the information in the line.
		head = addElement(head, courseCode, courseName, studentID, elementCount); // Adds the given information to the linked list.
		elementCount++;
	}

	cout << "The linked list is created." << endl << "The initial list is:" << endl;
	displayAllNodes(head);

	int optionSelected = getOption();
	while(true) {
		if(optionSelected == 1) { // Gets information for an element to add it to the linked list.
			cout << "Give the student ID and the course names and course codes that he/she wants to add:" << endl;
			string addInput, addInputValue, courseCode, courseName, studentID;
			bool newCourse = false;
			cin.ignore();
			getline(cin, addInput); // Gets an input for adding it to the linked list.
			istringstream lineStream(addInput);

			while((lineStream >> addInputValue)) { // Gets the input value and by finding its format, executes necessary operations.
				if((!isStudentID(addInputValue)) && newCourse == false) { // Represents course code.
					courseCode = addInputValue;
					newCourse = true;
				} else if((!isStudentID(addInputValue)) && newCourse == true) { // Represents course name.
					courseName = addInputValue;
					newCourse = false;
				} else if(isStudentID(addInputValue) && newCourse == false) { // Represents student ID.
					studentID = addInputValue;
					char operation = '0';
					head = addElementOption(head, courseCode, courseName, stoi(studentID), operation);
					if(operation == '1') {
						cout << "Student with id " << studentID << " already is enrolled to " << courseCode << ". No action taken." << endl;
					} else if(operation == '2') {
						cout << "Student with id " << studentID << " is enrolled to " << courseCode << "." << endl;
					} else if(operation == '3') {
						cout << courseCode << " does not exist in the list of Courses. It is added up." << endl;
						cout << "Student with id " << studentID << " is enrolled to " << courseCode << "." << endl;
					}
					newCourse = false;
				}
			}

		} else if(optionSelected == 2) { // Gets information for an element to drop it from the linked list.
			cout << "Give the student ID and the course names and course codes that he/she wants to drop:" << endl;
			string deleteInput, deleteInputValue, courseCode, courseName, studentID;
			bool newCourse = false;
			cin.ignore();
			getline(cin, deleteInput); // Gets an input for deleting it from the linked list.
			istringstream lineStream(deleteInput);

			while((lineStream >> deleteInputValue)) { // Gets the input value and by finding its format, executes necessary operations.
				if((!isStudentID(deleteInputValue)) && newCourse == false) { // Represents course code.
					courseCode = deleteInputValue;
					newCourse = true;
				} else if((!isStudentID(deleteInputValue)) && newCourse == true) { // Represents course name.
					courseName = deleteInputValue;
					newCourse = false;
				} else if(isStudentID(deleteInputValue) && newCourse == false) { // Represents student ID.
					studentID = deleteInputValue;
					char operation = '0';
					head = deleteElementOption(head, courseCode, courseName, stoi(studentID), operation);
					if(operation == '1') {
						cout << "Student with id " << studentID << " has dropped " << courseCode << "." << endl;
					} else if(operation == '2') {
						cout << "Student with id " << studentID << " is not enrolled to " << courseCode << ", thus he can't drop that course." << endl;
					} else if(operation == '3') {
						cout << "The " << courseCode << " course is not in the list, thus student with id " << studentID << " can't be dropped." << endl;
					}
					newCourse = false;
				}
			}
		} else if(optionSelected == 3) { // Displays all linked list in general format.
			cout << "The current list of course and the students attending them:" << endl;
			displayAllNodes(head);
		} else if(optionSelected == 4) { // Prints all the nodes so that the linked list in final format and exits the program.
			cout << "The add/drop period is finished. Printing the final list of courses and students attending them." << endl;
			cout << "NOTE: Courses with less than 3 students will be closed this semester." << endl;
			displayAllNodesEnd(head); // Displays all linked list in final format.
			deleteAllNodes(head); // Deletes all the nodes (linked list) before closing the program.
			break;
		}
		optionSelected = getOption();
	}

	return 0;

}