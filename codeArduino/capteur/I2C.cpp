/*
 * I2C.cpp
 *
 *  Created on: 22 févr. 2019
 *      Author: Sébastien
 */

#include "I2C.h"

I2C::I2C()
: globalSize(0), actual(0), dataReceveid(0), buffer(){
	// TODO Auto-generated constructor stub

}

I2C::~I2C() {
	// TODO Auto-generated destructor stub
}

void I2C::receivedData(int byteCount)
{
	if(Wire.available()){
	    dataReceveid = Wire.read();
	  }
	  if(globalSize == 0) {
	    globalSize = dataReceveid;
	    actual = 0;
	    buffer = (char *)calloc(globalSize+1, sizeof(char));
	    buffer[globalSize] = '\0';
	  }
	  else
	  {
	    buffer[actual] = dataReceveid;
	    actual ++;
	  }

	  if(actual == globalSize){
		if(strcmp(buffer, "UAvDr")==0)
		{
			Serial.println("UAvDr");
			Wire.write(125);
		}
		else if(strcmp(buffer, "UAvGa")==0)
		{
			Serial.println("UAvGa");
			Wire.write(300);
		}
		else
		{
			//pas compris
		}
		globalSize = 0;
	  }
}
