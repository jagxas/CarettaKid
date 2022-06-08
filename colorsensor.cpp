#include "colorsensor.hpp"
#include "constants.hpp"

ColorSensor::ColorSensor(int S3, int Out) : pin_s3(S3), pin_out(Out) {

}

void ColorSensor::setup(){
	pinMode(this->pin_s3, OUTPUT);
	pinMode(this->pin_out, INPUT);
}

ColorSensor::Colors ColorSensor::read_color(){
	digitalWrite(this->pin_s3, LOW);
  int RedPW = pulseIn(this->pin_out, LOW);
  digitalWrite(this->pin_s3, HIGH);
  int BluePW = pulseIn(this->pin_out, LOW);
 
  //Hmm
  int BlueValue = map(BluePW, BLUE_MIN, BLUE_MAX, 255, 0);
  int RedValue = map(RedPW, RED_MIN, RED_MAX, 255, 0);
  //Hmm

  Colors FinalValue;
  if(BlueValue > RedValue && ((BlueValue-RedValue) >= 30) && RedValue < 110){ //Rules can change depending upon calibration values
    FinalValue = Colors::Blue;
    return FinalValue;
  }
  else if(BlueValue < RedValue && RedValue > 150 && (RedValue-BlueValue >= 30)){ //Rules can change depending upon calibration values
    FinalValue = Colors::Red;
    return FinalValue;
  }
  else{
    FinalValue = Colors::Ground;
    return FinalValue;
  }

}
