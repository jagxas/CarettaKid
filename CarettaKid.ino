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
Motors DCMotors(&LeftSonic, &RightSonic, PIN_M1F, PIN_M1B, PIN_M2F, PIN_M2B, PIN_M1S, PIN_M2S);


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
  //DC
  if(Servos::our_count < 5){
    DCMotors.go_around_mode();
  }
  else{
    DCMotors.follow_the_walls_mode();
  }

  //Color
  ColorSensor::Colors PuckColor = Color1.sync_color();
  ColorSensor::Colors BaseColor = Color2.sync_color();

  //Servos
  if (PuckColor == RivalColor) {
    if (Servos::rival_count < 4) {
      Servos::S1::take_rival();
    } else {
      //Step back and turn right
      DCMotors.force_back_right();
    }
  } else if (PuckColor == TeamColor) {
    if (Servos::our_count < 5) {
      Servos::S1::take_ours();
    }
  } else {
    Servos::S1::finish_taking();
  }

  if (BaseColor == TeamColor) {
    Servos::S2::open();
  } else {
    Servos::S2::close();
  }

  DCMotors.main_loop();
}
