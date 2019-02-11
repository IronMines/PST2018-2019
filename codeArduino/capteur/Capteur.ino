#include "Arduino.h"
//The setup function is called once at startup of the sketch

#include <Wire.h>
#include "Infrarouge.h"
#include "Tension.h"
#include "Ultrasons.h"

//analog pin
const int pinInfrarougeAvantDroit = A0;
const int pinInfrarougeAvantGauche = A1;
const int pinInfrarougeLatéralDroiteAvant = A2;
const int pinInfrarougeLatéralDroiteArriere = A3;
const int pinInfrarougeLatéralGaucheAvant = A4;
const int pinInfrarougeLatéralGaucheArriere = A5;
const int pinInfrarougeArriere = A6;

const int pinTension = A7 ;

//digital pin
const int echoPinUltrasonsAvantDroit = 22;
const int trigPinUltrasonsAvantDroit = 23;
const int echoPinUltrasonsAvantGauche = 24;
const int trigPinUltrasonsAvantGauche = 25;
const int echoPinUltrasonsLatéralDroiteAvant = 26;
const int trigPinUltrasonsLatéralDroiteAvant = 27;
const int echoPinUltrasonsLatéralDroiteArriere = 28;
const int trigPinUltrasonsLatéralDroiteArriere = 29;
const int echoPinUltrasonsLatéralGaucheAvant = 30;
const int trigPinUltrasonsLatéralGaucheAvant = 31;
const int echoPinUltrasonsLatéralGaucheArriere = 32;
const int trigPinUltrasonsLatéralGaucheArriere = 33;
const int echoPinUltrasonsArriere = 34;
const int trigPinUltrasonsArriere = 35;

//Initialize
Infrarouge InfrarougeAvantDroit (pinInfrarougeAvantDroit);
Infrarouge InfrarougeAvantGauche (pinInfrarougeAvantGauche);
Infrarouge InfrarougeLatéralDroiteAvant (pinInfrarougeLatéralDroiteAvant);
Infrarouge InfrarougeLatéralDroiteArriere (pinInfrarougeLatéralDroiteArriere);
Infrarouge InfrarougeLatéralGaucheAvant (pinInfrarougeLatéralGaucheAvant);
Infrarouge InfrarougeLatéralGaucheArriere (pinInfrarougeLatéralGaucheArriere);
Infrarouge InfrarougeArriere (pinInfrarougeArriere);

Ultrasons UltrasonsAvantDroit (trigPinUltrasonsAvantDroit, echoPinUltrasonsAvantDroit);
Ultrasons UltrasonsAvantGauche (trigPinUltrasonsAvantGauche, echoPinUltrasonsAvantGauche);
Ultrasons UltrasonsLatéralDroiteAvant (trigPinUltrasonsLatéralDroiteAvant, echoPinUltrasonsLatéralDroiteAvant);
Ultrasons UltrasonsLatéralDroiteArriere (trigPinUltrasonsLatéralDroiteArriere, echoPinUltrasonsLatéralDroiteArriere);
Ultrasons UltrasonsLatéralGaucheAvant (trigPinUltrasonsLatéralGaucheAvant, echoPinUltrasonsLatéralGaucheAvant);
Ultrasons UltrasonsLatéralGaucheArriere (trigPinUltrasonsLatéralGaucheArriere, echoPinUltrasonsLatéralGaucheArriere);
Ultrasons UltrasonsArriere (trigPinUltrasonsArriere, echoPinUltrasonsArriere );

Tension tension(pinTension);

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
	InfrarougeAvantDroit.calculDistance();
	InfrarougeAvantGauche.calculDistance();
	InfrarougeLatéralDroiteAvant.calculDistance();
	InfrarougeLatéralDroiteArriere.calculDistance();
	InfrarougeLatéralGaucheAvant.calculDistance();
	InfrarougeLatéralGaucheArriere.calculDistance();
	InfrarougeArriere.calculDistance();

	UltrasonsAvantDroit.calculDistance();
	UltrasonsAvantGauche.calculDistance();
	UltrasonsLatéralDroiteAvant.calculDistance();
	UltrasonsLatéralDroiteArriere.calculDistance();
	UltrasonsLatéralGaucheAvant.calculDistance();
	UltrasonsLatéralGaucheArriere.calculDistance();
	UltrasonsArriere.calculDistance();

	tension.calculTension();

	delay(100);
}

// function that executes whenever data is requested by master
// this function is registered as an event, see setup()
void requestEvent() {
  Wire.write("hello ");
  // respond with message of 6 bytes
  // as expected by master
}
