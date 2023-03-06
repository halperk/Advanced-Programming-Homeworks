/*Modified from the DynIntStack.cpp shown in the lectures.*/
#include <iostream>
#include "SharedStack.h"
using namespace std;

SharedStack::SharedStack() {
	/*Constructs an empty stack.*/
	top = NULL; 
}

void SharedStack::push(StackNode stackNode) {
	/*Pushes a new argument onto the stack.*/
	StackNode *newNode = new StackNode(stackNode.service, stackNode.command, stackNode.parameter);
	if (isEmpty()) { /*Makes it first node if there is no nodes in the list.*/
		top = newNode;
		newNode->next = NULL;
	} else { // Otherwise, insert NewNode before top
		newNode->next = top;
		top = newNode;
	}
}

void SharedStack::pop(StackNode &stackNode) {
	/*Pops the value at the top of the stack off, and copies it into the variable passed as an argument.*/
	StackNode *temp;

	if (isEmpty()) {
		cout << "The stack is empty." << endl;
	} else { // pop value off top of stack
		stackNode = *top;
		temp = top->next;
		delete top;
		top = temp;
	}
}

bool SharedStack::isEmpty(void) {
	/*Checks the stack, returns true if the stack is empty, and returns false otherwise.*/
	bool status;
	if (top == NULL) {
		status = true;
	} else {
		status = false;
	}
	return status;
}

SharedStack::~SharedStack() {
	/*Destructor to prevent memory leak.*/
	StackNode stackNode; /*Dummy variable for clearing operation.*/

	while(!isEmpty()) { /*Pops all elements on the stack one by one.*/
		pop(stackNode);
	}
}