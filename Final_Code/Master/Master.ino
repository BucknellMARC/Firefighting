#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ETin, ETout; //Created Object
Servo servo;
int START_BUTTON = 7;
int LED = 9;
boolean CLOSED = true;
boolean OPEN = false;
boolean FOLLOW = true;
boolean NO_FOLLOW = false;

boolean ALIGN = true;
boolean NO_ALIGN = false;

int THRESHOLD = 75;

struct SEND_DATA_STRUCTURE{
  char dir;
  boolean condition;
  int dist;
  char side;
  boolean align;
  boolean follow;
};    

struct RECEIVE_DATA_STRUCTURE{
  boolean done;
};

SEND_DATA_STRUCTURE dataOut;
RECEIVE_DATA_STRUCTURE dataIn;

void setup (){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  ETout.begin(details(dataOut), &Serial);
  ETin.begin(details(dataIn), &Serial);
  pinMode(13, OUTPUT);
  servo.attach(8);
  servo.write(0);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}
void loop (){
  while(!digitalRead(START_BUTTON)){
    delay(1);
  } 
  driveInterrupt('f', 50, 0, 0, 0, 0); 
  /*drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);*/
  //drive('r', 540, 0, 0, 0, 0);
  blinkLED(3);
}

void drive(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  driveInterrupt(dir, dist, condition, side, align, follow); 
  while (!dataIn.done){
    ETin.receiveData();  
  }
}

void blinkLED(int times){
  for(int i = 0; i < times; i ++){
    digitalWrite(LED, HIGH);
    delay(100);
    digitalWrite(LED, LOW);
    delay(100);
  } 
}

void driveInterrupt(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  dataOut.dir = dir;
  dataOut.condition = condition;
  dataOut.dist = dist;
  dataOut.side = side;
  dataOut.align = align;
  dataOut.follow = follow;
  ETout.sendData();
}

void extinguish(){
  blinkLED(5);
  boolean flamePresent = true; //Insert sensor information to detect if true here
  while(flamePresent){
    servo.write(180);
    delay(1000);
    servo.write(0);
    flamePresent = false; //Insert sensor information to detect if true here
  }
  blinkLED(5);
}

void search(){
  delay(750);
  int checks = 0;
  int sensor0;
  int sensor1;
  int sensor2;
  int sensor3;
  int sensor4;
  while (checks < 4){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      blinkLED(5);
      return;
    };
    checks += 1;
  };

  drive('l',15,0,0,0,0);
  checks = 0;
  delay(500);
  while (checks < 4){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      blinkLED(5);
      return;

    };
    checks += 1;
  };
  drive('r',30,0,0,0,0);
  delay(500);
  checks = 0;
  while (checks < 4){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      blinkLED(5);
      return;

    };
    checks += 1;

  };
}



