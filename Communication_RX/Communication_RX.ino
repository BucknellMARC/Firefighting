/*Have this arduino communicate four values to the second arduino,
a motor left value, a motor right value, a shooter value, and a fourth
value for expandabilities sake.  The second arduino will then convert
them into values useful for its motor controller and echo those values.
Ideally two way communication would be added, though it should not be requisite*/

//Created by Ward Prescott - November, 2013 for Bucknell MARC

RECIEVER

void setup {
            Serial.begin(9600);
}
void loop {}
