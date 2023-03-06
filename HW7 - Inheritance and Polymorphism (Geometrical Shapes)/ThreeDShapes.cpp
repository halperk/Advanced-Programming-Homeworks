#include "ThreeDShapes.h"

/* Returns perimeter as zero since it is a 3D shape so that doesn't have a perimeter. */
float ThreeDShape::perimeter() {
	return 0;
};

/* Returns the calculated value of the volume of the box. */
float box::volume() {
	return (2 * ((myWidth * myLength) + (myWidth * myHeight) + (myLength * myHeight)));
};

/* Returns the calculated value of the area of the box. */
float box::area() {
	return (myWidth * myLength * myHeight);
};