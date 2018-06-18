/*
  Code for Falcon X - Draft 2

  Status:
  Semi-autonomous Zumo robot with autonomous movement via Ultrasound and control via Bluetooth

  Last Edit: 22/6 21:50

  By Kieron
*/
#include <avr/pgmspace.h>

char blueToothVal;   // value sent over via bluetooth
char lastValue;      // stores last state of device (on/off)
char MLdirpin = 8;   // pin number for left motor direction (LOW/HIGH for forward/reverse)
char MLspdpin = 10;  // pin number for left motor speed (PWM control)
char MRdirpin = 7;   // pin number for right motor direction (LOW/HIGH for forward/reverse)
char MRspdpin = 9;   // pin number for right motor speed (PWM control)
char MLdirval = 0;   // value  for left motor direction (LOW/HIGH for forward/reverse)
int MLspdval = 0;    // value for left motor speed (PWM control)
char MRdirval = 0;   // value for right motor direction (LOW/HIGH for forward/reverse)
int MRspdval = 0;    // value for right motor speed (PWM control)

#define trigPin 4    // Trigger Pin
#define echoPin 5    // Echo Pin
// #define LEDPin 13    // Onboard LED

// Beep Settings
char speakerPin = 3;        // small loudspeaker for status and feedback

// Speed Settings
float speedSet = 0.5;       // speed setting multiplier (need to reduce speed of standard 10G motors for easier control)

// Ultrasound Settings
int maximumRange = 30; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {

  for (int i = 7; i <= 10; i++) { // set all the digital pins to output
    pinMode(i, OUTPUT);
  }
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  // pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)
  pinMode(speakerPin, OUTPUT);
  Beeps();  // Sound 4 beeps
  Beeps();
  Beeps();
  Beeps();
}

void loop() {

  TrigEchoCycle();    // Run trigPin/echoPin cycle to determine the distance of the nearest object by bouncing soundwaves off of it
  checkUltraSound();  // Use UltraSound to determine direction of movement
  checkBluetooth();   // Receive command and set motor/music variables accordingly (first time)
  setMotors();        // Set left and right motor speed and direction
  delay(50);          // Delay update limit to 50ms
}

void TrigEchoCycle() {

  digitalWrite(trigPin, LOW);
  delayMicroseconds(2);

  digitalWrite(trigPin, HIGH);
  delayMicroseconds(10);

  digitalWrite(trigPin, LOW);
  duration = pulseIn(echoPin, HIGH);
}

void setMotors() {

  digitalWrite(MLdirpin, MLdirval);
  digitalWrite(MRdirpin, MRdirval);
  analogWrite(MLspdpin, MLspdval);
  analogWrite(MRspdpin, MRspdval);
}

void checkUltraSound() {
  distance = duration / 58.2;

  if (distance <= maximumRange) {
    /* Send a negative number to computer and Turn LED ON
      to indicate "out of range" */
    Serial.println(distance);
    // digitalWrite(LEDPin, HIGH);
    Beeps();
    // 45 degree right turn
    digitalWrite(MLdirpin, 0);
    digitalWrite(MRdirpin, 1);
    analogWrite(MLspdpin, 128);
    analogWrite(MRspdpin, 128);
    delay(250);


  }
  else {
    /* Send the distance to the computer using Serial protocol, and
      turn LED OFF to indicate successful reading. */
    Serial.println(distance);
    // digitalWrite(LEDPin, LOW);
    digitalWrite(MLdirpin, 0);
    digitalWrite(MRdirpin, 0);
    analogWrite(MLspdpin, 160);
    analogWrite(MRspdpin, 160);

  }

  //Delay 10ms before next reading.
  delay(10);
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
    MLspdval = speedSet * 200; MLdirval = 1;
    MRspdval = speedSet * 200; MRdirval = 0;
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
    MLspdval = speedSet * 200; MLdirval = 0;
    MRspdval = speedSet * 200; MRdirval = 1;
    if (lastValue != 'h')
      Serial.println(F("Spin-Right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'c')
  { // reverse left
    MLspdval = speedSet * 128; MLdirval = 1;
    MRspdval = speedSet * 255; MRdirval = 1;
    if (lastValue != 'c')
      Serial.println(F("Reverse-Left")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'v')
  { // full reverse
    MLspdval = speedSet * 255; MLdirval = 1;
    MRspdval = speedSet * 255; MRdirval = 1;
    if (lastValue != 'v')
      Serial.println(F("Full-Reverse")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }

  if (blueToothVal == 'b')
  { // reverse right
    MLspdval = speedSet * 255; MLdirval = 1;
    MRspdval = speedSet * 128; MRdirval = 1;
    if (lastValue != 'b')
      Serial.println(F("Reverse-Right")); // print setting (flash-memory based string) if newly changed instruction
    if (!(lastValue == blueToothVal)) {   // Only play chord if new bluetooth command received
    }
    lastValue = blueToothVal;
  }
}

void Beeps() {
  for (int i = 0; i <= 100; i++) { // play note C for 100 cycles (about 200 milliseconds)
    digitalWrite(speakerPin, HIGH);
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
  }
  delay(50);
}

