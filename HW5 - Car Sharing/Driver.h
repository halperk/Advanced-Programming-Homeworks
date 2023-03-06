#ifndef DRIVER_H
#define DRIVER_H

#include "Car.h"
using namespace std;

class Driver {
private:
	double budget; /*Budget of driver.*/
	Car & car; /*Shared car object.*/

public:
	Driver(Car &, double); /*Constructs a Driver object with initialization.*/
	void drive(int); /*Executes necessary operations for driving of the car.*/
	void repairCar(string); /*Executes necessary operations to repair the car by the accident type.*/
	void display(); /*Displays the budget of the driver.*/
	void fullFuel(); /*Fulls the fuel level of the car.*/
};

#endif
