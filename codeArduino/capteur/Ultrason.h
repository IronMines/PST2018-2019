/*
 * Ultrason.h
 *
 *  Created on: 20 f�vr. 2019
 *      Author: S�bastien
 */

#ifndef Ultrason_H_
#define Ultrason_H_
#import "arduino.h"


class Ultrason {
public:
	Ultrason(int _trigPin, int _echoPin);
	virtual ~Ultrason();

	void calculDistance();
	int getDistance();
	String getDistanceToString();
private:
	int trigPin;
	int echoPin;
	int distance;
};

#endif /* Ultrason_H_ */
