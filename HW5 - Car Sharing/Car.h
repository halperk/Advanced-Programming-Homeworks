#ifndef CAR_H
#define CAR_H

class Car {
private:
	double fuelLevel; /*Fuel level of the car.*/
	double insuranceFee; /*Annual insurance fee of the car.*/
	int totalDistance; /*Total distance taken by the car.*/

public:
	Car(double, double, int); /*Constructs a Car object with initialization.*/
	void display(); /*Displays the fuel level, insurance fee, and total distance value of the car.*/
	double getFuelLevel(); /*Returns the fuel level of the car.*/
	double getInsuranceFee(); /*Returns the insurance fee of the car.*/
	int getTotalDistance(); /*Returns the total distance taken by the car in total.*/
	void setFuelLevel(double); /*Sets a new value to the fuel level of the car.*/
	void setInsuranceFee(double); /*Sets a new value to the insurance fee of the car.*/
	void setTotalDistance(int); /*Sets a new value to the total distance taken by the car in total.*/
};

#endif
