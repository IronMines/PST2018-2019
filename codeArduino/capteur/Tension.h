/*
 * Tension.h
 *
 *  Created on: 11 f�vr. 2019
 *      Author: S�bastien
 */
#import "arduino.h"
#ifndef Tension_H_
#define Tension_H_

class Tension {
public:
	Tension(int _pin);
	virtual ~Tension();

	void calculTension();
	float getTension();
private:
	int pin;
	float tension;
};


#endif /* Tension_H_ */
