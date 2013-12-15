#include <AFMotor.h>
#include <MotorControl.h>

MotorControl MC;
void setup() {
Serial.begin(9600);

}
void loop(){
  MC.forward(1072*6);
  MC.brake(100000);
}
