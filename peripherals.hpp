#pragma once

#include <Arduino.h>

// -- PINS --

//Color Sensor Pins

#define PIN_COLOR1_S3 A2
#define PIN_COLOR1_OUT A3
#define PIN_COLOR2_S3 A0
#define PIN_COLOR2_OUT A1

//DC Motor Pins

#define PIN_M1F 29
#define PIN_M1B 30
#define PIN_M2F 22
#define PIN_M2B 21

//TODO: Speed Pins

#define PIN_M1S 0
#define PIN_M2S 0

//Servo Pins

#define PIN_SERVO1 27
#define PIN_SERVO2 28

//Sonic Sensor Pins

#define PIN_SONIC_LEFT_ECHO 26
#define PIN_SONIC_LEFT_TRIG 25
#define PIN_SONIC_RIGHT_ECHO A5
#define PIN_SONIC_RIGHT_TRIG 0

//Team Switch Pin

#define PIN_IS_TEAM_BLUE 31