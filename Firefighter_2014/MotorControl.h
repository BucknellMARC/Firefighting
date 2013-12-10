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
    void forward(int distance);
    void turnLeft();
    void turnLeft(int distance);
    void turnRight();
    void turnRight(int distance);
    void backward();
    void backward(int distance);
    void brake();
    void brake(int time);
private:
    int ENCODER_LEFT_A;
    int ENCODER_LEFT_B;
<<<<<<< HEAD
    int ENCODER_RIGHT_ONE;
    int ENCODER_RIGHT_TWO;
=======
    int ENCODER_RIGHT_A;
    int ENCODER_RIGHT_B;
>>>>>>> 9aa6aa13a17cf821f68277b31321a223c2bc0e79
    int TURN_SCALE;
	bool newA;
	bool newB;
	bool oldA;
	bool oldB;
};

#endif /* defined(__Firefighter_2014__MotorControl__) */
