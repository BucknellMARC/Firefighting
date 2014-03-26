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
}
void loop (){
  while(!digitalRead(START_BUTTON)){
    delay(1);
  }
  driveInterrupt('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  driveInterrupt('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  driveInterrupt('r', 90, 0, 0, 0, 0);
  driveInterrupt('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  driveInterrupt('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  driveInterrupt('f', 20, 0, 0, 0, 0);
  driveInterrupt('r', 90, 0, 0, 0, 0);
  driveInterrupt('f', 20, 0, 0, 0, 0);
  
  /*
  drive('r', 90, 0, 0, 0, 0);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  checkRoom();
  drive('l', 180, 0, 0, 0, 0);
  drive('f', 0, CLOSED, 'f', NO_ALIGN, NO_FOLLOW);
  drive('l', 90, 0, 0, 0, 0);*/
  blinkLED(5);
}

void drive(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  driveInterrupt(dir, dist, condition, side, align, follow);
  while (data.dir != -1){
    ET.receiveData();
    delay(5);
  }
}

void checkRoom(){
  // INSERT CODE TO CHECK IF THERE IS FLAME IN ROOM
  /*
  if (FLAME IN ROOM){
    MOVE TOWARDS FLAME
    extinguish();
    loop();
  }
  */
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


