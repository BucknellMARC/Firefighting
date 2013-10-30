//Written by Ward Prescott - 2013 - For Bucknell MARC

              int Aoutput = 2;
              int Boutput = 3;
              long counter;
              long revs;
              long signedrevs;
              int  ratio = 64;
              boolean  oldA;
              boolean  oldB;
              boolean  newA;
              boolean  newB;

void setup(){
              pinMode(Aoutput, INPUT);
              pinMode(Boutput, INPUT);
              }

void loop(){
              newA = digitalRead(Aoutput);
              newB = digitalRead(Boutput);
              if (newA != oldA){
                counter = counter + 1;
              };
              if (newB != oldB){
                counter = counter + 1;
              };
              oldA = newA;
              oldB = newB;
              revs = counter / ratio;
            }
