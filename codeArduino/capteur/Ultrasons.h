/*
 * Ultrasons.h
 *
 *  Created on: 11 f�vr. 2019
 *      Author: S�bastien
 */
#import "arduino.h"
#ifndef ULTRASONS_H_
#define ULTRASONS_H_


class Ultrasons {
public:
	Ultrasons(int _trigPin, int _echoPin);
	virtual ~Ultrasons();

	int getDistance();
	void calculDistance();
private:
	// defines pins numbers
	int trigPin;
	int echoPin;
	// defines variables
	long duration;
	int distance;
};


#endif /* ULTRASONS_H_ */
