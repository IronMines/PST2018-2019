/*
 * Tension.cpp
 *
 *  Created on: 11 févr. 2019
 *      Author: Sébastien
 */

#include "Tension.h"


Tension::Tension(int _pin)
: pin(_pin), tension(0)
{
	// TODO Auto-generated constructor stub
	pinMode(this->pin, INPUT);
}

Tension::~Tension() {
	// TODO Auto-generated destructor stub
}

float Tension::getTension(){
	return this->tension;
}

void Tension::calculTension(){
	int val = analogRead(this->pin);
	this->tension = 0.0f;//((float)val)*5f/1024f;
}
