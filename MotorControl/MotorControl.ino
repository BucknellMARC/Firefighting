#include <AFMotor.h>

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(3);
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT_STRAIT = .01318765572869;
double TICK_MULT_TURN = TICK_MULT_STRAIT * 5.20871012;

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
  /* Put in serial code to get move commands here.
     Code should wait for instruction, act, then send return signal. */
  
  forward(10);
  delay(1000);
  backward(10);
  delay(1000);
  left(30);
  delay(1000);
  right(30);
  delay(1000);
}

void forward(int dist){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
  } while (ticksLeft * TICK_MULT_STRAIT < dist && ticksRight * TICK_MULT_STRAIT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  ticksLeft = 0;
  ticksRight = 0;
}

void backward(int dist){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
  } while (ticksLeft * TICK_MULT_STRAIT < dist && ticksRight * TICK_MULT_STRAIT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  ticksLeft = 0;
  ticksRight = 0;
}

void left(int deg){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
  } while (ticksLeft * TICK_MULT_TURN < deg && ticksRight * TICK_MULT_TURN < deg);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  ticksLeft = 0;
  ticksRight = 0;
}

void right(int deg){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
  } while (ticksLeft * TICK_MULT_TURN < deg && ticksRight * TICK_MULT_TURN < deg);
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
