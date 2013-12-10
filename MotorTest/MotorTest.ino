#include <AFMotor.h>

AF_DCMotor motorLeft(3);
AF_DCMotor motorRight(2);
int ENCODER_LEFT_A = A4;
int ENCODER_LEFT_B = A5;
int ENCODER_RIGHT_ONE = 6;
int ENCODER_RIGHT_TWO = 9;
int TURN_SCALE = 151.6569768;


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
  int revolutions = 0;
  int steps = 0;
  boolean oldA;
  boolean oldB;
  boolean newA;
  boolean newB;
  while (revolutions < distance){
      newA = digitalRead(ENCODER_LEFT_A);
      newB = digitalRead(ENCODER_LEFT_B);
      if (newA != oldA || newB != oldB){
        steps ++;
      }
      
      /*
      if (oldA == 0 && newA == 1){
          if (newB == 0){
              steps += 1;
          };
          if (newB == 1){
              steps -= 1;
          };
      };
        
        
      if (oldA == 1 && newA == 0){
          if (newB == 0){
              steps -= 1;
          };
          if (newB == 1){
              steps += 1;
          };
       };
        
       if (oldB == 0 && newB == 1){
          if (newA == 0){
              steps -= 1;
          };
          if (newA == 1){
              steps += 1;
          };
       };
        
       if (oldB == 1 && newB == 0){
          if (newA == 0){
              steps += 1;
          };
          if (newA == 1){
              steps -= 1;
          };
       };*/
       oldA = newA;
       oldB = newB;
       revolutions = steps / 64;
    }
    brake();
}

void loop(){
  forward(5);
  brake(1000000000);
}

