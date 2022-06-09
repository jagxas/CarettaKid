#pragma once

#include <Arduino.h>
#include "sonic.hpp"

class Motors{

  public:
    Motors(Sonic *left, Sonic *right, int M1F, int M1B, int M2F, int M2B, int M1S, int M2S);
    void setup();
    void follow_the_walls_mode();
    void go_around_mode();
    void main_loop();
    void force_back_right();
    
  private:
    Sonic *const left;
    Sonic *const right;

    const int pin_m1f;
    const int pin_m1b;
    const int pin_m2f;
    const int pin_m2b;
    const int pin_m1s;
    const int pin_m2s;
    bool step();
    void cruise();
    void step_back();
    void turn_right();
    class MotorStateMachine {
      public:
        MotorStateMachine();
        enum States {
          None = 0,
          GoAroundDecide,
          GoAroundCruise,
          GoAroundStepBack,
          GoAroundTurnRight,

          FollowTheWallsDecide,
          FollowTheWallsCruise,
          FollowTheWallsStepBack,
          FollowTheWallsTurnRight,

          RivalPuckStepBack,
          RivalPuckTurnRight,

          LENGTH
        };
        static const int durations[States::LENGTH];
        static const States next[States::LENGTH];
        void reset_timer();
        States current;
        bool poll_and_switch();
        void continuous_schedule(States s);
      private:
        unsigned long time;
        States cont;
    };

    MotorStateMachine MSM;
};