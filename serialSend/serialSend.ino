//----------------------
// Pin Assignments
//----------------------
int BUTTON = 10;

//----------------------
// Data Values
//----------------------
byte myValue = 0;

//----------------------
// Communication Values
//----------------------
const int DATA_RATE    = 9600;     
const int DATA_LENGTH  = 4;
const char DATA_BEGIN  = ':';
const char DATA_END    = ';';
char data[DATA_LENGTH + 1];   // One for the string terminator

//----------------------
// Setup Section
//----------------------
void setup()
{
  Serial.begin(DATA_RATE);
  pinMode(BUTTON, INPUT);
}

//----------------------
// Main Program
//----------------------
void loop()
{
  if(digitalRead(BUTTON) == HIGH)
    myValue = 255;
  else
    myValue = 0;
  sendData();
  
  /*
  if(myValue < 255)
    myValue += 1;
  else
    myValue = 0;
  sendData();
  */
  delay(10);
}

//--------------------------
// Communication  Functions
//--------------------------

// ----- Send Data -----
// Set data and then print it serially
void sendData(){
  setData();
  Serial.print(data);
}

// ----- Set Data -----
// Set each character to be sent based on corresponding value
void setData(){
  data[0] = DATA_BEGIN;      // Begin the message
 
  setByte(0, myValue);       // Set data values
  
  data[3] = DATA_END;        // End the message
  data[DATA_LENGTH] = '\0';  // Terminate the string
}

// ----- Set Byte -----
// Set characters associated with byte [pos] of the data string
void setByte(int pos, byte val){
  pos = 2*pos + 1;                // 2 -> bytes in pairs, 1 -> first character is DATA_BEGIN
  byte b1 = (val & 0xf0) >> 4;    // Set b1 equal to first four bits of val
  byte b2 = val & 0x0f;           // Set b2 equal to last four bits of val
  char c1 = getAlpha(b1);        
  char c2 = getAlpha(b2);
  data[pos] = c1;
  data[pos + 1] = c2;
}

// ----- Get Alpha -----
// Returns the alphabetic character associated with the given byte value
char getAlpha(byte val){
  return (char) 'a' + val;
}
  
