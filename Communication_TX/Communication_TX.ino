/*Have this arduino communicate four values to the second arduino,
 a motor left value, a motor right value, a shooter value, and a fourth
 value for expandabilities sake.  The second arduino will then convert
 them into values useful for its motor controller and echo those values.
 Ideally two way communication would be added, though it should not be requisite*/
//Created by Ward Prescott - November, 2013 for Bucknell MARC

#include <EasyTransfer.h>

EasyTransfer ET; //Created Object
int button = 10;
boolean val = 0;

struct SEND_DATA_STRUCTURE{ //creates data structure, and must be the same on both the TX and RX
  short motorl;
  short motorr;
  short motor3;
  short motor4;
  short motor5;
};         

SEND_DATA_STRUCTURE mydata;

void setup (){
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  pinMode(button, INPUT);
}
void loop (){
  val = digitalRead(button);
  if (val == 1) {
   mydata.motorl = 100;
  }
  else {
   mydata.motorl = 200;
  } 
  mydata.motorr = 200;
  mydata.motor3 = 300;
  mydata.motor4 = 400;
  mydata.motor5 = 500;
  ET.sendData();
    
}

