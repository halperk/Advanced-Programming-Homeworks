#ifndef TWODSHAPES_H
#define TWODSHAPES_H

#include "Shape.h"
#include <iostream>
using namespace std;

class TwoDShape: public shape { /* A class that inherited by shape but also a base class for rectangle class. */
public:
	TwoDShape(string name): shape(name) {}; /* Constructs the TwoDShape object. */
	virtual float volume(); /* Returns volume as zero since it is a 2D shape so that doesn't have a volume at all. */
};

class rectangle: public TwoDShape { /* A class which stores details about a rectangle, inherited by TwoDShape.*/
public:
	rectangle(float width, float length, string name): myWidth(width), myLength(length), TwoDShape(name) {}; /* Constructs the rectangle object. */
	float perimeter(); /* Returns the calculated value of the perimeter of the rectangle. */
	float area(); /* Returns the calculated value of the area of the rectangle. */
protected:
	float myWidth; /* Stores the width of the rectangle. */
	float myLength; /* Stores the length of the rectangle. */
};

#endif