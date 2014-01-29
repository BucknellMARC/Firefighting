//----------------------
// Pin Assignments
//----------------------
int LED = 10;

//----------------------
// Data Values
//----------------------
byte myValue = 0;
byte myValue2 = 23;

//----------------------
// Communication Values
//----------------------

// Message Information
const int DATA_RATE    = 9600; 
const byte DATA_LENGTH = 4;
const char DATA_BEGIN = ':';
const char DATA_END   = ';';
char goodData[DATA_LENGTH + 1];      // One for null terminator
char incomingData[DATA_LENGTH + 1];  // One for null terminator

// Possible states of communication
const byte LOOKING    = 0;
const byte COLLECTING = 1;

// Other values
byte commState     = 0;
byte dataPosition  = 0;


//------------------------
// Setup
//------------------------
void setup()+
{
  Serial.begin(DATA_RATE);
  pinMode(LED, OUTPUT);
}

//------------------------
// Main Program
//------------------------

void loop()
{
  while(Serial.available() > 0){          // Read data while there is data to read
    readData();
  }
  analogWrite(LED, (byte) getByte(0));    // Perform action based on data
  Serial.println(getByte(0));
}

//------------------------
// Serial Data Processing
//------------------------

// ----- Read Data -----
// Get a character from serial and deal with it based on communication state
void readData(){
  char val = Serial.read();        // Read a single byte from serial
  if(commState == LOOKING){
    receiveLooking(val);
  }else{
    receiveCollecting(val);
  }
}

// ----- If commState LOOKING ------
// Deals with data wile in LOOKING communication state

void receiveLooking(char val){
  // Begin message indicator
  if(val == DATA_BEGIN){
    incomingData[0] = DATA_BEGIN;
    commState       = COLLECTING;
    dataPosition    = 1;
  }
}

// ----- If commState COLLECTING -----
// Deals with data while in COLLECTING communication state

void receiveCollecting(char val){
  incomingData[dataPosition] = val;
  dataPosition += 1;
  //End of message indicated
  if(val == DATA_END){
    // Correct Values
    if(dataPosition == DATA_LENGTH){
      saveData();
    }
    // Incorrect Values
    else{
      commState = LOOKING;
      dataPosition = 0;
    }
  }
  // Message longer than expected
  else if(dataPosition > DATA_LENGTH){
    commState = LOOKING;
    dataPosition = 0;
  }
}

// ----- Save Data -----
// Stores incomingData in goodData and resets communication state

void saveData(){
  // Store null terminated string in correct location
  incomingData[DATA_LENGTH] = '\0';
  goodData[DATA_LENGTH] = '\0';
  strcpy(goodData, incomingData);
  
  // Reset the search state
  commState = LOOKING;
  dataPosition = 0;
  Serial.println(goodData);
}

// ----- Convert Data To Bytes -----
// Convert the characters in goodData at index and index + 1 
// from a HEX representation back into their byte values.

byte getByte(int index){
  index = 2*index + 1;                      // 2 -> bytes in pairs, 1 -> first character is DATA_BEGIN
  byte b1 = getNibble(goodData[index]);
  byte b2 = getNibble(goodData[index + 1]);
  return (b1 << 4) + b2;
}

// ----- Get numeric equivillent of given letter -----
byte getNibble(char val){
  return (byte) val - 'a';
}

//------------------------
// End Program
//------------------------
  
