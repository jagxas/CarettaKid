#include "motors.hpp"
#include "sonic.hpp"
#include "colorsensor.hpp"
#include "peripherals.hpp"
#include "constants.hpp"
#include "servos.hpp"

ColorSensor Color1(PIN_COLOR1_S3, PIN_COLOR1_OUT);
ColorSensor Color2(PIN_COLOR2_S3, PIN_COLOR2_OUT);

Motors DCMotors(PIN_M1F, PIN_M1B, PIN_M2F, PIN_M2B, PIN_M1S, PIN_M2S);

int CurrentState = 0;
int PreviousState = 0;

int OurStore = 0;
int RivalStore = 0;

int PreviousPuck = 0;

void setup(){
  //Call all the setup functions here
  Color1.setup();
  Color2.setup();

  DCMotors.setup();


  Servos::setup_servos();
  pinMode(SwitchPin, INPUT);
  Serial.begin(9600);
}

ColorSensor::Colors TeamColor = ColorSensor::Colors::Blue;
ColorSensor::Colors RivalColor = ColorSensor::Colors::Red;

void loop(){
  //Button
  CurrentState = digitalRead(SwitchPin);
  
  if (PreviousState != CurrentState){
    if(CurrentState == 0){
      ColorSensor::Colors TeamColor = ColorSensor::Colors::Red;
      ColorSensor::Colors RivalColor = ColorSensor::Colors::Blue;}
    if(PreviousState == 0){
      ColorSensor::Colors TeamColor = ColorSensor::Colors::Blue;
      ColorSensor::Colors RivalColor = ColorSensor::Colors::Red;}
    PreviousState = CurrentState;
  }
  
  //Sonic


  //DC
  if(OurStore < 5){
    DCMotors.go_around();
  }

  else{
    DCMotors.follow_the_walls();
  }

  //Color
  int OurPuck = Color1.read_color(TeamColor);
  int RivalPuck = Color1.read_color(RivalColor);
  int BaseColor = Color2.read_color(TeamColor);

  //Servo
  if (OurPuck > COLOR_THRESHOLD && PreviousPuck < COLOR_THRESHOLD) {
    Servos::S1::take_it();
    OurStore += 1;
    PreviousPuck = OurPuck;
    
  } 
  else if (RivalPuck > COLOR_THRESHOLD && PreviousPuck < COLOR_THRESHOLD) {
    Servos::S1::dont_take_it();
    RivalStore += 1;
    PreviousPuck = RivalPuck;
  }

  if (BaseColor > COLOR_THRESHOLD) {
    Servos::S2::open();
    OurStore = 0;
  } else {
    Servos::S2::close();
  }
}
