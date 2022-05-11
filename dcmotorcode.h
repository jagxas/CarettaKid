#ifndef DCMOTORCODE_H
#define DCMOTORCODE_H

#include <Arduino.h>

class DC{

  public:
    //TO DO: Speed Pin
    int SpeedPin1 = 0, SpeedPin2 = 0;

    //TO DO: Speed Values
    int CruiseSpeed = 0;
    int TurningSpeed = 0;

    int LeftForwards = 29, LeftBackwards = 30;
    int RightForwards = 22, RightBackwards = 21;

    void DCSetup(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S);
    void go(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int CruiseSpeed);
    void stepBack(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int Speed);
    void turnRight(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S, int TurningSpeed);

};
#endif
