#include "TwoDShapes.h"

/* Returns volume as zero since it is a 2D shape so that doesn't have a volume at all. */
float TwoDShape::volume() {
	return 0;
};

/* Returns the calculated value of the perimeter of the rectangle. */
float rectangle::perimeter() {
	return (2 * (myWidth + myLength));
};

/* Returns the calculated value of the area of the rectangle. */
float rectangle::area() {
	return (myWidth * myLength);
};