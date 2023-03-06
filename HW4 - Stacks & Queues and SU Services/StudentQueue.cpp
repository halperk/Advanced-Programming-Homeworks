/*Modified from the DynIntQueue.cpp shown in the lectures.*/
#include <iostream>
#include "StudentQueue.h"
using namespace std;

StudentQueue::StudentQueue() {
	/*Constructs an empty queue.*/
	front = NULL;
	rear = NULL;
}

void StudentQueue::enqueue(StudentNode stNode) {
	/*Inserts the student node at the rear of the queue.*/
	StudentNode *student = new StudentNode(stNode.service, stNode.name, stNode.ID);
	if(isEmpty())  { /*Makes it first element if the queue is empty.*/
		front = student;
		rear = front;
	} else { /*Adds it after rear if the queue is not empty.*/
		rear->next = student;
		rear = rear->next;
	}
}

void StudentQueue::dequeue(StudentNode &stNode) {
	/*Removes the value at the front of the queue, and copies it into num.*/
	StudentNode *temp;
	if(isEmpty()) {
		cout << "Attempting to dequeue on empty queue, exiting program..." << endl;
		exit(1);
	} else { /*Returns the front node, updates the front and then, deletes old front.*/
		stNode = *front;
		temp = front;
		front = front->next;
		delete temp;
	}
}

bool StudentQueue::isEmpty() const {
	/*Checks the queue, returns true if the queue is empty, and returns false otherwise.*/
	if(front == NULL) {
		return true;
	} else {
		return false;
	}
}

void StudentQueue::clear() {
	/*Dequeues all the elements in the queue.*/
	StudentNode stNode; /*Dummy variable for dequeue operation.*/

	while(!isEmpty()) { /*Dequeues all elements one by one.*/
		dequeue(stNode);
	}
}

StudentQueue::~StudentQueue() {
	/*Destructor to prevent memory leak.*/
	clear();
}