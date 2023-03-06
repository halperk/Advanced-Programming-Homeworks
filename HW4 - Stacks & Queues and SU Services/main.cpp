12q221/*******************************************

CS 204 (Fall 2021-2022)
Homework #4 - SU Services
Huseyin Alper Karadeniz (28029)
Date: 11/22/2021

********************************************/

#include <iostream>
#include <string>
#include <vector>
#include <sstream>
#include <fstream>
#include "InstructorQueue.h"
#include "StudentQueue.h"
#include "SharedStack.h"
using namespace std;

InstructorQueue instructorQueue(5);
StudentQueue studentQueue;
SharedStack sharedStack;

struct operationNode {
	/*Creates a struct to store function operations inside of the service function.*/
    string command; /*Stores the command such as print, call, or define.*/
	string parameter; /*Stores the parameter of the command.*/
    operationNode *nextOperation; /*Stores the next operation node.*/
	
	operationNode::operationNode() {
		nextOperation = NULL;
	}
	operationNode(string cmd, string param, operationNode *ptr = NULL) {
		/*Constructs an operation node according to the parameters given.*/
		command = cmd;
		parameter = param;
		nextOperation = ptr;
	}
};

struct serviceNode {
	/*Creates a struct to keep service functions together.*/
    string serviceName; /*Stores the name of the service.*/
    serviceNode *nextService; /*Stores the next service node.*/
    operationNode *firstOperationNode; /*Stores the first operation node inside of the service.*/

	serviceNode::serviceNode() {
		nextService = NULL;
		firstOperationNode = NULL;
	}
	serviceNode(string service, serviceNode *ptrService = NULL, operationNode *ptrOperation = NULL) {
		/*Constructs a service node according to the parameters given.*/
		serviceName = service;
		nextService = ptrService;
		firstOperationNode = ptrOperation;
	}
    
};

serviceNode* servicesHead = nullptr;

void addNewServiceNode(serviceNode *newServiceNode) {
	/*Adds given service node to the services linked list.*/
	serviceNode *ptr = servicesHead;
	if(ptr == NULL) { /*Detects if there is no services on the list.*/
		servicesHead = newServiceNode; /*Makes new service node to the head of the linked list.*/
	} else {
		while(ptr->nextService != NULL) {ptr = ptr->nextService;} /*Goes until the last node.*/
		ptr->nextService = newServiceNode; /*Adds new service node to the end of the linked list.*/
	}
}

void addNewOperationNode(operationNode *prevOperationNode, operationNode *newOperationNode) {
	/*Adds given new operation node after the given previous operation node.*/
	prevOperationNode->nextOperation = newOperationNode;
}

void addNewOperationNode(serviceNode *serviceNode, operationNode *newOperationNode) {
	/*Adds given new operation node as the first operation node of given service node.*/
	serviceNode->firstOperationNode = newOperationNode;
}

void initializeInputFile(string inputFileName) {
	/*Initializes the input file and creates necessary linked lists accordingly.*/
    ifstream fileInput;
    fileInput.open(inputFileName.c_str());
    if(!fileInput.fail()) { /*Continues if the file opened successfully.*/
		serviceNode *newServiceNode = new serviceNode(); /*Creates a new service node to use it with the input file.*/
		operationNode *ptrOperationNode; /*Defines an operation node to use it in the loop to store previous operation node.*/
        string operationLine;
        int commandCounter = 0;
        while(getline(fileInput, operationLine)) {
            operationLine.pop_back(); /*Removes the last letter of the input line which is ":" or ";" sign.*/
            istringstream lineStream(operationLine);
            if(commandCounter == 0) { /*It is the first line in the input file so that it contains the name of the service.*/
                string serviceName;
                lineStream >> serviceName; /*Gets the name of the service.*/
				newServiceNode->serviceName = serviceName; /*Saves the name of the service into the node.*/
				addNewServiceNode(newServiceNode); /*Adds the service node to the services linked list.*/
			} else if (commandCounter == 1) { /*It is the first command in the input file.*/
				string command, parameter;
                lineStream >> command >> parameter; /*Gets the command and its parameter from the line.*/
				operationNode *newOperationNode = new operationNode(command, parameter); /*Creates a new operation node properly.*/
				addNewOperationNode(newServiceNode, newOperationNode); /*Adds new operation node to the service node.*/
				ptrOperationNode = newOperationNode; /*Moves the pointer to new node in order to use it as previous node later.*/
			} else {
                string command, parameter;
                lineStream >> command >> parameter; /*Gets the command and its parameter from the line.*/
				operationNode *newOperationNode = new operationNode(command, parameter); /*Creates a new operation node properly.*/
				addNewOperationNode(ptrOperationNode, newOperationNode); /*Adds new operation node to the end of the operations list.*/
				ptrOperationNode = newOperationNode; /*Updates the pointer as new node to use it in further operations in the loop.*/
            }
            commandCounter++; /*Increments the command counter by one for further operations to check if they are the first ones.*/
        }
    } else { /*Gives an error if the given input file cannot be opened successfully.*/
        cout << "Cannot open the file of " << inputFileName << endl;
    }
}

