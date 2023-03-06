/*******************************************

CS 204 (Fall 2021-2022)
Homework #7 - Geometrical shapes (inheritance and polymorphism)
Huseyin Alper Karadeniz (28029)
Date: 12/27/2021
Last Update: 01/05/2022

P.S. Main function is taken from Artrim Kjamilji.

********************************************/

#include <iostream>
#include <string>
#include "Shape.h"
#include "TwoDShapes.h"
#include "ThreeDShapes.h"
using namespace std;

shape * getShape() { /* A function that gets some shape details and by creating necessary shape, returns it. */
	/* Gets the shape option from the user whether rectangle, or box. */
	char option;
	cout << "Choose an option <1 or 2>:" << endl
		 << "1. Rectangle" << endl
		 << "2. Box" << endl;
	cin >> option;

	/* Executes necessary operations for the opted shape by getting more details. */
	string name;
	float width = 0, length = 0, height = 0;
	if (option == '1') { /* Detects if rectangle is opted by the user. */
		cout << "You chose rectangle. Give it's width, length, and name." << endl;
		cin >> width >> length >> name; /* Gets details of rectangle. */
		rectangle * rectangleResult = new rectangle(width,length,name); /* Creates a rectangle pointer object. */
		return rectangleResult; /* Returns the rectangle pointer created in the previous line. */
	} else if (option == '2') { /* Detects if box is opted by the user. */
		cout << "You chose box. Give it's width, length, height and name." << endl;
		cin >> width >> length >> height >> name; /* Gets details of box. */
		box * boxResult = new box(width,length,height,name); /* Creates a box pointer object. */
		return boxResult; /* Returns the box pointer created in the previous line. */
	}
}

int main()
{ /* The main function of this program is taken from Artrim Kjamilji. */
	cout << "WELCOME TO THE SHAPE COMPARISONN PROGRAM" << endl;
	cout << "FOR EXITIING PRESS Y/y, OTHERWISE PRESS ANY KEY" << endl;
	shape * shape_1, * shape_2;
	char c;
	while (tolower(c = getchar()) != 'y') {
		cout << "Defining (getting) shape 1..." << endl;
		shape_1 = getShape();
		cout << "Defining (getting) shape 2..." << endl;
		shape_2 = getShape();
		cout << "********************************************************************" << endl;
		cout << "PRINTING SHAPE_1 INFOS:" << endl << "Name: " << shape_1->getName() << ", perimeter: "
			<< shape_1->perimeter() << ", area: " << shape_1->area() << ", volume: " << shape_1->volume() << endl << endl;
		cout << "PRINTING SHAPE_2 INFOS:" << endl << "Name: " << shape_2->getName() << ", perimeter: "
			<< shape_2->perimeter() << ", area: " << shape_2->area() << ", volume: " << shape_2->volume() << endl;		
		bool nothingInCommon = true; /* Checks whether they have anything in common (perimeter, area, volume). */
		if(shape_1->perimeter() == shape_2->perimeter()) {
			nothingInCommon = false;
			cout << shape_1->getName() << " and " << shape_2->getName() << " have the same perimeter, which is: " << shape_1->perimeter() << " cm." << endl;
		}
		if(shape_1->area()==shape_2->area()) {
			nothingInCommon = false;
			cout << shape_1->getName() << " and " << shape_2->getName() << " have the same area, which is: " << shape_1->area() << " cm^2." << endl;
		}
		if(shape_1->volume()==shape_2->volume()) {
			nothingInCommon = false;
			cout << shape_1->getName() << " and " << shape_2->getName() << " have the same volume, which is: " << shape_1->volume() << " cm^3." << endl;
		}
		if (nothingInCommon)
			cout << shape_1->getName() << " and " << shape_2->getName() << " don't have anything in common." << endl;
			
		delete shape_1;
		delete shape_2;

		cout << "********************************************************************" << endl;
		cout << "FOR EXITIING PRESS Y/y, OTHERWISE, FOR ANOTHER COMPARISON PRESS ANY KEY" << endl << endl;
		cin.ignore(); /* Flush the buffer for remaining character(s), in order getchar() to work. */
  	}
	cout << "PROGRAM EXITING. THANKS FOR USING IT." << endl;
	system("pause");
	return 0;
}