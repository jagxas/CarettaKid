#include "colorsensor.hpp"
#include "constants.hpp"

ColorSensor::ColorSensor(int S3, int Out) : pin_s3(S3), pin_out(Out), red_last_millis(0), blue_last_millis(0), counting_red(0), counting_blue(0) {

}

void ColorSensor::setup(){
	pinMode(this->pin_s3, OUTPUT);
	pinMode(this->pin_out, INPUT);
}

ColorSensor::Colors ColorSensor::read_color() {
	digitalWrite(this->pin_s3, LOW);
	int RedPW = pulseIn(this->pin_out, LOW);
	digitalWrite(this->pin_s3, HIGH);
	int BluePW = pulseIn(this->pin_out, LOW);
	
	//Hmm
	int BlueValue = map(BluePW, BLUE_MIN, BLUE_MAX, 255, 0);
	int RedValue = map(RedPW, RED_MIN, RED_MAX, 255, 0);
	
	//Hmm
	if(BlueValue > 70 && RedValue < 50) { //Rules can change depending upon calibration values
		return Colors::Blue;
	} else if (RedValue > 150 && BlueValue < 80) { //Rules can change depending upon calibration values
		return Colors::Red;
	} else {
		return Colors::None;
	}
}

ColorSensor::Colors ColorSensor::sync_color() {
	//Public wrapper for threshholding
	Colors sensed = this->read_color();
	switch (sensed) {
		case Colors::Red:
			counting_blue = false;
			if (counting_red) {
				if (millis() - red_last_millis >= COLOR_SENSOR_CONSISTENCY_THRESHHOLD) {
					return Colors::Red;					
				} else {
					return Colors::None;
				}
			} else {
				counting_red = true;
				red_last_millis = millis();
				return Colors::None;
			}
		break;
		case Colors::Blue:
			counting_red = false;
			if (counting_blue) {
				if (millis() - blue_last_millis >= COLOR_SENSOR_CONSISTENCY_THRESHHOLD) {
					return Colors::Red;					
				} else {
					return Colors::None;
				}
			} else {
				counting_blue = true;
				blue_last_millis = millis();
				return Colors::None;
			}
		break;
		case Colors::None:
			counting_blue = false;
			counting_red = false;
		break;
	}
}
