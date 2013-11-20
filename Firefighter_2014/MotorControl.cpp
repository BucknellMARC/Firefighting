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
int ENCODER_LEFT_ONE = 10;
int ENCODER_LEFT_TWO = 11;
int ENCODER_RIGHT_ONE = 6;
int ENCODER_RIGHT_TWO = 9;
int TURN_SCALE = 0.0065283615521376;


MotorControl::MotorControl(){
    Serial.begin(9600);
    Serial.print("MotorControl initiated");
    motorLeft.setSpeed(255);
    motorRight.setSpeed(255);
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::forward(){
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
}

void MotorControl::forward(int distance){
    forward();
    int revolutions = 0;
    int steps = 0;
    while (revolutions * TURN_SCALE < distance){
        bool oldA;
        bool oldB;
        bool newA = digitalRead(ENCODER_LEFT_ONE);
        Serial.print(steps);
        bool newB = digitalRead(ENCODER_LEFT_TWO);
        if (oldA == 0 && newA == 1){
            if (newB == 0){
                steps++;
            };
            if (newB == 1){
                steps--;
            };
        };
        if (oldA == 1 && newA == 0){
            if (newB == 0){
                steps--;
            };
            if (newB == 1){
                steps++;
            };
        };
        revolutions = steps / 64;
        oldA = newA;
        oldB = newB;
    };
    brake();
}

void MotorControl::turnLeft(){
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
}

void MotorControl::turnLeft(int degree){
    turnLeft();
    int count = 0;
    while (count < TURN_SCALE * degree){
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

void MotorControl::turnRight(int degree){
    turnRight();
    int count = 0;
    while (count < TURN_SCALE){
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
    brake();
    delay(time);
}

void MotorControl::backward(){
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
}

void MotorControl::backward(int distance){
    backward();
    int count = 0;
    while (count < TURN_SCALE * distance){
        if (digitalRead(ENCODER_LEFT_ONE) && digitalRead(ENCODER_LEFT_TWO) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}