/*
 * Tension.cpp
 *
 *  Created on: 11 f�vr. 2019
 *      Author: S�bastien
 */

#include "Tension.h"


Tension::Tension(int _pin)
: pin(_pin), Tension(0)
{
	// TODO Auto-generated constructor stub

}

Tension::~Tension() {
	// TODO Auto-generated destructor stub
}

float Tension::getTension(){
	return this->tension;
}

void Tension::calculTension(){

}
