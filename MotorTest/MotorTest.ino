#include <MotorControl.h>

MotorControl c;

void setup(){
 Serial.begin(9600);
}

void loop(){
  c.forward(5);
  c.brake(100000);
}
