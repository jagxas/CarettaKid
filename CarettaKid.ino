#include "dcmotorcode.hpp"
#include "sonicsensorcode.hpp"
#include "colorsensorcode.hpp"

#include "peripherals.hpp"

#include "servos.hpp"

ColorSensors Color1(PIN_COLOR1_S3, PIN_COLOR1_OUT);
ColorSensors Color2(PIN_COLOR2_S3, PIN_COLOR2_OUT);
Sonic RightSonic(PIN_SONIC_RIGHT_ECHO, PIN_SONIC_RIGHT_TRIG);
Sonic LeftSonic(PIN_SONIC_LEFT_ECHO, PIN_SONIC_LEFT_TRIG);
DC DCMotors(PIN_M1F, PIN_M1B, PIN_M2F, PIN_M2B, PIN_M1S, PIN_M2S);



void setup(){
  //Call all the setup functions here
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
  int RedValue1 = Color1.read_color(ColorSensors::Colors::Red);
  int BlueValue1 = Color1.read_color(ColorSensors::Colors::Blue);

  //Color
  int RedValue2 = Color2.read_color(ColorSensors::Colors::Red);
  int BlueValue2 = Color2.read_color(ColorSensors::Colors::Blue); 


  //Servo
  if (RedValue1 > 100){
    #ifdef IS_TEAM_BLUE
      Servos::S1::dont_take_it();
    #else
      Servos::S1::take_it();
    #endif
  } else if (BlueValue1 > 100) {
    #ifdef IS_TEAM_BLUE
      Servos::S1::take_it();
    #else
      Servos::S1::dont_take_it();
    #endif
  }

  if (RedValue2 > 100) {
    #ifdef IS_TEAM_BLUE
      Servos::S2::close();
    #else
      Servos::S2::open();
    #endif
  } else if (BlueValue2 > 100){
    #ifdef IS_TEAM_BLUE
      Servos::S2::open();
    #else
      Servos::S2::close();
    #endif
  } else {
    Servos::S2::close();
  }

}
