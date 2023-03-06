/*Modified from the DynIntStack.h shown in the lectures.*/
using namespace std;

struct StackNode {
	string service;
	string command;
	string parameter;
	StackNode *next;

	StackNode::StackNode() {}
	StackNode(string serviceName, string stackCommand, string stackParameter, StackNode *stackNext = NULL) {
		service = serviceName;
		command = stackCommand;
		parameter = stackParameter;
		next = stackNext;
	}
};

class SharedStack {
private:
	StackNode *top;
public:
	SharedStack(void); /*Constructs an empty stack.*/
	void push(StackNode); /*Pushes a new argument onto the stack.*/
	void pop(StackNode &); /*Pops the value at the top of the stack off, and copies it into the variable passed as an argument.*/
	bool isEmpty(void); /*Checks the stack if it is empty, or not.*/
	~SharedStack(); /*Destructor to prevent memory leak.*/
};
