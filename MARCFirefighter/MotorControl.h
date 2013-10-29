//
//  MotorControl.h
//  MARCFirefighter
//
//  Created by Joseph Kale on 1/31/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#ifndef MARCFirefighter_MotorControl_h
#define MARCFirefighter_MotorControl_h

#include "Arduino.h"
#include "AFMotor.h"

class MotorControl{
public:
    MotorControl(int leftForward, int rightForward, int leftReverse, int rightReverse);
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
    int _leftForward;
    int _rightForward;
    int _leftReverse;
    int _rightReverse;
};

#endif
