#include <Arduino.h>
#include <Servo.h>
#include "peripherals.hpp"
#include "constants.hpp"
#include "servos.hpp"

static Servo PuckServo;
static Servo OpenCloseServo;

int Servos::our_count = 0;
int Servos::rival_count = 0;
bool rival_taking = false;
bool ours_taking = false;

void Servos::setup_servos() {
    PuckServo.attach(PIN_SERVO1);
    OpenCloseServo.attach(PIN_SERVO2);
}

void Servos::S1::take_rival() {
    rival_taking = true;
    PuckServo.write(WRONG_PUCK_ANGLE);
}

void Servos::S1::take_ours() {
    ours_taking = true;
    PuckServo.write(CORRECT_PUCK_ANGLE);
}

void Servos::S1::finish_taking() {
    if (ours_taking) {
        ours_taking = false;
        our_count++;
    }
    if (rival_taking) {
        rival_taking = false;
        rival_count++;
    }
}

void Servos::S2::open() {
    OpenCloseServo.write(OPEN_ANGLE);
    our_count = 0;
}

void Servos::S2::close() {
    OpenCloseServo.write(CLOSE_ANGLE);
}