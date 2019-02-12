/*
 * Tension.h
 *
 *  Created on: 11 f�vr. 2019
 *      Author: S�bastien
 */

#ifndef Tension_H_
#define Tension_H_
#import "arduino.h"

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
