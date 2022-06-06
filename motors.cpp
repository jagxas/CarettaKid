#include "motors.hpp"
#include "constants.hpp"
Motors::Motors(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S) : pin_m1f(M1F), pin_m1b(M1B), pin_m2f(M2F), pin_m2b(M2B), pin_m1s(M1S), pin_m2s(M2S) {
}

void Motors::setup() {
	pinMode(pin_m1f, OUTPUT);
	pinMode(pin_m1b, OUTPUT);

	pinMode(pin_m2f, OUTPUT);
	pinMode(pin_m2b, OUTPUT);

	pinMode(pin_m1s, OUTPUT);
	pinMode(pin_m2s, OUTPUT);
}

void Motors::go(){
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m1b, LOW);
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m2b, LOW);

	analogWrite(pin_m1s, CRUISE_SPEED_M1);
	analogWrite(pin_m2s, CRUISE_SPEED_M2);
}

void Motors::turn_right(){
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m1b, LOW);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, LOW);

	analogWrite(pin_m1s, TURNING_SPEED);
	delay(500);
}

void Motors::step_back(){
	digitalWrite(pin_m1f, LOW);
	digitalWrite(pin_m1b, HIGH);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, HIGH);

	analogWrite(pin_m1s, CRUISE_SPEED_M1);
	analogWrite(pin_m2s, CRUISE_SPEED_M2);
	delay(500);
}
