#ifndef SERVOCODE_H
#define SERVOCODE_H

#include <Arduino.h>

class ColorSensors{

  public:
  //Calibration Values
    int RedMinimum = 0, GreenMinimum = 0, BlueMinimum = 0;
    int RedMaximum = 255, GreenMaximum = 255, BlueMaximum = 255;

    //PulseWidth Values
    int RedPW=0, GreenPW=0, BluePW=0;

    //Final RGB Values
    int Red=0, Green=0, Blue=0;

    //Pins (Sensor1 => Pucks) (Sensor2 => Floor)
    int Color1_S3 = A2, Color1_OUT = A3;
    int Color2_S3 = A0, Color2_OUT = A1;

    void ColorSetup(int S3, int Out);

    int getRedPW(int S3, int Out);
    int getBluePW(int S3, int Out);

    int ActualColorValue(int PW, int MaxVal, int MinVal); 

};
#endif
