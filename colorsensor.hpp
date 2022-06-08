#pragma once

#include <Arduino.h>

class ColorSensor {

  public:
    ColorSensor(int S3, int Out);

    void setup();

    enum class Colors {
      Red,
      Blue,
      Ground
    };
    Colors read_color(); 
  private:
    const int pin_s3;
    const int pin_out;
};
