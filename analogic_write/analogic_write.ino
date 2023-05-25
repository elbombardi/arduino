/*
  Blink

  Turns an LED on for one second, then off for one second, repeatedly.

  Most Arduinos have an on-board LED you can control. On the UNO, MEGA and ZERO
  it is attached to digital pin 13, on MKR1000 on pin 6. LED_BUILTIN is set to
  the correct LED pin independent of which board is used.
  If you want to know what pin the on-board LED is connected to on your Arduino
  model, check the Technical Specs of your board at:
  https://www.arduino.cc/en/Main/Products

  modified 8 May 2014
  by Scott Fitzgerald
  modified 2 Sep 2016
  by Arturo Guadalupi
  modified 8 Sep 2016
  by Colby Newman

  This example code is in the public domain.

  https://www.arduino.cc/en/Tutorial/BuiltInExamples/Blink
*/

int red;
int green;
int blue;

// the setup function runs once when you press reset or power the board
void setup() {
  Serial.begin(9600);
  // initialize digital pin LED_BUILTIN as an output.
  pinMode(9, OUTPUT);
  pinMode(10, OUTPUT);
  pinMode(11, OUTPUT);
  
  red = random(255);
  green = random(255);
  blue=random(255);
  
}

// ther loop function runs over and over again forever
void loop() {

  int r = random(3);
  int g = random(3);
  int b = random(3);

  red += (1 - r) * 5; 
  green += (1- g) * 5 ;
  blue += (1- b) * 5;   
  analogWrite(9, red);//ED on (HIGH is the voltage level)
  analogWrite(10, green);//ED on (HIGH is the voltage level)
  analogWrite(11, blue);//ED on (HIGH is the voltage level)
  Serial.println(red);
  // delay(2);                      // wait for a second
  //digitalWrite(10, HIGH);   // turn the LED off by making the voltage LOW
  //delay(3000);
  // if (red == 256) {
  //   raising = false;
  // }
  // if (red == 0) {
  //   raising =true;
  // }
  // if (raising) {
  //   red++;// wait for a second
  // } else {
  //   red--;
  // }
  
}
