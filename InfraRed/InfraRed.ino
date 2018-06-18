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

void setup() {
  // This setup code runs just once:

  for (int i = 7; i <= 10; i++) { // set all the digital pins to output
    pinMode(i, OUTPUT);
  }
  Serial.begin(9600);  // enable communication to connected PC via USB
  //  Beeps();  // Sound 2 beeps
  //  Beeps();

  //  digitalWrite(MLdirpin, 0);
  //  digitalWrite(MRdirpin, 0);
  //  analogWrite(MLspdpin, 128);
  //  analogWrite(MRspdpin, 80);
  //  delay(800);
  //
  //  digitalWrite(MLdirpin, 0);
  //  digitalWrite(MRdirpin, 0);
  //  analogWrite(MLspdpin, 50);
  //  analogWrite(MRspdpin, 128);
  //  delay(6000);



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
  delay(1450);

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

  digitalWrite(MLdirpin, 1);//First left turn
  digitalWrite(MRdirpin, 0);
  analogWrite(MLspdpin, 64);
  analogWrite(MRspdpin, 64);
  delay(1300);

  digitalWrite(MLdirpin, 0);
  digitalWrite(MRdirpin, 0);
  analogWrite(MLspdpin, 128);
  analogWrite(MRspdpin, 128);
  delay(1850);

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
  delay(1900);

  digitalWrite(MLdirpin, 0);
  digitalWrite(MRdirpin, 0);
  analogWrite(MLspdpin, 0);
  analogWrite(MRspdpin, 0);
  delay(100);

  digitalWrite(MLdirpin, 1);//Third left turn
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
  analogWrite(MLspdpin, 0);
  analogWrite(MRspdpin, 0);
  delay(1000);


}


void loop() {
  // this main code runs repeatedly...
  // checkInfraRed();  // Measure the IR incident on each infra-red sensor then determine motor speeds
  //  setMotors();  //  Set left and right motor speed and direction
  //  delay(100);  // Delay to limit to 10 updates per second


  // void checkInfraRed() {
  IR0 = analogRead(0);  // find infra-red level incident on left IR sensor (lower value shows more IR is incident)
  IR1 = analogRead(1); // find infra-red level incident on right IR sensor (lower value shows more IR is incident)
  if (IR0 > 800) IR0 = 1023;  // In low-light condition, ensure motor is stopped
  if (IR1 > 800) IR1 = 1023;  // In low-light condition, ensure motor is stopped
  MLspdval = speedSet * (255 - IR0 / 4); // set motor speeds according to intensity of IR
  MRspdval = speedSet * (255 - IR1 / 4);
  Serial.print("L spd:"); // Send left and right speed values to PC
  Serial.print(MLspdval);
  Serial.print("   ");
  Serial.print("R spd:");
  Serial.println(MRspdval);
  //  Serial.print("L spd:"); // Send left and right speed values to PC
  //  Serial.print(IR0);
  //  Serial.print("   ");
  //  Serial.print("R spd:");
  //  Serial.println(IR1);
}

// void setMotors() {
//digitalWrite(MLdirpin, MLdirval);
//digitalWrite(MRdirpin, MRdirval);
//analogWrite(MLspdpin, MLspdval);
//analogWrite(MRspdpin, MRspdval);


// void Beeps() {
//  for (int i = 0; i <= 50; i++) { // play note C for 50 cycles (about 100 milliseconds)
//   digitalWrite(speakerPin, HIGH);
//   delayMicroseconds(955);
//   digitalWrite(speakerPin, LOW);
//  delayMicroseconds(955);

//  delay(50);  // space between beeps is 50 milliseconds


