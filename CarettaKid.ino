#include "motors.hpp"
#include "sonic.hpp"
#include "colorsensor.hpp"
#include "peripherals.hpp"
#include "constants.hpp"
#include "servos.hpp"

ColorSensor Color1(PIN_COLOR1_S3, PIN_COLOR1_OUT);
ColorSensor Color2(PIN_COLOR2_S3, PIN_COLOR2_OUT);

Motors DCMotors(PIN_M1F, PIN_M1B, PIN_M2F, PIN_M2B, PIN_M1S, PIN_M2S);

int OurStore = 0; //Puck Count
int RivalStore = 0; //Puck Count

int Count1 = 0; //Puck Count for Accuracy
int Count2 = 0; //Ground Count for Accuracy

void setup(){
  
  Color1.setup();
  Color2.setup();

  DCMotors.setup();
  
  Servos::setup_servos();
  
  pinMode(SwitchPin, INPUT);

  Serial.begin(9600);
}

ColorSensor::Colors TeamColor;
ColorSensor::Colors RivalColor;
ColorSensor::Colors SensorState1;
ColorSensor::Colors SensorState2;

void loop(){
  
  //Button
  if(digitalRead(SwitchPin)){
    TeamColor = ColorSensor::Colors::Blue;
    RivalColor = ColorSensor::Colors::Red;
  } 
  else {
    TeamColor = ColorSensor::Colors::Red;
    RivalColor = ColorSensor::Colors::Blue;
  }
  

  //DC
  if(OurStore < 5){
    DCMotors.go_around();
  }
  else{
    DCMotors.follow_the_walls();
  }

  //Color
  SensorState1 = Color1.read_color();
  SensorState2 = Color2.read_color();
  
  //Servo
  if (SensorState1 == TeamColor) {
    if(Count1 == 3){
    Servos::S1::take_it();
    OurStore += 1;
    }
    Count1++;
  } 
  
  else if (SensorState1 == RivalColor) {
    Count1 = 0;
      if(RivalStore >= 4){
       DCMotors.step_back();
       DCMotors.turn_right();
      }
      else{
        Servos::S1::dont_take_it();
        RivalStore += 1;
      }
  }



  if (SensorState2 == TeamColor) {
    if(Count2 >= 3){
      Servos::S2::open();
      OurStore = 0;
    }
  else {
     Servos::S2::close();
     Count2 = 0;
     }
  }


  
}
