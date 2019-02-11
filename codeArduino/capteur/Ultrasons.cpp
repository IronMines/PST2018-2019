/*
 * Ultrasons.cpp
 * Ultrasonic Sensor HC-SR04
 *  Created on: 11 févr. 2019
 *      Author: Sébastien
 */

#include "Ultrasons.h"


Ultrasons::Ultrasons(int _trigPin, int _echoPin)
: trigPin(_trigPin), echoPin(_echoPin), duration(0), distance(0)
{
	pinMode(this->trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(this->echoPin, INPUT); // Sets the echoPin as an Input
	Serial.begin(9600); // Starts the serial communication

}

Ultrasons::~Ultrasons() {
	// TODO Auto-generated destructor stub
}

void Ultrasons::calculDistance(){
	// Clears the trigPin
	digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	this->duration = pulseIn(this->echoPin, HIGH);
	// Calculating the distance
	this->distance= this->duration*0.034/2;
	// Prints the distance on the Serial Monitor
	Serial.print("Distance: ");
	Serial.println(distance);
}

int Ultrasons::getDistance(){
	return this->distance;
}
