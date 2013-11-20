//Written by Ward Prescott - 2013 - For Bucknell MARC
long     steps;
long     oldsteps;
long     revolutions;
boolean  oldA;
boolean  oldB;
boolean  newA;
boolean  newB;
int Aoutput = 2;
int Boutput = 3;

void setup(){
  pinMode(Aoutput, INPUT);
  pinMode(Boutput, INPUT);
  Serial.begin(9600);
}

void loop(){
  newA = digitalRead(Aoutput);
  newB = digitalRead(Boutput);

  if (oldA == 0 && newA == 1){
    if (newB == 0){
      steps = oldsteps + 1;
      oldsteps = steps;
    };
    if (newB == 1){
      steps = oldsteps - 1;
      oldsteps = steps;
    };
  };
  
  
  if (oldA == 1 && newA == 0){
    if (newB == 0){
      steps = oldsteps - 1;
      oldsteps = steps;
    };
    if (newB == 1){
      steps = oldsteps + 1;
      oldsteps = steps;
    };
  };
  
  if (oldB == 0 && newB == 1){
    if (newA == 0){
      steps = oldsteps - 1;
      oldsteps = steps;
    };
    if (newA == 1){
      steps = oldsteps + 1;
      oldsteps = steps;
    };
  };
  
  if (oldB == 1 && newB == 0){
    if (newA == 0){
      steps = oldsteps + 1;
      oldsteps = steps;
    };
    if (newA == 1){
      steps = oldsteps - 1;
      oldsteps = steps;
    };
  };
revolutions = steps / 64;  
}


