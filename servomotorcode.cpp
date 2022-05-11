#include "servomotorcode.h"

void MS::Servo1_TakeIt(){
  ServoMotor1.write(CorrectPuckAngle);
}

void MS::Servo1_DontTakeIt(){
  ServoMotor1.write(WrongPuckAngle);
}

void MS::Servo2_Close(){
  ServoMotor2.write(ClosingAngle);
}

void MS::Servo2_Open(){
  ServoMotor2.write(OpeningAngle);
}

void MS::SetupServo(int ServoPin1,int ServoPin2){
  Serial.begin(9600);
  ServoMotor1.attach(ServoPin1);
  ServoMotor2.attach(ServoPin2);
}
