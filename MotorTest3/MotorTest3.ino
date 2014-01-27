#include <MotorControl.h>
#include <AFMotor.h>

MotorControl MC;

int distance = 2144;
volatile int steps = 0;

void setup() {
  Serial.begin(9600);
  attachInterrupt(0, doEncoder, CHANGE);
}

void doEncoder() {
  steps ++;
}

void loop() {
  while (steps < (distance)){
      MC.forward();
            };
  MC.brake(100000);
}

