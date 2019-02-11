#include "Arduino.h"
//The setup function is called once at startup of the sketch

#include <Wire.h>
#include "Infrarouge.h"
#include "Tension.h"
#include "Ultrasons.h"

//analog pin
const int pinInfrarougeAvantDroit = A0;
const int pinInfrarougeAvantGauche = A1;
const int pinInfrarougeLat�ralDroiteAvant = A2;
const int pinInfrarougeLat�ralDroiteArriere = A3;
const int pinInfrarougeLat�ralGaucheAvant = A4;
const int pinInfrarougeLat�ralGaucheArriere = A5;
const int pinInfrarougeArriere = A6;

const int pinTension = A7 ;

//digital pin
const int echoPinUltrasonsAvantDroit = 22;
const int trigPinUltrasonsAvantDroit = 23;
const int echoPinUltrasonsAvantGauche = 24;
const int trigPinUltrasonsAvantGauche = 25;
const int echoPinUltrasonsLat�ralDroiteAvant = 26;
const int trigPinUltrasonsLat�ralDroiteAvant = 27;
const int echoPinUltrasonsLat�ralDroiteArriere = 28;
const int trigPinUltrasonsLat�ralDroiteArriere = 29;
const int echoPinUltrasonsLat�ralGaucheAvant = 30;
const int trigPinUltrasonsLat�ralGaucheAvant = 31;
const int echoPinUltrasonsLat�ralGaucheArriere = 32;
const int trigPinUltrasonsLat�ralGaucheArriere = 33;
const int echoPinUltrasonsArriere = 34;
const int trigPinUltrasonsArriere = 35;

//Initialize
Infrarouge InfrarougeAvantDroit (pinInfrarougeAvantDroit);
Infrarouge InfrarougeAvantGauche (pinInfrarougeAvantGauche);
Infrarouge InfrarougeLat�ralDroiteAvant (pinInfrarougeLat�ralDroiteAvant);
Infrarouge InfrarougeLat�ralDroiteArriere (pinInfrarougeLat�ralDroiteArriere);
Infrarouge InfrarougeLat�ralGaucheAvant (pinInfrarougeLat�ralGaucheAvant);
Infrarouge InfrarougeLat�ralGaucheArriere (pinInfrarougeLat�ralGaucheArriere);
Infrarouge InfrarougeArriere (pinInfrarougeArriere);

Ultrasons UltrasonsAvantDroit (trigPinUltrasonsAvantDroit, echoPinUltrasonsAvantDroit);
Ultrasons UltrasonsAvantGauche (trigPinUltrasonsAvantGauche, echoPinUltrasonsAvantGauche);
Ultrasons UltrasonsLat�ralDroiteAvant (trigPinUltrasonsLat�ralDroiteAvant, echoPinUltrasonsLat�ralDroiteAvant);
Ultrasons UltrasonsLat�ralDroiteArriere (trigPinUltrasonsLat�ralDroiteArriere, echoPinUltrasonsLat�ralDroiteArriere);
Ultrasons UltrasonsLat�ralGaucheAvant (trigPinUltrasonsLat�ralGaucheAvant, echoPinUltrasonsLat�ralGaucheAvant);
Ultrasons UltrasonsLat�ralGaucheArriere (trigPinUltrasonsLat�ralGaucheArriere, echoPinUltrasonsLat�ralGaucheArriere);
Ultrasons UltrasonsArriere (trigPinUltrasonsArriere, echoPinUltrasonsArriere );

Tension tension(pinTension);

void setup() {
  Wire.begin(8);                // join i2c bus with address #8
  Wire.onRequest(requestEvent); // register event
}

void loop() {
	InfrarougeAvantDroit.calculDistance();
	InfrarougeAvantGauche.calculDistance();
	InfrarougeLat�ralDroiteAvant.calculDistance();
	InfrarougeLat�ralDroiteArriere.calculDistance();
	InfrarougeLat�ralGaucheAvant.calculDistance();
	InfrarougeLat�ralGaucheArriere.calculDistance();
	InfrarougeArriere.calculDistance();

	UltrasonsAvantDroit.calculDistance();
	UltrasonsAvantGauche.calculDistance();
	UltrasonsLat�ralDroiteAvant.calculDistance();
	UltrasonsLat�ralDroiteArriere.calculDistance();
	UltrasonsLat�ralGaucheAvant.calculDistance();
	UltrasonsLat�ralGaucheArriere.calculDistance();
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
