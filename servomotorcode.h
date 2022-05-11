#ifndef SERVOMOTORCODE_H
#define SERVOMOTORCODE_H

#include <Arduino.h>
#include <Servo.h>

class MS{

  public:
    Servo ServoMotor1, ServoMotor2;
    int CorrectPuckAngle = 100, WrongPuckAngle = 200;
    int OpeningAngle = 90, ClosingAngle = 0;
    //TO DO: Find the accurate numbers

    int ServoPin1 = 27, ServoPin2 = 28;

    void Servo1_TakeIt();
    void Servo1_DontTakeIt();
    void Servo2_Open();
    void Servo2_Close();
    void SetupServo(int ServoPin1,int ServoPin2);
};
#endif
