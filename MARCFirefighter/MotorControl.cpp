//
//  MotorControl.cpp
//  MARCFirefighter
//
//  Created by Joseph Kale on 1/31/13.
//  Copyright (c) 2013 Joseph Kale. All rights reserved.
//

#include "Arduino.h"
#include "AFMotor.h"
#include "MotorControl.h"

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(2);
int STOP_TIME=100;
int MC_DISTANCE_THRESHOLD=350;
int ADJUST_TURN_TIME=50;

MotorControl::MotorControl(int leftForward, int rightForward, int leftReverse, int rightReverse){
    Serial.begin(9600);
    Serial.print("MotorControl initiated");
    _leftForward=leftForward;
    _rightForward=rightForward;
    _leftReverse=leftReverse;
    _rightReverse=rightReverse;
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::forward(){
    motorLeft.setSpeed(_leftForward);
    motorRight.setSpeed(_rightForward);
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
}

void MotorControl::forward(int time){
    forward();
    delay(time);
    brake(STOP_TIME);
    long leftSum=0;
    long rightSum=0;
    int i=0;
    for(i;i<100;i++) {
        leftSum+=analogRead(A4);
        rightSum+=analogRead(A5);
    }
    double leftAverage=leftSum/100;
    double rightAverage=rightSum/100;
    if(leftAverage>MC_DISTANCE_THRESHOLD){
        turnRight(ADJUST_TURN_TIME);
    }
    else if (rightAverage>MC_DISTANCE_THRESHOLD){
        turnLeft(ADJUST_TURN_TIME);
    }
    brake(STOP_TIME);
}

void MotorControl::turnLeft(){
    motorLeft.setSpeed(_leftReverse);
    motorRight.setSpeed(_rightForward);
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
}

void MotorControl::turnLeft(int time){
    turnLeft();
    delay(time);
    brake(STOP_TIME);
}

void MotorControl::turnRight(){
    motorLeft.setSpeed(_leftForward);
    motorRight.setSpeed(_rightReverse);
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
}

void MotorControl::turnRight(int time){
    turnRight();
    delay(time);
    brake(STOP_TIME);
}

void MotorControl::brake(){
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::backward(){
    motorLeft.setSpeed(_leftReverse);
    motorRight.setSpeed(_rightReverse);
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
}

void MotorControl::backward(int time){
    backward();
    delay(time);
    brake(STOP_TIME);
}

void MotorControl::brake(int time){
    brake();
    delay(time);
}