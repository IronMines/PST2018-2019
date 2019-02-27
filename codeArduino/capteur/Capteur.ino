//#include "Arduino.h"
//The setup function is called once at startup of the sketch

#include <Wire.h>
#include "Infrarouge.h"
//#include "Tension.h"
#include "Ultrason.h"


//Adresse de l'esclave
#define SLAVE_ADDRESS 0x08

//Variable pour la laison i2c
bool orderReceveid=false;
char dataReceveid;
char actual = 0;
char *buffer;
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
//Tension tension(pinTension);


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
//
//	tension.calculTension();

//	Serial.print("distance Ultrason : ");
//	String str = UltrasonAvantDroit.getDistanceToString();
//	char buf[str.length()+1];
//	str.toCharArray(buf, str.length()+1);
//	Serial.println(buf);
//	Serial.print("distance Infrarouge : ");
//	Serial.println(InfrarougeAvantDroit.getDistance());

	delay(400);
}


void receiveData(int byteCount) {
	Serial.println("data received");
	if(Wire.available())
		dataReceveid = Wire.read();

	Serial.print("donnée :");
	Serial.println((int)dataReceveid);
	if((int)dataReceveid==5) {
		//On recoit toujours 5 octets s'il s'agit bien d'un ordre
		Serial.println("donnée recu");
		actual = 0;
		if (orderReceveid){
			//si on a recu un ordre
			free(buffer);
		}
		orderReceveid=true;
		buffer = (char *)calloc(6, sizeof(char));
	}
	else
	{
		if(orderReceveid){
			buffer[actual] = dataReceveid;
			actual ++;
		}
	}

	if(orderReceveid && actual == 5){
		//L'ordre est recu
		orderReceveid=false;
		Serial.print("buffer : ");
		Serial.println(buffer);
		/*
		 * Capteurs Ultrasons
		 */
		if(strcmp(buffer, "UAvDr")==0)
		{
			value = UltrasonAvantDroit.getDistance();
		}
		else if(strcmp(buffer, "UAvGa")==0)
		{
			value = UltrasonAvantGauche.getDistance();
		}
		else if(strcmp(buffer, "ULDAv")==0)
		{
			value = UltrasonLateralDroiteAvant.getDistance();
		}
		else if(strcmp(buffer, "ULDAr")==0)
		{
			value = UltrasonLateralDroiteArriere.getDistance();
		}
		else if(strcmp(buffer, "ULGAv")==0)
		{
			value = UltrasonLateralGaucheAvant.getDistance();
		}
		else if(strcmp(buffer, "ULGAr")==0)
		{
			value = UltrasonLateralGaucheArriere.getDistance();
		}
		else if(strcmp(buffer, "UArCe")==0)
		{
			value = UltrasonArriere.getDistance();
		}

		/*
		 * Capteurs Infrarouges
		 */

		else if(strcmp(buffer, "IAvDr")==0)
		{
			value = InfrarougeAvantDroit.getDistance();
		}
		else if(strcmp(buffer, "IAvGa")==0)
		{
			value = InfrarougeAvantGauche.getDistance();
		}
		else if(strcmp(buffer, "ILDAv")==0)
		{
			value = InfrarougeLateralDroiteAvant.getDistance();
		}
		else if(strcmp(buffer, "ILDAr")==0)
		{
			value = InfrarougeLateralDroiteArriere.getDistance();
		}
		else if(strcmp(buffer, "ILGAv")==0)
		{
			value = InfrarougeLateralGaucheAvant.getDistance();
		}
		else if(strcmp(buffer, "ILGAr")==0)
		{
			value = InfrarougeLateralGaucheArriere.getDistance();
		}
		else if(strcmp(buffer, "IArCe")==0)
		{
			value = InfrarougeArriere.getDistance();
		}

		/*
		 * Capteur de tension pour la batterie :
		 */

		else if(strcmp(buffer, "BaLvl")==0)
		{
			value = 2019;
		}

		else
		{
			//pas compris
		}
		Serial.print("valeur : ");
		Serial.println(value);
		free(buffer);
	}
}

void requestEvent(){
	Serial.println("request");
	int val1,val2;
	if (value>9999){
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
