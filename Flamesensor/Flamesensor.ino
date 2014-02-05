/* 
Methodology:
If any of the sensors read something over the base threshold the robot will halt.
It will then take a closer look.
If it determines that there is indeed a flame it will move to align itself with the center sensor.
It will double check if it is alighned well.
It will loop until it is aligned
Then it will advance forward some distance, align again, and make sure that it is not over the closeness threshold for distance.
It will repeat this until it gets to the required closeness.

*/

void setup(){
	int sensor1 = A0;
	int sensor2	= A1;
	int sensor3 = A2;
	int sensor4 = A3;
	int sensor5 = A4;

	int state1;
	int state2;
	int state3;
	int state4;
	int state5;	
}
void loop() {
	state1 = analogRead(sensor1);
	state2 = analogRead(sensor2);
	state3 = analogRead(sensor3);
	state4 = analogRead(sensor4);
	state5 = analogRead(sensor5);

}