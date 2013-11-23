//Written by Ward Prescott - 2013 - For Bucknell MARC
long     steps;
long     revolutions;
boolean  oldA;
boolean  oldB;
boolean  newA;
boolean  newB;
int Aoutput = 3;
int Boutput = 4;
int button = 7;
boolean state = 0;

void setup(){
  pinMode(Aoutput, INPUT);
  pinMode(Boutput, INPUT);
  pinMode(button, INPUT);
  Serial.begin(9600);
}

void loop(){
  newA = digitalRead(Aoutput);
  newB = digitalRead(Boutput);

  if (oldA == 0 && newA == 1){
    if (newB == 0){
      steps++;
    };
    if (newB == 1){
      steps--;
    };
  };

  if (oldA == 1 && newA == 0){
    if (newB == 0){
      steps--;
    };
    if (newB == 1){
      steps++;
    };
  };

  if (oldB == 0 && newB == 1){
    if (newA == 0){
      steps--;
    };
    if (newA == 1){
      steps++;
    };
  };

  if (oldB == 1 && newB == 0){
    if (newA == 0){
      steps++;
    };
    if (newA == 1){
      steps--;
    };
  };
  oldA = newA;
  oldB = newB;

  revolutions = (steps / (64));  
  state = digitalRead(button);

  if (state == 1) {
    Serial.print(revolutions);
    delay(300);
  };

}



