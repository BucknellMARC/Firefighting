#include <AFMotor.h>

const int NEAR_DISTANCE = 5;

AF_DCMotor motorLeft(1);
AF_DCMotor motorRight(3);
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT_STRAIT = .02637531 / 2;
double TICK_MULT_TURN = TICK_MULT_STRAIT * 6.0311347;

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
  
  left(90);
  delay(2000);
}

void forward(int dist){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(FORWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
    }
    motorRight.run(FORWARD);
    
  } while (ticksLeft * TICK_MULT_STRAIT < dist || ticksRight * TICK_MULT_STRAIT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
}

void backward(int dist){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(FORWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
    }
    motorRight.run(FORWARD);
    
  } while (ticksLeft * TICK_MULT_STRAIT < dist && ticksRight * TICK_MULT_STRAIT < dist);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
}

void left(int deg){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(BACKWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
    }
    motorRight.run(FORWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg && ticksRight * TICK_MULT_TURN < deg);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
}

void right(int deg){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(FORWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
    }
    motorRight.run(BACKWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg && ticksRight * TICK_MULT_TURN < deg);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(100);
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
