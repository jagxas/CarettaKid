#include "colorsensorcode.h"


void ColorSensors::ColorSetup(int S3, int Out){
	pinMode(S3, OUTPUT);
	pinMode(Out, INPUT);
}

int ColorSensors::getRedPW(int S3, int Out){
	digitalWrite(S3, LOW);
	int PW = pulseIn(Out, LOW);
	return PW;
}

int ColorSensors::getBluePW(int S3, int Out){
	digitalWrite(S3, HIGH);
	int PW = pulseIn(Out, LOW);
	return PW;
}

int ColorSensors::ActualColorValue(int PW, int MaxVal, int MinVal){
  	
	int Value = map(PW, MaxVal, MinVal, 255, 0);
	delay(200);
	return Value;

}
