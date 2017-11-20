const int SPEED_BUTTON_PIN = 1;
const int PATTERN_BUTTON_PIN = 2;
const int LED_PINS[4] = {3, 4, 5, 6};

int speedIndex = 0;
int sequencerSpeed[3] = {500, 1000, 2000};
int sequenceIndex = 0;                                // Current sequence index
int sequencerData[4][4][4] =                          // Max 4 different patterns per sequence
{
  {
    {1, 0, 0, 0},
    {0, 1, 0, 0},
    {0, 0, 1, 0},
    {0, 0, 0, 1}
  }, {
    {0, 1, 0, 1},
    {1, 0, 1, 0},
    {0, 1, 0, 1},
    {1, 0, 1, 0}
  }, {
    {1, 0, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 0, 1},
    {0, 1, 1, 0}
  }, {
    {1, 1, 0, 1},
    {0, 1, 1, 0},
    {1, 0, 1, 1},
    {1, 1, 0, 1}
  }
};

void setup() {
  for (int i = 0; i < 4; i++) {
    pinMode(LED_PINS[i], OUTPUT);
  }

  pinMode(PATTERN_BUTTON_PIN, INPUT);
  pinMode(SPEED_BUTTON_PIN, INPUT);
}

void loop() {
  sequencer();
  
  delay(sequencerSpeed[speedIndex]);
}

void changeSpeed() {
  speedIndex++;

  if (speedIndex >= sizeof(sequencerSpeed)) {
    speedIndex = 0;
  }
}

void changeSequence() {
  sequenceIndex++;

  if (sequenceIndex >= sizeof(sequencerData)) {
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
