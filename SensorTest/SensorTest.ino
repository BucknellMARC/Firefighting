void setup(){
  Serial.begin(9600);
}

void loop(){
  Serial.println(digitalRead(A0));
  delay(1000);
  Serial.println(digitalRead(A1));
  delay(1000);
  Serial.println(digitalRead(A2));
  delay(1000);
  Serial.println(digitalRead(A3));
  delay(1000);
  Serial.println(digitalRead(A4));
}
