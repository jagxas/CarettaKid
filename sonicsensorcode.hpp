#ifndef SONICSENSORCODE_H
#define SONICSENSORCODE_H

#include <Arduino.h>

class Sonic{

  public:
    Sonic(int EchoPin, int TrigPin);

    void setup();
    double distance();

  public:
    const int pin_echo;
    const int pin_trig;
};
#endif
