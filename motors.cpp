#include "motors.hpp"
#include "constants.hpp"
#include "sonic.hpp"
#include "peripherals.hpp"

Motors::Motors(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S) : pin_m1f(M1F), pin_m1b(M1B), pin_m2f(M2F), pin_m2b(M2B), pin_m1s(M1S), pin_m2s(M2S) {
	
}

Sonic RightSonic(PIN_SONIC_RIGHT_ECHO, PIN_SONIC_RIGHT_TRIG);
Sonic LeftSonic(PIN_SONIC_LEFT_ECHO, PIN_SONIC_LEFT_TRIG);

void Motors::setup() {
	pinMode(pin_m1f, OUTPUT);
	pinMode(pin_m1b, OUTPUT);

	pinMode(pin_m2f, OUTPUT);
	pinMode(pin_m2b, OUTPUT);
	
	pinMode(pin_m1s, OUTPUT);
	pinMode(pin_m2s, OUTPUT);

  RightSonic.setup();
  LeftSonic.setup();

}


void Motors::go_around(){
  double DistanceR = RightSonic.distance();
  double DistanceL = LeftSonic.distance();

  if(DistanceR > 10 && DistanceL > 10){
    digitalWrite(pin_m1f, HIGH);
    digitalWrite(pin_m1b, LOW);
    digitalWrite(pin_m1f, HIGH);
    digitalWrite(pin_m2b, LOW);
  
    digitalWrite(pin_m1s, CRUISE_SPEED);
    digitalWrite(pin_m2s, CRUISE_SPEED);  
    delay(100);
  }
  if(DistanceR < 10 && DistanceL < 10){
    step_back();
    delay(100);
    turn_right();
    delay(400);
  }
}

void Motors::turn_right(){
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m1b, LOW);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, LOW);
	
	digitalWrite(pin_m1s, TURNING_SPEED);	
}

void Motors::step_back(){
	digitalWrite(pin_m1f, LOW);
	digitalWrite(pin_m1b, HIGH);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, HIGH);
	
	digitalWrite(pin_m1s, CRUISE_SPEED);
	digitalWrite(pin_m2s, CRUISE_SPEED);	
}

void Motors::follow_the_walls(){
  double DistanceR = RightSonic.distance();
  double DistanceL = LeftSonic.distance();

  if(DistanceR > 10 && DistanceL > 10){
    digitalWrite(pin_m1f, HIGH);
    digitalWrite(pin_m1b, LOW);
    digitalWrite(pin_m1f, HIGH);
    digitalWrite(pin_m2b, LOW);
  
    digitalWrite(pin_m1s, CRUISE_SPEED);
    digitalWrite(pin_m2s, CRUISE_SPEED);  
    delay(100);
  }
  
  if(DistanceR < 10 && DistanceL < 10){
    step_back();
    delay(100);
    turn_right();
    delay(200);
  }
  
}
