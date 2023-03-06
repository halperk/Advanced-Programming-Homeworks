/*Modified from the IntQueue.cpp shown in the lectures.*/
#include <iostream>
#include "InstructorQueue.h"
using namespace std;

InstructorQueue::InstructorQueue(int s) {
	/*Creates an empty queue with given number of elements.*/
	queueArray = new InstructorNode[s];
	queueSize = s;
	front = -1;
	rear = -1;
	numItems = 0;
}

void InstructorQueue::enqueue(InstructorNode inNode) {
	/*Inserts the value in num at the rear of the queue.*/
	if (isFull()) { 
		cout << "The queue is full." << endl;
    } else {
		rear = (rear + 1) % queueSize; /*Calculates new rear position circularly.*/
		queueArray[rear] = inNode;
		numItems++;
	}
}

void InstructorQueue::dequeue(InstructorNode &inNode) {
	/*Removes the value at the front of the queue, and copies it into num.*/
	if (isEmpty()){
       cout << "Attempting to dequeue on empty queue, exiting program..." << endl;
       exit(1);
    } else {
		front = (front + 1) % queueSize; /*Moves front.*/
		inNode = queueArray[front];
		numItems--;
	}
}

bool InstructorQueue::isEmpty() const {
	/*Checks the queue, returns true if the queue is empty, and returns false otherwise.*/
	if (numItems > 0) {
		return false;
	} else {
		return true;
	}
}

bool InstructorQueue::isFull() const {
	/*Checks the queue, returns true if the queue is full, and returns false otherwise.*/
	if (numItems < queueSize) {
		return false;
	} else {
		return true;
	}
}

void InstructorQueue::clear() {
	/*Resets the front and rear indices, and sets numItems to 0.*/
	front =  - 1;
	rear =  - 1;
	numItems = 0;
}