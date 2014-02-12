#include <Average.h>  //used to perform math operations like average on an array, usueful for stabilizing data
#include <EasyTransfer.h>
#include <AFMotor.h>


EasyTransfer ET;
AF_DCMotor motorLeft(3); 
AF_DCMotor motorRight(1);
int ENCODER_LEFT = 1;  // Argument of 1 means encoder is connected to pin 3
int ENCODER_RIGHT = 0; // Argument of 0 means encode is connected to pin 2
long ticksLeft = 0;
long ticksRight = 0;
double TICK_MULT_STRAIT = .02637581; // Real value is 0.02637581
double TICK_MULT_TURN = TICK_MULT_STRAIT * 6.0311347;
boolean OPEN = true;
boolean CLOSED = false;
int DIST_SENSOR_FRONT = A0;
int DIST_SENSOR_LEFT = A1;
int DIST_SENSOR_RIGHT = A2;
float leftarray[5];    //Array used to store several values of left distance sensor
float rightarray[5];   //Array used to store several values of right distance sensor
float leftIRavg;
float rightIRavg;


struct RECEIVE_DATA_STRUCTURE{
  char dir;
  boolean condition;
  int dist;
  char side;
};

RECEIVE_DATA_STRUCTURE data;

void setup(){
  Serial.begin(9600);
  pinMode(13, OUTPUT);
  ET.begin(details(data), &Serial);
  attachInterrupt(ENCODER_LEFT, countLeft, RISING);
  attachInterrupt(ENCODER_RIGHT, countRight, RISING);
  motorLeft.setSpeed(255);
  motorRight.setSpeed(255);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void loop(){
  /* Put in serial code to get move commands here.
     Code should wait for instruction, act, then send return signal. */
  // if (ET.receiveData()){
  //   processData();
  // }
  align();
  delay(5000);
}

void processData(){
  int distance = data.dist;
  if (distance > 0){
    if (data.dir == 'r'){
      right(distance);
    } else if (data.dir == 'l'){
      left(distance);
    } else if (data.dir == 'f'){
      forward(distance);
    } else if (data.dir == 'b'){
      backward(distance);
    }
  } /*else {
    if (data.dir == 'r'){
      rightCondition(data.condition, data.side);
    } else if (data.dir == 'l'){
      leftCondition(data.condition, data.side);
    } else if (data.dir == 'f'){
      forwardCondition(data.condition, data.side);
    } else if (data.dir == 'b'){
      backwardCondition(data.condition, data.side);
    }
  }*/
}

void done(){
  data.dir = -1;
  data.condition = 0;
  data.dist = 0;
  data.side = 0;
  ET.sendData();
}

void align(){
    senseLR();
    
    while( ((abs(leftIRavg - rightIRavg))/((leftIRavg+rightIRavg)/2)) > .50){
       
     if (leftIRavg < .9*rightIRavg){   // This will be if it is left in the hall
       right(30.0);
       delay(50);
       forward(10);
       delay(50);
       left(30.0);
     }         
     if (rightIRavg < .9*leftIRavg){
       left(30.0);
       delay(50);
       forward(10);
       delay(50);
       right(30.0);
     }
    senseLR();
   };
   
  
 }
 
void senseLR(){ //This function returns an 2 length array with a left and right IR sensor value.  These two values are composed of the average of 10 of their values.
leftarray[0] = analogRead(DIST_SENSOR_LEFT);
rightarray[0] = analogRead(DIST_SENSOR_RIGHT);
delay(3);
leftarray[1] = analogRead(DIST_SENSOR_LEFT);
rightarray[1] = analogRead(DIST_SENSOR_RIGHT);
delay(3);
leftarray[2] = analogRead(DIST_SENSOR_LEFT);
rightarray[2] = analogRead(DIST_SENSOR_RIGHT);
delay(3);
leftarray[3] = analogRead(DIST_SENSOR_LEFT);
rightarray[3] = analogRead(DIST_SENSOR_RIGHT);
delay(3);
leftarray[4] = analogRead(DIST_SENSOR_LEFT);
rightarray[4] = analogRead(DIST_SENSOR_RIGHT);
delay(3);
leftIRavg = mean(leftarray, 5);
rightIRavg = mean(rightarray, 5);
}


void forwardCondition(char condition, char side){
  int distSensor = DIST_SENSOR_FRONT;
  if (side == 'l'){
    distSensor = DIST_SENSOR_LEFT;
  } else if (side == 'r'){
    distSensor = DIST_SENSOR_RIGHT;
  }
  boolean conditionMet = false;
  while (!conditionMet){
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
    
    if (condition == OPEN){
      conditionMet = (analogRead(distSensor) > 512);
    } else {
      conditionMet = (analogRead(distSensor) <= 512);
    }
  }
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(BACKWARD);
  motorRight.run(BACKWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
  done();
}

void forward(int dist){
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
  done();
}

void backwardCondition(char condition, char side){
  int distSensor = DIST_SENSOR_FRONT;
  if (side == 'l'){
    distSensor = DIST_SENSOR_LEFT;
  } else if (side == 'r'){
    distSensor = DIST_SENSOR_RIGHT;
  }
  boolean conditionMet = false;
  while (!conditionMet){
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
    
    if (condition == OPEN){
      conditionMet = (analogRead(distSensor) > 512);
    } else {
      conditionMet = (analogRead(distSensor) <= 512);
    }
  }
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
  done();
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
  done();
}

void leftCondition(char condition, char side){
  int distSensor = DIST_SENSOR_FRONT;
  if (side == 'l'){
    distSensor = DIST_SENSOR_LEFT;
  } else if (side == 'r'){
    distSensor = DIST_SENSOR_RIGHT;
  }
  boolean conditionMet = false;
  while (!conditionMet){
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
    
    if (condition == OPEN){
      conditionMet = (analogRead(distSensor) > 512);
    } else {
      conditionMet = (analogRead(distSensor) <= 512);
    }
  }
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(FORWARD);
  motorRight.run(BACKWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
  done();
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
  done();
}


void rightCondition(char condition, char side){
  int distSensor = DIST_SENSOR_FRONT;
  if (side == 'l'){
    distSensor = DIST_SENSOR_LEFT;
  } else if (side == 'r'){
    distSensor = DIST_SENSOR_RIGHT;
  }
  boolean conditionMet = false;
  while (!conditionMet){
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
    
    if (condition == OPEN){
      conditionMet = (analogRead(distSensor) > 512);
    } else {
      conditionMet = (analogRead(distSensor) <= 512);
    }
  }
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  motorLeft.run(BACKWARD);
  motorRight.run(FORWARD);
  delay(100);
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
  
  ticksLeft = 0;
  ticksRight = 0;
  done();
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
  done();
}

void countLeft(){
  ticksLeft ++;
}

void countRight(){
  ticksRight ++;
}
