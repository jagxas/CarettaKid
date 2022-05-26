#include <Arduino.h>
#include <Servo.h>
#include "peripherals.hpp"
#include "constants.hpp"
#include "servos.hpp"

static Servo PuckServo;
static Servo OpenCloseServo;

void Servos::setup_servos() {
    PuckServo.attach(PIN_SERVO1);
    OpenCloseServo.attach(PIN_SERVO2);
}

void Servos::S1::dont_take_it() {
    PuckServo.write(WRONG_PUCK_ANGLE);
}

void Servos::S1::take_it() {
    PuckServo.write(CORRECT_PUCK_ANGLE);
}

void Servos::S2::open() {
    OpenCloseServo.write(OPEN_ANGLE);
}

void Servos::S2::close() {
    OpenCloseServo.write(CLOSE_ANGLE);
}