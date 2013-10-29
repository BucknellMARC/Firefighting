//
//  FlameSensorArray.cpp
//  MARCFirefighter
//
//  Created by Joseph Kale on 1/31/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#include "Arduino.h"
#include "FlameSensorArray.h"

FlameSensorArray::FlameSensorArray(int pinLeft, int pinMiddleLeft, int pinMiddleRight, int pinRight, int threshold){
    _pinLeft=pinLeft;
    _pinRight=pinRight;
    _pinMiddleLeft=pinMiddleLeft;
    _pinMiddleRight=pinMiddleRight;
    _threshold=threshold;
    baselineLeft=analogRead(_pinLeft);
    baselineLeftMiddle=analogRead(_pinMiddleLeft);
    baselineRightMiddle=analogRead(_pinMiddleRight);
    baselineRight=analogRead(_pinRight);

}

double FlameSensorArray::getAverage(){
    int i=0;
    long sum=0;
    for (i;i<100;i++)
        sum+=analogRead(_pinLeft)+analogRead(_pinMiddleLeft)+analogRead(_pinMiddleRight)+analogRead(_pinRight);
    Serial.println(sum);
    return sum/400.0;
}

bool FlameSensorArray::isFlame(){
    return getAverage()>=_threshold;
}

int FlameSensorArray::getSector(){
    if(!isFlame())
        return -1;
    else{
        int average=getAverage();
        if (analogRead(_pinLeft)>=analogRead(_pinRight) && analogRead(_pinMiddleLeft)>=analogRead(_pinRight) && analogRead(_pinMiddleRight)>=analogRead(_pinRight))
            return 0;
        else if (analogRead(_pinRight)>=analogRead(_pinLeft) && analogRead(_pinMiddleLeft)>=analogRead(_pinLeft) && analogRead(_pinMiddleRight)>=analogRead(_pinLeft))
            return 2;
        else return 1;
    }
}

bool FlameSensorArray::isCentered(){
    return ((analogRead(_pinMiddleLeft) + analogRead(_pinMiddleRight))/2) >= _threshold;
}

void FlameSensorArray::stepThreshold(int step){
    _threshold+=step;
}

int FlameSensorArray::getThreshold(){
    return _threshold;
}
