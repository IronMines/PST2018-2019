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
	this->tension = ((float)val)*5.f/1024.f;
}
