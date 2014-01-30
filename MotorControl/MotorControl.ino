#include <AFMotor.h>

const int NEAR_DISTANCE = 5;

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(1);
int ENCODER_LEFT = 1;  // Argument of 1 means encoder is connected to pin 3
int ENCODER_RIGHT = 0; // Argument of 0 means encode is connected to pin 2
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT_STRAIT = .0285; // Real value is 0.02637581
double TICK_MULT_TURN = TICK_MULT_STRAIT * 6.0311347;

void setup(){
  Serial.begin(9600);
  attachInterrupt(ENCODER_LEFT, countLeft, RISING);
  attachInterrupt(ENCODER_RIGHT, countRight, RISING);
  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);
  //motorLeft.run(RELEASE);
  //motorRight.run(RELEASE);
}

void loop(){
  /* Put in serial code to get move commands here.
     Code should wait for instruction, act, then send return signal. */
  
  forward(100);
  left(90);
  forward(50);
  right(180);
  backward(50);
  right(90);
  forward(100);
  right(270);
  backward(100);

  delay(2000);
}

void serialEvent(){
  String inputString = "";
  while (Serial.available()) {
    char inChar = (char)Serial.read();
    inputString += "";
    if (inChar == ';'){
      processSerialData(inputString);
    }
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
  do{
    motorLeft.run(FORWARD);
    motorRight.run(FORWARD);
    
    while (ticksLeft > ticksRight) {
      motorLeft.run(RELEASE);
    }
    motorLeft.run(FORWARD);
    while (ticksRight > ticksLeft){
      motorRight.run(RELEASE);
      Serial.println(ticksLeft);
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

void left(double deg){
  do{
    motorLeft.run(BACKWARD);
    motorRight.run(FORWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg & ticksRight * TICK_MULT_TURN < deg);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  int stopTime = 100;
  if (deg < 90){
    stopTime = 50;
  }
  if (deg < 30){
    stopTime = 10;
  }
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);

  ticksLeft = 0;
  ticksRight = 0;
}

void right(double deg){
  do{
    motorLeft.run(FORWARD);
    motorRight.run(BACKWARD);
    
  } while (ticksLeft * TICK_MULT_TURN < deg & ticksRight * TICK_MULT_TURN < deg);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  int stopTime = 100;
  if (deg < 90){
    stopTime = 50;
  }
  if (deg < 30){
    stopTime = 10;
  }
  
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(deg);
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
