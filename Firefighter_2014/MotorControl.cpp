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
int ENCODER_LEFT_A = 10;
int ENCODER_LEFT_B = 11;
int ENCODER_RIGHT_A = 6;
int ENCODER_RIGHT_B = 9;
int button = 9;
int state = 0;
//int TURN_SCALE = 0.0065283615521376;
int TURN_SCALE = 67;

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
	pinMode(button, INPUT);
	pinMode(ENCODER_LEFT_A, INPUT);
	pinMode(ENCODER_LEFT_B, INPUT);
	int revolutions = 0;
    int steps = 0;
	while ((revolutions / TURN_SCALE) < 500){
		newA = digitalRead(ENCODER_LEFT_A);
		newB = digitalRead(ENCODER_LEFT_B);
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

		if (oldB == 0 && newB == 1){
			if (newA == 0){
			  steps--;
			};
			if (newA == 1){
			  steps++;
			};
		};

		if (oldB == 1 && newB == 0){
			if (newA == 0){
				steps++;
			};
			if (newA == 1){
				steps--;
			};
		};
		oldA = newA;
		oldB = newB;
		revolutions = (steps / (64));
		state = digitalRead(button);
		if (state == 1){
			Serial.print(revolutions);
			delay(200);
		};		
    };
    brake();
}
/*
void MotorControl::turnLeft(){
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
}

void MotorControl::turnLeft(int degree){
    turnLeft();
    int count = 0;
    while (count < TURN_SCALE * degree){
        
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
*/
void MotorControl::brake(){
    motorLeft.run(RELEASE);
    motorRight.run(RELEASE);
}

void MotorControl::brake(int time){
    brake();
    delay(time);
}
/*
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
*/