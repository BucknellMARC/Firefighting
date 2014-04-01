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
int FLAME_SEARCHES = 4;

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
  int front;
  int left;
  int right;
};

struct flameSensorArray{
  int left;
  int leftCenter;
  int center;
  int rightCenter;
  int right;
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
  /*alignBeginning();
  firstRoom();
  secondRoom();
  thirdRoom();
  fourthRoom();*/
  if (search()){
    goToFlame();
  }
  /*Serial.println(analogRead(A0));
  Serial.println(analogRead(A1));
  Serial.println(analogRead(A2));
  Serial.println(analogRead(A3));
  Serial.println(analogRead(A4));
  Serial.println();
  delay(100);*/
}

void alignBeginning(){
  drive('r', 0, CLOSED, 'r', NO_ALIGN, NO_FOLLOW);
}

void firstRoom(){
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 80, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  search();
  drive('l', 180, 0, 0, 0, 0);
}

void secondRoom(){
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  search();
  drive('l', 180, 0, 0, 0, 0);
}

void thirdRoom(){
  drive('f', 20, CLOSED, 'f', NO_ALIGN, NO_FOLLOW);
  if (dataIn.front > 200){   // Wall in lower position
     drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
     search();
     drive('f', 0, OPEN, 'l', NO_ALIGN, NO_FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  } else {  // wall in upper position
    drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
    search();
    drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 0, OPEN, 'l', NO_ALIGN, FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  }
}

void fourthRoom(){
  boolean dogs[3];
 
  drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
  if (dataIn.left > 150){
    dogs[0] = true;
  } else {
    dogs[0] = false;
  }
  
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  if(dataIn.front > 150){
    dogs[1] = true;
  } else {
    dogs[0] = false;
  }
  
  if (!dogs[0] && !dogs[1]){
    dogs[2] = true;
  } else {
    dogs[2] = false;
  }
  
  if (!dogs[1]){
    drive('f', 0, OPEN, 'l', NO_ALIGN, FOLLOW);
    drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
    if (dataIn.left > 150){
      drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
      search();
    } else {
      if (dogs[2]){
        drive('r', 180, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
        drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
        
        drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
        drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
        
        drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
        drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
        search();
      } else {
        drive('f', 0, OPEN, 'l', NO_ALIGN, FOLLOW);
        drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
        
        drive('f', 0, OPEN, 'l', NO_ALIGN, FOLLOW);
        drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
        
        drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
        search();
      }
    }
  } else {
    drive('r', 180, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
    
    if (dataIn.left > 150){
      drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
      search();
    } else {
      drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
      drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
      drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
      drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
      search();
    }
  }
}

void drive(char dir, int dist, boolean condition, char side, boolean align, boolean follow){
  dataIn.done = false;
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

struct flameSensorArray avgFlameSensors(){
  struct flameSensorArray sense;
  
  for (int i = 0; i < 500; i ++){
    sense.left += analogRead(A0);
    sense.leftCenter += analogRead(A1);
    sense.center += analogRead(A2);
    sense.rightCenter += analogRead(A3);
    sense.right += analogRead(A4);
  }
  sense.left /= 500;
  sense.leftCenter /= 500;
  sense.center /= 500;
  sense.rightCenter /= 500;
  sense.right /= 500;
  return sense;
}

void goToFlame(){
  int degreeLong = 45;
  int degreeShort = 30;
  int forwardDist = 7;
  int flameThreshold = 700;
  int i;
  
  struct flameSensorArray sense = avgFlameSensors();
  
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  while (sense.center < sense.left && sense.center < sense.leftCenter && sense.center < sense.rightCenter 
          && sense.center < sense.right){
    drive('r', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
    sense = avgFlameSensors();
  }
  for (i = 0; i < 3; i++){
    sense = avgFlameSensors();
    int avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
    while (avg < flameThreshold){
      
      drive('f', forwardDist, 0, 0, NO_ALIGN, NO_FOLLOW);
      if (sense.left < sense.leftCenter && sense.left < sense.center && sense.left < sense.rightCenter 
          && sense.left < sense.right){
        drive('r', degreeLong, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.leftCenter < sense.left && sense.leftCenter < sense.center && sense.leftCenter 
                  < sense.rightCenter && sense.leftCenter < sense.right){
        drive('r', degreeShort, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.center < sense.left && sense.center < sense.leftCenter && sense.center < sense.rightCenter 
          && sense.center < sense.right){
        
      } else if (sense.rightCenter < sense.left && sense.rightCenter < sense.leftCenter && sense.rightCenter 
                  < sense.center && sense.rightCenter < sense.right){
        drive('l', degreeShort, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else {
        drive('l', degreeLong, 0, 0, NO_ALIGN, NO_FOLLOW);
      }
      sense = avgFlameSensors();
      avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
    }
    flameThreshold += 75;
    degreeShort /= 2;
    degreeLong /= 2;
    forwardDist /= 2;
    blinkLED(1);
  }
  extinguish();
}

boolean search(){
  boolean flame = false;
  int checks = 0;
  int sensor0;
  int sensor1;
  int sensor2;
  int sensor3;
  int sensor4;
  while (checks < FLAME_SEARCHES){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      flame = true;
    };
    checks += 1;
  };

  drive('l',15,0,0,0,0);
  checks = 0;
  delay(500);
  while (checks < FLAME_SEARCHES){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      flame = true;

    };
    checks += 1;
  };
  drive('r',30,0,0,0,0);
  delay(500);
  checks = 0;
  while (checks < FLAME_SEARCHES){
    sensor0 = analogRead(A0);
    sensor1 = analogRead(A1);
    sensor2 = analogRead(A2);
    sensor3 = analogRead(A3);
    sensor4 = analogRead(A4);
    if(sensor0 > THRESHOLD or sensor1 > THRESHOLD or sensor2 > THRESHOLD or sensor3 > THRESHOLD or sensor4 > THRESHOLD){
      flame = true;

    };
    checks += 1;

  };
  
  drive('l', 15, 0, 0, 0, 0); // Return robot to prior position
  return flame;
}



