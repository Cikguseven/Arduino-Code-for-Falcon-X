/*
  Control of a Polulu Zumo robot via Infra-Red beam from a hand-held torchlight.

  Two infra-red two-pin phototransistors (or photodiodes)are connected as potential dividers with the centre-points connected to analogue inputs A0 and A1.
  An analogue value between 0 and 1023 represents the voltage at the centre-point.  This is used to set the direction and speed of the Zumo robot.

  By J. P. Caplin 06/16
*/

int IR0; // Value for infra-red sensor on A0
int IR1; // Value for infra-red sensor on A1
char MLdirpin = 8;   // pin number for left motor direction (LOW/HIGH for forward/reverse)
char MLspdpin = 10;  // pin number for left motor speed (PWM control)
char MRdirpin = 7;   // pin number for right motor direction (LOW/HIGH for forward/reverse)
char MRspdpin = 9;   // pin number for right motor speed (PWM control)
char MLdirval = 0;   // value  for left motor direction (LOW/HIGH for forward/reverse)
int MLspdval = 0;   // value for left motor speed (PWM control)
char MRdirval = 0;   // value for right motor direction (LOW/HIGH for forward/reverse)
int MRspdval = 0;   // value for right motor speed (PWM control)

char speakerPin = 3;        // small loudspeaker for status and feedback

float speedSet = 0.5;       // speed setting multiplier (need to reduce speed of standard 10G motors for easier control)

#define echoPin 7 // Echo Pin
#define trigPin 8 // Trigger Pin
#define LEDPin 13 // Onboard LED

int maximumRange = 200; // Maximum range needed
int minimumRange = 0; // Minimum range needed
long duration, distance; // Duration used to calculate distance

void setup() {
  // This setup code runs just once:

  for (int i = 7; i <= 10; i++) { // set all the digital pins to output
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);  // enable communication to connected PC via USB
  pinMode(trigPin, OUTPUT);
  pinMode(echoPin, INPUT);
  pinMode(LEDPin, OUTPUT); // Use LED indicator (if required)


digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(2016);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 0);//First right turn
digitalWrite(MRdirpin, 1);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1470);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(2000);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 1);//First left turn
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1250);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(1950);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 1);//Second left turn
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1450);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(2050);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 1);//Third left turn
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1480);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(1950);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 1);//Fourth left turn
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1450);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(1900);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);


digitalWrite(MLdirpin, 0);//Second right turn
digitalWrite(MRdirpin, 1);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1450);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(1900);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(100);

digitalWrite(MLdirpin, 0);//Second right turn
digitalWrite(MRdirpin, 1);
analogWrite(MLspdpin, 64);
analogWrite(MRspdpin, 64);
delay(1450);

digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 128);
analogWrite(MRspdpin, 128);
delay(1900);





digitalWrite(MLdirpin, 0);
digitalWrite(MRdirpin, 0);
analogWrite(MLspdpin, 0);
analogWrite(MRspdpin, 0);
delay(1000);
}


void loop() {
 digitalWrite(trigPin, LOW); 
 delayMicroseconds(2); 

 digitalWrite(trigPin, HIGH);
 delayMicroseconds(10); 
 
 digitalWrite(trigPin, LOW);
 duration = pulseIn(echoPin, HIGH);
 
 //Calculate the distance (in cm) based on the speed of sound.
 distance = duration/58.2;
 
 if (distance >= maximumRange || distance <= minimumRange){
 /* Send a negative number to computer and Turn LED ON 
 to indicate "out of range" */
 Serial.println("-1");
 digitalWrite(LEDPin, HIGH); 
 }
 else {
 /* Send the distance to the computer using Serial protocol, and
 turn LED OFF to indicate successful reading. */
 Serial.println(distance);
 digitalWrite(LEDPin, LOW); 
 }
 
 //Delay 50ms before next reading.
 delay(50);
}
