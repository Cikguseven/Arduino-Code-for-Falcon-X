// Twinkle Twinkle Little Star Test 1

char speakerPin = 3;        // small loudspeaker for status and feedback

void setup() {
  // put your setup code here, to run once:
  Serial.begin(9600);  // enable communication to connected PC via USB
  Beeps(); 
}

void loop() {
  // put your main code here, to run repeatedly:

}

void Beeps() {
  for (int i = 0; i <= 70; i++) { // play note C for 50 cycles (about 100 milliseconds)
    // Notes of song: C C G G A A G | F F E E D D C
    digitalWrite(speakerPin, HIGH);  // C
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
    
    digitalWrite(speakerPin, HIGH);  // C
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
    
    digitalWrite(speakerPin, HIGH);  // G
    delayMicroseconds(638);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(638);

    digitalWrite(speakerPin, HIGH);  // G
    delayMicroseconds(638);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(638);

    digitalWrite(speakerPin, HIGH);  // A
    delayMicroseconds(568);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(568);

    digitalWrite(speakerPin, HIGH);  // A
    delayMicroseconds(568);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(568);

    digitalWrite(speakerPin, HIGH);  // G
    delayMicroseconds(638);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(638);

    delay(175);

    digitalWrite(speakerPin, HIGH);  // F
    delayMicroseconds(716);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(716);

    digitalWrite(speakerPin, HIGH);  // F
    delayMicroseconds(716);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(716);

    digitalWrite(speakerPin, HIGH);  // E
    delayMicroseconds(758);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(758);

    digitalWrite(speakerPin, HIGH);  // E
    delayMicroseconds(758);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(758);

    digitalWrite(speakerPin, HIGH);  // D
    delayMicroseconds(851);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(851);

    digitalWrite(speakerPin, HIGH);  // D
    delayMicroseconds(851);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(851);

    digitalWrite(speakerPin, HIGH);  // C
    delayMicroseconds(955);
    digitalWrite(speakerPin, LOW);
    delayMicroseconds(955);
  }
  delay(50);  // space between beeps is 50 milliseconds
}

