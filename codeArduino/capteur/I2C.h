/*
 * I2C.h
 *
 *  Created on: 22 f�vr. 2019
 *      Author: S�bastien
 */

#ifndef I2C_H_
#define I2C_H_

#include "string.h"
#include "Arduino.h"
#include <Wire.h>

class I2C {
public:
	I2C();
	virtual ~I2C();
    void receivedData(int byteCount);
    void test();

private:
    char dataReceveid;
    unsigned char globalSize;
    unsigned char actual;
    char * buffer;

};

#endif /* I2C_H_ */
