#include <AFMotor.h>

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(2);
int ENCODER_LEFT_A = A4;
int ENCODER_LEFT_B = A5;
int ENCODER_RIGHT_ONE = 6;
int ENCODER_RIGHT_TWO = 9;
int TURN_SCALE = 1;


void setup(){
 Serial.begin(9600);
 motorLeft.setSpeed(255);
 motorRight.setSpeed(255);
 brake();
}

void brake(){
  motorLeft.run(RELEASE);
  motorRight.run(RELEASE);
}

void brake(int time){
  brake();
  delay(time);
}

void forward(){
  motorLeft.run(FORWARD);
  motorRight.run(FORWARD);
}

void forward(int distance){
  forward();
  long revolutions = 0;
  long steps = 0;
  boolean oldA;
  boolean oldB;
  boolean newALeft;
  boolean newBLeft;
  while (revolutions * TURN_SCALE < distance){
      newA = digitalRead(ENCODER_LEFT_A);
      newB = digitalRead(ENCODER_LEFT_B);
      if (newA != oldA || newB != oldB){
        steps ++;
      }
      oldA = newA;
      oldB = newB;
      revolutions = steps / 64;
    }
    brake();
}

void loop(){
  forward(800);
  brake(1000000000);
}

