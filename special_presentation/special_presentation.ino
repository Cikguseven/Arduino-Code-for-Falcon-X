/* Code for presentation
   By Kieron 24/06

*/

#include <avr/pgmspace.h>

char blueToothVal;      // value sent over via bluetooth
char lastValue;         // stores last state of device (on/off)
char MLdirpin = 8;   // pin number for left motor direction (LOW/HIGH for forward/reverse)
char MLspdpin = 10;  // pin number for left motor speed (PWM control)
char MRdirpin = 7;   // pin number for right motor direction (LOW/HIGH for forward/reverse)
char MRspdpin = 9;   // pin number for right motor speed (PWM control)
char MLdirval = 0;   // value  for left motor direction (LOW/HIGH for forward/reverse)
char MLspdval = 0;   // value for left motor speed (PWM control)
char MRdirval = 0;   // value for right motor direction (LOW/HIGH for forward/reverse)
char MRspdval = 0;   // value for right motor speed (PWM control)

#define redLED 11
#define greenLED 12

#define trigPin 4 // Trigger Pin
#define echoPin 5 // Echo Pin

char speakerPin = 3;        // small loudspeaker for status and feedback

float speedSet = 0.5;       // speed setting multiplier (need to reduce speed of standard 10G motors for easier control)

// UltraSound Settings
int maximumRange = 30; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);
  pinMode(MLdirpin, OUTPUT);
  pinMode(MLspdpin, OUTPUT);
  pinMode(MRdirpin, OUTPUT);
  pinMode(MRspdpin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(speakerPin, OUTPUT);
  pinMode(redLED, OUTPUT);
  pinMode(greenLED, OUTPUT);
  Beeps();
}

void loop() {
  // put your main code here, to run repeatedly:
  checkBluetooth();     // Receive command and set motor/music variables accordingly (first time)
  // checkUltraSound();
  setMotors();          // Set left and right motor speed and direction according to received data
}


void TrigEchoCycle() {
  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);
  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);
  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
  distance = duration / 58.2;
}


void turnRight() {
  TrigEchoCycle();
  
  if (distance <= maximumRange) {
    Serial.println(distance);
    Beeps();
    Beeps();
    digitalWrite(MLdirpin, 0);//First right turn
    digitalWrite(MRdirpin, 1);
    analogWrite(MLspdpin, 128);
    analogWrite(MRspdpin, 128);
    delay(200);
  }
  else {
    Serial.println(distance);
    digitalWrite(MLdirpin, 0);
    digitalWrite(MRdirpin, 0);
    analogWrite(MLspdpin, 200);
    analogWrite(MRspdpin, 200);
  }
  //Delay 20ms before next reading.
  delay(10);
}

void turnLeft() {
  TrigEchoCycle();
  if (distance <= maximumRange) {
    Serial.println(distance);
    Beeps();
    Beeps();
    digitalWrite(MLdirpin, 1);//First right turn
    digitalWrite(MRdirpin, 0);
    analogWrite(MLspdpin, 128);
    analogWrite(MRspdpin, 128);
    delay(200);
  }
  else {
    Serial.println(distance);
    digitalWrite(MLdirpin, 0);
    digitalWrite(MRdirpin, 0);
    analogWrite(MLspdpin, 200);
    analogWrite(MRspdpin, 200);
  }
  //Delay 10ms before next reading.
  delay(10);
}


void setMotors() {
  digitalWrite(MLdirpin, MLdirval);
  digitalWrite(MRdirpin, MRdirval);
  analogWrite(MLspdpin, MLspdval);
  analogWrite(MRspdpin, MRspdval);
}


void checkBluetooth() {
  if (Serial.available())
  { //if there is data being received
    blueToothVal = Serial.read(); //read it
  }
  else
  {
    //    blueToothVal = 103;   // default is "g" press for STOP
  }


  if (blueToothVal == 'r')
  { // autonomous left
    turnLeft();
    //    digitalWrite(redLED, HIGH);
    //    delay(50);
    //    digitalWrite(redLED, LOW);
    if (lastValue != 'r')
      Serial.println(F("Switched to autonomous left movement")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 't')
  { // slower speed
    MLspdval = 155; MLdirval = 0;
    MRspdval = 155; MRdirval = 0;
    if (lastValue != 't')
      Serial.println(F("Full Forward")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'y')
  { // autonomous right
    turnRight();
    //    digitalWrite(greenLED, HIGH);
    //    delay(50);
    //    digitalWrite(greenLED, LOW);
    if (lastValue != 'y')
      Serial.println(F("Switched to autonomous right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'f')
  { // slower speed
    MLspdval = 120; MLdirval = 0;
    MRspdval = 120; MRdirval = 0;
    if (lastValue != 'f')
      Serial.println(F("Speed adjusted to 0.3")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'g')
  { // stop
    MLspdval = 0; MLdirval = 0;
    MRspdval = 0; MRdirval = 0;
    if (lastValue != 'g')
      Serial.println(F("STOP")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'h')
  { // faster speed
    MLspdval = 190; MLdirval = 0;
    MRspdval = 190; MRdirval = 0;
    //    digitalWrite(greenLED, HIGH);
    //    delay(50);
    //    digitalWrite(greenLED, LOW);
    if (lastValue != 'h')
      Serial.println(F("Speed adjusted to 0.7")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'c')
  { // Blink red LED
    //    MLspdval = speedSet * 128; MLdirval = 1;
    //    MRspdval = speedSet * 255; MRdirval = 1;
    digitalWrite(redLED, HIGH);
    delay(50);
    digitalWrite(redLED, LOW);
    if (lastValue != 'c')
      Serial.println(F("Blink red LED")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  // if (blueToothVal == 'v')
  //  { // Beep once
  //    Beeps();
  //    MLspdval = speedSet * 200; MLdirval = 1;
  //    MRspdval = speedSet * 200; MRdirval = 1;
  //
  //    checkUltraSound();
  //    if (lastValue != 'v')
  //      Serial.println(F("Beep")); // print setting (flash-memory based string) if newly changed instruction
  //    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
  //    }
  //    lastValue = blueToothVal;
  //  }

  if (blueToothVal == 'b')
  { // Blink green LED
    //    MLspdval = speedSet * 255; MLdirval = 1;
    //    MRspdval = speedSet * 128; MRdirval = 1;
    digitalWrite(greenLED, HIGH);
    delay(100);
    digitalWrite(greenLED, LOW);
    if (lastValue != 'b')
      Serial.println(F("Blink green LED")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }
}


void Beeps() {
  //for (int i = 0; i <= 50; i++) { // play note C for 50 cycles (about 100 milliseconds)
  { digitalWrite(speakerPin, HIGH);
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
  }
  delay(50);  // space between beeps is 50 milliseconds
}



