#include <EasyTransfer.h>

EasyTransfer ET; //Created Object

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
  ET.begin(details(data), &Serial);
  pinMode(13, OUTPUT);
}
void loop (){
  drive('f', 0, CLOSED, 'f', ALIGN);
  delay(2500);
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


