#include <AFMotor.h>
#include <MotorControl.h>
long distance = 1072;
MotorControl MC;
void setup() {
Serial.begin(9600);
pinMode(2, INPUT);

}
void loop(){
MC.forward();
long steps = 0;
bool newA = 0;
bool oldA = 0;
while (steps < (distance - 120)){
    newA = digitalRead(2);
    if (oldA == 0 && newA == 1){
            steps ++;
        };
    oldA = newA;
	};
 
  MC.brake(100000);
}
