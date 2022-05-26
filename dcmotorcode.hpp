#ifndef DCMOTORCODE_H
#define DCMOTORCODE_H

#include <Arduino.h>

class DC{

  public:

    DC(int M1F, int M1B, int M2F, int M2B, int M1S, int M2S);
    void setup();
    void go();
    void step_back();
    void turn_right();
  private:
    const int pin_m1f;
    const int pin_m1b;
    const int pin_m2f;
    const int pin_m2b;
    const int pin_m1s;
    const int pin_m2s;
};
#endif
