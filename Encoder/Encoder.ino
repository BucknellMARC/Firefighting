//Written by Ward Prescott - 2013 - For Bucknell MARC
#include <MotorControl.h>

MotorControl c;

long     steps;
long     revolutions;
boolean  oldA;
boolean  oldB;
boolean  newA;
boolean  newB;
<<<<<<< HEAD
int Aoutput = A4;
int Boutput = A5;
=======
int Aoutput = 10;
int Boutput = 11;
int button = 9;
boolean state = 0;
>>>>>>> 9aa6aa13a17cf821f68277b31321a223c2bc0e79

void setup(){
  pinMode(Aoutput, INPUT);
  pinMode(Boutput, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
  
}

void loop(){
  newA = digitalRead(Aoutput);
  newB = digitalRead(Boutput);

  if (oldA == 0 && newA == 1){
    if (newB == 0){
      steps++;
    };
    if (newB == 1){
      steps--;
    };
  };

  if (oldA == 1 && newA == 0){
    if (newB == 0){
      steps--;
    };
    if (newB == 1){
      steps++;
    };
  };

  if (oldB == 0 && newB == 1){
    if (newA == 0){
      steps--;
    };
    if (newA == 1){
      steps++;
    };
  };

  if (oldB == 1 && newB == 0){
    if (newA == 0){
      steps++;
    };
    if (newA == 1){
      steps--;
    };
  };
<<<<<<< HEAD
  oldA = newA;
  oldB = newB;
=======
<<<<<<< HEAD
>>>>>>> 9aa6aa13a17cf821f68277b31321a223c2bc0e79
revolutions = steps / 64;
if (digitalRead(6) == 1){
  Serial.println(revolutions);
  delay(500);
}
=======
  oldA = newA;
  oldB = newB;

  revolutions = (steps / (64));  
  state = digitalRead(button);

  if (state == 1) {
    Serial.print(revolutions);
    delay(300);
  };

>>>>>>> 91d99e7e24fa2135290ec816a8814256f3800ab6
}



