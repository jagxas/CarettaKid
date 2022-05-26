#ifndef SERVOCODE_H
#define SERVOCODE_H

#include <Arduino.h>

class ColorSensors{

  public:
    ColorSensors(int S3, int Out);

    void setup();

    enum class Colors {
      Red,
      Blue
    };
    int read_color(Colors color); 
  private:
    const int pin_s3;
    const int pin_out;
};
#endif
