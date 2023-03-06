/*Modified from the IntQueue.h shown in the lectures.*/
#ifndef INSTRUCTORQUEUE_H
#define INSTRUCTORQUEUE_H
using namespace std;

struct InstructorNode {
	string service;
	string name;
	int ID;
	
	InstructorNode::InstructorNode() {}
	InstructorNode(string inService, string inName, int inID) {
		service = inService;
		name = inName;
		ID = inID;
	}
};

class InstructorQueue {
private:
	InstructorNode *queueArray;
	int queueSize;
	int front;
	int rear;
	int numItems;
public:
	InstructorQueue(int);
  	void enqueue(InstructorNode);
  	void dequeue(InstructorNode &);
  	bool isEmpty() const;
  	bool isFull() const;
  	void clear();
};

#endif