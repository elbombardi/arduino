//www.elegoo.com
//2016.12.9

#include "IRremote.h"

const int IR_RECEIVER_PIN = 11; // Signal Pin of IR receiver to Arduino Digital Pin 11
const int BUZZER_PIN = 2;
const int CLOSED_GATE_PIN = 12;
const int OPEN_GATE_PIN = 10;

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

const char* SECRET_CODE = "8421";

IRrecv irrecv(IR_RECEIVER_PIN);   
decode_results results;     
char digit = 0;
int *sevenSegArray;
bool open = false;
char* code = "";

void executeIRCommand(unsigned long irCommand) 
{
  switch(irCommand)
  {
    case IR_POWER: openOrCloseGate(); break; 
    case IR_FUNC_STOP : break; 
    case IR_VOL_UP : break; 
    case IR_FAST_BACK : break;    
    case IR_PAUSE : break;    
    case IR_FAST_FORWARD : break;   
    case IR_DOWN :  break;    
    case IR_VOL_DOWN : break;    
    case IR_UP :  break;    
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
  }
}

void setDigit(char d) 
{
  if (!open) 
  {
    digit = d;
    strcat(code, d);
    //Serial.println(code);
  }
  translateDigitTo7seg();
}

void openOrCloseGate()
{
  open = !open;
  code = "";
}

void translateDigitTo7seg() 
{
  if (open) 
  {
   sevenSegArray =  SEVEN_SEG_OFF;
   return;
  }

  switch(digit) 
  {
    case '0': sevenSegArray = SEVEN_SEG_0; break;
    case '1': sevenSegArray = SEVEN_SEG_1; break;
    case '2': sevenSegArray = SEVEN_SEG_2; break;
    case '3': sevenSegArray = SEVEN_SEG_3; break;
    case '4': sevenSegArray = SEVEN_SEG_4; break;
    case '5': sevenSegArray = SEVEN_SEG_5; break;
    case '6': sevenSegArray = SEVEN_SEG_6; break;
    case '7': sevenSegArray = SEVEN_SEG_7; break;
    case '8': sevenSegArray = SEVEN_SEG_8; break;
    case '9': sevenSegArray = SEVEN_SEG_9; break;
  }

  for (int i = 0; i < 7; i++) 
  {
    digitalWrite(3 + i, sevenSegArray[i]);
  }
}

void setup()  
{
  Serial.begin(9600);
  Serial.println("IR Receiver Button Decode"); 
  irrecv.enableIRIn(); 
  pinMode(2, OUTPUT);
  pinMode(3, OUTPUT);
  pinMode(4, OUTPUT);
  pinMode(5, OUTPUT);
  pinMode(6, OUTPUT);
  pinMode(7, OUTPUT);
  pinMode(8, OUTPUT);
  pinMode(9, OUTPUT);
  pinMode(12, OUTPUT);
  pinMode(13, OUTPUT);
  digitalWrite(OPEN_GATE_PIN, LOW);
  digitalWrite(CLOSED_GATE_PIN, HIGH);
}

void loop()  
{
  if (irrecv.decode(&results))
  {
    executeIRCommand(results.value);
    if (open) 
    {
      Serial.println("Gate is open"); 
      digitalWrite(OPEN_GATE_PIN, HIGH);
      digitalWrite(CLOSED_GATE_PIN, LOW);
    } 
    else 
    {
      Serial.println("Gate is closed");
      digitalWrite(CLOSED_GATE_PIN, HIGH);
      digitalWrite(OPEN_GATE_PIN, LOW);
    }
    irrecv.resume();
  }  
}