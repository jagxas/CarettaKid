#ifndef SONICSENSORCODE_H
#define SONICSENSORCODE_H

#include <Arduino.h>

class Sonic{

  public:
    int EchoLeftPin = 26, EchoRightPin = A5;
    int LeftTrigPin=25, RightTrigPin = 0;
    double Max=50.0, Min=0.5;

    void SetupSonic(int EchoPin, int TrigPin);
    double CalculateDistance(double Max, double Min, int SensorPin, int EchoTrigPin);
};
#endif
