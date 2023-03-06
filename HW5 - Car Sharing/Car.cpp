#include <iostream>
#include "Car.h"
using namespace std;

/*Constructs a Car object with initialization.*/
Car::Car(double fuelLevelValue, double insuranceFeeValue, int totalDistanceValue) : fuelLevel(fuelLevelValue), insuranceFee(insuranceFeeValue), totalDistance(totalDistanceValue) {}

/*Displays the fuel level, insurance fee, and total distance value of the car.*/
void Car::display() {
	cout << "Fuel Level: " << fuelLevel << endl;
	cout << "Insurance Fee: " << insuranceFee << endl;
	cout << "Total distance that the car has travelled: " << totalDistance << endl;
}

/*Returns the fuel level of the car.*/
double Car::getFuelLevel() {
	return fuelLevel;
}

/*Returns the insurance fee of the car.*/
double Car::getInsuranceFee() {
	return insuranceFee;
}

/*Returns the total distance taken by the car in total.*/
int Car::getTotalDistance() {
	return totalDistance;
}

/*Sets a new value to the fuel level of the car.*/
void Car::setFuelLevel(double newFuelLevel) {
	fuelLevel = newFuelLevel;
}

/*Sets a new value to the insurance fee of the car.*/
void Car::setInsuranceFee(double newInsuranceFee) {
	insuranceFee = newInsuranceFee;
}

/*Sets a new value to the total distance taken by the car in total.*/
void Car::setTotalDistance(int newTotalDistance) {
	totalDistance = newTotalDistance;
}
