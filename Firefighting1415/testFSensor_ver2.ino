int sensorPin[] = {A0,A1,A2,A4}; //an array of pin numbers to which sensors are attached
int readFSensor[4]; //an array that record sensor reading
int pinCount=3;
int ledPin[]={3,4,2};
boolean flame = false;
const int upperThreshold = 300;
const int lowerThreshold = 400;
  
// the setup routine runs once you press reset
void setup() {
  Serial.begin(9600);
  pinMode(ledPin[0],OUTPUT);
  pinMode(ledPin[1],OUTPUT);
  pinMode(ledPin[2],OUTPUT);
}
// the loop routine runs over and over again forever
void loop() {
  //record sensor value into an array
  for(int thisPin = 0; thisPin <= pinCount; thisPin++){
    readFSensor[thisPin]=analogRead(sensorPin[thisPin]);
  };
  //test if the robot is in front of the flame
  if (readFSensor[1] = readFSensor[2] and readFSensor[1]>upperThreshold and readFSensor[2]>upperThreshold){
    digitalWrite(ledPin[1], HIGH);
    flame=true;
  }; 
  //if left sensors sense something, light up left LED
  if (readFSensor[0]>lowerThreshold) {
    flame=false;
    while (flame==false){
      for(int thisPin = 0; thisPin <= pinCount; thisPin++){
    readFSensor[thisPin]=analogRead(sensorPin[thisPin]);
  };
      digitalWrite(ledPin[0], HIGH);
      if (readFSensor[1] = readFSensor[2] and readFSensor[1]>upperThreshold and readFSensor[2]>upperThreshold){
        digitalWrite(ledPin[1], HIGH);
        digitalWrite(ledPin[0], LOW);
        flame=true;};
    }; 
  };
   
  //if right sensors sense something, light up right LED
  if (readFSensor[3]>lowerThreshold) {
    flame=false;
     while (flame==false){
       for(int thisPin = 0; thisPin <= pinCount; thisPin++){
    readFSensor[thisPin]=analogRead(sensorPin[thisPin]);
  };
      digitalWrite(ledPin[2], HIGH);
      if (readFSensor[1] = readFSensor[2] and readFSensor[1]>upperThreshold and readFSensor[2]>upperThreshold){
        digitalWrite(ledPin[1], HIGH);
        
        flame=true;};
  };
  };
  delay(2);
  digitalWrite(ledPin[0],LOW);
  digitalWrite(ledPin[1],LOW);
  digitalWrite(ledPin[2],LOW);
}

