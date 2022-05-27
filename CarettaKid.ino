#include "motors.hpp"
#include "sonic.hpp"
#include "colorsensor.hpp"
#include "peripherals.hpp"
#include "constants.hpp"
#include "servos.hpp"

ColorSensor Color1(PIN_COLOR1_S3, PIN_COLOR1_OUT);
ColorSensor Color2(PIN_COLOR2_S3, PIN_COLOR2_OUT);
Sonic RightSonic(PIN_SONIC_RIGHT_ECHO, PIN_SONIC_RIGHT_TRIG);
Sonic LeftSonic(PIN_SONIC_LEFT_ECHO, PIN_SONIC_LEFT_TRIG);
Motors DCMotors(PIN_M1F, PIN_M1B, PIN_M2F, PIN_M2B, PIN_M1S, PIN_M2S);


ColorSensor::Colors TeamColor;
ColorSensor::Colors RivalColor;

void setup(){
  if (digitalRead(PIN_IS_TEAM_BLUE)) {
    TeamColor = ColorSensor::Colors::Blue;
    RivalColor = ColorSensor::Colors::Red;
  } else {
    TeamColor = ColorSensor::Colors::Red;
    RivalColor = ColorSensor::Colors::Blue;
  }

  Color1.setup();
  Color2.setup();

  DCMotors.setup();

  RightSonic.setup();
  LeftSonic.setup();

  Servos::setup_servos();
  
  Serial.begin(9600);
}


void loop(){
  
  //Sonic
  double DistanceR = RightSonic.distance();
  double DistanceL = LeftSonic.distance();

  //DC
  if(DistanceR > 10 && DistanceL > 10){
    DCMotors.go();
    delay(100);
  }

  if(DistanceR < 10 && DistanceL < 10){
    DCMotors.step_back();
    delay(30);
    DCMotors.turn_right();
    delay(100);
  }

  //Color
  int OurPuck = Color1.read_color(TeamColor);
  int RivalPuck = Color1.read_color(RivalColor);
  int BaseColor = Color2.read_color(TeamColor);

  //Servo
  if (OurPuck > COLOR_THRESHOLD) {
    Servos::S1::take_it();
  } else if (RivalPuck > COLOR_THRESHOLD) {
    Servos::S1::dont_take_it();
  }

  if (BaseColor > COLOR_THRESHOLD) {
    Servos::S2::open();
  } else {
    Servos::S2::close();
  }
}
