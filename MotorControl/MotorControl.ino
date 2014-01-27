#include <AFMotor.h>

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(3);
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT = .01318765572869;

void setup(){
  Serial.begin(9600);
  attachInterrupt(0, countLeft, CHANGE);
  attachInterrupt(1, countRight, CHANGE);
  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void loop(){
  forward(10);
  delay(1000);
}

void forward(int dist){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  } while (ticksLeft * TICK_MULT < dist && ticksRight * TICK_MULT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  ticksLeft = 0;
  ticksRight = 0;
}

void backward(int dist){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
  } while (ticksLeft * TICK_MULT < dist && ticksRight * TICK_MULT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  ticksLeft = 0;
  ticksRight = 0;
}

void countLeft(){
  ticksLeft ++; 
}

void countRight(){
  ticksRight ++;
}
