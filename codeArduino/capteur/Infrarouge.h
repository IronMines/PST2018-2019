/*
 * Infrarouge.h
 *
 *  Created on: 11 févr. 2019
 *      Author: Sébastien
 */

#ifndef INFRAROUGE_H_
#define INFRAROUGE_H_
#import "arduino.h"

class Infrarouge {
public:
	Infrarouge(int _pin);
	virtual ~Infrarouge();

	int getDistance();
	void calculDistance();
private:
	int pin;                 // analog pin used to connect the sharp sensor
	int distance;			 // in millimeters
};


#endif /* INFRAROUGE_H_ */
