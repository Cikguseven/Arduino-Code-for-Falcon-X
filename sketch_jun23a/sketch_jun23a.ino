/* 
  Code for Falcon X Draft 1
  By Kieron
*/



char MLdirpin = 8;   // pin number for left motor direction (LOW/HIGH for forward/reverse)
char MLspdpin = 10;  // pin number for left motor speed (PWM control)
char MRdirpin = 7;   // pin number for right motor direction (LOW/HIGH for forward/reverse)
char MRspdpin = 9;   // pin number for right motor speed (PWM control)
char MLdirval = 0;   // value  for left motor direction (LOW/HIGH for forward/reverse)
int MLspdval = 0;   // value for left motor speed (PWM control)
char MRdirval = 0;   // value for right motor direction (LOW/HIGH for forward/reverse)
int MRspdval = 0;   // value for right motor speed (PWM control)

#define trigPin 4 // Trigger Pin
#define echoPin 5 // Echo Pin

float speedSet = 0.5;       // speed setting multiplier (need to reduce speed of standard 10G motors for easier control)

// Beep Settings
char speakerPin = 3;        // small loudspeaker for status and feedback

// UltraSound Settings
int maximumRange = 35; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {

  for (int i = 7; i <= 10; i++) { // set all the digital pins to output
    pinMode(i, OUTPUT);
  }
  Serial.begin (9600);
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  Beeps();
}

void loop() {

  TrigEchoCycle();  // Run trigPin/echoPin cycle  to determine the distance of the nearest object by bouncing soundwaves off of it
  setMotors();  //  Set left and right motor speed and direction
  checkUltraSound();  // Use UltraSound to determine direction of movement
  delay(10);  // Delay update limit to 100ms
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
    digitalWrite(MLdirpin, 0);//First right turn
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
    analogWrite(MLspdpin, 150);
    analogWrite(MRspdpin, 150);
  }

  //Delay 50ms before next reading.
  delay(20);
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

