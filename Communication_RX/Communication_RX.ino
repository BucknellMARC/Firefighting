/*Have this arduino communicate four values to the second arduino,
 a motor left value, a motor right value, a shooter value, and a fourth
 value for expandabilities sake.  The second arduino will then convert
 them into values useful for its motor controller and echo those values.
 Ideally two way communication would be added, though it should not be requisite*/
//Created by Ward Prescott - November, 2013 for Bucknell MARC

#include <EasyTransfer.h>

EasyTransfer ET;

struct RECEIVE_DATA_STRUCTURE{
  int motorl;
  int motorr;
  int motor3;
  int value4;
};

RECEIVE_DATA_STRUCTURE mydata;

void setup(){
  int LED = 10;
  Serial.begin(9600);
  ET.begin(details(mydata), &Serial);
  pinMode(LED, OUTPUT);

}

void loop(){
  if(ET.receiveData()){
    if(mydata.value4 == 400){
      digitalWrite(10, HIGH);
            delay(10000);
    }
    
  };
  mydata.value4 = 0;
  delay(250);
}



