#include <AFMotor.h>
#include <MotorControl.h>

MotorControl MC;

int distance = 2144;
int steps = 0;

void setup() {
	Serial.begin(9600);
	attachInterrupt(2, doEncoder, CHANGE);
}

void doEncoder() {
	steps ++;
}

void loop(){
	MC.forward();

	while (steps < (distance)){
   	};
  
    MC.brake(100000);
}
