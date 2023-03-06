#ifndef SHAPE_H
#define SHAPE_H

#include <iostream>
using namespace std;

class shape { /* The shape class that will be used as the base class in further class declarations. */
public:
	shape(string name): myName(name) {}; /* Constructs the shape object. */
	virtual float perimeter() = 0; /* Defines a pure virtual function to use later. */
	virtual float area() = 0; /* Defines a pure virtual function to use later. */
	virtual float volume() = 0; /* Defines a pure virtual function to use later. */
	virtual string getName() { /* Returns the name of the object. */
		return myName;
	};
protected:
	string myName; /* Stores the name of the object. */
};

#endif