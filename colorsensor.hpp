#pragma once
#include <Arduino.h>

class ColorSensor {

  public:
    ColorSensor(int S3, int Out);

    void setup();

    enum class Colors {
      Red,
      Blue,
      None
    };
    Colors sync_color();
  private:
    Colors read_color();
    const int pin_s3;
    const int pin_out;

    unsigned long red_last_millis;
    unsigned long blue_last_millis;

    bool counting_red;
    bool counting_blue;
};