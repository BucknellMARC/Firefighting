//
//  DistanceSensorArray.h
//  MARCFirefighter
//
//  Created by Joseph Kale on 1/31/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#ifndef MARCFirefighter_DistanceSensorArray_h
#define MARCFirefighter_DistanceSensorArray_h

#include <"Arduino.h">

class DistanceSensorArray{
public:
    DistanceSensorArray(int frontPin, int leftPin, int rightPin, int threshold);
    bool isFrontOpen();
    bool isLeftOpen();
    bool isRightOpen();
    int leftDistance();
    int rightDistance();
    void setThreshold(int threshold);
    int getThreshold();
private:
    int _leftPin;
    int _rightPin;
    int _frontPin;
    int _threshold;
};

#endif
