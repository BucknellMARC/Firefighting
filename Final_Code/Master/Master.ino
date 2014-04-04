#include <EasyTransfer.h>
#include <Servo.h>

EasyTransfer ETin, ETout; //Created Object
Servo servo;
int START_BUTTON = 7;
int LED = 9;
int SOUND_DETECTION = 13;
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
  long left;
  long leftCenter;
  long center;
  long rightCenter;
  long right;
};

SEND_DATA_STRUCTURE dataOut;
RECEIVE_DATA_STRUCTURE dataIn;

void setup (){
  Serial.begin(9600);
  pinMode(9, OUTPUT);
  ETout.begin(details(dataOut), &Serial);
  ETin.begin(details(dataIn), &Serial);
  pinMode(13, INPUT);
  servo.attach(8);
  servo.write(0);
  pinMode(A0, INPUT);
  pinMode(A1, INPUT);
  pinMode(A2, INPUT);
  pinMode(A3, INPUT);
  pinMode(A4, INPUT);
}
void loop (){
  while(!digitalRead(START_BUTTON) && !digitalRead(SOUND_DETECTION)){
    delay(1);
  } 
  //ACTUAL CODE 
  alignBeginning();
  if (firstRoom()){
    return;
  } else if (secondRoom()){
    return;
  } else if (thirdRoom()){
    return;
  } else if (fourthRoom()){
    return;
  }  
}

void alignBeginning(){
  drive('r', 0, CLOSED, 'r', NO_ALIGN, NO_FOLLOW);
}

boolean firstRoom(){
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 80, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 10, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 80, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  if (search()){
    goToFlame();
    return true;
  }
  drive('l', 180, 0, 0, 0, 0);
  return false;
}

boolean secondRoom(){
  drive('f', 0, CLOSED, 'f', NO_ALIGN, NO_FOLLOW);
  drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
  drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  if (search()){
    goToFlame();
    return true;
  }
  drive('l', 180, 0, 0, 0, 0);
  return false;
}

boolean thirdRoom(){
  drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
  if (dataIn.front > 200){   // Wall in lower position
     drive('f', 0, OPEN, 'r', NO_ALIGN, FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
     if (search()){
       goToFlame();
       return true;
     }
     drive('f', 0, OPEN, 'l', NO_ALIGN, NO_FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
     drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  } else {  // wall in upper position
    drive('f', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
    if (search()){
      goToFlame();
      return true;
    }
    drive('r', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 0, OPEN, 'l', NO_ALIGN, FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('l', 90, 0, 0, NO_ALIGN, NO_FOLLOW);
    drive('f', 15, 0, 0, NO_ALIGN, NO_FOLLOW);
  }
  return false;
}

boolean fourthRoom(){
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
      if (search()){
        goToFlame();
        return true;
      }
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
        if (search()){
          goToFlame();
          return true;
        }
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
        if (search()){
          goToFlame();
          return true;
        }
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
      if (search()){
        goToFlame();
        return true;
      }
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
      if (search()){
        goToFlame();
        return true;
      }
    }
  }
  return false;
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
  struct flameSensorArray sense;
  sense = avgFlameSensors();
  long avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
  int threshold = 900;
  boolean extinguished = false;
  while (!extinguished){
    servo.write(180);
    delay(2000);
    servo.write(0);
    delay(1000);
    sense = avgFlameSensors();
    avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
    if (avg < 200){
      extinguished = true;
    } else {
      drive('f', 5, 0, 0, NO_ALIGN, NO_FOLLOW);
      sense = avgFlameSensors();
      if (sense.left > sense.right && sense.left > sense.center){
        drive('l', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.right > sense.left && sense.right > sense.center){
        drive('r', 20, 0, 0, NO_ALIGN, NO_FOLLOW);
      }
    }
  }
  blinkLED(5);
}

struct flameSensorArray avgFlameSensors(){
  struct flameSensorArray sense;
  
  sense.left = 0;
  sense.leftCenter = 0;
  sense.center = 0;
  sense.rightCenter = 0;
  sense.right = 0;
  
  for (int i = 0; i < 500; i ++){
    sense.left += analogRead(A0);
    sense.leftCenter += analogRead(A1);
    sense.center += analogRead(A2);
    sense.rightCenter += analogRead(A3);
    sense.right += analogRead(A4);
  }
  sense.left = sense.left/500;
  sense.leftCenter = sense.leftCenter/500;
  sense.center = sense.center/500;
  sense.rightCenter = sense.rightCenter/500;
  sense.right = sense.right/500;
  return sense;
}

void goToFlame(){
  struct flameSensorArray sense = avgFlameSensors();
  
  drive('f', 30, 0, 0, NO_ALIGN, NO_FOLLOW);
  long centerMax = 0;
  int turns = 0;
  long center = 0;
  for (int i = 0; i < 8; i ++){
    center = avgFlameSensors().center;
    if (center > centerMax){
      centerMax = center;
      turns = i;
    }
    drive('r', 45, 0, 0, NO_ALIGN, NO_FOLLOW);
  }
  drive('r', 45 * turns, 0, 0, NO_ALIGN, NO_FOLLOW);
  sense = avgFlameSensors();
  
  int flameThreshold = 600;
  int wallThreshold = 500;
  int forwardDistanceLarge = 13;
  int forwardDistanceSmall = 10;
  int forwardDistanceMin = 7;
  int smallAngle = 20;
  int largeAngle = 25;
  
  for (int i = 0; i < 3; i++){
    long avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
    while (avg < flameThreshold){
      
      if (sense.left < sense.leftCenter && sense.left < sense.center && sense.left < sense.rightCenter 
          && sense.left < sense.right){
        if (dataIn.front < wallThreshold)
          drive('f', forwardDistanceMin, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('r', largeAngle, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.leftCenter < sense.left && sense.leftCenter < sense.center && sense.leftCenter 
                  < sense.rightCenter && sense.leftCenter < sense.right){
        if (dataIn.front < wallThreshold)
          drive('f', forwardDistanceSmall, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('r', smallAngle, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.center < sense.left && sense.center < sense.leftCenter && sense.center < sense.rightCenter 
          && sense.center < sense.right){
        if (dataIn.front < wallThreshold)
          drive('f', forwardDistanceLarge, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else if (sense.rightCenter < sense.left && sense.rightCenter < sense.leftCenter && sense.rightCenter 
                  < sense.center && sense.rightCenter < sense.right){
        if (dataIn.front < wallThreshold)
          drive('f', forwardDistanceSmall, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('l', smallAngle, 0, 0, NO_ALIGN, NO_FOLLOW);
      } else {
        if (dataIn.front < wallThreshold)
          drive('f', forwardDistanceMin, 0, 0, NO_ALIGN, NO_FOLLOW);
        drive('l', largeAngle, 0, 0, NO_ALIGN, NO_FOLLOW);
      }
      sense = avgFlameSensors();
      avg = (sense.left + sense.leftCenter + sense.center + sense.rightCenter + sense.right) / 5;
    }
    flameThreshold += 100;
    forwardDistanceLarge -=2;
    forwardDistanceSmall -= 2;
    forwardDistanceMin -= 2;
    wallThreshold += 50;
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

  drive('l',30,0,0,0,0);
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
  drive('r',60,0,0,0,0);
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
  
  drive('l', 30, 0, 0, 0, 0); // Return robot to prior position
  return flame;
}



