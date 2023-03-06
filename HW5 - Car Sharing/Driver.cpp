#include <iostream>
#include <string>
#include "Driver.h"
using namespace std;

/*Constructs a Driver object with initialization.*/
Driver::Driver(Car & sharedCar, double initialBudget) : car(sharedCar), budget(initialBudget) {}

/*Executes necessary operations for driving of the car, decreases the car's fuel level and increases its total distance.*/
void Driver::drive(int distance) {
	car.setFuelLevel(car.getFuelLevel() - (distance * 0.25)); /*Decreases the car's fuel level.*/
	car.setTotalDistance(car.getTotalDistance() + distance); /*Increases the car's total distance.*/
}

/*Executes necessary operations to repair the car by the accident type.*/
void Driver::repairCar(string accidentType) {
    double newInsuranceFee;
	if(accidentType == "SMALL") {
		/*If the accident type is SMALL, executes accordingly.*/
		budget -= 50; /*Decreases the driver's budget $50.*/
		cout << "50$ is reduced from the driver's budget because of the SMALL accident" << endl;
        newInsuranceFee = car.getInsuranceFee() * 1.05;
		car.setInsuranceFee(newInsuranceFee); /*Increases the car's insurance fee 5%.*/
		cout << "Yearly insurance fee is increased to " << newInsuranceFee << " because of the SMALL accident" << endl;
	} else if(accidentType == "MEDIUM") {
		/*If the accident type is MEDIUM, executes accordingly.*/
		budget -= 150; /*Decreases the driver's budget $150.*/
		cout << "150$ is reduced from the driver's budget because of the MEDIUM accident" << endl;
		newInsuranceFee = car.getInsuranceFee() * 1.1;
		car.setInsuranceFee(newInsuranceFee); /*Increases the car's insurance fee 10%.*/
		cout << "Yearly insurance fee is increased to " << newInsuranceFee << " because of the MEDIUM accident" << endl;
	} else if(accidentType == "LARGE") {
		/*If the accident type is LARGE, executes accordingly.*/
		budget -= 300; /*Decreases the driver's budget $300.*/
		cout << "300$ is reduced from the driver's budget because of the LARGE accident" << endl;
		newInsuranceFee = car.getInsuranceFee() * 1.2;
		car.setInsuranceFee(newInsuranceFee); /*Increases the car's insurance fee 20%.*/
		cout << "Yearly insurance fee is increased to " << newInsuranceFee << " because of the LARGE accident" << endl;
	}
}

/*Displays the budget of the driver.*/
void Driver::display() {
	cout << endl << "Driver Budget: " << budget << endl;
}

/*Fulls the fuel level of the car, and decreases the budget of the driver accordingly.*/
void Driver::fullFuel() {
	budget -= (300.0 - car.getFuelLevel()); /*Decreases the budget of the driver to full the car's fuel level.*/
	car.setFuelLevel(300.0); /*Fulls the car's fuel level.*/
	cout << endl << "Fuel is full" << endl;
}
