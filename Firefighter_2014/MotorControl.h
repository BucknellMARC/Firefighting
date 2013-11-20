//
//  MotorControl.h
//  Firefighter_2014
//
//  Created by Joseph Kale on 11/5/13.
//
//

#ifndef __Firefighter_2014__MotorControl__
#define __Firefighter_2014__MotorControl__

#include <iostream>
#include "Arduino.h"
#include "AFMotor.h"

class MotorControl{
public:
    MotorControl();
    void forward();
    void forward(int time);
    void turnLeft();
    void turnLeft(int time);
    void turnRight();
    void turnRight(int time);
    void backward();
    void backward(int time);
    void brake();
    void brake(int time);
private:
    int ENCODER_LEFT_ONE;
    int ENCODER_LEFT_TWO;
    int ENCODER_RIGHT_ONE;
    int ENCODER_RIGHT_TWO;
    int TURN_SCALE;
};

#endif /* defined(__Firefighter_2014__MotorControl__) */
