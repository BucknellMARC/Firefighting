//
//  MotorControl.cpp
//  Firefighter_2014
//
//  Created by Joseph Kale on 11/5/13.
//
//

#include "MotorControl.h"
#include "Arduino.h"
#include "AFMotor.h"
#include "MotorControl.h"

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(2);
ENCODER_LEFT_ONE = 10
ENCODER_LEFT_TWO = 11
ENCODER_RIGHT_ONE = 6
ENCODER_RIGHT_TWO = 9
TURN_THRESHOLD = 153


MotorControl::MotorControl(){
    Serial.begin(9600);
    Serial.print("MotorControl initiated");
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::forward(){
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
}

void forward(int distance){
    forward();
    int count = 0;
    while (count < TURN_THRESHOLD * distance){
        if (digitalRead(ENCODER_LEFT_ONE) && digitalRead(ENCODER_LEFT_TWO) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}

void MotorControl::turnLeft(){
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
}

void MotorControl::turnLeft(int degree){
    turnLeft();
    int count = 0;
    while (count < TURN_THRESHOLD * degree){
        if (digitalRead(ENCODER_LEFT_ONE) && digitalRead(ENCODER_LEFT_TWO) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}

void MotorControl::turnRight(){
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
}

void MotorControl::turnRight(int degree * degree){
    turnRight();
    int count = 0;
    while (count < TURN_THRESHOLD){
        if (digitalRead(ENCODER_LEFT_ONE) && digitalRead(ENCODER_LEFT_TWO) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}

void MotorControl::brake(){
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::brake(int time){
    delay(time);
}

void MotorControl::backward(){
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
}

void MotorControl::backward(int distance){
    backward();
    int count = 0;
    while (count < TURN_THRESHOLD * distance){
        if (digitalRead(ENCODER_LEFT_ONE) && digitalRead(ENCODER_LEFT_TWO) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}