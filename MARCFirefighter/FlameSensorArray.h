//
//  FlameSensorArray.h
//  MARCFirefighter
//
//  Created by Joseph Kale on 1/31/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#ifndef MARCFirefighter_FlameSensorArray_h
#define MARCFirefighter_FlameSensorArray_h

#include "Arduino.h"

class FlameSensorArray{
public:
    FlameSensorArray(int pinLeft, int pinMiddleLeft, int pinMiddleRight, int pinRight, int threshold);
    bool isFlame();
    int getSector();
    void stepThreshold(int step);
    double getAverage();
    int getThreshold();
    bool isCentered();
private:
    int _pinLeft;
    int _pinMiddleLeft;
    int _pinMiddleRight;
    int _pinRight;
    int _threshold;
    int baselineLeft;
    int baselineLeftMiddle;
    int baselineRightMiddle;
    int baselineRight;
};

#endif
