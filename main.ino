#include "dcmotorcode.h"
#include "sonicsensorcode.h"
#include "colorsensorcode.h"

#include "servomotorcode.h"
#include <Servo.h>

#define Team "Blue"

ColorSensors Color1;
ColorSensors Color2;
Sonic RightSonic;
Sonic LeftSonic;
DC DCMotors;
MS ServoMotor;


void setup(){
  //Call all the setup functions here
  Color1.ColorSetup(Color1.Color1_S3, Color1.Color1_OUT);
  Color2.ColorSetup(Color2.Color2_S3, Color2.Color2_OUT);

  DCMotors.DCSetup(DCMotors.LeftForwards, DCMotors.LeftBackwards, DCMotors.RightForwards, DCMotors.RightBackwards, DCMotors.SpeedPin1, DCMotors.SpeedPin2); 

  RightSonic.SetupSonic(RightSonic.EchoRightPin, RightSonic.RightTrigPin);
  LeftSonic.SetupSonic(LeftSonic.EchoLeftPin, LeftSonic.LeftTrigPin);

  ServoMotor.SetupServo(ServoMotor.ServoPin1, ServoMotor.ServoPin2);
  
  Serial.begin(9600);
}





void loop(){
  
  //Sonic
  double DistanceR = RightSonic.CalculateDistance(RightSonic.Max, RightSonic.Min, RightSonic.EchoRightPin, RightSonic.RightTrigPin);
  double DistanceL = LeftSonic.CalculateDistance(LeftSonic.Max, LeftSonic.Min, LeftSonic.EchoLeftPin, LeftSonic.LeftTrigPin);

  
  //DC
  if(DistanceR > 10 && DistanceL > 10){
    DCMotors.go(DCMotors.LeftForwards, DCMotors.LeftBackwards, DCMotors.RightForwards, DCMotors.RightBackwards, DCMotors.SpeedPin1, DCMotors.SpeedPin2, DCMotors.CruiseSpeed);
    delay(100);
    }    
  if(DistanceR < 10 && DistanceL < 10){
    DCMotors.stepBack(DCMotors.LeftForwards, DCMotors.LeftBackwards, DCMotors.RightForwards, DCMotors.RightBackwards, DCMotors.SpeedPin1, DCMotors.SpeedPin2, DCMotors.CruiseSpeed);
    delay(30);
    DCMotors.turnRight(DCMotors.LeftForwards, DCMotors.LeftBackwards, DCMotors.RightForwards, DCMotors.RightBackwards, DCMotors.SpeedPin1, DCMotors.SpeedPin2, DCMotors.TurningSpeed);
    delay(100);
    }

                                                                                 
  //Color
  int RedPulseWidth1 = Color1.getRedPW(Color1.Color1_S3, Color1.Color1_OUT);
  int BluePulseWidth1 = Color1.getBluePW(Color1.Color1_S3, Color1.Color1_OUT);
  int RedValue1 = Color1.ActualColorValue(RedPulseWidth1, Color1.RedMaximum, Color1.RedMinimum);
  int BlueValue1 = Color1.ActualColorValue(BluePulseWidth1, Color1.BlueMaximum, Color1.BlueMinimum);
  
  //Comparison of Colors Here
  int FirstSensorColor = 0;
  if(RedValue1 > 100){FirstSensorColor = 1;}
  if(BlueValue1 > 100){FirstSensorColor = 2;}

  //Color
  int RedPulseWidth2 = Color2.getRedPW(Color2.Color1_S3, Color2.Color2_OUT);
  int BluePulseWidth2 = Color2.getBluePW(Color2.Color1_S3, Color2.Color2_OUT);
  int RedValue2 = Color2.ActualColorValue(RedPulseWidth2, Color2.RedMaximum, Color2.RedMinimum);
  int BlueValue2 = Color2.ActualColorValue(BluePulseWidth2, Color2.BlueMaximum, Color2.BlueMinimum);
  
  //Comparison of Colors Here
  int SecondSensorColor = 0;
  if(RedValue2 > 100){SecondSensorColor = 1;}
  if(BlueValue2 > 100){SecondSensorColor = 2;}


  //Servo
  if(FirstSensorColor == 1){
    if(Team == "Red"){ServoMotor.Servo1_TakeIt();}
    if(Team == "Blue"){ServoMotor.Servo1_DontTakeIt();}
  }
  if(FirstSensorColor == 2){
    if(Team == "Red"){ServoMotor.Servo1_DontTakeIt();}
    if(Team == "Blue"){ServoMotor.Servo1_TakeIt();}
  }

  if(SecondSensorColor == 1){
    if(Team == "Red"){ServoMotor.Servo2_Open();}
    if(Team == "Blue"){ServoMotor.Servo2_Close();}
  }
  if(SecondSensorColor == 2){
    if(Team == "Red"){ServoMotor.Servo2_Close();}
    if(Team == "Blue"){ServoMotor.Servo2_Open();}
  }
  if(SecondSensorColor == 0){ServoMotor.Servo2_Close();}
  
}
