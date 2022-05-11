#include "sonicsensorcode.h"

void Sonic::SetupSonic(int EchoPin, int TrigPin) {
  pinMode(TrigPin,OUTPUT);
  pinMode(EchoPin,INPUT);
  Serial.begin(9600); 
}

double Sonic::CalculateDistance(double Max, double Min, int SensorPin, int EchoTrigPin){
  double Time=0.0, Distance=0.0;
  digitalWrite(EchoTrigPin,LOW);
  delayMicroseconds(2);
  digitalWrite(EchoTrigPin,HIGH);
  delayMicroseconds(10);
  digitalWrite(EchoTrigPin,LOW);
  Time = pulseIn(SensorPin,HIGH);
  Distance = Time / 58.2;
  delay(50);
  
  
  if(Distance>=Max || Distance<=Min){
    return 0;
  }
  else{
    return Distance;
  }
  
  
}
