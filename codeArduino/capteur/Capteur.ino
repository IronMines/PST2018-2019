//#include "Arduino.h"
//The setup function is called once at startup of the sketch

#include <Wire.h>
#include "Infrarouge.h"
#include "Tension.h"
#include "Ultrason.h"


//Adresse de l'esclave
#define SLAVE_ADDRESS 0x08

//Variable pour la laison i2c
char dataReceveid;
int value;

//analog pin
const int pinInfrarougeAvantDroit = A0;
const int pinInfrarougeAvantGauche = A1;
const int pinInfrarougeLateralDroiteAvant = A2;
const int pinInfrarougeLateralDroiteArriere = A3;
const int pinInfrarougeLateralGaucheAvant = A4;
const int pinInfrarougeLateralGaucheArriere = A5;
const int pinInfrarougeArriere = A6;

const int pinTension = A7 ;

////digital pin
const int echoPinUltrasonAvantDroit = 53;
const int trigPinUltrasonAvantDroit = 52;
const int echoPinUltrasonLateralDroiteArriere = 50;
const int trigPinUltrasonLateralDroiteArriere = 51;
const int echoPinUltrasonLateralDroiteAvant = 48;
const int trigPinUltrasonLateralDroiteAvant = 49;
const int echoPinUltrasonArriere = 46;
const int trigPinUltrasonArriere = 47;
const int echoPinUltrasonLateralGaucheArriere = 44;
const int trigPinUltrasonLateralGaucheArriere = 45;
const int echoPinUltrasonLateralGaucheAvant = 42;
const int trigPinUltrasonLateralGaucheAvant = 43;
const int echoPinUltrasonAvantGauche = 40;
const int trigPinUltrasonAvantGauche = 41;

//Initialize
Infrarouge InfrarougeAvantDroit (pinInfrarougeAvantDroit);
Infrarouge InfrarougeAvantGauche (pinInfrarougeAvantGauche);
Infrarouge InfrarougeLateralDroiteAvant (pinInfrarougeLateralDroiteAvant);
Infrarouge InfrarougeLateralDroiteArriere (pinInfrarougeLateralDroiteArriere);
Infrarouge InfrarougeLateralGaucheAvant (pinInfrarougeLateralGaucheAvant);
Infrarouge InfrarougeLateralGaucheArriere (pinInfrarougeLateralGaucheArriere);
Infrarouge InfrarougeArriere (pinInfrarougeArriere);
//
Ultrason UltrasonAvantDroit (trigPinUltrasonAvantDroit, echoPinUltrasonAvantDroit);
Ultrason UltrasonAvantGauche (trigPinUltrasonAvantGauche, echoPinUltrasonAvantGauche);
Ultrason UltrasonLateralDroiteAvant (trigPinUltrasonLateralDroiteAvant, echoPinUltrasonLateralDroiteAvant);
Ultrason UltrasonLateralDroiteArriere (trigPinUltrasonLateralDroiteArriere, echoPinUltrasonLateralDroiteArriere);
Ultrason UltrasonLateralGaucheAvant (trigPinUltrasonLateralGaucheAvant, echoPinUltrasonLateralGaucheAvant);
Ultrason UltrasonLateralGaucheArriere (trigPinUltrasonLateralGaucheArriere, echoPinUltrasonLateralGaucheArriere);
Ultrason UltrasonArriere (trigPinUltrasonArriere, echoPinUltrasonArriere );
//
Tension tension(pinTension);


void setup() {
  Serial.begin(9600);
  Wire.begin(SLAVE_ADDRESS);
  Wire.onReceive(receiveData);
  Wire.onRequest(requestEvent);
}

void loop() {
	InfrarougeAvantDroit.calculDistance();
	InfrarougeAvantGauche.calculDistance();
	InfrarougeLateralDroiteAvant.calculDistance();
	InfrarougeLateralDroiteArriere.calculDistance();
	InfrarougeLateralGaucheAvant.calculDistance();
	InfrarougeLateralGaucheArriere.calculDistance();
	InfrarougeArriere.calculDistance();

	UltrasonAvantDroit.calculDistance();
	UltrasonAvantGauche.calculDistance();
	UltrasonLateralDroiteAvant.calculDistance();
	UltrasonLateralDroiteArriere.calculDistance();
	UltrasonLateralGaucheAvant.calculDistance();
	UltrasonLateralGaucheArriere.calculDistance();
	UltrasonArriere.calculDistance();

	delay(400);
}


void receiveData(int byteCount) {
	Serial.println("data received");
	if(Wire.available())
		dataReceveid = Wire.read();

	Serial.print("Adresse Reg :");
	Serial.println((int)dataReceveid);
	if((int)dataReceveid==0x10)
	{
		value = UltrasonAvantDroit.getDistance();
	}
	else if((int)dataReceveid==0x11)
	{
		value = UltrasonAvantGauche.getDistance();
	}
	else if((int)dataReceveid==0x12)
	{
		value = UltrasonLateralDroiteAvant.getDistance();
	}
	else if((int)dataReceveid==0x13)
	{
		value = UltrasonLateralDroiteArriere.getDistance();
	}
	else if((int)dataReceveid==0x14)
	{
		value = UltrasonLateralGaucheAvant.getDistance();
	}
	else if((int)dataReceveid==0x15)
	{
		value = UltrasonLateralGaucheArriere.getDistance();
	}
	else if((int)dataReceveid==0x16)
	{
		value = UltrasonArriere.getDistance();
	}

	/*
	 * Capteurs Infrarouges
	 */

	else if((int)dataReceveid==0x20)
	{
		value = InfrarougeAvantDroit.getDistance();
	}
	else if((int)dataReceveid==0x21)
	{
		value = InfrarougeAvantGauche.getDistance();
	}
	else if((int)dataReceveid==0x22)
	{
		value = InfrarougeLateralDroiteAvant.getDistance();
	}
	else if((int)dataReceveid==0x23)
	{
		value = InfrarougeLateralDroiteArriere.getDistance();
	}
	else if((int)dataReceveid==0x24)
	{
		value = InfrarougeLateralGaucheAvant.getDistance();
	}
	else if((int)dataReceveid==0x25)
	{
		value = InfrarougeLateralGaucheArriere.getDistance();
	}
	else if((int)dataReceveid==0x26)
	{
		value = InfrarougeArriere.getDistance();
	}

	/*
	 * Capteur de tension pour la batterie :
	 */

	else if((int)dataReceveid==0x30)
	{
		value = 2019;
	}

	else
	{
		//pas compris
	}
}

void requestEvent(){
	Serial.println("request");
	int val1,val2;
	if (value>9999 || value == 0){
		//valeur trop grande
		val1=255;
		val2=255;
	}
	else{
		val1=value/100;
		val2=value%100;
	}
	Serial.print(val1);
	Serial.println(val2);
	Wire.write(val2);
	Wire.write(val1);
	value = 0;
}
