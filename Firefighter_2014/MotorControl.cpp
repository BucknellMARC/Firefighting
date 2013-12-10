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
int ENCODER_LEFT_A = A4;
int ENCODER_LEFT_B = A5;
int ENCODER_RIGHT_ONE = 6;
int ENCODER_RIGHT_TWO = 9;
int TURN_SCALE = 151.6569768;


MotorControl::MotorControl(){
    Serial.begin(9600);
    Serial.print("MotorControl initiated");
    pinMode(ENCODER_LEFT_A, INPUT);
    pinMode(ENCODER_LEFT_B, INPUT);
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
    //forward();
    int revolutions = 0;
    int steps = 0;
    int oldsteps = 0;
    bool oldA;
    bool oldB;
    bool newA;
    bool newB;
    while (true){
        newA = digitalRead(A4);
        newB = digitalRead(A5);
        
        if (oldA == 0 && newA == 1){
            if (newB == 0){
                steps = oldsteps + 1;
                oldsteps = steps;
            };
            if (newB == 1){
                steps = oldsteps - 1;
                oldsteps = steps;
            };
        };
        
        
        if (oldA == 1 && newA == 0){
            if (newB == 0){
                steps = oldsteps - 1;
                oldsteps = steps;
            };
            if (newB == 1){
                steps = oldsteps + 1;
                oldsteps = steps;
            };
        };
        
        if (oldB == 0 && newB == 1){
            if (newA == 0){
                steps = oldsteps - 1;
                oldsteps = steps;
            };
            if (newA == 1){
                steps = oldsteps + 1;
                oldsteps = steps;
            };
        };
        
        if (oldB == 1 && newB == 0){
            if (newA == 0){
                steps = oldsteps + 1;
                oldsteps = steps;
            };
            if (newA == 1){
                steps = oldsteps - 1;
                oldsteps = steps;
            };
        };
        oldA = newA;
        oldB = newB;
        revolutions = steps / 64;
        Serial.println(revolutions);
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
    while (count < TURN_SCALE * degree){
        if (digitalRead(ENCODER_LEFT_A) && digitalRead(ENCODER_LEFT_B) &&
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
        if (digitalRead(ENCODER_LEFT_A) && digitalRead(ENCODER_LEFT_B) &&
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
        if (digitalRead(ENCODER_LEFT_A) && digitalRead(ENCODER_LEFT_B) &&
            digitalRead(ENCODER_RIGHT_ONE) && digitalRead(ENCODER_RIGHT_TWO)){
            count++;
        }
    }
    brake();
}