#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ET; //Created Object
Servo servo;
int START_BUTTON = 7;
int LED = 9;
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
  while(!digitalRead(START_BUTTON)){
    delay(1);
  }
  extinguish();
  
}

void drive(char dir, int dist, boolean condition, char side, boolean align){
  driveInterrupt(dir, dist, condition, side, align);
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

void driveInterrupt(char dir, int dist, boolean condition, char side, boolean align){
  data.dir = dir;
  data.condition = condition;
  data.dist = dist;
  data.side = side;
  data.align = align;
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


