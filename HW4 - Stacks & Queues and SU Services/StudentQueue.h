/*Modified from the DynIntQueue.h shown in the lectures.*/
#ifndef STUDENTQUEUE_H
#define STUDENTQUEUE_H
using namespace std;

struct StudentNode {
	string service;
	string name;
	int ID;
	StudentNode *next;
	StudentNode::StudentNode() {}
	StudentNode(string serviceName, string studentName, int studentID, StudentNode *ptr = NULL) {
		service = serviceName;
		name = studentName;
		ID = studentID;
		next = ptr;
	}
};

class StudentQueue {
private:
	StudentNode *front;
	StudentNode *rear;	
public:
	StudentQueue(); /*Constructs an empty queue.*/
	void enqueue(StudentNode); /*Inserts the student node at the rear of the queue.*/
	void dequeue(StudentNode &); /*Removes the value at the front of the queue, and copies it into num.*/
	bool isEmpty() const; /*Checks the queue if it is empty, or not.*/
	void clear(); /*Dequeues all the elements in the queue.*/
	~StudentQueue(); /*Destructor to prevent memory leak.*/
};

#endif