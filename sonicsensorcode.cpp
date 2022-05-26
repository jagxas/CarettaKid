#include "sonicsensorcode.hpp"
#include "peripherals.hpp"

Sonic::Sonic(int EchoPin, int TrigPin) : pin_echo(EchoPin), pin_trig(TrigPin) {

}

void Sonic::setup() {
  pinMode(pin_trig, OUTPUT);
  pinMode(pin_echo, INPUT);
}

double Sonic::distance(){
  double Time=0.0, Distance=0.0;
  digitalWrite(pin_trig,LOW);
  delayMicroseconds(2);
  digitalWrite(pin_trig,HIGH);
  delayMicroseconds(10);
  digitalWrite(pin_trig,LOW);
  Time = pulseIn(pin_echo,HIGH);
  Distance = Time / 58.2;
  delay(50);
  
  if(Distance>=DISTANCE_MAX || Distance<=DISTANCE_MIN){
    return 0;
  }
  else{
    return Distance;
  }

}
