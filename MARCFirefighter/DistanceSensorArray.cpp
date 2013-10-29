//
//  DistanceSensorArray.cpp
//  MARCFirefighter
//
//  Created by Joseph Kale on 3/9/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#include "DistanceSensorArray.h"
#include "Arduino.h"

DistanceSensorArray::DistanceSensorArray(int frontPin, int leftPin, int rightPin, int threshold){
    _frontPin=frontPin;
    _leftPin=leftPin;
    _rightPin=rightPin;
    _threshold=threshold;
    pinMode(_frontPin, INPUT);
    pinMode(_leftPin, INPUT);
    pinMode(_rightPin, INPUT);
}

bool DistanceSensorArray::isFrontOpen(){
    if (digitalRead(_frontPin)==0)
        return true;
    else return false;
}

bool DistanceSensorArray::isLeftOpen(){
    if (analogRead(_leftPin)<_threshold)
        return true;
    else return false;
}

bool DistanceSensorArray::isRightOpen(){
    if (analogRead(_rightPin)<_threshold)
        return true;
    else return false;
}

int DistanceSensorArray::leftDistance(){
    return analogRead(_leftPin);
}

int DistanceSensorArray::rightDistance(){
    return analogRead(_rightPin);
}

int DistanceSensorArray::getThreshold(){
    return _threshold;
}

void DistanceSensorArray::setThreshold(int threshold){
    _threshold=threshold;
}