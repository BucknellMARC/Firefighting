void setup(){
  Serial.begin(9600);
  Serial.print("FlameSensorArray Test");
}

void loop(){
  Serial.println(analogRead(0));
  Serial.println(analogRead(1));
  Serial.println(analogRead(2));
  Serial.println(analogRead(3));
  Serial.println();
  delay(2500);
}
