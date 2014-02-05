#include <EasyTransfer.h>
#include <AFMotor.h>

EasyTransfer ET;
const int NEAR_DISTANCE = 5;

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(1);
int ENCODER_LEFT = 1;  // Argument of 1 means encoder is connected to pin 3
int ENCODER_RIGHT = 0; // Argument of 0 means encode is connected to pin 2
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT_STRAIT = .02637581; // Real value is 0.02637581
double TICK_MULT_TURN = TICK_MULT_STRAIT * 6.0311347;

struct MotorInstruction{
  char dir;
  char condition;
  int dist;
  char side;
};

MotorInstruction data;

void setup(){
  Serial.begin(9600);
  ET.begin(details(data), &Serial);
  attachInterrupt(ENCODER_LEFT, countLeft, RISING);
  attachInterrupt(ENCODER_RIGHT, countRight, RISING);
  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}



void loop(){
  delay(1000); // Allow MC to catch up with itself
  /* Put in serial code to get move commands here.
     Code should wait for instruction, act, then send return signal. */
  if (ET.receieve()){
    processSerialData(data);
  }
}

void processSerialData(String inputString){
  if (inputString[0] == ':' && inputString[inputString.length() - 1] == ';'){
    // Processing well formatted string
    int distance = 0;
    char buff[3];
    inputString.substring(2,5).toCharArray(buff, 3);
    char dir = inputString[1];
    if (dir == 'f'){
      forward(distance);
    } else if (dir == 'b'){
      backward(distance);
    } else if (dir == 'l'){
      left(distance);
    } else if (dir == 'r'){
      right(distance);
    }
  } else {
    // Processing ill formatted string
    // Implement functionality to call for new string from master
    return;
  }
}

void forward(double dist){
  int tickMult = TICK_MULT_STRAIT;
  if (dist < 50 && dist > 25){
    tickMult -= .0035;
  } else if (dist < 25){
    dist -= 2;
  }
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

void backward(double dist){
  if (dist < 25){
    dist -= 2;
  }
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(BACKWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(BACKWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
    }
    motorRight.run(BACKWARD);
    
  } while (ticksLeft * TICK_MULT_STRAIT < dist || ticksRight * TICK_MULT_STRAIT < dist);
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

void left(double deg){
  if (deg > 30){
    deg -= 5;
  } else if (deg > 15){
    deg -= 3;
  }
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg & ticksRight * TICK_MULT_TURN < deg);
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

void right(double deg){
  if (deg > 30){
    deg -= 5;
  } else if (deg > 15){
    deg -= 3;
  }
  do{
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg & ticksRight * TICK_MULT_TURN < deg);
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
