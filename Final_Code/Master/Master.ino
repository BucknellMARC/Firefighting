#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ET; //Created Object
Servo servo;
int START_BUTTON = 7;
int LED = 9;
boolean CLOSED = true;
boolean OPEN = false;
boolean FOLLOW = true;
boolean NO_FOLLOW = false;

boolean ALIGN = true;
boolean NO_ALIGN = false;
int sensor0;
int sensor1;
int sensor2;
int sensor3;
int sensor4;
int THRESHOLD = 75;

struct SEND_DATA_STRUCTURE{
  char dir;
  boolean condition;
  int dist;
  char side;
  boolean align;
  boolean follow;
};    

SEND_DATA_STRUCTURE data;

void setup (){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  ET.begin(details(data), &Serial);
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
  search();
  blinkLED(1);
}

void drive(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  driveInterrupt(dir, dist, condition, side, align, follow);
  while (data.dir != -1){
    ET.receiveData();
  }
}

void blinkLED(int times){
  for(int i = 0; i < times; i ++){
    digitalWrite(LED, HIGH);
    delay(200);
    digitalWrite(LED, LOW);
    delay(200);
  } 
}

void driveInterrupt(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  data.dir = dir;
  data.condition = condition;
  data.dist = dist;
  data.side = side;
  data.align = align;
  data.follow = follow;
  ET.sendData();
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