bool choiceCheck(string choice) {
	/*Checks if the choice is yes, or not.*/
	if(choice == "Y" || choice == "y") {return true;}
	return false;
}

void getNewInputFile() {
	/*Gets a new input file and initializes its content if possible.*/
	string inputFileName;
	cout << "Enter the input file name: ";
	cin >> inputFileName; /*Gets the name of the input file.*/
	initializeInputFile(inputFileName); /*Initializes the input file if possible.*/
}
void exitProgram() {
	/*Exits from the program for some reason.*/
	cout << "Exiting the program..." << endl;
	exit(1);
}

void printServices() {
	/*Displays all services with their commands and parameters.*/
	cout << "-------------------------------------------------------------------" << endl
		 << "PRINTING AVAILABLE SERVICES (FUNCTIONS) TO BE CHOSEN FROM THE USERS" << endl
		 << "-------------------------------------------------------------------" << endl << endl;
	serviceNode *ptr = servicesHead;
	while(ptr != NULL) { /*Visits all service nodes one by one.*/
		cout << ptr->serviceName << endl;
		operationNode *ptrOp = ptr->firstOperationNode;
		while(ptrOp != NULL) { /*Visits all operation nodes inside of a service node one by one.*/
			if(ptrOp->nextOperation != NULL) { /*Prints the operation nodes before the last one.*/
				cout << ptrOp->command << " " << ptrOp->parameter << ", ";
			} else { /*Prints the operation node in a different format if it is the last node in the list.*/
				cout << ptrOp->command << " " << ptrOp->parameter << "." << endl;
			}
			ptrOp = ptrOp->nextOperation;
		}
		cout << endl;
		ptr = ptr->nextService;
	}
}

void initializeProgram() {
	/*Initializes program and gets necessary input files.*/
	cout << "If you want to open a service (function) defining file," << endl
		<< "then press (Y/y) for 'yes', otherwise press any single key" << endl;
	string choiceInput;
	cin >> choiceInput;
	if(choiceCheck(choiceInput)) { /*Gets the first input if Y, or y entered.*/
		getNewInputFile(); /*Gets the first input.*/
		while(choiceCheck(choiceInput)) { /*Goes until the choice is neither Y, nor y.*/
			cout << "Do you want to open another service defining file?" << endl
				<< "Press (Y/y) for 'yes', otherwise press anykey" << endl;
			cin >> choiceInput;
			if(choiceCheck(choiceInput)) {
				/*Gets the input from the input file.*/
				getNewInputFile(); /*Gets new input.*/
			}
		}
		if(servicesHead == NULL) {
			exitProgram(); /*Exits from the program since no files opened.*/
		} else {
			printServices(); /*Displays all saved services by visiting the linked list nodes one by one.*/
		}
	} else { /*Terminates the program if there is no files defined. */
		exitProgram(); /*Exits from the program since there is no inputs.*/
	}
}

void clearServiceNodes() {
	/*Prevents memory leak by deleting all service nodes at the end of the program.*/
	serviceNode *ptrService = servicesHead; /*Creates a service node pointer to visit service nodes.*/
	serviceNode *tmpService = ptrService; /*Creates a service node pointer to follow ptrService.*/
	while(ptrService != NULL) { /*Deletes all service nodes inside of the linked list.*/
		operationNode *ptrOperation = ptrService->firstOperationNode; /*Creates an operation node pointer to visit the nodes inside of a service node.*/
		operationNode *tmpOperation = ptrOperation; /*Creates an operation node pointer to follow ptrOperation.*/
		while(ptrOperation != NULL) { /*Deletes all operation nodes inside of a service node one by one.*/
			tmpOperation = ptrOperation;
			ptrOperation = ptrOperation->nextOperation;
			delete tmpOperation; /*Deletes the operation node that the pointer points.*/
		}
		tmpService = ptrService;
		ptrService = ptrService->nextService;
		delete tmpService; /*Deletes service node that the pointer points.*/
	}
}

