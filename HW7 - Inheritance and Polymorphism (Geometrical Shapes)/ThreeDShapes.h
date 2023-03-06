#ifndef THREEDSHAPES_H
#define THREEDSHAPES_H

#include "Shape.h"
#include <iostream>
using namespace std;

class ThreeDShape: public shape { /* A class that inherited by shape but also a base class for box class. */
public:
	ThreeDShape(string name): shape(name) {}; /* Constructs the ThreeDShape object. */
	virtual float perimeter(); /* Returns perimeter as zero since it is a 3D shape so that doesn't have a perimeter. */
};

class box: public ThreeDShape { /* A class which stores details about a box, inherited by ThreeDShape.*/
public:
	box(float width, float length, float height, string name): myWidth(width), myLength(length), myHeight(height), ThreeDShape(name) {}; /* Constructs the box object. */
	float volume(); /* Returns the calculated value of the volume of the box. */
	float area(); /* Returns the calculated value of the area of the box. */
protected:
	float myWidth; /* Stores the width of the box. */
	float myLength; /* Stores the length of the box. */
	float myHeight; /* Stores the height of the box. */
};

#endif