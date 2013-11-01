//sine wave freq detection with 38.5kHz sampling rate and interrupts
//by Amanda Ghassaei
//http://www.instructables.com/id/Arduino-Frequency-Detection/
//July 2012

/*
 * This program is free software; you can redistribute it and/or modify
 * it under the terms of the GNU General Public License as published by
 * the Free Software Foundation; either version 3 of the License, or
 * (at your option) any later version.
 *
 */

boolean startup = true;
//clipping indicator variables
boolean clipping = 0;
//data storage variables
byte newData = 0;
byte prevData = 0;
byte newfreqstor = 1;
byte prevfreqstor = 1;

//freq variables
unsigned int timer = 0;//counts period of wave
unsigned int period;
int frequency;

void setup(){
  delay(50);
  Serial.begin(9600);

  pinMode(13,OUTPUT);//led indicator pin

  cli();//diable interrupts

  //set up continuous sampling of analog pin 0

  //clear ADCSRA and ADCSRB registers
  ADCSRA = 0;
  ADCSRB = 0;

  ADMUX |= (1 << REFS0); //set reference voltage
  ADMUX |= (1 << ADLAR); //left align the ADC value- so we can read highest 8 bits from ADCH register only

  ADCSRA |= (1 << ADPS2) | (1 << ADPS0); //set ADC clock with 32 prescaler- 16mHz/32=500kHz
  ADCSRA |= (1 << ADATE); //enabble auto trigger
  ADCSRA |= (1 << ADIE); //enable interrupts when measurement complete
  ADCSRA |= (1 << ADEN); //enable ADC
  ADCSRA |= (1 << ADSC); //start ADC measurements

  sei();//enable interrupts
}

ISR(ADC_vect) {//when new ADC value ready

  prevData = newData;//store previous value
  newData = ADCH;//get value from A0
  if (prevData < 127 && newData >=127){//if increasing and crossing midpoint
    period = timer;//get period
    timer = 0;//reset timer
  }


  if (newData == 0 || newData == 1023){//if clipping
    PORTB |= B00100000;//set pin 13 high- turn on clipping indicator led
    clipping = 1;//currently clipping
  }

  timer++;//increment timer at rate of 38.5kHz
}

void loop(){ 
  if (startup == true){ 

    do {
      // if (clipping){//if currently clipping
      //   PORTB &= B11011111;//turn off clippng indicator led         ***CLIPPING CODE***  
      // clipping = 0;}
      frequency = 38462/period;//timer rate/period  
      Serial.print(frequency);
      Serial.println(" hz");
      delay (50);
      if (frequency < 3600 || frequency > 4000) {
        newfreqstor = prevfreqstor + 1;
        prevfreqstor = newfreqstor;
      }
    } 
    while (newfreqstor < 50);

    cli(); // disable interupts to properly reset analog register values
    ADCSRA=0; //reset register value (presumably to stop the constant collection)
    ADCSRA=0; //reset other register value listed above
    sei();  //let interrups happen again since they are used in many vital functions
    startup = !startup;
  }
  else if (startup == false){
    Serial.write("ready for the real stuff" );
  }
}



