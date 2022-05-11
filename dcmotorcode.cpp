#include "dcmotorcode.h"

void DC::DCSetup(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S){
	pinMode(M1F, OUTPUT);
	pinMode(M2B, OUTPUT);
	pinMode(M1B, OUTPUT);
	pinMode(M2F, OUTPUT);
	pinMode(M1S, OUTPUT);
	pinMode(M2S, OUTPUT);
}

void DC::go(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int CruiseSpeed){
	digitalWrite(M1F, HIGH);
	digitalWrite(M1B, LOW);
	digitalWrite(M2F, HIGH);
	digitalWrite(M2B, LOW);
	
	digitalWrite(M1S, CruiseSpeed);
	digitalWrite(M2S, CruiseSpeed);	
}

void DC::turnRight(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int TurningSpeed){
	digitalWrite(M1F, HIGH);
	digitalWrite(M1B, LOW);
	digitalWrite(M2F, LOW);
	digitalWrite(M2B, LOW);
	
	digitalWrite(M1S, TurningSpeed);
	delay(500); 	
}

void DC::stepBack(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int Speed){
	digitalWrite(M1F, LOW);
	digitalWrite(M1B, HIGH);
	digitalWrite(M2F, LOW);
	digitalWrite(M2B, HIGH);
	
	digitalWrite(M1S, Speed);
	digitalWrite(M2S, Speed);	
	delay(500);
}
