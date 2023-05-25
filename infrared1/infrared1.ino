//www.elegoo.com
//2016.12.9

#include "IRremote.h"

const int RECEIVER = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int SEVEN_SEG_OFF[7] = {0, 0, 0, 0, 0, 0, 0};
const int SEVEN_SEG_0[7] = {1, 1, 1, 0, 1, 1, 1};
const int SEVEN_SEG_1[7] = {1, 0, 0, 0, 0, 0, 1};
const int SEVEN_SEG_2[7] = {0, 1, 1, 1, 0, 1, 1};
const int SEVEN_SEG_3[7] = {1, 1, 0, 1, 0, 1, 1};
const int SEVEN_SEG_4[7] = {1, 0, 0, 1, 1, 0, 1};
const int SEVEN_SEG_5[7] = {1, 1, 0, 1, 1, 1, 0};
const int SEVEN_SEG_6[7] = {1, 1, 1, 1, 1, 1, 0};
const int SEVEN_SEG_7[7] = {1, 0, 0, 0, 0, 1, 1};
const int SEVEN_SEG_8[7] = {1, 1, 1, 1, 1, 1, 1};
const int SEVEN_SEG_9[7] = {1, 1, 0, 1, 1, 1, 1};

const unsigned long IR_POWER =  0xFFA25D;
const unsigned long IR_FUNC_STOP =  0xFFE21D;
const unsigned long IR_VOL_UP = 0xFF629D;
const unsigned long IR_FAST_BACK =  0xFF22DD;
const unsigned long IR_PAUSE =  0xFF02FD;
const unsigned long IR_FAST_FORWARD = 0xFFC23D;
const unsigned long IR_DOWN = 0xFFE01F;
const unsigned long IR_VOL_DOWN = 0xFFA857;
const unsigned long IR_UP = 0xFF906F;
const unsigned long IR_EQ = 0xFF9867;
const unsigned long IR_ST_REPT =  0xFFB04F;
const unsigned long IR_0 =  0xFF6897;
const unsigned long IR_1 =  0xFF30CF;
const unsigned long IR_2 =  0xFF18E7;
const unsigned long IR_3 =  0xFF7A85;
const unsigned long IR_4 =  0xFF10EF;
const unsigned long IR_5 =  0xFF38C7;
const unsigned long IR_6 =  0xFF5AA5;
const unsigned long IR_7 =  0xFF42BD;
const unsigned long IR_8 =  0xFF4AB5;
const unsigned long IR_9 =  0xFF52AD;
const unsigned long IR_REPEAT = 0xFFFFFFFF;

IRrecv irrecv(RECEIVER);     // create instance of 'irrecv'
decode_results results;      // create instance of 'decode_results'
int digit = 0;
bool off = true;
int *sevenSegArray;

// takes action based on IR code received 
char* translateIR() 
{
  switch(results.value)
  {
    case IR_POWER: return "POWER"; 
    case IR_FUNC_STOP : return "FUNC/STOP"; 
    case IR_VOL_UP : return "VOL+"; 
    case IR_FAST_BACK : return "FAST BACK";    
    case IR_PAUSE : return "PAUSE";    
    case IR_FAST_FORWARD : return "FAST FORWARD";   
    case IR_DOWN : return "DOWN";    
    case IR_VOL_DOWN : return "VOL-";    
    case IR_UP : return "UP";    
    case IR_EQ : return "EQ";    
    case IR_ST_REPT : return "ST/REPT";    
    case IR_0 : return "0";    
    case IR_1 : return "1";    
    case IR_2 : return "2";    
    case IR_3 : return "3";    
    case IR_4 : return "4";    
    case IR_5 : return "5";    
    case IR_6 : return "6";    
    case IR_7 : return "7";    
    case IR_8 : return "8";    
    case IR_9 : return "9";    
    case IR_REPEAT : return " REPEAT";  
    default: 
      return " Unknow ";
  }
  delay(500); // Do not get immediate repeat
} 

void executeIRCommand(unsigned long irCommand) 
{
  switch(irCommand)
  {
    case IR_POWER: off = !off; digit = 0; break; 
    case IR_FUNC_STOP : break; 
    case IR_VOL_UP : break; 
    case IR_FAST_BACK : setDigit(0); break;    
    case IR_PAUSE : break;    
    case IR_FAST_FORWARD : setDigit(9); break;   
    case IR_DOWN : lower(); break;    
    case IR_VOL_DOWN : break;    
    case IR_UP : upper(); break;    
    case IR_EQ : break;    
    case IR_ST_REPT :  break;    
    case IR_0 : setDigit(0);  break;    
    case IR_1 : setDigit(1);  break;    
    case IR_2 : setDigit(2);  break;    
    case IR_3 : setDigit(3);  break;    
    case IR_4 : setDigit(4);  break;    
    case IR_5 : setDigit(5);  break;    
    case IR_6 : setDigit(6);  break;    
    case IR_7 : setDigit(7);  break;    
    case IR_8 : setDigit(8);  break;    
    case IR_9 : setDigit(9);  break;    
    case IR_REPEAT : break;  
    default: 
      return " Unknow ";
  }
}

void upper() 
{
  setDigit(digit + 1);
}

void lower() 
{
  setDigit(digit - 1);
}

void setDigit(int d) 
{
  if (off) 
  {
    return;
  }

  if (d > 9) 
  {
    d = 9;
  }

  if (d < 0) {
    d = 0;
  }

  digit = d;
}
void translateDigitTo7seg() 
{
  if (off) 
  {
   sevenSegArray =  SEVEN_SEG_OFF;
   return;
  }

  switch(digit) 
  {
    case 0: sevenSegArray = SEVEN_SEG_0; break;
    case 1: sevenSegArray = SEVEN_SEG_1; break;
    case 2: sevenSegArray = SEVEN_SEG_2; break;
    case 3: sevenSegArray = SEVEN_SEG_3; break;
    case 4: sevenSegArray = SEVEN_SEG_4; break;
    case 5: sevenSegArray = SEVEN_SEG_5; break;
    case 6: sevenSegArray = SEVEN_SEG_6; break;
    case 7: sevenSegArray = SEVEN_SEG_7; break;
    case 8: sevenSegArray = SEVEN_SEG_8; break;
    case 9: sevenSegArray = SEVEN_SEG_9; break;
  }
}

void displaySevenSeg() 
{
  for (int i = 0; i < 7; i++) 
  {
    digitalWrite(3 + i, sevenSegArray[i]);
  }
}

void setup()  
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); // Start the receiver
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
}

void loop()  
{
  if (irrecv.decode(&results)) // have we received an IR signal?
  {
    //char* cmd = translateIR();
    executeIRCommand(results.value);
    translateDigitTo7seg();
    displaySevenSeg();
    if (off) {
      Serial.println("Display is Off"); 
    } else {
      Serial.println(digit);
    }
     
    irrecv.resume(); // receive the next value
    
  }  
}