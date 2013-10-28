/*Have this arduino communicate four values to the second arduino,
a motor left value, a motor right value, a shooter value, and a fourth
value for expandabilities sake.  The second arduino will then convert
them into values useful for its motor controller and echo those values.
Ideally two way communication would be added, though it should not be requisite*/

//Created by Ward Prescott - November, 2013 for Bucknell MARC

int motorl = 0
int motorr = 0
int motor3 = 0
int value4 = 0

void setup (){
            Serial.begin(9600);
}
void loop (){}
