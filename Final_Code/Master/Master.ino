#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ET; //Created Object
Servo servo;

boolean OPEN = true;
boolean CLOSED = false;

boolean ALIGN = true;
boolean NO_ALIGN = false;

struct SEND_DATA_STRUCTURE{
  char dir;
  boolean condition;
  int dist;
  char side;
  boolean align;
};    

SEND_DATA_STRUCTURE data;

void setup (){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  ET.begin(details(data), &Serial);
  pinMode(13, OUTPUT);
  servo.attach(8);
  servo.write(0);
}
void loop (){
  while(!digitalRead(7)){
    delay(1);
  }
  drive('r', 0, OPEN, 'r', 0);
  drive('l', 0, OPEN, 'l', 0);
  drive('f', 0, CLOSED, 'f', 0);
}

void drive(char dir, int dist, boolean condition, char side, boolean align){
  driveInterrupt(dir, dist, condition, side, align);
  while (data.dir != -1){
    ET.receiveData();
  }
}

void driveInterrupt(char dir, int dist, boolean condition, char side, boolean align){
  data.dir = dir;
  data.condition = condition;
  data.dist = dist;
  data.side = side;
  data.align = align;
  ET.sendData();
}


