#include "motors.hpp"
#include "constants.hpp"

Motors::Motors(Sonic *left, Sonic *right, int M1F, int M1B, int M2F, int M2B, int M1S, int M2S) : pin_m1f(M1F), pin_m1b(M1B), pin_m2f(M2F), pin_m2b(M2B), pin_m1s(M1S), pin_m2s(M2S), left(left), right(right) {
	
}

void Motors::setup() {
	pinMode(pin_m1f, OUTPUT);
	pinMode(pin_m1b, OUTPUT);

	pinMode(pin_m2f, OUTPUT);
	pinMode(pin_m2b, OUTPUT);
	
	pinMode(pin_m1s, OUTPUT);
	pinMode(pin_m2s, OUTPUT);
}

void Motors::cruise() {
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m1b, LOW);
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m2b, LOW);
	analogWrite(pin_m1s, CRUISE_SPEED1);
	analogWrite(pin_m2s, CRUISE_SPEED2); 
}

void Motors::turn_right(){
	digitalWrite(pin_m1f, HIGH);
	digitalWrite(pin_m1b, LOW);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, LOW);

	digitalWrite(pin_m1s, TURNING_SPEED);	
}

void Motors::step_back(){
	digitalWrite(pin_m1f, LOW);
	digitalWrite(pin_m1b, HIGH);
	digitalWrite(pin_m2f, LOW);
	digitalWrite(pin_m2b, HIGH);

	analogWrite(pin_m1s, CRUISE_SPEED1);
	analogWrite(pin_m2s, CRUISE_SPEED2);	
}

void Motors::follow_the_walls_mode() {
	MSM.continuous_schedule(MotorStateMachine::States::FollowTheWallsDecide);
}

void Motors::go_around_mode() {
	MSM.continuous_schedule(MotorStateMachine::States::GoAroundDecide);
}

//Force the robot to stop whatever it is doing with its motors and step away from that puck!
void Motors::force_back_right() {
	MSM.current = MotorStateMachine::States::RivalPuckStepBack;
	MSM.reset_timer();
}

Motors::MotorStateMachine::MotorStateMachine() : time(0), current(None), cont(None) {

}

void Motors::MotorStateMachine::continuous_schedule(States s) {
	cont = s;
}

void Motors::MotorStateMachine::reset_timer() {
	time = millis();
}

bool Motors::MotorStateMachine::poll_and_switch() {
	if (durations[current] == -1) return false;
	unsigned long newtime = millis();

	if (time - newtime >= durations[current]) {
		States old = current;
		current = next[current];
		if (current == None) {
			current = cont;
		}
		time = newtime;
		return old == current;
	} else {
		return false;
	}
}

void Motors::main_loop() {
	bool updated = MSM.poll_and_switch();
	while (updated) {
		updated = step();
	}
}

bool Motors::step() {
	using States=MotorStateMachine::States;
	
	States old = MSM.current;

	switch (MSM.current) {
		case States::None:

		break;
		case States::GoAroundDecide: {
			double DistanceR = right->distance();
			double DistanceL = left->distance();

			if(DistanceR > 10 && DistanceL > 10){
				MSM.current = States::GoAroundCruise;
			} else if(DistanceR < 10 && DistanceL < 10){
				MSM.current = States::GoAroundStepBack;
			} else {
				MSM.current = States::None;
			}
		}
		break;
		case States::FollowTheWallsCruise:
		case States::GoAroundCruise:
			cruise();	
		break;
		case States::RivalPuckStepBack:
		case States::FollowTheWallsStepBack:
		case States::GoAroundStepBack:
			step_back();
		break;
		case States::RivalPuckTurnRight:
		case States::FollowTheWallsTurnRight:
		case States::GoAroundTurnRight:
			turn_right();
		break;
		case States::FollowTheWallsDecide: {
			double DistanceR = right->distance();
			double DistanceL = left->distance();
			if(DistanceR < 10 && DistanceL < 10){
				MSM.current = States::FollowTheWallsStepBack;
			} else {
				MSM.current = States::FollowTheWallsCruise;
			}
		}
		break;
	}
	return old == MSM.current;
}


const int Motors::MotorStateMachine::durations[States::LENGTH] = {
	-1,					//None = 0,
	-1,					//GoAroundDecide,
	100,				//GoAroundCruise,
	100,				//GoAroundStepBack,
	400,				//GoAroundTurnRight,
	-1,					//FollowTheWallsDecide,
	100,				//FollowTheWallsCruise,
	100,				//FollowTheWallsStepBack,
	200,				//FollowTheWallsTurnRight,
	100,				//RivalPuckStepBack,
	200,				//RivalPuckTurnRight,
};

const Motors::MotorStateMachine::States Motors::MotorStateMachine::next[States::LENGTH] = {
	States::None,							//None = 0,
	States::None,							//GoAroundDecide, -> (GoAroundCruise | GoAroundStepBack | None)
	States::None,							//GoAroundCruise,
	States::GoAroundTurnRight,				//GoAroundStepBack,
	States::None,							//GoAroundTurnRight,
	States::None,							//FollowTheWallsDecide, -> (FollowTheWallsCruise | FollowTheWallsStepBack)
	States::None,							//FollowTheWallsCruise,
	States::FollowTheWallsTurnRight,		//FollowTheWallsStepBack,
	States::None,							//FollowTheWallsTurnRight,
	States::RivalPuckTurnRight,				//RivalPuckStepBack,
	States::None							//RivalPuckTurnRight,
};