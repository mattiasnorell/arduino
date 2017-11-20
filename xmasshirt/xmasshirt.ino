const int numberOfLights = 4;                         // Total number of leds
int loopSpeed = 1000;                                 // Loop speed in milliseconds
int sequenceIndex = 0;                                // Current sequence index
int sequencerData[1][numberOfLights] = {0, 1, 0, 0};  // Led sequencer script

void setup() {

}

void loop() {
  sequencer();
  delay(loopSpeed);
}

void changeSequence() {
  sequenceIndex++;

  if (sequenceIndex >= numberOfLights) {
    sequenceIndex = 0;
  }
}

void sequencer() {

  Serial.println(sizeof(sequencerData[sequenceIndex]));

  for (int i = 0; i < sizeof(sequencerData[sequenceIndex]); i++) {
    for (int ii = 0; ii < sizeof(sequencerData[sequenceIndex]); ii++) {
      Serial.println("Sequence");
      Serial.println(ii);
    }
  }

}
