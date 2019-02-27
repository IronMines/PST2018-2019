/*
 * Ultrason.cpp
 *
 *  Created on: 20 févr. 2019
 *      Author: Sébastien
 */

#include "Ultrason.h"


Ultrason::Ultrason(int _trigPin, int _echoPin)
: trigPin(_trigPin), echoPin(_echoPin), distance(0){
	// TODO Auto-generated constructor stub
	pinMode(this->trigPin, OUTPUT); // Sets the trigPin as an Output
	pinMode(this->echoPin, INPUT); // Sets the echoPin as an Input

}

Ultrason::~Ultrason() {
	// TODO Auto-generated destructor stub
}

void Ultrason::calculDistance(){
	unsigned long duration;
	// Clears the trigPin
	digitalWrite(this->trigPin, LOW);
	delayMicroseconds(2);
	// Sets the trigPin on HIGH state for 10 micro seconds
	digitalWrite(this->trigPin, HIGH);
	delayMicroseconds(10);
	digitalWrite(this->trigPin, LOW);
	// Reads the echoPin, returns the sound wave travel time in microseconds
	duration = pulseIn(this->echoPin, HIGH);
	// Calculating the distance
	this->distance= 10*duration*0.034/2;
}

int Ultrason::getDistance(){
	return this->distance;
}

String Ultrason::getDistanceToString(){
	char buffer[5];
	sprintf(buffer, "%d", this->getDistance());
	return buffer;
}


