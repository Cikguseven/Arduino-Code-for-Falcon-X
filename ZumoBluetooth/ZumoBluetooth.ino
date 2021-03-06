/*
  Control of a Polulu Zumo robot via Bluetooth

  For PC-based control, keypresses are used...
  for direction:
  R T Y
  F G H
  V B N

  Bluetooth uses D0 and D1 in the standard comms way, via a VL06 bluetooth module

  By J. P. Caplin 06/16
*/
// Enable program memory then load note names and values into program memory
#include <avr/pgmspace.h>

char blueToothVal;          // value sent over via bluetooth
char lastValue;             // stores last state of device (on/off)
char MLdirpin = 8;   // pin number for left motor direction (LOW/HIGH for forward/reverse)
char MLspdpin = 10;  // pin number for left motor speed (PWM control)
char MRdirpin = 7;   // pin number for right motor direction (LOW/HIGH for forward/reverse)
char MRspdpin = 9;   // pin number for right motor speed (PWM control)
char MLdirval = 0;   // value  for left motor direction (LOW/HIGH for forward/reverse)
char MLspdval = 0;  // value for left motor speed (PWM control)
char MRdirval = 0;   // value for right motor direction (LOW/HIGH for forward/reverse)
char MRspdval = 0;   // value for right motor speed (PWM control)

char speakerPin = 3;        // small loudspeaker for status and feedback

float speedSet = 0.5;       // speed setting multiplier (need to reduce speed of standard 10G motors for easier control)


void setup()
{
  Serial.begin(9600);
  pinMode(MLdirpin, OUTPUT);
  pinMode(MLspdpin, OUTPUT);
  pinMode(MRdirpin, OUTPUT);
  pinMode(MRspdpin, OUTPUT);
  pinMode(13, OUTPUT);
  pinMode(speakerPin, OUTPUT);
  Beeps();  // Sound 3 beeps
  Beeps();
  Beeps();
}


void loop() {
  checkBluetooth();     // Receive command and set motor/music variables accordingly (first time)
  setMotors();          // Set left and right motor speed and direction according to received data
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
  { // forward left
    MLspdval = speedSet * 128; MLdirval = 0;
    MRspdval = speedSet * 255; MRdirval = 0;
    if (lastValue != 'r')
      Serial.println(F("Forward-Left")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 't')
  { // full forward
    MLspdval = speedSet * 255; MLdirval = 0;
    MRspdval = speedSet * 255; MRdirval = 0;
    if (lastValue != 't')
      Serial.println(F("Full-Forward")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'y')
  { // forward right
    MLspdval = speedSet * 255; MLdirval = 0;
    MRspdval = speedSet * 128; MRdirval = 0;
    if (lastValue != 'y')
      Serial.println(F("Forward-Right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'f')
  { // spin left
    MLspdval = speedSet * 128; MLdirval = 1;
    MRspdval = speedSet * 128; MRdirval = 0;
    if (lastValue != 'f')
      Serial.println(F("Spin-Left")); // print setting (flash-memory based string) if newly changed instruction
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
  { // spin right
    MLspdval = speedSet * 128; MLdirval = 0;
    MRspdval = speedSet * 128; MRdirval = 1;
    if (lastValue != 'h')
      Serial.println(F("Spin-Right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'v')
  { // reverse left
    MLspdval = speedSet * 128; MLdirval = 1;
    MRspdval = speedSet * 255; MRdirval = 1;
    if (lastValue != 'v')
      Serial.println(F("Reverse-Left")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'b')
  { // full reverse
    MLspdval = speedSet * 255; MLdirval = 1;
    MRspdval = speedSet * 255; MRdirval = 1;
    if (lastValue != 'b')
      Serial.println(F("Full-Reverse")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'n')
  { // reverse right
    MLspdval = speedSet * 255; MLdirval = 1;
    MRspdval = speedSet * 128; MRdirval = 1;
    if (lastValue != 'n')
      Serial.println(F("Reverse-Right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }
}


void Beeps() {
  for (int i = 0; i <= 50; i++) { // play note C for 50 cycles (about 100 milliseconds)
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
  }
  delay(50);  // space between beeps is 50 milliseconds
}


