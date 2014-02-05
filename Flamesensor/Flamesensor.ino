/* 
 Methodology:
 If any of the sensors read something over the base threshold the robot will halt.
 It will then take a closer look.
 If it determines that there is indeed a flame it will move to align itself with the center sensor.
 It will double check if it is alighned well.
 It will loop until it is aligned
 Then it will advance forward some distance, align again, and make sure that it is not over the closeness threshold for distance.
 It will repeat this until it gets to the required closeness.
 */

int sensor1 = A0;
int sensor2 = A1;
int sensor3 = A2;
int sensor4 = A3;
int sensor5 = A4;

int state1;
int state2;
int state3;
int state4;
int state5;

float sensorArray[5];

void setup(){
  
}

void loop(){
  
  state1 = analogRead(sensor1);
  state2 = analogRead(sensor2);
  state3 = analogRead(sensor3);
  state4 = analogRead(sensor4);
  state5 = analogRead(sensor5);
  
  readFlameSensor(&sensorArray[0]);
}

void readFlameSensor(float *valueArray){

  valueArray[0] = state1;
  valueArray[1] = state2;
  valueArray[2] = state3;
  valueArray[3] = state4;
  valueArray[4] = state5;
}


//Returns a double indicating direction of the flame.
//A negative number indicates a relatively left direction, a positive number indicates a right direction
//Check if negative and positive actually map to right and left.
double getFlameDirection(float *valueArray){
  
  //Sensor 3 is not included because it only detects straight ahead
  sensorAngle = state1*-2 + state2*-1 + state4*1 + state5*3;
}
