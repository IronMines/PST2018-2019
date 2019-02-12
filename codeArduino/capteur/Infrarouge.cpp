/*
 * Infrarouge.cpp
 *
 *  Created on: 11 févr. 2019
 *      Author: Sébastien
 */

#include "Infrarouge.h"

Infrarouge::Infrarouge(int _pin)
: pin(_pin), distance(0)
{
	// TODO Auto-generated constructor stub
	pinMode(this->pin, INPUT);
}

Infrarouge::~Infrarouge() {
	// TODO Auto-generated destructor stub
}

void Infrarouge::calculDistance(){
	  int val = analogRead(this->pin);       // reads the value of the sharp sensor
	  this->distance = pow(3027.4/val, 1.2134)*10; //convert readings to distance(mm)
	  Serial.println(this->distance); //print the sensor value
}

int Infrarouge::getDistance(){
	return this->distance;
}