bool serviceNameExistence(string targetServiceName) {
	/*Checks the existence of a given service name in the linked list, and returns true/false accordingly.*/
	serviceNode *ptr = servicesHead;
	while(ptr != NULL) {
		if(ptr->serviceName == targetServiceName) {return true;} /*Returns true if the service name exists.*/
		ptr = ptr->nextService;
	}
	return false; /*Returns true if the service name does not exist in the linked list.*/
}

void addInstructorRequest() {
    /*Creates a new request for an instructor.*/
	string serviceName;
	cout << "Add a service (function) that the instructor wants to use:" << endl;
	cin >> serviceName;
	if(serviceNameExistence(serviceName)) {
		/*Continues if the service name exists in the linked list.*/
		string instructorName;
		int instructorID;
		cout << "Give instructor's name: ";
		cin >> instructorName;
		cout << "Give insturctor's ID (an int): ";
		cin >> instructorID;
		/*Creates a new instructor node and adds it to the instructors' queue.*/
		InstructorNode instructor = InstructorNode(serviceName, instructorName, instructorID);
		instructorQueue.enqueue(instructor);
		cout << "Prof. " << instructorName << "'s service request of " << serviceName << endl
			 << "has been put in the instructors' queue." << endl;
		cout << "Waiting to be served..." << endl;
	} else {
		/*Gives and error and goes back if given service name does not exist in the linked list.*/
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
}

void addStudentRequest() {
    /*Creates a new request for a student.*/
	string serviceName;
	cout << "Add a service (function) that the student wants to use:" << endl;
	cin >> serviceName;
	if(serviceNameExistence(serviceName)) {
		/*Continues if the service name exists in the linked list.*/
		string studentName;
		int studentID;
		cout << "Give student's name: ";
		cin >> studentName;
		cout << "Give student's ID (an int): ";
		cin >> studentID;
		/*Creates a new student node and adds it to the students' queue.*/
		StudentNode student = StudentNode(serviceName, studentName, studentID);
		studentQueue.enqueue(student);
		cout << studentName << "'s service request of " << serviceName
			 << " has been put in the students' queue." << endl;
		cout << "Waiting to be served..." << endl;
	} else {
		/*Gives and error and goes back if given service name does not exist in the linked list.*/
		cout << "The requested service (function) does not exist." << endl;
		cout << "GOING BACK TO MAIN MENU" << endl;
	}
}

void printSharedStack() {
	/*Prints the content in the shared stack in a proper format.*/
	cout << "PRINTING THE STACK TRACE:" << endl;
	if(!(sharedStack.isEmpty())) {
		SharedStack tempStack; /*Defines a temporary stack to make it reverse of the original one.*/
		while(!(sharedStack.isEmpty())) {
			/*Copies the shared stack into a temporary stack in reverse order.*/
			StackNode tempNode;
			sharedStack.pop(tempNode);
			tempStack.push(tempNode);
		}
		while(!(tempStack.isEmpty())) {
			/*Prints all nodes in shared stack while building it back.*/
			StackNode tempNode;
			tempStack.pop(tempNode);
			sharedStack.push(tempNode);
			cout << tempNode.service << ": " << tempNode.command << " " << tempNode.parameter << endl;
		}
	} else {
		cout << "The stack is empty" << endl;
	}
}

serviceNode *serviceFinder(string targetServiceName) {
	/*Finds a service from its name, and returns service's pointer accordingly.*/
	serviceNode *ptr = servicesHead;
	while(ptr != NULL) {
		if(ptr->serviceName == targetServiceName) {
			return ptr; /*Returns the service's pointer if the service name exists.*/
		}
		ptr = ptr->nextService;
	}
	return NULL; /*Returns true if the service does not exist in the linked list.*/
}

void clearFromStack(string serviceName) {
	/*Clears the instances of the given service from the shared stack.*/
	StackNode node;
	sharedStack.pop(node); /*Gets the last node in the stack.*/
	sharedStack.push(node); /*Puts the last node of the stack back.*/
	while(node.service == serviceName) {
		sharedStack.pop(node); /*Removes the last node of the stack if it belongs to the target service.*/
		if(sharedStack.isEmpty()) {break;} /*Breaks the loop if there is no node left on the shared stack.*/
		sharedStack.pop(node); /*Gets the last node in the stack.*/
		sharedStack.push(node); /*Puts the last node of the stack back.*/
	}
}

void processARequest(string serviceName) {
	/*Processes a request by calling a function.*/
	serviceNode *service = serviceFinder(serviceName); /*Finds the target service node.*/
	operationNode *ptr = service->firstOperationNode; /*Finds the first operation node in the service.*/
	while(ptr != NULL) { /*Visits all operation nodes inside of a service one by one.*/
		string currentCommand = ptr->command;
		string currentParameter = ptr->parameter;
		if(currentCommand == "define") { 
			StackNode newStack = StackNode(serviceName, currentCommand, currentParameter);
			sharedStack.push(newStack); /*Defines a variable according to the parameter and adds it to the shared stack.*/
		} else if(currentCommand == "call") {
			cout << "Calling " << currentParameter << " from " << serviceName << endl; /*Calls a function recursively.*/
			processARequest(currentParameter);
		} else {
			printSharedStack(); /*Prints the shared stack.*/
		}
		ptr = ptr->nextOperation;
	}
	cout << serviceName << " is finished. Clearing the stack from it's data..." << endl;
	clearFromStack(serviceName); /*Clears the instances of a given service from the shared stack.*/
	system("pause");
}

void processARequest() {
	/*Processes a request from the queues by considering the priorities.*/
	if(!instructorQueue.isEmpty()) {
		/*Performs the request coming from the instructor.*/
		InstructorNode instructor;
		instructorQueue.dequeue(instructor);
		cout << "Processing instructors' queue..." << endl;
		cout << "Processing Prof. " << instructor.name << "'s request (with ID "
			 << instructor.ID << ") of service (function):" << endl << instructor.service << endl;
		processARequest(instructor.service); /*Processes the request of an instructor.*/
		if(sharedStack.isEmpty()) {cout << "The stack is empty." << endl;}
		cout << "GOING BACK TO MAIN MENU" << endl;
	} else if(!studentQueue.isEmpty()) {
		/*Performs the request coming from the student if there is nothing in the instructors' queue.*/
		StudentNode student;
		studentQueue.dequeue(student);
		cout << "Instructors' queue is empty. Proceeding with students' queue..." << endl;
		cout << "Processing " << student.name << "'s request (with ID "
			 << student.ID << ") of service (function):" << endl << student.service << endl;
		processARequest(student.service); /*Processes the request of a student.*/
		if(sharedStack.isEmpty()) {cout << "The stack is empty." << endl;}
		cout << "GOING BACK TO MAIN MENU" << endl;
	} else {
		/*Goes back to the main menu because there is nothing on both queues.*/
		cout << "Both instructors' and students' queue is empty." << endl
			 << "No request is processed." << endl
			 << "GOING BACK TO MAIN MENU" << endl;
	}
}

void runMainProgram() {
	/*Runs the main program and performs the necessary operations according to the options chosen.*/
    while(true) {
        cout << endl;
        cout<< "************************************************************************" << endl
            << "**************** 0 - EXIT PROGRAM                       ****************" << endl
            << "**************** 1 - ADD AN INSTRUCTOR SERVICE REQUEST  ****************" << endl
            << "**************** 2 - ADD A STUDENT SERVICE REQUEST      ****************" << endl
            << "**************** 3 - SERVE (PROCESS) A REQUEST          ****************" << endl
            << "************************************************************************" << endl;
        cout << endl;
        int option;
        cout << "Pick an option from above (int number from 0 to 3):";
		cin>> option;
        switch(option) {
            case 0:
				cout << "PROGRAM EXITING ..." << endl;
				clearServiceNodes(); /*Clears all service nodes before exiting the program.*/
				system("pause");
				exit(0);
            case 1:
                addInstructorRequest(); /*Adds an instructor request by getting inputs from the user.*/
                break;
            case 2:
                addStudentRequest(); /*Adds a student request by getting inputs from the user.*/
                break;
            case 3:
                processARequest(); /*Processes a request by considering some priorities.*/
                break;
            default:
                break;
        }
    }
}

int main() {
    
	initializeProgram(); /*Initializes all input files.*/
    
    runMainProgram(); /*Runs the main program for operations.*/
    
    return 0;
}
