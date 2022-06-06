#include "colorsensor.hpp"
#include "constants.hpp"

ColorSensor::ColorSensor(int S3, int Out) : pin_s3(S3), pin_out(Out) {

}

void ColorSensor::setup(){
	pinMode(this->pin_s3, OUTPUT);
	pinMode(this->pin_out, INPUT);
}

int ColorSensor::read_color(Colors col){
  digitalWrite(this->pin_s3, col == Colors::Blue ? HIGH : LOW);
	int PW = pulseIn(this->pin_out, LOW);
 
  //Hmm
  if(col == Colors::Blue){int Value = map(PW, BLUE_MAX, BLUE_MIN, 255, 0);}
  if(col == Colors::Red){int Value = map(PW, RED_MAX, RED_MIN, 255, 0);}
  //Hmm
  
	int Value = map(PW, RGB_MAX, RGB_MIN, 255, 0);
	delay(200); //Okay, but w h y ????
	return Value;

}
